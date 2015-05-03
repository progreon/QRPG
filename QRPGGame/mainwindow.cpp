#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->mainToolBar->hide();
    ui->statusBar->hide();
    screen = new QRPG::QRPGScreen(this);
    game = new QRPG::QRPGGame(screen);
    this->setCentralWidget(screen);
    connect(game, SIGNAL(render()), screen, SLOT(doRender()));
    game->setupThread(&gameThread);
    game->moveToThread(&gameThread);
    gameThread.start();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete game;
}

void MainWindow::keyPressEvent(QKeyEvent *ke)
{
    game->keyPressed(ke->key());
}

void MainWindow::keyReleaseEvent(QKeyEvent *ke)
{
    game->keyReleased(ke->key());
}

void MainWindow::on_action_Stop_triggered()
{
    game->stop();
}

void MainWindow::closeEvent(QCloseEvent *)
{
    game->stop();
}
