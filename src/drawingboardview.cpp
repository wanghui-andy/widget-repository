#include "drawingboardview.h"
#include <QDebug>
#include <QPainter>
#include <qmath.h>

DrawingBoardView::DrawingBoardView(QWidget *parent) : QGraphicsView(parent)
{
    // setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setRenderHint(QPainter::Antialiasing);  //去锯齿
    m_scene = new DrawingBoardScene(parent);
    m_scene->setSceneRect(0, 0, width(), height());
    m_scene->setRect(rect());
    setScene(m_scene);
}

DrawingBoardView::~DrawingBoardView() {}

void DrawingBoardView::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);
}

void DrawingBoardView::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);
}

void DrawingBoardView::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);
}

void DrawingBoardView::wheelEvent(QWheelEvent *event)
{
    zoomBy(qPow(1.2, event->angleDelta().y() / 240.0));
}

void DrawingBoardView::zoomBy(qreal factor)
{
    const qreal currentZoom = zoomFactor();
    if ((factor < 1 && currentZoom < 0.1) || (factor > 1 && currentZoom > 10))
        return;
    scale(factor, factor);
}

qreal DrawingBoardView::zoomFactor() const
{
    return transform().m11();
}
