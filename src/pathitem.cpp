#include "pathitem.h"
#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>
#include <qmath.h>

PathItem::PathItem(QGraphicsItem *parent) : QGraphicsPathItem(parent) {}

PathItem::~PathItem() {}

QRectF PathItem::boundingRect() const
{
    //    qreal lx = m_lines.at(0).x1();
    //    qreal rx = 0.0;
    //    qreal ty = m_lines.at(0).y1();
    //    qreal by = 0.0;
    //    for (int i = 0; i < m_lines.size(); i++)
    //    {
    //        if (m_lines.at(i).x1() < lx)
    //            lx = m_lines.at(i).x1();
    //        if (m_lines.at(i).x2() < lx)
    //            lx = m_lines.at(i).x2();

    //        if (m_lines.at(i).x1() > rx)
    //            rx = m_lines.at(i).x1();
    //        if (m_lines.at(i).x2() > rx)
    //            rx = m_lines.at(i).x2();

    //        if (m_lines.at(i).y1() < ty)
    //            ty = m_lines.at(i).y1();
    //        if (m_lines.at(i).y2() < ty)
    //            ty = m_lines.at(i).y2();

    //        if (m_lines.at(i).y1() > by)
    //            by = m_lines.at(i).y1();
    //        if (m_lines.at(i).y2() > by)
    //            by = m_lines.at(i).y2();
    //    }

    //    return QRectF(lx, ty, rx - lx, by - ty);

    return QRectF(0, 0, 32.399985, 27.29992);
}

#define R2D (180.0 / M_PI)
#define D2R (M_PI / 180.0)

void PathItem::drawArc(QPainter &painter, qreal sx, qreal sy, qreal ex, qreal ey, qreal cx, qreal cy, qreal r, bool cw)
{
    qreal sax = sx - cx, say = sy - cy;
    qreal eax = ex - cx, eay = ey - cy;

    qreal sa = qAtan2(say, sax);
    qreal ea = qAtan2(eay, eax);

    if (cw)
    {
        if (sa <= ea)
        {
            sa += 2 * M_PI;
        }
    }
    else
    {
        if (ea <= sa)
        {
            ea += 2 * M_PI;
        }
    }

    qreal rectx_min = sx;
    qreal rectx_max = 0;
    qreal recty_min = sy;
    qreal recty_max = 0;
    if (sx < rectx_min)
        rectx_min = sx;
    if (ex < rectx_min)
        rectx_min = ex;
    if (cx < rectx_min)
        rectx_min = cx;

    if (sx > rectx_max)
        rectx_max = sx;
    if (ex > rectx_max)
        rectx_max = ex;
    if (cx > rectx_max)
        rectx_max = cx;

    if (sy < recty_min)
        recty_min = sy;
    if (ey < recty_min)
        recty_min = ey;
    if (cy < recty_min)
        recty_min = cy;

    if (sy > recty_max)
        recty_max = sy;
    if (ey > recty_max)
        recty_max = ey;
    if (cy > recty_max)
        recty_max = cy;

    painter.drawArc(QRectF(rectx_min, recty_min, rectx_max - rectx_min, recty_max - recty_min), sa * R2D * 16,
                    (ea - sa) * R2D * 16);
}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    // Q_UNUSED(widget);

    // painter->save();
    //    if (m_style.pen != nullptr)
    //    {
    //        painter->setOpacity(m_style.opacity);
    //        resetTransform();
    //        setTransform(m_style.transform);

    //        if (option->state & QStyle::State_HasFocus)
    //        {
    //            m_last_pen.setColor(Qt::red);
    //            painter->strokePath(path(), m_last_pen);
    //        }
    //        else
    //        {
    //            painter->strokePath(path(), *m_style.pen);
    //        }
    //    }
    //    else if (m_style.brush != nullptr)
    //    {
    //        painter->setOpacity(m_style.opacity);
    //        if (option->state & QStyle::State_HasFocus)
    //        {
    //            painter->fillPath(path(), QBrush(Qt::red));
    //        }
    //        else
    //        {
    //            painter->fillPath(path(), *m_style.brush);
    //        }
    //    }
    //    else
    //    {
    //    }

    {
        painter->setPen(m_bounding_pen);
        if (!m_bounding_rect.isEmpty())
            painter->drawRect(m_bounding_rect);
    }

    if (m_drawline)
    {
        painter->setPen(m_element_pen);
        painter->drawLines(m_lines);
    }
    if (m_bounding_rect.isEmpty())
        setPos(m_pos_x, m_pos_y);

    // painter->drawRect(QRectF(0, 0, 300, 300));

    if (m_drawarc)
    {
        for (auto &arc : m_arcs)
            drawArc(*painter, arc.sx, arc.sy, arc.ex, arc.ey, arc.cx, arc.cy, arc.r, arc.cw);
    }

    // painter->restore();
    // QGraphicsRectItem::paint(painter, option, widget);
}
