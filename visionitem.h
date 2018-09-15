#ifndef VISIONITEM_H
#define VISIONITEM_H


/**
 * @brief       自定义图形控件的基类
 * @author      xiaodongLi
 * @date        2018-06-13
 * @note        1. 图形控件的基本功能
 */
#include <QObject>
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <QVector>

/**
 * @brief       自定义图形控件的种类
 * @author      xiaodongLi
 * @date        2018-06-13
 */
enum ItemType{
    Rect,  //矩形
    EllipseItem,  //圆或者椭圆
    Line,  //线
    Arrow,  //圆弧
    Chain,   //链--（线和圆弧混用）
    Point  //点
};
enum ItemEvent{

};

enum DirecCursor
{
    normal_rect,
    left_rect,
    top_rect,
    right_rect,
    bottom_rect,  //标记点

    left_Top_rect,
    left_bottom_rect,
    right_top_rect,
    right_bottom_rect,

    arrowsUp
};

enum Operation_enum{
    AND,   //交集
    OR,   //并集
    SUB,  //差集
    NOR   //异或
};
//图形之间的关系
struct OperationStruct{
    void* item1;  //item
    void* item2;  //item
    Operation_enum operation;   //运算 交集，差集，并集，异或
};

class VisionItem : public QObject,public QGraphicsItem
{
    Q_OBJECT
public:
    VisionItem(QGraphicsItem *parent = 0);

    /**
     * @brief       设置图形的类型
     * @param       QString
     */
     void setType(ItemType type){
        m_type = type;
    }

    ItemType getType()
    {
        return m_type;
    }

    /**
     * @brief       设置item的状态
     * @param       bool
     */
    void setSelectedStatus(bool selectedStatus){
        m_bSelectedStatus = selectedStatus;
    }

    bool getSelectedStatus(){
        return m_bSelectedStatus;
    }

    //设置编辑模式 、、选中
    void setEdit(bool edit){
        m_bEdit = edit;
        update();
    }

    bool getEdit(){
        return m_bEdit;
    }

    void setItemEnable(bool enable){
        setEnabled(enable);
//        this->scene()
        //需要刷新
    }

    bool getEnable(){
        return this->isEnabled();
    }

    QPainterPath getPainterPath(){
        return m_path;
    }

    QPainterPath m_path;

    bool getPosInArea(qreal x,qreal y);

    ItemType m_type = Rect;

//    ItemType getType(){
//        return m_type;
//    }

signals:
    void signal_clicked(VisionItem* item,bool selected,bool bIn = true,qreal x=0,qreal y=0);
    void signal_ctrl(int eventStyle);  //事件类型
    void signal_press();   //用于提示item被点击

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

private:
    bool m_bSelectedStatus = false;  //未选中状态
    bool m_bEdit = false;

    bool m_bInArea = false;

};

#endif // VISIONITEM_H
