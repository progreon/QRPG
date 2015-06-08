/*
This file is part of the QRPG project
Copyright (C) 2015  Marco Willems

This program is free software; you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation; either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License along
with this program. If not, see <http://www.gnu.org/licenses/>.
*/

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
