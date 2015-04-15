#include "qrpgfiledao.h"

#include <assert.h>
#include <QDebug>
#include <QFile>
#include "../model/qrpgproject.h"

namespace QRPGDao {
namespace Impl {

QRPGFileDao::QRPGFileDao()
{

}

QRPGFileDao::~QRPGFileDao()
{
    foreach (QRPGDao::QRPGProject *proj, openProjects.values()) {
        delete proj;
    }
    openProjects.clear();
}

QRPGProject *QRPGFileDao::createNewProject(const QDir &projectLocationDir, QString projectTitle, QString gameTitle)
{
    // TODO: error handling??

//    QDir projectLocationDir(projectDirLocation); // The directory the project directory will be in
    if (projectLocationDir.exists()) {
        if (projectLocationDir.mkdir(projectTitle)) {
            QDir projectDir(projectLocationDir);
            assert(projectDir.cd(projectTitle));
            qDebug() << "Project directory: " << projectDir.absolutePath();

            // Creating subdirectories

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

//    QDir projectDir(projectFolderURI); // Used to create subfolders!
//    if (!projectDir.exists()) {
//        projectDir.mkpath(".");
//        if (projectDir.exists()) {
//            // Creating subfolders
//            QFile file(projectDir.absolutePath().append(QDir::separator()).append(gameTitle).append(".qrpg"));
//            file.open(QIODevice::ReadWrite);
//            file.close();
//            // Done creating subfolders
//            QRPGProject *proj = this->newProject(projectFolderURI, projectTitle, gameTitle);
//            openProjects.insert(projectFolderURI, proj);
//            return proj;
//        } else {
//            qDebug() << "Could not create project folder!";
//            return NULL;
//        }
//    } else {
//        qDebug() << "The project folder you wish to create already exists!";
//    }
//    return NULL;
}

QRPGProject *QRPGFileDao::openProjectDir(QString projectDirURI)
{
    QDir projectDir(projectDirURI); // Used to create subfolders!
    if (projectDir.exists()) {
        // TODO: project inladen in geheugen!
        QRPGProject * proj = this->newProject(projectDirURI, "projectTitle", "gameTitle");
        // TODO: project inladen in geheugen!
        openProjects.insert(projectDirURI, proj);
    }
    return NULL;
}

void QRPGFileDao::closeProject(QString projectDirURI)
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

