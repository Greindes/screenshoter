#ifndef SCENE_H
#define SCENE_H

#include <QGraphicsScene>
#include <QPixmap>

//класс, создающий окно для вырезания части снимка
class Scene : public QGraphicsScene
{
    Q_OBJECT
public:
    Scene(QObject * parent = nullptr);

    QPixmap getImg() const;
    void setImg(const QPixmap &value);

protected:
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    qreal x0, y0;
    QGraphicsRectItem * rect;
    QPixmap img;
signals:
    void screenshotTaken(const QPixmap& ss);

    // QGraphicsScene interface
protected:
    virtual void keyReleaseEvent(QKeyEvent *event) override;
};

#endif // SCENE_H
