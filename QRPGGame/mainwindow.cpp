#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>
#include "qrpgdatabase.h"
#include "model/qrpgproject.h"

MainWindow::MainWindow(const QRPGDao::QRPGProject *project, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->statusBar->hide();
    screen = new QRPG::QRPGScreen(this);
    this->setCentralWidget(screen);
    game = new QRPG::QRPGGame(screen, project);
//    connect(game, SIGNAL(render()), screen, SLOT(doRender()));
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
