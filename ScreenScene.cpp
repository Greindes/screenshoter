#include "ScreenScene.h"
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>
#include <QKeyEvent>


//QGraphicsScene(QRectF(0, 0, 1366, 768), parent)
Scene::Scene(QObject *parent) : QGraphicsScene(parent)
{
    imgItem = addPixmap(QPixmap());
    rectLeft = addRect(QRectF(sceneRect()), Qt::NoPen, QBrush(Qt::white));
    rectLeft->setOpacity(0.3);
    rectTop  = addRect(QRectF(sceneRect()), Qt::NoPen, QBrush(Qt::white));
    rectTop->setOpacity(0.3);
    rectRight  = addRect(QRectF(sceneRect()), Qt::NoPen, QBrush(Qt::white));
    rectRight->setOpacity(0.3);
    rectBottom  = addRect(QRectF(sceneRect()), Qt::NoPen, QBrush(Qt::white));
    rectBottom->setOpacity(0.3);
}

void Scene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    rectMid = addRect(QRectF(event->scenePos(), QSizeF(0.0, 0.0)),
                   QPen(QColor(Qt::red), 3, Qt::DashLine));
    x0 = rectMid->rect().x();
    y0 = rectMid->rect().y();
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
    rectMid->setRect(x, y, x1 - x, y1 - y);

    rectLeft->setRect(0, 0, std::min(x, x1), sceneRect().height());
    rectTop->setRect(std::min(x, x1), 0, std::abs(x - x1), std::min(y, y1));
    rectRight->setRect(std::max(x, x1), 0, sceneRect().width() - std::max(x, x1), sceneRect().height());
    rectBottom->setRect(std::min(x, x1), std::max(y, y1), std::abs(x - x1), sceneRect().height() - std::max(y, y1));
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
    removeItem(rectMid);
    rectMid = nullptr;
}

QPixmap Scene::getImg() const
{
    return img;
}

void Scene::setImg(const QPixmap &pix)
{
    img = pix;
    imgItem->setPixmap(img);
    //auto * rect = addRect(0, 0, img.width(), img.height(), QPen(), QBrush(Qt::white));
    setSceneRect(0, 0, img.width(), img.height());
    rectLeft->setRect(0, 0, img.width(), img.height());
    rectTop->setRect(0, 0, 0, 0);
    rectRight->setRect(0, 0, 0, 0);
    rectBottom->setRect(0, 0, 0, 0);
}


void Scene::keyReleaseEvent(QKeyEvent *event)
{
    if (event->matches(QKeySequence::Cancel))
        emit screenshotTaken(QPixmap());
}
