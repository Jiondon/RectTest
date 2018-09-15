#include "visionwidgetitem.h"
#include <QPainter>

VisionWidgetItem::VisionWidgetItem(VisionItem *parent) : VisionItem(parent)
{

}

void VisionWidgetItem::setPaintPath(QPainterPath path1, QPainterPath path2, Operation_enum opera)
{
    m_path1 = path1;
    m_path2 = path2;
    m_opera = opera;
    this->scene()->update();
}

QRectF VisionWidgetItem::boundingRect() const
{
    return m_path.boundingRect();
}

void VisionWidgetItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHint(QPainter::Antialiasing);

    QPainterPath path_end;
    if(m_opera == AND){
        path_end = (m_path1+m_path2)-(m_path1-m_path2)-(m_path2-m_path1);  //交集
    }else if(m_opera == OR){
        path_end = m_path1.united(m_path2);  //合并
    }else if(m_opera == NOR){
        path_end = (m_path2-m_path1)+(m_path1-m_path2);  ///异或--交集的取反
    }else if(m_opera == SUB){
        path_end = m_path1.subtracted(m_path2); // 扣掉圆  差集
    }else
        return;

    m_path = path_end;
//    painter.translate(20, 20);
    painter->setPen(QPen(QColor(255,0,0),0));
    painter->setBrush(Qt::lightGray);
    painter->drawPath(path_end);
//    painter.setBrush(Qt::NoBrush);
//    painter.drawRect(path.boundingRect());
}
