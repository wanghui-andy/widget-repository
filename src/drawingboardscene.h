#ifndef DRAWINGBOARDSCENE_H
#define DRAWINGBOARDSCENE_H
#include <QGraphicsItemGroup>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QVector>

class DrawingBoardScene : public QGraphicsScene
{
    Q_OBJECT
public:
    explicit DrawingBoardScene(QObject *parent = nullptr);
    ~DrawingBoardScene();

    void setRect(QRectF rect)
    {
        m_rect = rect;
    }

    enum ShapeType
    {
        typeRectangle,
        typePloygon,
    };
    ShapeType m_shape_type = typePloygon;
    void setShapeType(ShapeType type)
    {
        m_type = type;
        if (typePloygon == m_type)
        {
            m_is_drawing_poly = true;
        }
    }

protected:
    // Event handlers
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    ShapeType m_type = typePloygon;

    std::vector<QGraphicsItem *> m_items;  //装有父类指针的QVector，指向的是不同的子类对象
    QRectF m_rect;
    QPointF m_start_point;
    QPointF m_end_point;
    bool m_need_draw = false;
    bool m_is_drawing_poly = true;

    QVector<QPointF> m_polygonPoints;        //暂存的多边形的点集
    QVector<QPointF> m_freePoints;           //暂存的自由绘画的点集
    QVector<QGraphicsItem *> m_polygonTemp;  //用于暂存多边形的各条边，用于随后清除
};

#endif  // DRAWINGBOARDSCENE_H
