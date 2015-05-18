#include "qrpgfiledao.h"

#include <assert.h>
#include <QDebug>
#include <QFile>
#include <QTextStream>
#include "../model/qrpgproject.h"
#include "../model/qrpgsprite.h"
#include "../model/qrpgtile.h"
#include "../model/qrpgmap.h"

namespace QRPGDao {
namespace Impl {

const QString QRPGFileDao::relProjectFile = "project.qrpg";

QRPGFileDao::QRPGFileDao()
{

}

void QRPGFileDao::importMaps(QRPGProject *project, const QString &mapsFolderURI, const QString &mapsFileURI)
{
    // TODO: mapsfolder + / for sure!
    // get all maps
    QFile mapsFile(mapsFileURI);
    if (mapsFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream mapsIn(&mapsFile);
        while (!mapsIn.atEnd()) {
            QString mapsLine = mapsIn.readLine();
            mapsLine = mapsLine.trimmed();
            if (!mapsLine.isEmpty() && !mapsLine.startsWith('#')) {
                QStringList mapargs = mapsLine.split(";");
                if (mapargs.length() == 3) {
                    int mapID = mapargs.at(0).toInt();
                    QString mapTitle = mapargs.at(1);
                    QString mapFileURI = mapargs.at(2);

                    // TODO: in aparte methode??
                    int width = 0;
                    int height = 0;

                    QVector<QVector<QVector<QRPGTile *> > > tiles;
                    tiles.resize(3); // 3 layers (for now)

                    //    QString mapFileURI;
                    QFile mapFile(mapsFolderURI + mapFileURI);
                    if (mapFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
                        QTextStream in(&mapFile);
                        while (!in.atEnd()) {
                            QString line = in.readLine();
                            line = line.trimmed();
                            if (!line.isEmpty() && !line.startsWith('#')) {
                                QStringList lineargs = line.split(";");
                                if (lineargs.length() == 4) {
                                    int layer = lineargs.at(0).toInt();
                                    int x = lineargs.at(1).toInt();
                                    int y = lineargs.at(2).toInt();
                                    if (x+1 > width) {
                                        width = x+1;
                                        for (int l=0; l<tiles.size(); l++) {
                                            tiles[l].resize(width);
                                            for (int w=width-1; w>tiles[l][w].size(); w--) {
                                                tiles[l][w].resize(height);
                                            }
                                        }
                                    }
                                    if (y+1 > height) {
                                        height = y+1;
                                        for (int l=0; l<tiles.size(); l++) {
                                            for (int w=0; w<tiles[l].size(); w++) {
                                                tiles[l][w].resize(height);
                                            }
                                        }
                                    }
                                    int tileID = lineargs.at(3).toInt();
                                    qDebug() << "layer " << layer << ": (" << x << "," << y << ") = " << tileID;
//                                    qDebug() << "tiles.size" << tiles.size();
//                                    qDebug() << "tiles[layer].size" << tiles[layer].size();
//                                    qDebug() << "tiles[layer][x].size" << tiles[layer][x].size();
//                                    qDebug() << "project->tiles().size" << project->tiles().size();
                                    tiles[layer][x][y] = project->tiles().value(tileID);
                                }
                            }
                        }
                        mapFile.close();
                    }
                    QRPGMap *newMap = new QRPGMap(project, mapID, mapTitle, width, height);
                    for (int l=0; l<tiles.size(); l++) {
                        for (int x=0; x<tiles[l].size(); x++) {
                            for (int y=0; y<tiles[l][x].size(); y++) {
                                newMap->setTile(l, x, y, tiles[l][x][y]);
                            }
                        }
                    }
                    project->addNewMap(newMap);
                }
            }
        }
        mapsFile.close();
    }
}

void QRPGFileDao::importTiles(QRPGProject *project, const QString &tilesFolderURI, const QString &tilesFileURI)
{
//    QDir tilesFolder(tilesFolderURI);
    QFile tilesFile(tilesFileURI);
    if (tilesFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&tilesFile);
        while (!in.atEnd()) {
            QString line = in.readLine();
            line = line.trimmed();
            if (!line.isEmpty() && !line.startsWith('#')) {
                QStringList lineargs = line.split(";");
                if (lineargs.length() >= 5) {
                    qDebug() << "#lineargs:" << lineargs.length();
                    int id = lineargs.at(0).toInt();
                    QString name = lineargs.at(1);
                    QString file = lineargs.at(2);
                    QPixmap spritesheet(tilesFolderURI + file);
                    QRPGDao::QRPGSprite *sprite = new QRPGDao::QRPGSprite(id);
                    int i = 4;
                    while (i < lineargs.length()) {
                        int x = lineargs.at(i - 1).toInt();
                        int y = lineargs.at(i - 0).toInt();
                        QPixmap spriteframe = spritesheet.copy(x, y, 8, 8);
                        sprite->addSpriteFrame(spriteframe);
                        qDebug() << "creating spriteframe " << id << ": " << name << "(" << file << ": (" << x << "," << y << "))";
                        qDebug() << spriteframe;
                        i += 2;
                    }
                    if (i == lineargs.length()) {
                        sprite->setFps(lineargs.at(i - 1).toDouble());
                    } else if (sprite->spriteFrames().size() > 1) {
                        sprite->setFps(1);
                    }

//                    int x = lineargs.at(3).toInt();
//                    int y = lineargs.at(4).toInt();
//                    sprites.insert(id, sprite);
                    project->addNewSprite(sprite);
                    QRPGTile *newTile = new QRPGTile(id, name, sprite);
                    project->addNewTile(newTile);
                }
            }
        }
        tilesFile.close();
    }
}

void QRPGFileDao::initProjectFromFile(QRPGProject *project)
{
    qDebug() << "init project from project file";
    if (project != NULL) {
        QString projDirURI = project->getProjectFolderURI();
        if (!projDirURI.endsWith('/')) {
            projDirURI.append("/");
        }
        //        QDir projectDir(projDirURI);
        QFile projectFile(projDirURI + relProjectFile);
        qDebug() << projectFile.fileName();
        // reading project file
        if (projectFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            QString tilesFolderURI;
            QString tilesFileURI;
            QString mapsFolderURI;
            QString mapsFileURI;
            QTextStream io(&projectFile);
            while (!io.atEnd()) {
                QString line = io.readLine();
                if (!line.isEmpty() && !line.startsWith('#')) {
                    qDebug() << line;
                    QStringList lineargs = line.split(";");
                    if (lineargs.length() > 0) {
                        if (lineargs.at(0).compare("tilesize") == 0) {
                            setProjectTileSize(project, lineargs.at(1).toInt());
                        } else if (lineargs.at(0).compare("tilesfolder") == 0) {
                            tilesFolderURI = projDirURI + lineargs.at(1);
                        } else if (lineargs.at(0).compare("tilesfile") == 0) {
                            tilesFileURI = tilesFolderURI + lineargs.at(1);
                        } else if (lineargs.at(0).compare("mapsfolder") == 0) {
                            mapsFolderURI = projDirURI + lineargs.at(1);
                        } else if (lineargs.at(0).compare("mapsfile") == 0) {
                            mapsFileURI = mapsFolderURI + lineargs.at(1);
                        }
                    }
                }
            }
            qDebug() << "project file:" << projectFile.fileName();
            qDebug() << "tile size:" << project->tileSize();
            qDebug() << "tiles folder:" << tilesFolderURI;
            qDebug() << "tiles file:" << tilesFileURI;
            qDebug() << "maps folder:" << mapsFolderURI;
            qDebug() << "maps file:" << mapsFileURI;
            // import sprites & tiles
            // TODO
            importTiles(project, tilesFolderURI, tilesFileURI);

            // import maps
            // TODO
            importMaps(project, mapsFolderURI, mapsFileURI);

            projectFile.close();
        } else {
            qDebug() << "Failed to open project file!";
        }
    }
}

QRPGFileDao::~QRPGFileDao()
{
    //    foreach (QRPGDao::QRPGProject *proj, openProjects.values()) {
    //        delete proj;
    //    }
    //    openProjects.clear();
}

QRPGProject *QRPGFileDao::createNewProject(const QDir &projectLocationDir, const QString &projectTitle, const QString &gameTitle)
{
    // TODO: error handling??

    //    QDir projectLocationDir(projectDirLocation); // The directory the project directory will be in
    if (projectLocationDir.exists()) {
        if (projectLocationDir.mkdir(projectTitle)) {
            QDir projectDir(projectLocationDir);
            assert(projectDir.cd(projectTitle));
            qDebug() << "Project directory: " << projectDir.absolutePath();

            // Create project file
            QFile projectFile(projectDir.absolutePath().append(QDir::separator()).append(projectTitle).append(".qrpg"));
            projectFile.open(QIODevice::ReadWrite);
            //            projectFile.write("test");
            projectFile.close();

            // Creating subdirectories
            projectDir.mkdir("Maps");
            // Done creating subdirectories

            QString projectFolderURI = projectDir.absolutePath();
            QRPGProject *proj = this->newProject(projectFolderURI, projectTitle, gameTitle);
            openProjects.insert(projectFolderURI, proj);
            return proj;
        } else {
            qWarning() << "Failed to create project dir: " << projectLocationDir.absolutePath();
            return NULL;
        }
    } else {
        qWarning() << "The directory you're trying to create the project in does not exist: " << projectLocationDir.absolutePath();
        return NULL;
    }
}

QRPGProject *QRPGFileDao::openDummyProject()
{
    qDebug() << "opening dummy project ...";
    return this->openProjectDir(":qrpgdao/Dummy Project/");
}

QRPGProject *QRPGFileDao::openProjectDir(const QString &projectDirURI)
{
    qDebug() << "opening project: " << projectDirURI << "...";
    QRPGProject *proj = NULL;
    QDir projectDir(projectDirURI); // Used to create subfolders!

    if (projectDir.exists()) {
        proj = this->newProject(projectDirURI, "projectTitle", "gameTitle");
        // TODO: project inladen in geheugen!
        // project-file openen
        initProjectFromFile(proj);
        //        openProjects.insert(projectDirURI, proj);
    } else {
        qDebug() << "project folder " << projectDirURI << " does not exist!";
    }
    return proj;
}

void QRPGFileDao::closeProject(const QString &projectDirURI)
{
    QMap<QString, QRPGDao::QRPGProject *>::const_iterator projIt = openProjects.find(projectDirURI);
    if (projIt != openProjects.end()) {
        QRPGDao::QRPGProject *proj = projIt.value();
        openProjects.remove(projIt.key());
        delete proj;
    }
}

QString QRPGFileDao::getInfo() const
{
    return "This is the file-based dao.";
}

} // namespace Impl
} // namespace QRPGDao
