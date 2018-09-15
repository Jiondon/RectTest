#include "visionrectitem_rotate.h"
#include <QDebug>
#include <QCursor>
#include <QtMath>
#include <QMatrix>
#include <QPixmap>

#define pi 3.1415926

VisionRectItem_Rotate::VisionRectItem_Rotate(QGraphicsItem *parent) : QGraphicsItem(parent)
{
    setAcceptHoverEvents(true);
    setFlag(QGraphicsItem::ItemIsMovable,true);
    setFlag(QGraphicsItem::ItemIsSelectable,true);
}

void VisionRectItem_Rotate::setRect(qreal x, qreal y, qreal width, qreal height)
{
    m_width = width;
    m_height = height;
    m_x = x;
    m_y = y;
    m_centerX = m_x+m_width/2;
    m_centerY = m_y+m_height/2;

    initItem();
    //当控件被移动的时候，重新设置下坐标中心点（mouseMoveEvent）
    m_transform.translate(m_centerX,m_centerY);
    // 平移
    this->setPos(m_x,m_y);

    arrowsItem = new VisionArrows_Rotate(m_width,m_height/2-5,30,10,QColor(255,0,0),this);
    connect(arrowsItem,SIGNAL(signalHoverEnter()),this,SLOT(slotArrowsItem()));
    connect(arrowsItem,SIGNAL(signalHoverLeave()),this,SLOT(slotArrowsItem_leave()));

}

void VisionRectItem_Rotate::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget)
    Q_UNUSED(option)

    //旋转之前，先将旋转的坐标系设置到控件的中心处，

    painter->setTransform(m_transform);
    painter->rotate(m_angle);

    painter->setPen(QPen(QBrush(penColor),0));
//    painter->drawRect(QRectF(0,0,m_width,m_height));
    //更换坐标系后的位置重新设置
    painter->drawRect(QRectF(-m_width/2,-m_height/2,m_width,m_height));

    //item pos ()
    if(option->state & QStyle::State_Selected){
        //编辑模式下的小矩形框
        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(true);
        }
        m_bEdit = true;
    }else{
        for(int i=0;i<m_lstRect.count();i++){
            m_lstRect[i]->setVisible(false);
        }
        m_bEdit = false;
        if(directCursor != arrowsUp){
            this->setCursor(Qt::ArrowCursor);
            directCursor = normal_rect;
        }
    }
}

QRectF VisionRectItem_Rotate::boundingRect() const
{
    //为方便旋转后的区域变化问题，临时的将有效区域设置为圆（直径为矩形的对角线）
    qreal r = sqrt((m_width)*(m_width)+(m_height)*(m_height));
//    qDebug()<<m_width<<m_height<<r;
    QRectF rf = QRectF(-5-10,-5-10,r+20,r+20);
//    QRectF rf = QRectF(-5,-5,m_width+5+10+10,m_height+5+10+10);
    return rf;
}

void VisionRectItem_Rotate::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //鼠标左键
    QGraphicsItem::mousePressEvent(event);

    //过滤掉在boundingRect但是不在绘制的有效区域的点击

    //四个边角的点的坐标，依次为 m_lstRect[0] m_lstRect[2] m_lstRect[4] m_lstRect[6]
    //0-2  2-4 两条线，剩余两条线，直接平移可获得
    //4-6  6-0 两条线 采用平移需要考虑竖直的情况，采用每条线的方程直接表示出来
    qreal a1 = (m_lstRect[0]->pos().x()-m_lstRect[2]->pos().x());
    qreal b1 = (m_lstRect[0]->pos().y()-m_lstRect[2]->pos().y());
    qreal c1 = - (m_lstRect[0]->pos().x()-m_lstRect[2]->pos().x())*m_lstRect[0]->pos().x() - (m_lstRect[0]->pos().y()-m_lstRect[2]->pos().y())*m_lstRect[0]->pos().y();
    //线的直线方程 (m_lstRect[0]-m_lstRect[2])*x - (m_lstRect[0]-m_lstRect[2])*y - (m_lstRect[0]-m_lstRect[2])*m_lstRect[0] +(m_lstRect[0]-m_lstRect[2])*m_lstRect[0]
    qreal h1 = fabs((a1*event->pos().x()+b1*event->pos().y()+c1)/sqrt(a1*a1+b1*b1));

    qreal a2 = (m_lstRect[4]->pos().x()-m_lstRect[6]->pos().x());
    qreal b2 = (m_lstRect[4]->pos().y()-m_lstRect[6]->pos().y());
    qreal c2 = - (m_lstRect[4]->pos().x()-m_lstRect[6]->pos().x())*m_lstRect[4]->pos().x() - (m_lstRect[4]->pos().y()-m_lstRect[6]->pos().y())*m_lstRect[4]->pos().y();
    qreal h2 = fabs((a2*event->pos().x()+b2*event->pos().y()+c2)/sqrt(a2*a2+b2*b2));


    qreal a3 = (m_lstRect[2]->pos().x()-m_lstRect[4]->pos().x());
    qreal b3 = (m_lstRect[2]->pos().y()-m_lstRect[4]->pos().y());
    qreal c3 = - (m_lstRect[2]->pos().x()-m_lstRect[4]->pos().x())*m_lstRect[2]->pos().x() - (m_lstRect[2]->pos().y()-m_lstRect[4]->pos().y())*m_lstRect[2]->pos().y();
    qreal h3 = fabs((a3*event->pos().x()+b3*event->pos().y()+c3)/sqrt(a3*a3+b3*b3));

    qreal a4 = (m_lstRect[6]->pos().x()-m_lstRect[0]->pos().x());
    qreal b4 = (m_lstRect[6]->pos().y()-m_lstRect[0]->pos().y());
    qreal c4 = - (m_lstRect[6]->pos().x()-m_lstRect[0]->pos().x())*m_lstRect[6]->pos().x() - (m_lstRect[6]->pos().y()-m_lstRect[0]->pos().y())*m_lstRect[6]->pos().y();
    qreal h4 = fabs((a4*event->pos().x()+b4*event->pos().y()+c4)/sqrt(a4*a4+b4*b4));
        qDebug()<<h1+h2<<h3+h4<<m_width<<m_height<<event->pos();
    //得到四个直线方程，然后相对的两条直线之间的距离是固定的，点在矩形的内部，则满足 到相对的两条直线的距离是固定的分别是h和w
    // <和+1是为了防止出现四舍五入导致数据不能绝对的等于，-- 理论上四舍五入不会出现这样的情况，但是为了保险起见,+5考虑到编辑状态下的小边框
    if(!(h1+h2 <= m_width+10+2 && h3+h4 <= m_height+10+2)){
//        qDebug()<<" 111111111111111111111111111111111   waibu waibu ";
        setSelected(false);
        this->scene()->update();
        return;
    }


    if (event->button() == Qt::LeftButton) {
        if (event->modifiers() == Qt::ShiftModifier) {
//            qDebug() << "visionItem left clicked with SHIFT key.";
            // 选中 item
        } else if (event->modifiers() == Qt::AltModifier) {

        } else {
            setSelected(true);
            qDebug() << "Custom item left clicked.";
            QGraphicsItem::mousePressEvent(event);
            event->accept();
        }
    } else if (event->button() == Qt::RightButton) {
        event->ignore();
    }

    lastPoint = event->scenePos();
    lastPointF = event->pos();
    this->setPos(m_x,m_y);
    this->scene()->update();
}

void VisionRectItem_Rotate::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    qreal a1 = (m_lstRect[0]->pos().x()-m_lstRect[2]->pos().x());
    qreal b1 = (m_lstRect[0]->pos().y()-m_lstRect[2]->pos().y());
    qreal c1 = - (m_lstRect[0]->pos().x()-m_lstRect[2]->pos().x())*m_lstRect[0]->pos().x() - (m_lstRect[0]->pos().y()-m_lstRect[2]->pos().y())*m_lstRect[0]->pos().y();
    //线的直线方程 (m_lstRect[0]-m_lstRect[2])*x - (m_lstRect[0]-m_lstRect[2])*y - (m_lstRect[0]-m_lstRect[2])*m_lstRect[0] +(m_lstRect[0]-m_lstRect[2])*m_lstRect[0]
    qreal h1 = fabs((a1*event->pos().x()+b1*event->pos().y()+c1)/sqrt(a1*a1+b1*b1));

    qreal a2 = (m_lstRect[4]->pos().x()-m_lstRect[6]->pos().x());
    qreal b2 = (m_lstRect[4]->pos().y()-m_lstRect[6]->pos().y());
    qreal c2 = - (m_lstRect[4]->pos().x()-m_lstRect[6]->pos().x())*m_lstRect[4]->pos().x() - (m_lstRect[4]->pos().y()-m_lstRect[6]->pos().y())*m_lstRect[4]->pos().y();
    qreal h2 = fabs((a2*event->pos().x()+b2*event->pos().y()+c2)/sqrt(a2*a2+b2*b2));


    qreal a3 = (m_lstRect[2]->pos().x()-m_lstRect[4]->pos().x());
    qreal b3 = (m_lstRect[2]->pos().y()-m_lstRect[4]->pos().y());
    qreal c3 = - (m_lstRect[2]->pos().x()-m_lstRect[4]->pos().x())*m_lstRect[2]->pos().x() - (m_lstRect[2]->pos().y()-m_lstRect[4]->pos().y())*m_lstRect[2]->pos().y();
    qreal h3 = fabs((a3*event->pos().x()+b3*event->pos().y()+c3)/sqrt(a3*a3+b3*b3));

    qreal a4 = (m_lstRect[6]->pos().x()-m_lstRect[0]->pos().x());
    qreal b4 = (m_lstRect[6]->pos().y()-m_lstRect[0]->pos().y());
    qreal c4 = - (m_lstRect[6]->pos().x()-m_lstRect[0]->pos().x())*m_lstRect[6]->pos().x() - (m_lstRect[6]->pos().y()-m_lstRect[0]->pos().y())*m_lstRect[6]->pos().y();
    qreal h4 = fabs((a4*event->pos().x()+b4*event->pos().y()+c4)/sqrt(a4*a4+b4*b4));

    if(!(h1+h2 <= m_height+5 && h3+h4 <= m_width+5)){
        return;
    }
    QGraphicsItem::mouseReleaseEvent(event);
}

void VisionRectItem_Rotate::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    qDebug()<<directCursor;
    if(directCursor != arrowsUp){
        if(!m_bEdit){
            return;
        }
        //计算两次move的鼠标的差值，
        //计算两次move的鼠标的差值，
        QPointF curPoint = event->scenePos();
        QPointF disPoint = curPoint - lastPoint;
        QPointF linePoint = lastPoint;
        lastPoint = curPoint;
        lastPointF = event->pos();
        QGraphicsItem::mouseMoveEvent(event);

        //在获得坐标的时候，可换算出，该坐标相对于不是旋转的图形的情况下，坐标是多少
        //（中心点已知，圆上一点已知，角度已知，求另一点坐标）--用cos获取角度，区分第一第二象限和第三第四象限
        //获取旋转后的坐标的角度
//        qreal disW = sqrt((lastPoint.x()-event->scenePos().x())*(lastPoint.x()-event->scenePos().x())+(lastPoint.y()-event->scenePos().y())*(lastPoint.y()-event->scenePos().y()));

        qreal originX = linePoint.x();
        qreal originY = linePoint.y();
        qreal disX = event->scenePos().x()-originX;
        qreal disY = event->scenePos().y()-originY;
        qreal disZ = sqrt(disX*disX+disY*disY);
        qreal angle1 = acos(disX/disZ);
        qDebug()<<"111111111111111111111111 :: "<<angle1<<"disW : "<<"disZ : "<<disZ;

        //判断坐标系，采用pos来是吧，相对于item的坐标系

//        qreal alph = acos(x/z);
//        m_angle = 360 - (alph*180)/3.14159;

        if(event->pos().y() > 0){
            //1,2象限
            angle1 = (angle1*180)/pi;
        }else{
            //3,4象限  角度加上 PAI
            angle1 = 360-((angle1*180)/pi);
        }
        angle1 = angle1 - m_angle;
        qreal qx = disZ*cos(angle1);
        qreal qy = disZ*sin(angle1);
        qDebug()<<qx<<qy;
//        disPoint.setX(qx);
//        disPoint.setY(qy);
        //()

        if(directCursor == normal_rect){
            m_x = m_x + disPoint.x();
            m_y = m_y + disPoint.y();

            m_centerX = m_x+m_width/2;
            m_centerY = m_y+m_height/2;
            //当控件被移动的时候，重新设置下坐标中心点（mouseMoveEvent）  //因为控件坐标系已经变化了，故不能再设置成m_transform.translate(m_centerX,m_centerY);
            m_transform.translate(disPoint.x(),disPoint.y());
            // 平移
//            qDebug()<<boundingRect()<<m_x<<m_y;

        }else{

            /*
            //当没有旋转的时候，拉伸所处理的本质就是点到线的距离，当需要哪一边的变化的时候，直接处理点到该边的距离
            //当旋转的时候，相同的处理---修改实现方式，直接使用坐标和角度计算是错误的思路，改成，拉伸的点的变化，直接计算点到线的距离，来进行刷新
            //关键的问题在于，如何更好地计算得到结果，两点确定直线，然后直接计算点到直线的距离，此时由坐标计算得到位置改成直接通过线的距离来计算得到位置

            //获取四个边的直线方程
            QPointF eventPos = event->pos();

            qreal a1 = (m_lstRect[0]->pos().x()-m_lstRect[2]->pos().x());
            qreal b1 = (m_lstRect[0]->pos().y()-m_lstRect[2]->pos().y());
            qreal c1 = - (m_lstRect[0]->pos().x()-m_lstRect[2]->pos().x())*m_lstRect[0]->pos().x() - (m_lstRect[0]->pos().y()-m_lstRect[2]->pos().y())*m_lstRect[0]->pos().y();
            //线的直线方程 (m_lstRect[0]-m_lstRect[2])*x - (m_lstRect[0]-m_lstRect[2])*y - (m_lstRect[0]-m_lstRect[2])*m_lstRect[0] +(m_lstRect[0]-m_lstRect[2])*m_lstRect[0]
            qreal h1 = fabs((a1*eventPos.x()+b1*eventPos.y()+c1)/sqrt(a1*a1+b1*b1));

            qreal a2 = (m_lstRect[4]->pos().x()-m_lstRect[6]->pos().x());
            qreal b2 = (m_lstRect[4]->pos().y()-m_lstRect[6]->pos().y());
            qreal c2 = - (m_lstRect[4]->pos().x()-m_lstRect[6]->pos().x())*m_lstRect[4]->pos().x() - (m_lstRect[4]->pos().y()-m_lstRect[6]->pos().y())*m_lstRect[4]->pos().y();
            qreal h2 = fabs((a2*eventPos.x()+b2*eventPos.y()+c2)/sqrt(a2*a2+b2*b2));


            qreal a3 = (m_lstRect[2]->pos().x()-m_lstRect[4]->pos().x());
            qreal b3 = (m_lstRect[2]->pos().y()-m_lstRect[4]->pos().y());
            qreal c3 = - (m_lstRect[2]->pos().x()-m_lstRect[4]->pos().x())*m_lstRect[2]->pos().x() - (m_lstRect[2]->pos().y()-m_lstRect[4]->pos().y())*m_lstRect[2]->pos().y();
            qreal h3 = fabs((a3*eventPos.x()+b3*eventPos.y()+c3)/sqrt(a3*a3+b3*b3));

            qreal a4 = (m_lstRect[6]->pos().x()-m_lstRect[0]->pos().x());
            qreal b4 = (m_lstRect[6]->pos().y()-m_lstRect[0]->pos().y());
            qreal c4 = - (m_lstRect[6]->pos().x()-m_lstRect[0]->pos().x())*m_lstRect[6]->pos().x() - (m_lstRect[6]->pos().y()-m_lstRect[0]->pos().y())*m_lstRect[6]->pos().y();
            qreal h4 = fabs((a4*eventPos.x()+b4*eventPos.y()+c4)/sqrt(a4*a4+b4*b4));

            //点到需要获取的该边的距离  h1--top  h2--bottom h3--right  h4--left
            */

            //上述思路没错，但是线是错的，线不应该是边框的线，而是，过上一个点的线，而且是两条线，分别和四边形的相邻两条边垂直
            QPointF eventPos = event->scenePos();

            //Ax+By+C=0 -- 原方程
            //Bx-Ay+C=0 -- 与原方程垂直的方程
            qreal a1 = (m_lstRect[0]->pos().x()-m_lstRect[2]->pos().x());
            qreal b1 = (m_lstRect[0]->pos().y()-m_lstRect[2]->pos().y());
            qreal c1 =  a1*linePoint.y() - b1*linePoint.x();
            //线的直线方程 (m_lstRect[0]-m_lstRect[2])*x - (m_lstRect[0]-m_lstRect[2])*y - (m_lstRect[0]-m_lstRect[2])*m_lstRect[0] +(m_lstRect[0]-m_lstRect[2])*m_lstRect[0]
            qreal h1 = fabs((b1*eventPos.x()-a1*eventPos.y()+c1)/sqrt(a1*a1+b1*b1));

            qreal h2 = h1;


            qreal a3 = (m_lstRect[2]->pos().x()-m_lstRect[4]->pos().x());
            qreal b3 = (m_lstRect[2]->pos().y()-m_lstRect[4]->pos().y());
            qreal c3 =  a3*linePoint.y() - b3*linePoint.x();
            qreal h3 = fabs((b3*eventPos.x()-a3*eventPos.y()+c3)/sqrt(a3*a3+b3*b3));

            qreal h4 = h3;

            qDebug()<<h1<<h3<<event->pos();
            qreal angle = m_angle;

            /*
            if(directCursor == top_rect){
                //top point
                if(disPoint.y() < 0){
                    //往外拉
                    m_y = m_y - h1*(cos(angle));
                    m_height = m_height + h1;
                }else{
                    m_y = m_y + h1*(cos(angle));
                    m_height = m_height - h1;
                }
//                m_y = m_y + disPoint.y();
//                m_height = m_height - disPoint.y();

            }else if(directCursor == right_rect){
                //right point
                if(disPoint.x() > 0){
                    //往外拉
                    m_width = m_width + h3;
                }else{
                    m_width = m_width - h3;
                }
//                m_width = m_width + disPoint.x();

            }else if(directCursor == bottom_rect){
                //bottom point
                if(disPoint.y() > 0){
                    //往外拉
                    m_height = m_height + h2;
                }else{
                    m_height = m_height - h2;
                }
//                m_height = m_height + disPoint.y();

            }else if(directCursor == left_rect){
                //left point
                if(disPoint.x() < 0){
                    //往外拉
                    m_x = m_x - h4*(cos(angle));
                    m_width = m_width + h4;
                }else{
                    m_x = m_x + h4*(cos(angle));
                    m_width = m_width - h4;
                }
//                m_x = m_x + disPoint.x();
//                m_width = m_width - disPoint.x();
            }else if(directCursor == left_Top_rect){
                //left top
                if(disPoint.x() < 0){
                    //往外拉
                    m_x = m_x - h4*(cos(angle));
                    m_width = m_width + h4;
                }else{
                    m_x = m_x + h4*(cos(angle));
                    m_width = m_width - h4;
                }
                if(disPoint.y() < 0){
                    //往外拉
                    m_y = m_y - h1*(cos(angle));
                    m_height = m_height + h1;
                }else{
                    m_y = m_y + h1*(cos(angle));
                    m_height = m_height - h1;
                }

//                m_x = m_x + disPoint.x();
//                m_y = m_y + disPoint.y();
//                m_width = m_width - disPoint.x();
//                m_height = m_height - disPoint.y();
            } else if(directCursor == left_bottom_rect){
                if(disPoint.x() < 0){
                    //往外拉
                    m_x = m_x - h4*fabs(cos(angle));
                    m_width = m_width + h4;
                }else{
                    m_x = m_x + h4*fabs(cos(angle));
                    m_width = m_width - h4;
                }
                if(disPoint.y() > 0){
                    //往外拉
                    m_height = m_height + h2;
                }else{
                    m_height = m_height - h2;
                }

//                m_x = m_x + disPoint.x();

//                m_width = m_width - disPoint.x();
//                m_height = m_height + disPoint.y();
            } else if(directCursor == right_top_rect){
                if(disPoint.x() > 0){
                    //往外拉
                    m_width = m_width + h3;
                }else{
                    m_width = m_width - h3;
                }
                if(disPoint.y() < 0){
                    //往外拉
                    m_y = m_y - h1*fabs(cos(angle));
                    m_height = m_height + h1;
                }else{
                    m_y = m_y + h1*fabs(cos(angle));
                    m_height = m_height - h1;
                }
//                m_y = m_y + disPoint.y();

//                m_width = m_width + disPoint.x();
//                m_height = m_height - disPoint.y();
            }else if(directCursor == right_bottom_rect){
                if(disPoint.x() > 0){
                    //往外拉
                    m_width = m_width + h3;
                }else{
                    m_width = m_width - h3;
                }

                if(disPoint.y() > 0){
                    //往外拉
                    m_height = m_height + h2;
                }else{
                    m_height = m_height - h2;
                }
//                m_width = m_width + disPoint.x();
//                m_height = m_height + disPoint.y();
            }
            else{
                qDebug()<<"error directCursor";
            }

            */


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
            }else if(directCursor == left_Top_rect){
                //left top
                m_x = m_x + disPoint.x();
                m_y = m_y + disPoint.y();
                m_width = m_width - disPoint.x();
                m_height = m_height - disPoint.y();
            } else if(directCursor == left_bottom_rect){
                m_x = m_x + disPoint.x();

                m_width = m_width - disPoint.x();
                m_height = m_height + disPoint.y();
            } else if(directCursor == right_top_rect){
                m_y = m_y + disPoint.y();

                m_width = m_width + disPoint.x();
                m_height = m_height - disPoint.y();
            }else if(directCursor == right_bottom_rect){
                m_width = m_width + disPoint.x();
                m_height = m_height + disPoint.y();
            }
            else{
                qDebug()<<"error directCursor";
            }


            if(m_width < 1)
                m_width = 1;
            if(m_height < 1)
                m_height = 1;

            //中心原点，在item存在倾角的情况下，不可以直接进行赋值，需要经过角度换算才能得到相关的大小。

            //偏移的直线距离，通过旋转角度计算得到直线坐标的偏移量，就是中心点的偏移坐标
            qreal tempX = m_x+m_width/2 - m_centerX;
            qreal tempY = m_y+m_height/2 - m_centerY;
            m_centerX =  m_x+m_width/2;
            m_centerY = m_y+m_height/2;


            //由于坐标x y的偏移导致同步的偏移
//            qreal r = sqrt((m_width/2)*(m_width/2)+(m_height/2)*(m_height/2));
//            qreal tempX = m_x+r*cos(m_angle) - m_centerX;
//            qreal tempY = m_y+r*sin(m_angle) - m_centerY;
//            m_centerX =  m_x+r*cos(m_angle);
//            m_centerY = m_y+r*sin(m_angle);
            //当控件被移动的时候，重新设置下坐标中心点（mouseMoveEvent） 此处设置原点，应该在上次的控件的坐标系的基础上进行设置，（同时要记录对应的中心点）
//            m_transform.translate(tempX,tempY);
            // 平移

            //new 中心点为对角线的中点，故可用下面的逻辑实现设置旋转的中点 -- 测试不可用
            m_transform.translate(tempX,tempY);
        }
        this->setPos(m_x,m_y);
    }else{
        qDebug()<<"arrow up";
        qreal x = event->pos().x();
        qreal y = event->pos().y();
        qreal z = sqrt(x*x+y*y);

        qDebug()<<event->pos();
        if(y >= 0){
            //第一和第二象限
            qreal alph = acos(x/z);
            m_angle = (alph*180)/3.14159;
        }else{
            //第三和第四象限
            qreal alph = acos(x/z);
            m_angle = 360 - (alph*180)/3.14159;
        }
    }
    updateItem();
    this->scene()->update();
}

void VisionRectItem_Rotate::hoverMoveEvent(QGraphicsSceneHoverEvent *event)
{
    QGraphicsItem::hoverMoveEvent(event);
}

void VisionRectItem_Rotate::initItem()
{
    m_lstRect.clear();

    qDebug()<<m_x<<m_y<<m_width<<m_height;
    MiniRect* miniRect1 = new MiniRect(-5,-5,10,10,QColor(255,0,0),this);
    miniRect1->setIndex(0);
    connect(miniRect1,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect2 = new MiniRect(-5+m_width/2,-5,10,10,QColor(255,0,0),this);
    miniRect2->setIndex(1);
    miniRect2->setParent(this);
    connect(miniRect2,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect3 = new MiniRect(-5+m_width,-5,10,10,QColor(255,0,0),this);
    miniRect3->setIndex(2);
    connect(miniRect3,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect4 = new MiniRect(-5+m_width,-5+m_height/2,10,10,QColor(255,0,0),this);
    miniRect4->setIndex(3);
    connect(miniRect4,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect5 = new MiniRect(-5+m_width,-5+m_height,10,10,QColor(255,0,0),this);
    miniRect5->setIndex(4);
    connect(miniRect5,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect6 = new MiniRect(-5+m_width/2,-5+m_height,10,10,QColor(255,0,0),this);
    miniRect6->setIndex(5);
    connect(miniRect6,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect7 = new MiniRect(-5,-5+m_height,10,10,QColor(255,0,0),this);
    miniRect7->setIndex(6);
    connect(miniRect7,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    MiniRect* miniRect8 = new MiniRect(-5,-5+m_height/2,10,10,QColor(255,0,0),this);
    miniRect8->setIndex(7);
    connect(miniRect8,SIGNAL(signalIndex(int)),this,SLOT(slotIndex(int)));

    m_lstRect.append(miniRect1);
    m_lstRect.append(miniRect2);
    m_lstRect.append(miniRect3);
    m_lstRect.append(miniRect4);
    m_lstRect.append(miniRect5);
    m_lstRect.append(miniRect6);
    m_lstRect.append(miniRect7);
    m_lstRect.append(miniRect8);

}

void VisionRectItem_Rotate::updateItem()
{
    qDebug()<<m_x<<m_y<<m_width<<m_height;
    qreal x;
    qreal y;
    QRectF rf = boundingRect();
    //由于当w和h变化的时候，对于的对角线的角度就会变好，
    qreal angle = atan(m_height/m_width);
    qreal r = sqrt((m_width/2)*(m_width/2)+(m_height/2)*(m_height/2));

    qreal w1 = arrowsItem->boundingRect().width();
    qreal h1 = arrowsItem->boundingRect().height();
    qreal x1 = (m_width/2+w1/2)*cos(m_angle*pi/180)+m_width/2;
    qreal y1 = (m_width/2+w1/2)*sin(m_angle*pi/180)+m_height/2;
    //update arrowItem
    arrowsItem->setPos(x1-w1/2,y1-h1/2);
    arrowsItem->setRotation(m_angle);

    //update miniRect
    for(int i=0;i<m_lstRect.count();i++){

        if(i == 0){
            x = r*cos(angle+pi+m_angle*pi/180)+m_width/2;
            y = r*sin(angle+pi+m_angle*pi/180)+m_height/2;

        }else if(i == 1){
            x = (m_height/2)*cos(pi*3/2+m_angle*pi/180)+m_width/2;
            y = (m_height/2)*sin(pi*3/2+m_angle*pi/180)+m_height/2;

        }else if(i == 2){
            x = r*cos(2*pi-angle+m_angle*pi/180)+m_width/2;
            y = r*sin(2*pi-angle+m_angle*pi/180)+m_height/2;

        }else if(i == 3){
            x = (m_width/2)*cos(m_angle*pi/180)+m_width/2;
            y = (m_width/2)*sin(m_angle*pi/180)+m_height/2;

        }else if(i == 4){
            x = r*cos(angle+m_angle*pi/180)+m_width/2;
            y = r*sin(angle+m_angle*pi/180)+m_height/2;

        }else if(i == 5){
            x = (m_height/2)*cos(pi/2+m_angle*pi/180)+m_width/2;
            y = (m_height/2)*sin(pi/2+m_angle*pi/180)+m_height/2;

        }else if(i == 6){
            x = r*cos(pi-angle+m_angle*pi/180)+m_width/2;
            y = r*sin(pi-angle+m_angle*pi/180)+m_height/2;

        }else if(i == 7){
            x = (m_width/2)*cos(pi+m_angle*pi/180)+m_width/2;
            y = (m_width/2)*sin(pi+m_angle*pi/180)+m_height/2;

        }
        m_lstRect[i]->setPos(x-5,y-5);
        m_lstRect[i]->setRotation(m_angle);
    }
}

void VisionRectItem_Rotate::slotIndex(int index)
{
    //可以将对于的miniRect的鼠标样式修改下
//    qDebug()<<"click miniRect : "<<index;
    m_bCircle = false;
    QMatrix leftmatrix;
    leftmatrix.rotate(m_angle);
    QCursor cursor;

    if(index == 7){
        //left
        directCursor = left_rect;
//        this->setCursor(Qt::SizeHorCursor);

        cursor = QCursor(QPixmap(":/cursor-sizeh.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else if(index == 0){
        //left top
        directCursor = left_Top_rect;
//        this->setCursor(Qt::SizeFDiagCursor);

        cursor = QCursor(QPixmap(":/cursor-sizef.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else if(index == 1){
        //top
        directCursor = top_rect;
//        this->setCursor(Qt::SizeVerCursor);

        cursor = QCursor(QPixmap(":/cursor-sizev.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else if(index == 2){
        //top right
        directCursor = right_top_rect;
//        this->setCursor(Qt::SizeBDiagCursor);

        cursor = QCursor(QPixmap(":/cursor-sizeb.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else if(index == 3){
        //right
        directCursor = right_rect;
//        this->setCursor(Qt::SizeHorCursor);

        cursor = QCursor(QPixmap(":/cursor-sizeh.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else if(index == 4){
        //right bottom
        directCursor = right_bottom_rect;
//        this->setCursor(Qt::SizeFDiagCursor);

        cursor = QCursor(QPixmap(":/cursor-sizef.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else if(index == 5){
        //bottom
        directCursor = bottom_rect;
//        this->setCursor(Qt::SizeVerCursor);

        cursor = QCursor(QPixmap(":/cursor-sizev.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else if(index == 6){
        //bottom left
        directCursor = left_bottom_rect;
//        this->setCursor(Qt::SizeBDiagCursor);

        cursor = QCursor(QPixmap(":/cursor-sizeb.png").transformed(leftmatrix,Qt::SmoothTransformation));
        this->setCursor(cursor);

    }else{
        directCursor = normal_rect;
        this->setCursor(Qt::ArrowCursor);
    }
}

void VisionRectItem_Rotate::slotArrowsItem()
{
    directCursor = arrowsUp;
    m_bCircle = true;
}

void VisionRectItem_Rotate::slotArrowsItem_leave()
{
    directCursor = normal_rect;
    m_bCircle = false;
}
