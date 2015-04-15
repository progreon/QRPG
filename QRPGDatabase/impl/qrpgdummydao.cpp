#include "qrpgdummydao.h"
#include "model/qrpgproject.h"

namespace QRPGDao {
namespace Impl {

QRPGDummyDao::QRPGDummyDao()
{

}

QRPGDummyDao::~QRPGDummyDao()
{
    foreach (QRPGDao::QRPGProject *proj, allProjects.values()) {
        delete proj;
    }
    openProjects.clear();
    allProjects.clear();
}

QRPGDao::QRPGProject *QRPGDummyDao::createNewProject(const QDir &projectLocationDir, QString projectTitle, QString gameTitle)
{
    QString projectFolderURI = projectLocationDir.absolutePath().append(QDir::separator()).append(projectTitle);
    if (!allProjects.contains(projectFolderURI)) {
        QRPGDao::QRPGProject *proj = this->newProject(projectFolderURI, projectTitle, gameTitle);
        allProjects.insert(projectFolderURI, proj);
        return openProjectDir(projectFolderURI);
    } else {
        return NULL;
    }
}

QRPGDao::QRPGProject *QRPGDummyDao::openProjectDir(QString projectDirURI)
{
    QMap<QString, QRPGDao::QRPGProject *>::const_iterator projIt = allProjects.find(projectDirURI);
    if (projIt != allProjects.end()) {
        openProjects.insert(projIt.key(), projIt.value());
        return projIt.value();
    } else {
        return NULL;
    }
}

void QRPGDummyDao::closeProject(QString projectDirURI)
{
    QMap<QString, QRPGDao::QRPGProject *>::const_iterator projIt = openProjects.find(projectDirURI);
    if (projIt != openProjects.end()) {
        openProjects.remove(projIt.key());
    }
}

QString QRPGDummyDao::getInfo() const
{
    return "This is the dummy dao.";
}

} // namespace Impl
} // namespace QRPGDao

