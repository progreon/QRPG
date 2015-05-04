#include "qrpggame.h"
#include <QDebug>
#include <QDateTime>

QRPG::QRPGGame::QRPGGame(QRPGScreen *screen)
{
    this->screen = screen;
    screen->setScene(&map);
    screen->centerScreenOn(0, 0);
}

QRPG::QRPGGame::~QRPGGame()
{

}

void QRPG::QRPGGame::keyPressed(int key)
{
    inputMutex.lock();
    input.insert(key, true);
    inputMutex.unlock();
}

void QRPG::QRPGGame::keyReleased(int key)
{
    inputMutex.lock();
    input.insert(key, false);
    inputMutex.unlock();
}

void QRPG::QRPGGame::setupThread(QThread *gameThread)
{
    this->gameThread = gameThread;
    connect(gameThread, SIGNAL(started()), this, SLOT(start()));
}

//void QRPG::Game::test()
//{
//}

void QRPG::QRPGGame::handleInput()
{
    QPointF pos = screen->screenPos();
    if (input[Qt::Key_Left] | input[Qt::Key_Q]) {
        pos.setX(pos.x() - 2.0);
    }
    if (input[Qt::Key_Right] | input[Qt::Key_D]) {
        pos.setX(pos.x() + 2.0);
    }
    if (input[Qt::Key_Up] | input[Qt::Key_Z]) {
        pos.setY(pos.y() - 2.0);
    }
    if (input[Qt::Key_Down] | input[Qt::Key_S]) {
        pos.setY(pos.y() + 2.0);
    }
    screen->setScreenPos(pos.x(), pos.y());
//    screen->centerScreenOn(pos.x(), pos.y());
}

void QRPG::QRPGGame::start()
{
    qDebug() << "starting...";
    looping = true;
    run();
}

void QRPG::QRPGGame::stop()
{
    qDebug() << "stopping...";
    looping = false;
    while (isRunning()) {}
    gameThread->exit();
    qDebug() << "stopped";
}

void QRPG::QRPGGame::run()
{
    running = true;

    //    int ticks_per_sec = 60;
    double msPerTick = 1000.0/60.0;
    int ticks = 0;
    int frames = 0;
    screen->resetFrames();
    qint64 start = QDateTime::currentMSecsSinceEpoch();
    qint64 last = QDateTime::currentMSecsSinceEpoch();
    float delta = 0.0;

    while (looping) {
        qint64 now = QDateTime::currentMSecsSinceEpoch();
        qint64 deltams = now - last;
        last = now;
        delta += deltams / msPerTick;
        bool shouldRender = true;
        while (delta >= 1) {
            ticks++;
            tick();
            delta -= 1;
        }
        gameThread->msleep(3);
        if (shouldRender) {
            frames++;
//            emit render();
            screen->doRender();
        }
        if (QDateTime::currentMSecsSinceEpoch() - start >= 1000) {
            start += 1000;
            qDebug() << ticks << " ticks, " << frames << " renders, " << screen->frames() << " real frames";
            ticks = 0;
            frames = 0;
            screen->resetFrames();
        }

    }
    running = false;
}

void QRPG::QRPGGame::tick()
{
//    map.doTick();
    handleInput();
}

