#include "mainwindow.h"

#include <QDebug>
#include <QtMath>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setFixedSize(800,600);

    QWidget *widget = new QWidget(this);
    view = new VisionGraphView(widget);
    connect(view,SIGNAL(signal_Move()),this,SLOT(slot_Update()));
    scene = new VisionGraphScene(widget);
//    connect(scene,SIGNAL(signal_MousePress(qreal,qreal)),this,SLOT(slot_Press(qreal,qreal)));
    scene->setSceneRect(0,0,800,600);
    view->setScene(scene);
    this->setCentralWidget(widget);
    view->setSceneRect(0,0,800,600);

    rectItem1 = new VisionRectItem(true);
    connect(rectItem1,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
    scene->addItem(rectItem1);
    rectItem1->setRect(50,50,100,100);
    m_lstItem.append(rectItem1);

//    VisionRing *item1 = new VisionRing(300,300,50,20);
//    scene->addItem(item1);

    ellipseItem1 = new VisionEllipseItem_New(true);
    connect(ellipseItem1,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
    scene->addItem(ellipseItem1);
    ellipseItem1->setRect(150,150,200,200);
    m_lstItem.append(ellipseItem1);

    ellipseItem2 = new VisionEllipseItem_New(true);
    connect(ellipseItem2,SIGNAL(signal_clicked(VisionItem*,bool,bool,qreal,qreal)),this,SLOT(slot_Press(VisionItem*,bool,bool,qreal,qreal)));
    scene->addItem(ellipseItem2);
    ellipseItem2->setRect(300,300,100,100);
    m_lstItem.append(ellipseItem2);

//    VisionLineItem *item3 = new VisionLineItem();
//    scene->addItem(item3);
//    item3->setLine(QPointF(300,300),QPointF(500,500));
//    m_lstItem.append(item3);

    VisionPoint* point = new VisionPoint();
    scene->addItem(point);
    point->setPointF(QPointF(200,200));
}

MainWindow::~MainWindow()
{

}

void MainWindow::mousePressEvent(QMouseEvent *event)
{

}

QPainterPath MainWindow::and_Item(QPainterPath path1,QPainterPath path2)
{
    //获取到一个公共的区域，将该区域的表达式传给每个item，在绘制每个item 的时候，判断绘制的点是否在公共区域，在的话绘制特殊颜色，不在的话，绘制其他颜色
    //A和B的交集 属于A并且也属于B
    return (path1+path2)-(path1-path2)-(path2-path1);
}

QPainterPath MainWindow::sub_Item(QPainterPath path1,QPainterPath path2)
{
    //A和B的差集  属于A，但不属于B的点
    return path1.subtracted(path2);
}

QPainterPath MainWindow::or_Item(QPainterPath path1,QPainterPath path2)
{
    //A和B的并集 属于A或者属于B
    return path1.united(path2);
}

QPainterPath MainWindow::nor_Item(QPainterPath path1,QPainterPath path2)
{
    //A异或B，属于A并且不属于B 或者 属于B并且不属于A
    return (path2-path1)+(path1-path2);
}

void MainWindow::slot_Update()
{
//    view->setDrawPath(and_Item(rectItem1->getPainterPath(),ellipseItem1->getPainterPath()),ellipseItem2->getPainterPath(),SUB);
    //调用算法，将关系式传给算法，获取算法的结果，绘制算法提供的结果
    //测试，虚拟点的链表
    QVector<QLineF> lstLines;
    for(int i=0;i<1000;i++){
        m_lstPainterPointF.push_back(QPointF(50+m_iTest*5,50+i));
        m_lstPainterPointF.push_back(QPointF(150+m_iTest*5,50+i));
        lstLines.push_back(QLineF(50+m_iTest*5,50+i,150+m_iTest*5,50+i));
    }

    if(m_iTest == 100){
        m_iTest = 0;
    }
    m_iTest++;
    view->setLines(lstLines);
}

void MainWindow::slot_Press(VisionItem *item, bool bSelected,bool bIn,qreal x,qreal y)
{
    //修改，该函数的触发，改成有基类VisionItem进行触发，限制在点击item的时候触发

    //修改哪些item的zValue的值，需要根据点击的pos来定位在该pos的item有哪些

    //change zValue

    //点击item，如果该item是被选中的，则直接改为未选中，同时判断其底部是否有其他的item
    //如果有，则将该item的zValue值设为5，同时将该item的状态设置为选中状态

    //需要对基类添加的函数，设置选中和未选中的接口，获取选中状态的接口,获取item的painterPath，获取坐标是否在item的有效区域内

    QList<VisionItem*> lstClickedItem;
    qDebug()<<m_lstItem.count()<<x<<y;
    for(int i=0;i<m_lstItem.count();i++){
        //点击了某一个item的无效区域，该item的z值是0，显示是in area，
        //clicked some item's uneffect area, and this item's z value is 0, this if think it is in area
        //but this item’s mousePressEvent() will think the click event is uneffect,and no deal with

        //此处判断修改，改为传输坐标给item，返回值为该坐标是否在该item内部---   true-in  false-out
        if(m_lstItem[i]->getType() == Rect){
            VisionRectItem* itemTest = (VisionRectItem*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"out of range";
            }
        }else if (m_lstItem[i]->getType() == EllipseItem) {
            VisionEllipseItem_New* itemTest = (VisionEllipseItem_New*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"out of range";
            }
        }else{
            VisionRectItem* itemTest = (VisionRectItem*)m_lstItem[i];
            if(itemTest->getPosInArea(x,y)){
                qDebug()<<"in of range";
                lstClickedItem.push_back(m_lstItem[i]);
            }else{
                qDebug()<<"out of range";
            }

        }
    }

    if(lstClickedItem.count() == 1){
        lstClickedItem[0]->setZValue(5);
        lstClickedItem[0]->setSelected(true);
        lstClickedItem[0]->scene()->update();
        return;
    }

    for(int j=0;j<lstClickedItem.count();j++){
        if(lstClickedItem[j]->isSelected()){
            qDebug()<<j<<lstClickedItem.count()-1;
            if(j == lstClickedItem.count()-1){
                qDebug()<<j;
                lstClickedItem[0]->setZValue(5);
                lstClickedItem[0]->setSelected(true);
                lstClickedItem[0]->scene()->update();
            }else{
                qDebug()<<j;
                lstClickedItem[j+1]->setZValue(5);
                lstClickedItem[j+1]->setSelected(true);
                lstClickedItem[j+1]->scene()->update();
            }
            lstClickedItem[j]->setZValue(0);
            lstClickedItem[j]->setSelected(false);
            break;
        }
    }

    qDebug()<<rectItem1->zValue()<<ellipseItem1->zValue()<<ellipseItem2->zValue();
}
