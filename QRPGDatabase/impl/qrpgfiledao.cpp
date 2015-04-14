#include "qrpgfiledao.h"

#include <QDir>
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

QRPGProject *QRPGFileDao::createNewProject(QString projectFolderURI, QString projectTitle, QString gameTitle)
{
    QDir projectDir(projectFolderURI); // Used to create subfolders!
    if (!projectDir.exists()) {
        projectDir.mkpath(".");
        // TODO: create subfolders etc here
        QRPGProject * proj = this->newProject(projectFolderURI, projectTitle, gameTitle);
        openProjects.insert(projectFolderURI, proj);
    }
    return NULL;
}

QRPGProject *QRPGFileDao::openProjectFolder(QString projectFolderURI)
{
    QDir projectDir(projectFolderURI); // Used to create subfolders!
    if (projectDir.exists()) {
        // TODO: project inladen in geheugen!
        QRPGProject * proj = this->newProject(projectFolderURI, "projectTitle", "gameTitle");
        // TODO: project inladen in geheugen!
        openProjects.insert(projectFolderURI, proj);
    }
    return NULL;
}

void QRPGFileDao::closeProject(QString projectFolderURI)
{
    QMap<QString, QRPGDao::QRPGProject *>::const_iterator projIt = openProjects.find(projectFolderURI);
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

