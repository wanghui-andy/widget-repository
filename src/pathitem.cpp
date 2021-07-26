#include "pathitem.h"

PathItem::PathItem(QGraphicsItem *parent) : QGraphicsPathItem(parent) {}

PathItem::~PathItem() {}

void PathItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    //    if (option->state & QStyle::State_HasFocus)
    //    {
    //        painter->setPen(Qt::DotLine);
    //    }
    //    else
    //    {
    //        painter->setPen(Qt::SolidLine);
    //    }

    // painter->setBrush(Qt::yellow);
    //    QPen pen;
    //    pen.setBrush()

    if (m_style.pen != nullptr)
    {
        //        Qt::PenCapStyle capStyle = m_style.pen->capStyle();
        //        Qt::PenJoinStyle joinStyle = m_style.pen->joinStyle();
        //        qreal miterLimit = m_style.pen->miterLimit();
        //        qreal widthF = m_style.pen->widthF();

        m_style.pen->setStyle(Qt::SolidLine);
        painter->setOpacity(m_style.opacity);
        painter->setTransform(m_style.transform);
        painter->strokePath(path(), *m_style.pen);
    }

    if (m_style.brush != nullptr)
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
}
