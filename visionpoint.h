#ifndef VISIONPOINT_H
#define VISIONPOINT_H

#include <QObject>
#include <QPainter>
#include "visionitem.h"

class VisionPoint : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionPoint(VisionItem *parent = 0);

    void setPointF(QPointF pointF);

public:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

signals:

private:
    QPointF m_pointF;

public slots:
};

#endif // VISIONPOINT_H
