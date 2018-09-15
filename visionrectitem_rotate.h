﻿#ifndef VISIONRECTITEM_ROTATE_H
#define VISIONRECTITEM_ROTATE_H

#include <QObject>
#include <QGraphicsItem>
#include "visionitem.h"
#include <QGraphicsView>
#include <QGraphicsScene>
#include <QStyleOptionGraphicsItem>
#include <QTransform>
#include "minirect.h"
#include "visionarrows_rotate.h"


//编辑模式的八个小矩形，编号从左上角开始，顺时针

class VisionRectItem_Rotate : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    explicit VisionRectItem_Rotate(QGraphicsItem *parent = 0);

    /**
     * @brief       设置椭圆矩形
     */
    void setRect(qreal x,qreal y,qreal width,qreal height);

    /**
     * @brief       获得矩形框大小
     * @return      矩形
     */
    QRect getRect()
    {
        return QRect(m_x,m_y,m_width,m_height);
    }


    /**
     * @brief       设置画笔(线条)颜色
     * @param       color
     */
    void setPenColor(QColor color)
    {
        penColor = color;
    }

    /**
     * @brief       设置画笔(线条)宽度
     * @param       width
     */
    void setPenWidth(qreal width)
    {
        penWidth = width;
    }

    /**
     * @brief       获得矩形的基础大小，不添加可选框的尺寸
     * @return      矩形框基础尺寸
     */
    QRectF getBaseRect()
    {
        return QRectF(m_x,m_y,m_width,m_height);
    }

signals:

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event);

private:
    qreal m_x = 0,m_y = 0,m_width = 0,m_height = 0;//矩形
    qreal m_centerX = 0;qreal m_centerY = 0;

    QColor penColor;//画笔颜色 默认黑色
    qreal penWidth;//画笔宽度 默认1

    QPointF lastPoint;  //scenePos
    QPointF lastPointF; //pos

    DirecCursor  directCursor = normal_rect;

    qreal m_angle = 0;  //旋转的角度

    bool m_bCircle = false;
    bool m_bEdit = false;

    QTransform m_transform;

    QList<MiniRect* > m_lstRect;

    VisionArrows_Rotate* arrowsItem;  //箭头item  表示坐标方向的

private:
    void initItem(); //初始化编辑模式下的几个小矩形以及旋转的箭头控件
    void updateItem();  //出现拖动和缩放等操作的时候，更新item的位置

private slots:
    void slotIndex(int index);
    void slotArrowsItem();
    void slotArrowsItem_leave();

public slots:
};

#endif // VISIONRECTITEM_ROTATE_H
