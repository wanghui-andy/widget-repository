#ifndef RECTITEM_H
#define RECTITEM_H

#include <QGraphicsRectItem>

enum STATE_FLAG
{
    INVALID_FLAG = -1,
    MOV_LEFT_LINE,    //标记当前为用户按下矩形的左边界区域
    MOV_TOP_LINE,     //标记当前为用户按下矩形的上边界区域
    MOV_RIGHT_LINE,   //标记当前为用户按下矩形的右边界区域
    MOV_BOTTOM_LINE,  //标记当前为用户按下矩形的下边界区域
    MOV_RECT          //标记当前为鼠标拖动图片移动状态
};

class RectItem : public QGraphicsRectItem
{
public:
    explicit RectItem(QGraphicsItem *parent = nullptr);
    ~RectItem();
    void setRectSize(QRectF mrect);

    bool isSelected()
    {
        return m_selected;
    }
    void JudgeMouseEdgePos(QPointF pos);
    void UpdateRect();

protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPointF m_startPos;
    QRectF m_oldRect;
    QRectF m_insicedRectf;
    QRectF m_leftRectf;
    QRectF m_topRectf;
    QRectF m_rightRectf;
    QRectF m_bottomRectf;
    STATE_FLAG m_StateFlag;
    QPointF m_centerPointF;
    QRectF m_rect;
    QPointF m_scene_start_pos;

    bool m_selected = false;
};

#endif  // RECTITEM_H
