#ifndef PATHITEM_H
#define PATHITEM_H
#include "svgparser.h"
#include <QBrush>
#include <QGraphicsPathItem>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>
#include <QVector>

struct Arc
{
    Arc() {}
    Arc(qreal sx1, qreal sy1, qreal ex1, qreal ey1, qreal cx1, qreal cy1, qreal r1, bool cw1)
        : sx(sx1), sy(sy1), ex(ex1), ey(ey1), cx(cx1), cy(cy1), r(r1), cw(cw1)
    {
    }
    Arc &operator=(const Arc &other)
    {
        sx = other.sx;
        sy = other.sy;
        ex = other.ex;
        ey = other.ey;
        cx = other.cx;
        cy = other.cy;
        cw = other.cw;
        r = other.r;

        return *this;
    }
    qreal sx;
    qreal sy;
    qreal ex;
    qreal ey;
    qreal cx;
    qreal cy;
    qreal r;
    bool cw;
};

class PathItem : public QGraphicsPathItem
{
public:
    explicit PathItem(QGraphicsItem *parent = nullptr);
    ~PathItem();

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = nullptr) override;

    void setStyle(SvgStyle style)
    {
        m_style = style;
        if (style.pen != nullptr)
        {
            m_last_pen = *style.pen;
        }
    }

    void setLines(QVector<QLineF> lines)
    {
        m_lines = lines;
        m_drawline = true;
    }
    void setArcs(QVector<Arc> arcs)
    {
        m_arcs = arcs;
        m_drawarc = true;
    }

    void setBoundingPen(QPen p)
    {
        m_bounding_pen = p;
    }

    void setElementPen(QPen p)
    {
        m_element_pen = p;
    }

    void setCoordinate(qreal x, qreal y)
    {
        m_pos_x = x;
        m_pos_y = y;
    }

protected:
    QRectF boundingRect() const override;

    // protected:
    //    // Event handlers
    //    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    //    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    //    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event) override;

private:
    void drawArc(QPainter &painter, qreal sx, qreal sy, qreal ex, qreal ey, qreal cx, qreal cy, qreal r, bool cw);

private:
    SvgStyle m_style;
    QPen m_last_pen;

    QVector<QLineF> m_lines;
    QVector<Arc> m_arcs;
    bool m_drawline = false;
    bool m_drawarc = false;

    QPointF m_startPos;
    QPen m_element_pen;
    QPen m_bounding_pen;
    qreal m_pos_x;
    qreal m_pos_y;
};

#endif  // PATHITEM_H
