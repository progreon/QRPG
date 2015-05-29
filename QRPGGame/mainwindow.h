#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include "qrpggame.h"
#include "qrpgscreen.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(const QRPGDao::QRPGProject *project, QWidget *parent = 0);
    ~MainWindow();
    void startGame();

private:
    Ui::MainWindow *ui;
    QRPG::QRPGScreen *screen;
    QRPG::QRPGGame *game;
    QThread gameThread;

    // QWidget interface
protected:
    void keyPressEvent(QKeyEvent *ke);
    void keyReleaseEvent(QKeyEvent *ke);
private slots:
    void on_action_Stop_triggered();

    // QWidget interface
protected:
    void closeEvent(QCloseEvent *);
};

#endif // MAINWINDOW_H
