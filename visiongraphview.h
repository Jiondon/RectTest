#ifndef VISIONGRAPHVIEW_H
#define VISIONGRAPHVIEW_H

#include <QGraphicsView>
#include <QMouseEvent>
#include "visionitem.h"

/**
 * @brief       自定义图形View控件
 * @note        除了鼠标位置，更多的是扩展使用
 * @author      kuainq
 * @date        create:2017-11-13
 */
class VisionGraphView : public QGraphicsView
{
    Q_OBJECT
public:
    VisionGraphView(QWidget *parent =0);

    void setDrawPath(QPainterPath path1,QPainterPath path2,Operation_enum opera);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent* event);

    void setLines(QVector<QLineF> lines);
    void setPainterCursor(bool painterCursor);

signals:
    void signal_Move();

private:
    QPainterPath m_path1;
    QPainterPath m_path2;
    Operation_enum m_opera;

    QVector<QLineF> m_lstLines;

    bool m_bPainer = true;   //绘制
    qreal m_qCircleR = 20;
    QPointF  m_lastPointF;
    QList<QPointF> m_lstPoint;

    qreal zoom = 1;

protected:

};

#endif // VISIONGRAPHVIEW_H
