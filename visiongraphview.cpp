#include "visiongraphview.h"
#include "qdebug.h"
#include "visiongraphscene.h"

VisionGraphView::VisionGraphView(QWidget *parent):
    QGraphicsView(parent)
{
    this->setMouseTracking(true);//捕捉鼠标移动信息
}

void VisionGraphView::setDrawPath(QPainterPath path1, QPainterPath path2, Operation_enum opera)
{
    m_path1 = path1;
    m_path2 = path2;
    m_opera = opera;
    this->update();
}

void VisionGraphView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
//    qDebug()<<event->pos();
    emit signal_Move();
    if(m_bPainer){
        m_lstPoint.push_back(event->pos());
    }
    this->scene()->update();
}

void VisionGraphView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
    m_lastPointF = event->screenPos();

    zoom = zoom+0.2;

    QMatrix matrix;
    matrix.scale(zoom, zoom);
    this->setMatrix(matrix);

    if(m_bPainer){
        m_lstPoint.push_back(event->pos());
    }
    this->scene()->update();
}

void VisionGraphView::paintEvent(QPaintEvent *event)
{
    QGraphicsView::paintEvent(event);



    QPainter painter(this->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(QPen(QColor(255,0,0),10));
    painter.setBrush(Qt::red);


    return;

//    QPainterPath path_end;
//    if(m_opera == AND){
//        path_end = (m_path1+m_path2)-(m_path1-m_path2)-(m_path2-m_path1);  //交集
//    }else if(m_opera == OR){
//        path_end = m_path1.united(m_path2);  //合并
//    }else if(m_opera == NOR){
//        path_end = (m_path2-m_path1)+(m_path1-m_path2);  ///异或--交集的取反
//    }else if(m_opera == SUB){
//        path_end = m_path1.subtracted(m_path2); // 扣掉圆  差集
//    }else
//        return;

//    painter.setPen(QPen(QColor(255,0,0),0));
//    painter.setBrush(Qt::lightGray);
//    painter.drawPath(path_end);


    if(m_bPainer){
        painter.setPen(QPen(QColor(255,0,0),0));
        painter.setBrush(Qt::red);

        if(m_lstPoint.count() == 1){
            painter.drawEllipse(m_lstPoint[0],m_qCircleR,m_qCircleR);
        }else{
            for(int i=0;i<m_lstPoint.count()-1;i++){
                painter.drawEllipse(m_lstPoint[i],m_qCircleR,m_qCircleR);
                //获取两点之间的矩形区域，用QPolygonF表示，并绘制
                //通过获取四个区域的四点，注意，四个点都是圆的切点，
//                A = Y2 - Y1
//                B = X1 - X2
//                C = X2*Y1 - X1*Y2
                qreal a = m_lstPoint[i+1].y() - m_lstPoint[i].y();
                qreal b = m_lstPoint[i].x() - m_lstPoint[i+1].x();
//                qreal c = m_lstPoint[i+1].x()*m_lstPoint[i].y() - m_lstPoint[i].x()*m_lstPoint[i+1].y();
                //ax+by+c=0; 直线和圆相切得到四个点    圆心到线的距离等于半径
//                qreal l = fabs((a*m_lstPoint[i].x()+b*m_lstPoint[i].y()+c)/sqrt(a*a+b*b));
                qreal c1 = m_qCircleR*sqrt(a*a+b*b) - (a*m_lstPoint[i].x()+b*m_lstPoint[i].y());
                qreal c2 = -m_qCircleR*sqrt(a*a+b*b) - (a*m_lstPoint[i].x()+b*m_lstPoint[i].y());
                //求过圆1和圆2的并且和l1和l2垂直的线的方程
                //la(圆1):bx-ay+ca = 0;  ca = ay-bx
                qreal ca = a*m_lstPoint[i].y() - b*m_lstPoint[i].x();

                //lb(圆2):bx-ay+cb = 0;
                qreal cb = a*m_lstPoint[i+1].y() - b*m_lstPoint[i+1].x();

                //A1x+B1x+C1=0;A2x+B2y+C2=0
                //if(A1*B2-A2*B1 != 0) 有唯一解  x=(B1*C2-B2*C1)/(A1*B2-A2*B1）  y=-(A1*C2-A2*C1)/(A1*B2-A2*B1）

                //与圆得到切点p --- 不容易求，计算过圆心的和l1垂直的线即可轻松得到交点
                //l1:ax+by+c1=0;   la:bx-ay+ca = 0; p1
                QPointF p1 = QPointF((b*ca-(-a)*c1)/(a*(-a)-b*b),-(a*ca-b*c1)/(a*(-a)-b*b));

                //l1:ax+by+c1=0;  lb:bx-ay+cb = 0; p2
                QPointF p2 = QPointF((b*cb-(-a)*c1)/(a*(-a)-b*b),-(a*cb-b*c1)/(a*(-a)-b*b));

                //l2:ax+by+c2=0;   lb:bx-ay+cb = 0; p3
                QPointF p3 = QPointF((b*cb-(-a)*c2)/(a*(-a)-b*b),-(a*cb-b*c2)/(a*(-a)-b*b));

                //l2:ax+by+c2=0;   la:bx-ay+ca = 0; p4
                QPointF p4 = QPointF((b*ca-(-a)*c2)/(a*(-a)-b*b),-(a*ca-b*c2)/(a*(-a)-b*b));

                QVector<QPointF> vec;
                vec.clear();
                vec.push_back(p1);
                vec.push_back(p2);
                vec.push_back(p3);
                vec.push_back(p4);

                QPolygonF polygonF(vec);
                painter.drawPolygon(polygonF);

                painter.drawEllipse(m_lstPoint[i+1],m_qCircleR,m_qCircleR);
            }
        }

    }

}

void VisionGraphView::setLines(QVector<QLineF> lines)
{
    m_lstLines = lines;
    this->update();
}

void VisionGraphView::setPainterCursor(bool painterCursor)
{
    if(painterCursor){
        //修改鼠标为绘图样式
        QCursor cursor = QCursor(QPixmap(":/cursor-sizeh.png"));
        this->setCursor(cursor);

    }else{
        this->setCursor(Qt::ArrowCursor);
    }
}
