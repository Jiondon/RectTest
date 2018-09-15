#ifndef VISIONCIRCLEITEM_H
#define VISIONCIRCLEITEM_H

#include <QGraphicsItem>
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <QFocusEvent>
#include <QStyleOptionGraphicsItem>
#include "visionitem.h"
#include <QGraphicsView>

/**
 * @brief       椭圆形自定义控件
 * @author      kuainq
 * @date        create:20180208
 * @note        暂时没有添加可编辑椭圆
 */
class VisionEllipseItem : public QObject,public VisionItem
{
    Q_OBJECT
public:
    VisionEllipseItem(VisionItem *parent = 0);

    /**
     * @brief       设置椭圆矩形
     */
    void setRect(qreal x,qreal y,qreal width,qreal height);

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


signals:
    void signal_SizeChanged(void *rect);
    void signal_Release(QString str);
    void signal_Change(VisionItem* item);

protected:
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget);
    QRectF boundingRect() const;

    virtual void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    virtual void mousePressEvent(QGraphicsSceneMouseEvent *event);
    virtual void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    virtual void hoverMoveEvent(QGraphicsSceneHoverEvent *event);
    virtual void mouseDoubleClickEvent(QGraphicsSceneMouseEvent *event);

    void contextMenuEvent(QGraphicsSceneContextMenuEvent *event);

private:
    qreal m_x = 0,m_y = 0,m_width = 0,m_height = 0;//矩形决定圆
    QColor penColor;//画笔颜色 默认黑色
    qreal penWidth;//画笔宽度 默认1


//    QPointF curPoint;  //当前移动后的位置
//    QPointF prePoint;  //前一次移动后的位置
    QPointF lastPoint;

    DirecCursor  directCursor = normal_rect;

    bool m_bEdit = false;
};

#endif // VISIONCIRCLEITEM_H
