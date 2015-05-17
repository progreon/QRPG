#ifndef QRPG_QRPGSCENE_H
#define QRPG_QRPGSCENE_H

#include <QObject>
//#include <QMutex>
//#include <QMutexLocker>
#include <QPixmap>
#include <QImage>
#include <QPointF>
#include <QMap>
#include <QSet>
#include <QVector>
#include "graphicsitem.h"

namespace QRPG {

class QRPGScene : public QObject
{
    Q_OBJECT
public:
    explicit QRPGScene(QObject *parent = 0);
    ~QRPGScene();
    //TODO: Needs optimisation!
    //TODO: Return rendered "boundingRect"
    /**
     * @brief render Renders its items onto a given pixmap
     * @param screen The pixmap to render on
     * @param point The top-left corner of the scene that should be rendered
     */
    virtual void render(QPixmap *screen, const QPointF &pos);
    /**
     * @brief addGraphicsItem Add an item to the scene
     * @param item The item to add to the scene
     * @param layer On which layer to add this item (default 0)
     * @return <code>true</code> if the item is new to this scene, <code>false</code> otherwise
     */
    virtual bool addGraphicsItem(GraphicsItem *item, int layer = 0);
    virtual bool deleteGraphicsItem(GraphicsItem *item);

signals:

public slots:
    virtual void doTick();

private:
//    QMutex renderMutex;

//    QVector<int> usedLayers; // To keep track of the layers used, and to be able to loop over them in order.
    QMap<int, QSet<GraphicsItem *> > itemsPerLayer;
    // TODO: needs optimisation?
    bool itemIsInRect(const QRectF &rect, const GraphicsItem *item) const;
};

}

#endif // QRPG_QRPGSCENE_H
