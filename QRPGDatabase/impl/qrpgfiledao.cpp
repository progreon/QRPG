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

const QString QRPGFileDao::relProjectFile = "qrpgproject";

QRPGFileDao::QRPGFileDao()
{

}

bool QRPGFileDao::importMaps(QRPGProject *project, const QString &mapsFolderURI, const QString &mapsFileURI)
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
//                                qDebug() << "layer " << layer << ": (" << x << "," << y << ") = " << tileID;
                                newMap->setTile(layer, x, y, project->tiles().value(tileID));
                            }
                        }
                    }
                }
                project->addNewMap(newMap);

                mapFile.close();
            } else {
                qWarning() << "Could not open map file!" << mapFile.fileName();
                mapsFile.close();
                return false;
            }
        }
        mapsFile.close();
    } else {
        qWarning() << "Could not open maps file!" << mapsFile.fileName();
        return false;
    }
    return true;
}

bool QRPGFileDao::importTiles(QRPGProject *project, const QString &tilesFolderURI, const QString &tilesFileURI)
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
                QPixmap spriteframe = spritesheet.copy(x, y, project->tileSize(), project->tileSize());
                sprite->addSpriteFrame(spriteframe);
//                qDebug() << "creating spriteframe " << id << ": " << name << "(" << file << ": (" << x << "," << y << "))";
//                qDebug() << spriteframe;
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
        return false;
    }
    return true;
}

void QRPGFileDao::initMapsDir(const QDir &mapsDir)
{
    QString mapsFileRelURI = "qrpgmaps";
    if (mapsDir.exists()) {
        QFile mapsFile(mapsDir.canonicalPath() + QDir::separator() + mapsFileRelURI);
        if (mapsFile.open(QFile::WriteOnly)) {
            QJsonObject jsonObj;
            jsonObj["version"] = 0.0;
            jsonObj["maps"] = QJsonArray();
            QJsonDocument jsonDoc(jsonObj);
            mapsFile.write(jsonDoc.toJson(QJsonDocument::Indented));
            mapsFile.close();
        } else {
            qWarning() << "Failed to create/open the new tiles file!" << mapsFile.fileName();
        }
    } else {
        qWarning() << "The tiles directory doesn't exist!" << mapsDir.canonicalPath();
    }
}

void QRPGFileDao::initProjectFile(const QDir &projectDir, const QString &gameTitle, int tileSize)
{
    QString projectFileRelURI("qrpgproject");
    QString tilesFolder("Graphics/Tiles/");
    QString tilesFile("qrpgtiles");
    QString mapsFolder("Maps/");
    QString mapsFile("qrpgmaps");
    if (projectDir.exists()) {
        QFile projectFile(projectDir.canonicalPath() + QDir::separator() + projectFileRelURI);
        if (projectFile.open(QFile::WriteOnly)) {
            QJsonObject jsonObj;
            jsonObj["version"] = 0.0;
            jsonObj["tilesize"] = tileSize;
            jsonObj["gametitle"] = gameTitle;
            jsonObj["tilesfolder"] = tilesFolder;
            jsonObj["tilesfile"] = tilesFile;
            jsonObj["mapsfolder"] = mapsFolder;
            jsonObj["mapsfile"] = mapsFile;
            QJsonDocument jsonDoc(jsonObj);
            projectFile.write(jsonDoc.toJson(QJsonDocument::Indented));
            projectFile.close();
        } else {
            qWarning() << "Failed to create/open the new tiles file!" << projectFile.fileName();
        }
    } else {
        qWarning() << "The tiles directory doesn't exist!" << projectDir.canonicalPath();
    }
}

bool QRPGFileDao::initProjectFromFile(QRPGProject *project)
{
    // TODO: value checks!
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
            QString gameTitle;
            QString tilesFolderURI;
            QString tilesFileURI;
            QString mapsFolderURI;
            QString mapsFileURI;

            QJsonObject jsonObj = QJsonDocument(QJsonDocument::fromJson(projectFile.readAll())).object();
            tileSize = jsonObj["tilesize"].toInt();
            gameTitle = jsonObj["gametitle"].toString();
            tilesFolderURI = projDirURI + jsonObj["tilesfolder"].toString();
            tilesFileURI = tilesFolderURI + jsonObj["tilesfile"].toString();
            mapsFolderURI = projDirURI + jsonObj["mapsfolder"].toString();
            mapsFileURI = mapsFolderURI + jsonObj["mapsfile"].toString();

            project->setGameTitle(gameTitle);
            setProjectTileSize(project, tileSize);

            qDebug() << "project file:" << projectFile.fileName();
            qDebug() << "tile size:" << project->tileSize();
            qDebug() << "game title:" << gameTitle;
            qDebug() << "tiles folder:" << tilesFolderURI;
            qDebug() << "tiles file:" << tilesFileURI;
            qDebug() << "maps folder:" << mapsFolderURI;
            qDebug() << "maps file:" << mapsFileURI;

            bool noError;
            // import sprites & tiles
            noError = importTiles(project, tilesFolderURI, tilesFileURI);
            if (!noError) return false;

            // import maps
            noError = importMaps(project, mapsFolderURI, mapsFileURI);
            if (!noError) return false;

            projectFile.close();
        } else {
            qWarning() << "Could not open project file!" << projectFile.fileName();
            return false;
        }
    } else {
        return false;
    }
    return true;
}

void QRPGFileDao::initTilesDir(const QDir &tilesDir)
{
    QString tilesFileRelURI = "qrpgtiles";
    if (tilesDir.exists()) {
        QFile tilesFile(tilesDir.canonicalPath() + QDir::separator() + tilesFileRelURI);
        if (tilesFile.open(QFile::WriteOnly)) {
            QJsonObject jsonObj;
            jsonObj["version"] = 0.0;
            jsonObj["tiles"] = QJsonArray();
            QJsonDocument jsonDoc(jsonObj);
            tilesFile.write(jsonDoc.toJson(QJsonDocument::Indented));
            tilesFile.close();
        } else {
            qWarning() << "Failed to create/open the new tiles file!" << tilesFile.fileName();
        }
    } else {
        qWarning() << "The tiles directory doesn't exist!" << tilesDir.canonicalPath();
    }
}

QRPGFileDao::~QRPGFileDao()
{
    if (currentProject != NULL) delete currentProject;
}

QRPGProject *QRPGFileDao::createNewProject(const QString &projectLocationURI, const QString &projectTitle, const QString &gameTitle)
{
    qDebug() << "Creating new project:" << projectTitle << "in" << projectLocationURI << "...";
    QRPGProject *project = NULL;
    int tileSize = 8;
    // This dir object is used to walk through the directory structure of the project folder
    QDir dir(projectLocationURI);
    if (dir.exists()) {
        qDebug() << "The project's location directory exists! :)" << dir.canonicalPath();
        // Creating the directory structure
        if (dir.mkdir(projectTitle)) {
            dir.cd(projectTitle);
            // Audio directory
                dir.mkdir("Audio");
                    dir.cd("Audio");
                    dir.mkdir("Background");
                    dir.mkdir("Effects");
                dir.cdUp();
                // Graphics directory
                dir.mkdir("Graphics");
                    dir.cd("Graphics");
                    dir.mkdir("Animations");
                    dir.mkdir("Characters");
                    dir.mkdir("System");
                    dir.mkdir("GUI");
                    dir.mkdir("Fonts");
                    dir.mkdir("Scenes");
                    dir.mkdir("Tiles");
                        dir.cd("Tiles");
                        initTilesDir(dir);
                    dir.cdUp();
                dir.cdUp();
                // Maps directory
                dir.mkdir("Maps");
                    dir.cd("Maps");
                    initMapsDir(dir);
                dir.cdUp();
                dir.mkdir("System");
                    dir.cd("System");
                    dir.mkdir("lib");
                    // TODO: copy libraries
                    // TODO: copy QRPGGame
                dir.cdUp();
                initProjectFile(dir, gameTitle, tileSize);
                // TODO: start script

                project = openProjectDir(dir.canonicalPath());
        } else {
            qWarning() << "Failed to create a new project directory!";
        }
    } else {
        qWarning() << "The project's location directory doesn't exist!" << dir.canonicalPath();
    }
    return project;
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
        QString projectTitle(projectDir.canonicalPath());
        if (projectTitle.endsWith('/')) {
            projectTitle.resize(projectTitle.size()-1);
        }
        int i = projectTitle.lastIndexOf('/');
        projectTitle.remove(0, i+1);
        qDebug() << "project title:" << projectTitle;
        proj = this->newProject(projectDirURI, projectTitle, "gameTitle");
        // project-file openen
        if (!initProjectFromFile(proj)) {
            proj = NULL;
        }
    } else {
        qDebug() << "project folder " << projectDirURI << " does not exist!";
    }
    currentProject = proj;
    return proj;
}

void QRPGFileDao::closeProject()
{
    if (currentProject != NULL) {
        delete currentProject;
        currentProject = NULL;
    }
}

QString QRPGFileDao::info() const
{
    return "This is the file-based dao.";
}

} // namespace Impl
} // namespace QRPGDao
