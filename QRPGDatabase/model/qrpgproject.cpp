#include "qrpgproject.h"
#include "../qrpgdatabase.h"

namespace QRPGDao {

QRPGProject::QRPGProject(QRPGDatabase *dao, QString projectFolderURI, QString projectTitle, QString gameTitle)
    : _dao(dao), _projectFolderURI(projectFolderURI), _projectTitle(projectTitle), _gameTitle(gameTitle)
{
}

QRPGProject::~QRPGProject()
{

}

void QRPGProject::setProjectTitle(QString projectTitle)
{
    // TODO
    this->_projectTitle = projectTitle;
}

void QRPGProject::setGameTitle(QString gameTitle)
{
    this->_gameTitle = gameTitle;
}

} // namespace QRPGDao

