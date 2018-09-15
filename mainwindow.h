#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "visiongraphscene.h"
#include "visiongraphview.h"
#include "visionitem.h"
#include "visionwidgetitem.h"
#include "visionellipseitem.h"
#include "visionrectitem.h"
#include "visionrectitem_new.h"
#include "visionring.h"
#include "visionellipseitem_new.h"
#include "visionlineitem.h"
#include "visionpoint.h"

#include "./include/XVBase.h"
#include "./include/XVCreateRegion.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
protected:
    void mousePressEvent(QMouseEvent *event);

private:
    VisionGraphScene *scene;
    VisionGraphView *view;

    QList<VisionItem*> m_lstItem;
    QList<VisionItem*> m_lstItemSelected;
    OperationStruct m_Operation;

    VisionEllipseItem_New* ellipseItem1 = NULL;
    VisionRectItem* rectItem1 = NULL;
    VisionEllipseItem_New* ellipseItem2 = NULL;


    QPainterPath m_path1;
    QPainterPath m_path2;
    Operation_enum m_opera;

    QPainterPath m_path;


    QList<QPointF> m_lstPainterPointF;  //绘制算法提供的直线的点的集合（两两配对）

    int m_iTest = 0;

    XVCreateRegionIn regionIn;

private:
    QPainterPath and_Item(QPainterPath path1,QPainterPath path2);  //交集  &&
    QPainterPath sub_Item(QPainterPath path1,QPainterPath path2);  //差集  ！
    QPainterPath or_Item(QPainterPath path1,QPainterPath path2);  //并集 ||
    QPainterPath nor_Item(QPainterPath path1,QPainterPath path2); //异或

private slots:
    void slot_Update();
    void slot_Press(VisionItem *item, bool bSelected, bool bIn, qreal x, qreal y);

};

#endif // MAINWINDOW_H
