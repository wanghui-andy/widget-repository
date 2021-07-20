#include "drawingboard.h"
#include <QDebug>
#include <QPainter>

DrawingBoard::DrawingBoard(QWidget *parent) : QGraphicsView(parent) {}

DrawingBoard::~DrawingBoard() {}

void DrawingBoard::paintEvent(QPaintEvent *event)
{
    if (m_need_paint)
    {
        QPainter painter(this->viewport());
        painter.setPen(Qt::green);
        int x, y, w, h;
        x = m_start_pos.x();
        y = m_start_pos.y();
        w = m_end_pos.x() - x;
        h = m_end_pos.y() - y;

        if (typeRectangle == m_shape_type)
        {
            painter.drawRect(x, y, w, h);
        }
        else
        {
            painter.setRenderHints(QPainter::Antialiasing);
            painter.drawLine(m_start_pos, m_end_pos);
            for (auto line : m_lines)
            {
                painter.drawLine(line.begin_point, line.end_point);
            }
        }
    }
}

void DrawingBoard::mousePressEvent(QMouseEvent *event)
{
    if (typeRectangle == m_shape_type)
    {
        if (Qt::LeftButton == event->button())
        {
            m_prepare_paint = true;
            m_start_pos = event->pos();
        }
    }
    else if (typePloygon == m_shape_type)
    {
        if (Qt::LeftButton == event->button())
        {
            m_need_paint = false;
            m_prepare_paint = true;
            m_lines.push_back(Line(m_start_pos, m_end_pos));
            m_start_pos = event->pos();
        }
    }
}

void DrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
    if (typeRectangle == m_shape_type)
    {
        if (m_prepare_paint)
        {
            m_end_pos = event->pos();
            m_need_paint = true;
            update();
        }
    }
    else if (typePloygon == m_shape_type)
    {
        if (m_prepare_paint)
        {
            m_need_paint = true;
            m_end_pos = event->pos();
            update();
        }
    }
    else
    {
    }
}

void DrawingBoard::mouseReleaseEvent(QMouseEvent *event)
{
    if (typeRectangle == m_shape_type)
    {
        m_prepare_paint = false;
    }
    else if (typePloygon == m_shape_type)
    {
    }
    else
    {
    }
}

void DrawingBoard::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (typeRectangle == m_shape_type)
    {
        // do nothing
    }
    else if (typePloygon == m_shape_type)
    {
        m_prepare_paint = false;
        m_need_paint = false;
    }
    else
    {
    }
}
