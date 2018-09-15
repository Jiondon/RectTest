#ifndef VISIONLINEITEM_H
#define VISIONLINEITEM_H

#include <QObject>
#include "visionitem.h"
#include <QPainter>
#include "minirect.h"

class VisionLineItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionLineItem(QPointF p1 = QPointF(0,0),QPointF p2 = QPointF(0,0),bool bEdit = true,qreal penWidth = 0,
                            QColor penColor = QColor(0,0,0),VisionItem *parent = 0);
    void setLine(QPointF p1,QPointF p2);
    void setEditStatus(bool edit);
    void setPenWidth(qreal penWidth);
    void setPenColor(QColor color);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

signals:

private:
    qreal m_x=0;qreal m_y;qreal m_width=0;qreal m_height=0;
    QPointF m_pointF1 = QPointF(0,0);
    QPointF m_pointF2 = QPointF(0,0);
    qreal m_penWidth = 0;
    QColor m_penColor = QColor(0,0,0);
    bool m_bEditStatus = false;
    bool m_bSelected = false;

    int m_iIndex = -1;
    MiniRect* m_miniRect1 = nullptr;
    MiniRect* m_miniRect2 = nullptr;

    qreal m_angle = 0;  //角度
    QPointF m_lastPointF;
private:
    void updateRect(QPointF p1,QPointF p2);

private slots:
    void slotMiniRectIndex(int index);

public slots:
};

#endif // VISIONLINEITEM_H
