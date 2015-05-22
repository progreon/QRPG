#include "qrpgfiledao.h"

#include <assert.h>
#include <QDebug>
#include <QFile>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include "../model/qrpgproject.h"
#include "../model/qrpgsprite.h"
#include "../model/qrpgtile.h"
#include "../model/qrpgmap.h"

namespace QRPGDao {
namespace Impl {

//const QString QRPGFileDao::relProjectFile = "project.qrpg";
const QString QRPGFileDao::relProjectFile = "qrpgproject";

QRPGFileDao::QRPGFileDao()
{

}

void QRPGFileDao::importMaps(QRPGProject *project, const QString &mapsFolderURI, const QString &mapsFileURI)
{
    // TODO: mapsfolder + / for sure!
    // get all maps
    QFile mapsFile(mapsFileURI);
    if (mapsFile.open(QIODevice::ReadOnly)) {
        QJsonObject jsonObject = QJsonDocument(QJsonDocument::fromJson(mapsFile.readAll())).object();
        QJsonArray maps = jsonObject["maps"].toArray();
        for (int i=0; i<maps.count(); i++) {
            QJsonObject jsonMapEntry = maps.at(i).toObject();
            int mapID = jsonMapEntry["id"].toInt();
            QString mapTitle = jsonMapEntry["title"].toString();

            QString mapFileURI = jsonMapEntry["file"].toString();
            QFile mapFile(mapsFolderURI + mapFileURI);
            if (mapFile.open(QIODevice::ReadOnly)) {
                QJsonDocument jsonMapDoc(QJsonDocument::fromJson(mapFile.readAll()));
                QJsonObject mapObject = jsonMapDoc.object();
                int width = mapObject["width"].toInt();
                int height = mapObject["height"].toInt();
                QRPGMap *newMap = new QRPGMap(project, mapID, mapTitle, width, height);

                QJsonArray jsonTileArray = mapObject["tiles"].toArray();
                for (int j=0; j<jsonTileArray.count(); j++) {
                    QJsonObject jsonTileLayer = jsonTileArray.at(j).toObject();
                    int layer = jsonTileLayer["layer"].toInt();
                    QJsonArray tileYArray = jsonTileLayer["ids"].toArray();
                    for (int y=0; y<tileYArray.count(); y++) {
                        QJsonArray tileXArray = tileYArray.at(y).toArray();
                        for (int x=0; x<tileXArray.count(); x++) {
                            int tileID = tileXArray.at(x).toInt(-1);
                            if (tileID >= 0 && project->tiles().contains(tileID)) {
                                qDebug() << "layer " << layer << ": (" << x << "," << y << ") = " << tileID;
                                newMap->setTile(layer, x, y, project->tiles().value(tileID));
                            }
                        }
                    }
                }
                project->addNewMap(newMap);

                mapFile.close();
            } else {
                qWarning() << "Could not open map file!" << mapFile.fileName();
            }
        }
        mapsFile.close();
    } else {
        qWarning() << "Could not open maps file!" << mapsFile.fileName();
    }
}

void QRPGFileDao::importTiles(QRPGProject *project, const QString &tilesFolderURI, const QString &tilesFileURI)
{
    QFile tilesFile(tilesFileURI);
    if (tilesFile.open(QIODevice::ReadOnly)) {
        QJsonObject jsonObject = QJsonDocument(QJsonDocument::fromJson(tilesFile.readAll())).object();
        QJsonArray tiles = jsonObject["tiles"].toArray();
        for (int i=0; i<tiles.count(); i++) {
            // Tile info
            QJsonObject jsonTile = tiles.at(i).toObject();
            int id = jsonTile["id"].toInt();
            QString name = jsonTile["name"].toString();
            // Sprite
            QJsonObject jsonSprite = jsonTile["sprite"].toObject();
            QString file = jsonSprite["file"].toString();
            QPixmap spritesheet(tilesFolderURI + file);
            QRPGDao::QRPGSprite *sprite = new QRPGDao::QRPGSprite(id);
            QJsonArray jsonFrames = jsonSprite["frames"].toArray();
            for (int j=0; j<jsonFrames.count(); j++) {
                QJsonObject jsonFrame = jsonFrames.at(j).toObject();
                int x = jsonFrame["x"].toInt();
                int y = jsonFrame["y"].toInt();
                QPixmap spriteframe = spritesheet.copy(x, y, 8, 8);
                sprite->addSpriteFrame(spriteframe);
                qDebug() << "creating spriteframe " << id << ": " << name << "(" << file << ": (" << x << "," << y << "))";
                qDebug() << spriteframe;
            }
            if (sprite->spriteFrames().count() > 1) {
                sprite->setFps(jsonSprite.value("fps").toDouble(1.0));
            }
            project->addNewSprite(sprite);
            // Add tile to project
            QRPGTile *newTile = new QRPGTile(id, name, sprite);
            project->addNewTile(newTile);
        }
        tilesFile.close();
    } else {
        qWarning() << "Could not open tiles file!" << tilesFile.fileName();
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
        QFile projectFile(projDirURI + relProjectFile);
        qDebug() << projectFile.fileName();
        // reading project file
        if (projectFile.open(QIODevice::ReadOnly)) {
            int tileSize;
            QString tilesFolderURI;
            QString tilesFileURI;
            QString mapsFolderURI;
            QString mapsFileURI;

            QJsonObject jsonObj = QJsonDocument(QJsonDocument::fromJson(projectFile.readAll())).object();
            tileSize = jsonObj["tilesize"].toInt();
            tilesFolderURI = projDirURI + jsonObj["tilesfolder"].toString();
            tilesFileURI = tilesFolderURI + jsonObj["tilesfile"].toString();
            mapsFolderURI = projDirURI + jsonObj["mapsfolder"].toString();
            mapsFileURI = mapsFolderURI + jsonObj["mapsfile"].toString();

            setProjectTileSize(project, tileSize);

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
            qWarning() << "Could not open project file!" << projectFile.fileName();
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
