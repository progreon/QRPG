#ifndef QRPGDAO_IMPL_QRPGFILEDAO_H
#define QRPGDAO_IMPL_QRPGFILEDAO_H

#include <QMap>
#include <QDir>
#include "qrpgdatabase.h"

namespace QRPGDao {
namespace Impl {

class QRPGFileDao : public QRPGDao::QRPGDatabase
{
public:
    friend QRPGDao::QRPGDatabase *QRPGDao::newDao(QRPGDao::DaoType daoType);
    ~QRPGFileDao();

private:
    static const QString relProjectFile;

    QRPGFileDao();
    QMap<QString, QRPGDao::QRPGProject *> openProjects; // projectDirURI => project*
    //            importTiles(project, tilesFolderURI, tilesFileURI);
    void importMaps(QRPGProject *project, const QString &mapsFolderURI, const QString &mapsFileURI);
    void importTiles(QRPGProject *project, const QString &tilesFolderURI, const QString &tilesFileURI);
    void initProjectFromFile(QRPGDao::QRPGProject *project);

    // QRPGDatabase interface
public:
    QRPGDao::QRPGProject *createNewProject(const QDir &projectLocationDir, const QString &projectTitle, const QString &gameTitle);
    QRPGDao::QRPGProject *openDummyProject();
    QRPGDao::QRPGProject *openProjectDir(const QString &projectDirURI);
    void closeProject(const QString &projectDirURI);
    QString getInfo() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGFILEDAO_H
