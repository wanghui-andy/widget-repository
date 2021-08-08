#include "pathitem.h"

PathItem::PathItem(QGraphicsItem *parent) : QGraphicsPathItem(parent) {}

PathItem::~PathItem() {}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);

    painter->save();
    if (m_style.pen != nullptr)
    {
        painter->setOpacity(m_style.opacity);
        resetTransform();
        setTransform(m_style.transform);

        if (option->state & QStyle::State_HasFocus)
        {
            m_last_pen.setColor(Qt::red);
            painter->strokePath(path(), m_last_pen);
        }
        else
        {
            painter->strokePath(path(), *m_style.pen);
        }
    }
    else if (m_style.brush != nullptr)
    {
        painter->setOpacity(m_style.opacity);
        if (option->state & QStyle::State_HasFocus)
        {
            painter->fillPath(path(), QBrush(Qt::red));
        }
        else
        {
            painter->fillPath(path(), *m_style.brush);
        }
    }
    else
    {
    }

    painter->restore();
}
