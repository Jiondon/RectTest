#ifndef VISIONARROWS_ROTATE_H
#define VISIONARROWS_ROTATE_H

#include <QObject>
#include <QGraphicsItem>
#include <QColor>
#include <QStyleOptionGraphicsItem>
#include <QPainter>

//方向坐标--暂时固定大小
class VisionArrows_Rotate :public QObject, public QGraphicsItem
{
    Q_OBJECT
public:
    explicit VisionArrows_Rotate(qreal x=0, qreal y=0, qreal w=0, qreal h=0, QColor penColor = QColor(255,0,0), QGraphicsItem *parent = 0);
    void setRect(qreal x,qreal y,qreal w,qreal h);

    QRectF boundingRect() const;

signals:
    void signalHoverLeave();
    void signalHoverEnter();

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);
    void hoverEnterEvent(QGraphicsSceneHoverEvent *event);

private:
    int m_index = 0;
    qreal m_x = 0;
    qreal m_y = 0;
    qreal m_width = 0;
    qreal m_height = 0;

    QColor m_penColor = QColor(255,0,0);

public slots:
};

#endif // VISIONARROWS_ROTATE_H
