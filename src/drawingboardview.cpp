#include "drawingboardview.h"
#include <QDebug>
#include <QPainter>

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
