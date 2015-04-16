#ifndef QRPGDAO_QRPGPROJECT_H
#define QRPGDAO_QRPGPROJECT_H


#include <QString>
#include "../qrpgdatabase.h"

namespace QRPGDao {
class QRPGProject
{
    friend class QRPGDatabase;
//    friend QRPGProject *QRPGDatabase::createNewProject(const QDir&, QString, QString);
public:
    ~QRPGProject();
    QString getProjectFolderURI() const {return _projectFolderURI;}
    QString getProjectTitle() const {return _projectTitle;}
    void setProjectTitle(QString projectTitle);
    QString getGameTitle() const {return _gameTitle;}
    void setGameTitle(QString gameTitle);
    const QRPGDatabase *getDao() const {return _dao;}

private:
    QRPGProject(QRPGDatabase *dao, QString projectFolderURI, QString projectTitle, QString gameTitle);

    const QRPGDatabase *_dao; /*!< The dao used in the application, do NOT delete this pointer!*/
    QString _projectFolderURI;
    QString _projectTitle;
    QString _gameTitle;
};

} // namespace QRPGDao

#endif // QRPGDAO_QRPGPROJECT_H
