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
    virtual QRPGProject *createNewProject(const QDir &projectLocationDir, QString projectTitle, QString gameTitle) = 0;
    virtual QRPGProject *openProjectDir(QString projectDirURI) = 0;
//    virtual QRPGProject *openProjectFile(QString projectFileURI) = 0;
//    virtual QList<QRPGProject *> getOpenProjects() const = 0;
    virtual void closeProject(QString projectDirURI) = 0;
    virtual QString getInfo() const = 0; // Tells you what kind of Dao this is

protected:
    QRPGProject *newProject(QString projectDirURI, QString projectTitle, QString gameTitle);
};

enum DaoType
{
    DUMMY,
    FILE
};

QRPGDatabase *newDao(DaoType daoType = DUMMY);

} // namespace QRPGDao

#endif // QRPGDATABASE_H
