#ifndef QRPG_QRPGGAME_H
#define QRPG_QRPGGAME_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QMap>
#include "model/qrpgproject.h"
#include "qrpgscreen.h"
#include "qrpgscene.h"
#include "maps/mapscene.h"
#include "loaders/qrpgmaploader.h"

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
    void openGameProject(const QRPGDao::QRPGProject *project);
    void setupThread(QThread *gameThread);
    void stop();
//    void test();
    qreal tps() const {return _tps;}

signals:
    void render();

public slots:
    void start();

private:
    qreal _tps;

    QRPGScreen *screen;
    QMap<int, bool> input;
    QThread *gameThread;
    QMutex inputMutex;

    MapScene *map;
    void handleInput();

    volatile bool running;
    volatile bool looping;
    void run();
    void tick();

    const QRPGDao::QRPGProject *currProject;
    QRPGMapLoader mapLoader;
};

}

#endif // QRPG_QRPGGAME_H
