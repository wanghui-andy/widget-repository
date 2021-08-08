#ifndef PATHITEM_H
#define PATHITEM_H
#include "svgparser.h"
#include <QBrush>
#include <QGraphicsPathItem>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QStyleOptionGraphicsItem>

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

private:
    SvgStyle m_style;
    QPen m_last_pen;
};

#endif  // PATHITEM_H
