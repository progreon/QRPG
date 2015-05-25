#ifndef QRPGDAO_IMPL_QRPGFILEDAO_H
#define QRPGDAO_IMPL_QRPGFILEDAO_H

#include <QDir>
#include "qrpgdatabase.h"

namespace QRPGDao {
namespace Impl {

class QRPGFileDao : public QRPGDao::QRPGDatabase
{
public:
    friend QRPGDao::QRPGDatabase *QRPGDao::newDao();
    ~QRPGFileDao();

private:
    static const QString relProjectFile;

    QRPGFileDao();
    QRPGDao::QRPGProject *currentProject;
    void importMaps(QRPGProject *project, const QString &mapsFolderURI, const QString &mapsFileURI);
    void importTiles(QRPGProject *project, const QString &tilesFolderURI, const QString &tilesFileURI);
    void initMapsDir(const QDir &mapsDir);
    void initProjectFile(const QDir &projectDir, const QString &gameTitle, int tileSize);
    void initProjectFromFile(QRPGDao::QRPGProject *project);
    void initTilesDir(const QDir &tilesDir);

    // QRPGDatabase interface
public:
    QRPGDao::QRPGProject *createNewProject(const QString &projectLocationURI, const QString &projectTitle, const QString &gameTitle);
    QRPGDao::QRPGProject *openDummyProject();
    QRPGDao::QRPGProject *openProjectDir(const QString &projectDirURI);
    void closeProject();
    QString info() const;
};

} // namespace Impl
} // namespace QRPGDao

#endif // QRPGDAO_IMPL_QRPGFILEDAO_H
