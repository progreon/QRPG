#ifndef QRPGGAME_H
#define QRPGGAME_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMap>
#include "qrpgscreen.h"
#include "qrpgscene.h"
#include "maps/mapscene.h"

namespace QRPG {

class Game : public QObject
{
    Q_OBJECT
public:
    explicit Game(Screen *screen);
    ~Game();
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
    Screen *screen;
    QMap<int, bool> input;
    QThread *gameThread;
    QMutex inputMutex;

    Map map;
    void handleInput();

    volatile bool running;
    volatile bool looping;
    void run();
    void tick();
};

}

#endif // QRPGGAME_H
