#include "drawingboard.h"
#include <QDebug>
#include <QPainter>

DrawingBoard::DrawingBoard(QWidget *parent) : QGraphicsView(parent)
{
    m_pix = QPixmap(300, 300);
}

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
            if (m_isDrawing)  //如果正在绘图，就在辅助画布上绘制
            {
                //将以前pix中的内容复制到tempPix中，保证以前的内容不消失
                m_tempPix = m_pix;
                QPainter pp(&m_tempPix);
                pp.setRenderHints(QPainter::Antialiasing);
                pp.drawLine(m_start_pos, m_end_pos);
                painter.drawPixmap(0, 0, m_tempPix);
            }
            else
            {
                QPainter pp(&m_pix);
                pp.setRenderHints(QPainter::Antialiasing);
                pp.drawLine(m_start_pos, m_end_pos);
                painter.drawPixmap(0, 0, m_pix);
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
            m_press_mouse = true;
            m_start_pos = event->pos();
        }
    }
    else if (typePloygon == m_shape_type)
    {
        if (Qt::LeftButton == event->button())
        {
            m_need_paint = false;
            m_press_mouse = true;
            m_start_pos = event->pos();

            if (m_need_paint)
            {
                m_isDrawing = false;
            }
            else
            {
                m_isDrawing = true;
            }
        }
    }
}

void DrawingBoard::mouseMoveEvent(QMouseEvent *event)
{
    if (typeRectangle == m_shape_type)
    {
        if (m_press_mouse)
        {
            m_end_pos = event->pos();
            m_need_paint = true;
            update();
        }
    }
    else if (typePloygon == m_shape_type)
    {
        if (m_press_mouse)
        {
            m_need_paint = true;
        }

        if (m_need_paint)
        {
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
        m_press_mouse = false;
    }
    else if (typePloygon == m_shape_type)
    {
    }
    else
    {
    }
}
