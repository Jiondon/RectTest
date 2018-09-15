#ifndef VISIONWIDGETITEM_H
#define VISIONWIDGETITEM_H

#include <QObject>
#include "visionitem.h"
#include <QPainterPath>
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QColor>
#include <QStyleOptionGraphicsItem>

class VisionWidgetItem : public VisionItem
{
    Q_OBJECT
public:
    explicit VisionWidgetItem(VisionItem *parent = 0);

    void setPaintPath(QPainterPath path1,QPainterPath path2,Operation_enum opera);

protected:
    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);

signals:

private:
    QPainterPath m_path1;
    QPainterPath m_path2;
    Operation_enum m_opera;

    QPainterPath m_path;

public slots:
};

#endif // VISIONWIDGETITEM_H
