#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "qrpgdatabase.h"
#include "model/qrpgproject.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->statusBar->hide();
    game = NULL;
    screen = new QRPG::QRPGScreen(this);
    game = new QRPG::QRPGGame(screen);
    this->setCentralWidget(screen);
//    connect(game, SIGNAL(render()), screen, SLOT(doRender()));
    QRPGDao::QRPGDatabase *dao = QRPGDao::newDao();
    QRPGDao::QRPGProject *dummyProject = dao->openDummyProject();
    game->openGameProject(dummyProject);
    game->setupThread(&gameThread);
    game->moveToThread(&gameThread);
}

MainWindow::~MainWindow()
{
    delete ui;
    if (game != NULL) delete game;
}

void MainWindow::startGame()
{
    gameThread.start();
    game->openMap(0);

}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    if (game != NULL) game->keyPressed(ke->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent *ke)
{
    if (game != NULL) game->keyReleased(ke->key());
}

void MainWindow::on_action_Stop_triggered()
{
    if (game != NULL) game->stop();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    if (game != NULL) game->stop();
}
