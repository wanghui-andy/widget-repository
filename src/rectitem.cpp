#include "rectitem.h"
#include <QCursor>
#include <QDebug>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QPen>

RectItem::RectItem(QGraphicsItem *parent) : QGraphicsRectItem(parent) {}

RectItem::~RectItem() {}

void RectItem::setRectSize(QRectF mrect)
{
    m_oldRect = mrect;
    m_insicedRectf = QRectF(m_oldRect.x() + 4, m_oldRect.y() + 4, m_oldRect.width() - 8, m_oldRect.height() - 8);
    m_leftRectf = QRectF(m_oldRect.x(), m_oldRect.y(), 4, m_oldRect.height() - 4);
    m_topRectf = QRectF(m_oldRect.x() + 4, m_oldRect.y(), m_oldRect.width() - 4, 4);
    m_rightRectf = QRectF(m_oldRect.right() - 4, m_oldRect.y() + 4, 4, m_oldRect.height() - 8);
    m_bottomRectf = QRectF(m_oldRect.x(), m_oldRect.bottom() - 4, m_oldRect.width() - 4, 4);
}

void RectItem::JudgeMouseEdgePos(QPointF pos)
{
    if (m_insicedRectf.contains(pos))
    {
        setCursor(Qt::ArrowCursor);
        m_StateFlag = MOV_RECT;

        qDebug() << "MOV_RECT";
    }
    else if (m_leftRectf.contains(pos))
    {
        setCursor(QCursor(Qt::SizeHorCursor));
        m_StateFlag = MOV_LEFT_LINE;
    }
    else if (m_rightRectf.contains(pos))
    {
        setCursor(QCursor(Qt::SizeHorCursor));
        m_StateFlag = MOV_RIGHT_LINE;
    }
    else if (m_topRectf.contains(pos))
    {
        setCursor(QCursor(Qt::SizeVerCursor));
        m_StateFlag = MOV_TOP_LINE;
    }
    else if (m_bottomRectf.contains(pos))
    {
        setCursor(QCursor(Qt::SizeVerCursor));
        m_StateFlag = MOV_BOTTOM_LINE;
    }
    else
    {
        setCursor(Qt::ArrowCursor);
        m_StateFlag = INVALID_FLAG;
    }
}

void RectItem::UpdateRect()
{
    m_rect = rect();
}

void RectItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_startPos = event->scenePos();
    m_selected = true;

    m_scene_start_pos = event->pos();

    qDebug() << "start pos: " << m_scene_start_pos.x();

    QGraphicsItem::mousePressEvent(event);
}

void RectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->drawRect(QRectF(0, 0, 100, 100));
}

void RectItem::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (m_StateFlag == MOV_RECT)
    {
        QPointF point = (event->pos() - m_startPos);
        moveBy(point.x(), point.y());
    }
    else if (m_StateFlag == MOV_LEFT_LINE)
    {
        if (event->pos().x() > (m_oldRect.right() - 10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setLeft(event->pos().x());
            setRectSize(newRect);
            setRect(newRect);
            // UpdateRect();
            scene()->update();
        }
    }
    else if (m_StateFlag == MOV_TOP_LINE)
    {
        if (event->pos().y() > (m_oldRect.bottom() - 10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setTop(event->pos().y());
            setRectSize(newRect);
            setRect(newRect);
            // UpdateRect();
            scene()->update();
        }
    }
    else if (m_StateFlag == MOV_RIGHT_LINE)
    {
        if (event->pos().x() < (m_oldRect.left() + 10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setRight(event->pos().x());
            setRectSize(newRect);
            setRect(newRect);
            // UpdateRect();
            scene()->update();
        }
    }
    else if (m_StateFlag == MOV_BOTTOM_LINE)
    {
        if (event->pos().y() < (m_oldRect.top() + 10))
        {
            return;
        }
        else
        {
            QRectF newRect(m_oldRect);
            newRect.setBottom(event->pos().y());
            setRectSize(newRect);
            setRect(newRect);
            // UpdateRect();
            scene()->update();
        }
    }
    else
    {
        QGraphicsRectItem::mouseMoveEvent(event);
    }
}

void RectItem::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    setCursor(Qt::ArrowCursor);
    m_selected = false;
    if (MOV_RECT == m_StateFlag)
    {
        m_StateFlag = INVALID_FLAG;

        //        QRectF newRect(m_rect.x() + event->scenePos().x() - m_scene_start_pos.x(),
        //                       m_rect.y() + event->scenePos().y() - m_scene_start_pos.y(), m_rect.width(),
        //                       m_rect.height());
        //        m_rect = newRect;
        //        setRectSize(m_rect);

        //        qDebug() << "release pos: " << pos().x();
    }
    else
    {
        QGraphicsItem::mouseReleaseEvent(event);
    }
}
