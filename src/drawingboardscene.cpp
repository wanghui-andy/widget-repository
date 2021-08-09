#include "drawingboardscene.h"
#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>

DrawingBoardScene::DrawingBoardScene(QObject *parent) : QGraphicsScene(parent) {}

DrawingBoardScene::~DrawingBoardScene() {}

void DrawingBoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_start_point = event->scenePos();
    m_end_point = event->scenePos();
    if (typeRectangle == m_type && !m_finish_draw)
    {
        m_need_draw = true;
        QGraphicsRectItem *rectItem = new QGraphicsRectItem();
        rectItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
                           QGraphicsItem::ItemIsFocusable);
        QPen *pen = new QPen(QColor("green"));
        rectItem->setPen(*pen);
        m_items.push_back(rectItem);
        addItem(rectItem);
    }
    else if (typePloygon == m_type)
    {
        if (m_is_drawing_poly)
        {
            if (event->button() == Qt::LeftButton)  //点击左键先画线
            {
                if (m_polygonPoints.isEmpty())
                {
                    m_polygonPoints = QVector<QPointF>();
                    m_polygonPoints.append(m_start_point);
                    QGraphicsLineItem *lineItem = new QGraphicsLineItem();
                    lineItem->setLine(m_start_point.x(), m_start_point.y(), m_end_point.x(), m_end_point.y());
                    QPen *pen = new QPen(QColor("green"));
                    lineItem->setPen(*pen);
                    lineItem->setPen(*pen);
                    m_polygonTemp.push_back(lineItem);
                    addItem(lineItem);
                }
                else
                {
                    m_polygonPoints.append(m_start_point);
                    QGraphicsLineItem *lineItem = new QGraphicsLineItem;
                    lineItem->setLine(m_polygonPoints.at(m_polygonPoints.size() - 2).x(),
                                      m_polygonPoints.at(m_polygonPoints.size() - 2).y(), m_end_point.x(),
                                      m_end_point.y());
                    QPen *pen = new QPen(QColor("green"));
                    lineItem->setPen(*pen);
                    m_polygonTemp.push_back(lineItem);
                    addItem(lineItem);
                    update(m_rect);
                }
            }
            if (event->button() == Qt::RightButton)  //点击右键删除之前的线并显示为完整的多边形
            {
                int initialCount = m_polygonTemp.count();
                for (int i = 0; i < initialCount; i++)
                {
                    removeItem(m_polygonTemp.last());
                    m_polygonTemp.pop_back();
                }
                QGraphicsPolygonItem *polyItem = new QGraphicsPolygonItem;
                polyItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable |
                                   QGraphicsItem::ItemIsSelectable);
                polyItem->setPolygon(*(new QPolygonF(m_polygonPoints)));
                QPen *pen = new QPen(QColor("green"));
                polyItem->setPen(*pen);
                addItem(polyItem);
                m_polygonPoints.clear();

                m_is_drawing_poly = false;
            }
        }
    }

    QGraphicsScene::mousePressEvent(event);
}

void DrawingBoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (typeRectangle == m_type)
    {
        if (m_need_draw && !m_items.empty())
        {
            m_end_point = event->scenePos();
            QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(m_items[0]);
            rectItem->setRect(*(new QRectF(m_start_point, m_end_point)));
            update();
        }
    }
    QGraphicsScene::mouseMoveEvent(event);
}

void DrawingBoardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    if (typeRectangle == m_type)
    {
        m_need_draw = false;
        m_finish_draw = true;
    }

    QGraphicsScene::mouseReleaseEvent(event);
}
