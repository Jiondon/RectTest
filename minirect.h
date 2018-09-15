#ifndef MINIRECT_H
#define MINIRECT_H

#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QColor>
#include <QStyleOptionGraphicsItem>

class MiniRect : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit MiniRect(qreal x,qreal y,qreal w,qreal h,QColor penColor = QColor(255,0,0),QGraphicsItem *parent = 0);
    void setRect(qreal x,qreal y,qreal w,qreal h);
    void setIndex(int index);

signals:
    void signalIndex(int index);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent *event);

private:
    int m_index = 0;
    qreal m_x = 0;
    qreal m_y = 0;
    qreal m_width = 0;
    qreal m_height = 0;

    QColor m_penColor = QColor(255,0,0);

public slots:
};

#endif // MINIRECT_H
