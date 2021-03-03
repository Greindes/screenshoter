#include "scene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QKeyEvent>


Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    rect = addRect(QRectF(event->scenePos(), QSizeF(0.0, 0.0)));
    x0 = rect->rect().x();
    y0 = rect->rect().y();
    rect->setPen(QPen(QColor(Qt::black), 3, Qt::DashLine));
    //if left button press {
    //x0 = x, y0 = y;
    //}
    //initialize rect
}

void Scene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //resize rect
    qreal x1 = event->scenePos().x(), y1 = event->scenePos().y();
    qreal x = x0, y = y0;
    if (x1 < x0)
        std::swap(x, x1);
    if (y1 < y0)
        std::swap(y, y1);
    rect->setRect(x, y, x1 - x, y1 - y);
}

void Scene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //copy rect area and save it or return? Send it in signal?
    qreal x1 = event->scenePos().x(), y1 = event->scenePos().y();
    qreal x = x0, y = y0;
    if (x1 < x0)
        std::swap(x, x1);
    if (y1 < y0)
        std::swap(y, y1);
    emit screenshotTaken(img.copy(x, y, x1 - x, y1 - y));
}

QPixmap Scene::getImg() const
{
    return img;
}

void Scene::setImg(const QPixmap &value)
{
    img = value;
    clear();
    auto * ptr = addPixmap(img.copy(0, 0, img.width() - 2, img.height() - 2));
    auto * rect = addRect(0, 0, img.width() - 3, img.height() - 3, QPen(), QBrush(Qt::white));
    rect->setOpacity(0.3);
}


void Scene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::Cancel))
        emit screenshotTaken(QPixmap());
}
