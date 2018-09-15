#include "visionellipseitem.h"
#include <QDebug>
#include <QCursor>
#include <QGraphicsRectItem>

VisionEllipseItem::VisionEllipseItem(VisionItem *parent):
    VisionItem(parent)
{
    penColor = QColor(0,0,0);//black
    penWidth = 1;
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
}

void VisionEllipseItem::setRect(qreal x, qreal y, qreal width, qreal height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
    this->setPos(m_x,m_y);
//    this->scene()->update();
    qDebug()<<this->boundingRect().width();
}



QRectF VisionEllipseItem::boundingRect() const
{
    QRectF rf = QRectF(-5,-5,m_width+10,m_height+10);
    return rf;
}

void VisionEllipseItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //计算两次move的鼠标的差值，
    QPointF curPoint = event->scenePos();
    QPointF disPoint = curPoint - lastPoint;
    lastPoint = curPoint;
    QGraphicsItem::mouseMoveEvent(event);

    if(directCursor == normal_rect){
        m_x = m_x + disPoint.x();
        m_y = m_y + disPoint.y();
        this->setPos(m_x,m_y);
        this->scene()->update();
    }else{
        if(directCursor == top_rect){
            //top point
            m_y = m_y + disPoint.y();
            m_height = m_height - disPoint.y();

        }else if(directCursor == right_rect){
            //right point
            m_width = m_width + disPoint.x();

        }else if(directCursor == bottom_rect){
            //bottom point
            m_height = m_height + disPoint.y();

        }else if(directCursor == left_rect){
            //left point
            m_x = m_x + disPoint.x();
            m_width = m_width - disPoint.x();
        }else{
            qDebug()<<"error directCursor";
        }

        if(m_width < 1)
            m_width = 1;
        if(m_height < 1)
            m_height = 1;

        this->setPos(m_x,m_y);
        this->scene()->update();
    }
    emit signal_Change(this);
}

void VisionEllipseItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //判断，x2/a+y2/b<=1 如果成立，则在椭圆内，否则不在圆内（a和b想要的增长一点,已bondingrect中的wid和hei作为标准参考，防止在选中的情况下，矩形框的范围）
    qreal qx = event->scenePos().x();
    qreal qy = event->scenePos().y();
    qreal dx = m_x+m_width/2;
    qreal dy = m_y+m_height/2;

    qreal ret = ((qx-dx)*(qx-dx))/((m_width/2)*(m_width/2))+((qy-dy)*(qy-dy))/((m_height/2)*(m_height/2));
    qDebug()<<"ret ::"<<ret;
    if(ret > 1){
        qDebug()<<"out of ellipse";
        setSelected(false);
        return;
    }
    //鼠标左键
    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() == Qt::ShiftModifier) {
            // 选中 item
            setSelected(true);
        } else if (event->modifiers() == Qt::AltModifier) {

        } else {
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    } else if (event->button() == Qt::RightButton) {
        event->ignore();
    }

    lastPoint = event->scenePos();
    this->setPos(m_x,m_y);
    this->scene()->update();
}

void VisionEllipseItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
//    QGraphicsItem::mouseReleaseEvent(event);  //注释此行，可以解决在椭圆外部，外切矩形内部，区域点击，达到取消椭圆的选中状态，，，具体原因暂时不确定
    emit signal_Release("Ellipse");
    emit signal_SizeChanged(this);
}

void VisionEllipseItem::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    if(!m_bEdit)
        return;
    qreal iTemp = 10;
    QRectF rect1 = QRectF(m_x+m_width/2-iTemp,m_y-iTemp,2*iTemp,2*iTemp);
    QRectF rect2 = QRectF(m_x+m_width-iTemp,m_y+m_height/2-iTemp,2*iTemp,2*iTemp);
    QRectF rect3 = QRectF(m_x+m_width/2-iTemp,m_y+m_height-iTemp,2*iTemp,2*iTemp);
    QRectF rect4 = QRectF(m_x-iTemp,m_y+m_height/2-iTemp,2*iTemp,2*iTemp);

    qreal qx = event->scenePos().x();
    qreal qy = event->scenePos().y();

    QGraphicsView *view = this->scene()->views().at(0);

    if(rect1.contains(event->scenePos())){
        //top point
        this->setCursor(Qt::SizeVerCursor);
        directCursor = top_rect;
    }else if(rect2.contains(event->scenePos())){
        //right point
        this->setCursor(Qt::SizeHorCursor);
        directCursor = right_rect;
    }else if(rect3.contains(event->scenePos())){
        //bottom point
        this->setCursor(Qt::SizeVerCursor);
        directCursor = bottom_rect;
    }else if(rect4.contains(event->scenePos())){
        //left point
        this->setCursor(Qt::SizeHorCursor);
        directCursor = left_rect;
    }else{
        this->setCursor(Qt::ArrowCursor);
        directCursor = normal_rect;
    }
}

void VisionEllipseItem::mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event)
{
}

void VisionEllipseItem::contextMenuEvent(QGraphicsSceneContextMenuEvent *event)
{
    qDebug()<<"mouse right clicked";
}

void VisionEllipseItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    painter->setPen(QPen(QBrush(penColor),0));
    painter->drawEllipse(QRectF(0,0,m_width,m_height));


    if(option->state & QStyle::State_Selected){
        m_bEdit = true;
        painter->setPen(QPen(QColor(255,0,0),0));
        painter->setBrush(QBrush(QColor(255,0,0)));

        qreal iTemp = 5;
        painter->drawRect(m_width/2-iTemp,-iTemp,2*iTemp,2*iTemp); //top
        painter->drawRect(m_width-iTemp,m_height/2-iTemp,2*iTemp,2*iTemp); //right
        painter->drawRect(m_width/2-iTemp,m_height-iTemp,2*iTemp,2*iTemp);  //bottom
        painter->drawRect(-iTemp,+m_height/2-iTemp,2*iTemp,2*iTemp); //left
    }else{
        m_bEdit = false;
    }
}
