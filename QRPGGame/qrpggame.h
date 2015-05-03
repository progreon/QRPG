#ifndef QRPG_QRPGGAME_H
#define QRPG_QRPGGAME_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMap>
#include "qrpgscreen.h"
#include "qrpgscene.h"
#include "maps/mapscene.h"

namespace QRPG {

class QRPGGame : public QObject
{
    Q_OBJECT
public:
    explicit QRPGGame(QRPGScreen *screen);
    ~QRPGGame();
    bool isRunning() const {return running;}
    void keyPressed(int key);
    void keyReleased(int key);
    void setupThread(QThread *gameThread);
    void stop();
//    void test();

signals:
    void render();

public slots:
    void start();

private:
    QRPGScreen *screen;
    QMap<int, bool> input;
    QThread *gameThread;
    QMutex inputMutex;

    MapScene map;
    void handleInput();

    volatile bool running;
    volatile bool looping;
    void run();
    void tick();
};

}

#endif // QRPG_QRPGGAME_H
