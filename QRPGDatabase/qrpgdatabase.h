#ifndef QRPGDATABASE_H
#define QRPGDATABASE_H

#include <QString>
#include <QDir>
//#include <QList>

namespace QRPGDao {

//class QRPGDatabase;
//typedef QRPGDatabase Dao;

class QRPGProject;

class QRPGDatabase
{

public:
    virtual QRPGProject *createNewProject(const QDir &projectLocationDir, const QString &projectTitle, const QString &gameTitle) = 0;
    virtual QRPGProject *openDummyProject() = 0;
    virtual QRPGProject *openProjectDir(const QString &projectDirURI) = 0;
//    virtual QRPGProject *openProjectFile(QString projectFileURI) = 0;
//    virtual QList<QRPGProject *> getOpenProjects() const = 0;
    virtual void closeProject(const QString &projectDirURI) = 0;
    virtual QString getInfo() const = 0; // Tells you what kind of Dao this is

protected:
    QRPGProject *newProject(const QString &projectDirURI, const QString &projectTitle, const QString &gameTitle);
    void setProjectTileSize(QRPGProject *project, int tileSize);
};

enum DaoType
{
    DUMMY,
    FILE
};

QRPGDatabase *newDao(DaoType daoType = FILE);

} // namespace QRPGDao

#endif // QRPGDATABASE_H
