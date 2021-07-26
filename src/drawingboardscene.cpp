#include "drawingboardscene.h"
#include "pathitem.h"
#include "svgparser.h"

#include <QGraphicsRectItem>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>
#include <QtXml/QDomDocument>
DrawingBoardScene::DrawingBoardScene(QObject *parent) : QGraphicsScene(parent)
{
    //    QPainterPath car;
    //    QPainterPath house;
    //    QPainterPath moon;
    //    QPainterPath tree;

    //    QFile file("C:\\Qt\\Qt5.14.1\\5.14.1\\Src\\qtsvg\\examples\\svg\\svggenerator\\resources\\shapes.dat");
    //    file.open(QIODevice::ReadOnly);
    //    QByteArray data = file.readAll();
    //    QDataStream stream(data);
    //    stream >> car >> house >> tree >> moon;
    //    file.close();

    //    //    QPen *pen = new QPen(QColor("green"));
    //    PathItem *item1 = new PathItem();
    //    item1->setPath(moon);
    //    item1->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
    //    QGraphicsItem::ItemIsFocusable);
    //    //    item1.setPen(*pen);
    //    //    item1.setBrush(Qt::green);
    //    //    QGraphicsPathItem item2(house);
    //    //    QPen *pen2 = new QPen(QColor("green"));
    //    //    item2.setPen(*pen);
    //    //    item2.setBrush(Qt::green);
    //    addItem(item1);
    //    //    addItem(&item2);

    QFile file("C:\\Qt\\Qt5.14.1\\5.14.1\\Src\\qtsvg\\examples\\svg\\svggenerator\\resources\\new.svg");
    file.open(QIODevice::ReadOnly);
    QByteArray data = file.readAll();
    QString str = data;
    QString head = str.left(str.indexOf("<path"));
    QString tail = str.right(str.size() - str.indexOf("</g"));
    QString content = str.mid(head.length(), str.length() - head.length() - tail.length() - 2);
    int index = 0;
    QList<QString> sub_svg_strings;
    QString new_line_symbol = "\r\n";
    while (index < content.size())
    {
        int mark_index = content.indexOf(">", index);
        QString substr = content.mid(index, mark_index - index + 1);
        index = index + substr.length() + new_line_symbol.length();
        QString sub_svg_str = head + substr + new_line_symbol + tail;
        sub_svg_strings.push_back(sub_svg_str);
    }

    for (auto sub_svg : sub_svg_strings)
    {
        //        QSvgRenderer *renderer = new QSvgRenderer(sub_svg.toUtf8());
        //        QScopedPointer<QGraphicsSvgItem> svgItem(new QGraphicsSvgItem());
        //        svgItem->setSharedRenderer(renderer);
        //        svgItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable |
        //                          QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemClipsToShape);

        //        addItem(svgItem.take());

        QXmlStreamReader xml(sub_svg.toUtf8());
        xml.setNamespaceProcessing(false);
        while (!xml.atEnd())
        {
            xml.readNext();
            if (xml.attributes().hasAttribute("d"))
            {
                PathItem *item = new PathItem();

                QPainterPath path;
                bool result = SvgParser::parsePathData(xml.attributes(), path);

                SvgStyle style;
                SvgParser::parstStyle(xml.attributes(), style);

                path.setFillRule(style.fillRule);

                item->setPath(path);
                item->setStyle(style);
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable |
                               QGraphicsItem::ItemIsMovable);

                addItem(item);
            }
        }
    }

    // setSceneRect(itemsBoundingRect());
}

DrawingBoardScene::~DrawingBoardScene() {}

void DrawingBoardScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    //    m_start_point = event->scenePos();
    //    m_end_point = event->scenePos();
    //    if (typeRectangle == m_type)
    //    {
    //        m_need_draw = true;
    //        QGraphicsRectItem *rectItem = new QGraphicsRectItem();
    //        rectItem->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsMovable |
    //                           QGraphicsItem::ItemIsFocusable);
    //        QPen *pen = new QPen(QColor("green"));
    //        rectItem->setPen(*pen);
    //        m_items.push_back(rectItem);
    //        addItem(rectItem);
    //    }
    //    else if (typePloygon == m_type)
    //    {
    //        if (m_is_drawing_poly)
    //        {
    //            if (event->button() == Qt::LeftButton)  //点击左键先画线
    //            {
    //                if (m_polygonPoints.isEmpty())
    //                {
    //                    m_polygonPoints = QVector<QPointF>();
    //                    m_polygonPoints.append(m_start_point);
    //                    QGraphicsLineItem *lineItem = new QGraphicsLineItem();
    //                    lineItem->setLine(m_start_point.x(), m_start_point.y(), m_end_point.x(), m_end_point.y());
    //                    QPen *pen = new QPen(QColor("green"));
    //                    lineItem->setPen(*pen);
    //                    lineItem->setPen(*pen);
    //                    m_polygonTemp.push_back(lineItem);
    //                    addItem(lineItem);
    //                }
    //                else
    //                {
    //                    m_polygonPoints.append(m_start_point);
    //                    QGraphicsLineItem *lineItem = new QGraphicsLineItem;
    //                    lineItem->setLine(m_polygonPoints.at(m_polygonPoints.size() - 2).x(),
    //                                      m_polygonPoints.at(m_polygonPoints.size() - 2).y(), m_end_point.x(),
    //                                      m_end_point.y());
    //                    QPen *pen = new QPen(QColor("green"));
    //                    lineItem->setPen(*pen);
    //                    m_polygonTemp.push_back(lineItem);
    //                    addItem(lineItem);
    //                    update(m_rect);
    //                }
    //            }
    //            if (event->button() == Qt::RightButton)  //点击右键删除之前的线并显示为完整的多边形
    //            {
    //                int initialCount = m_polygonTemp.count();
    //                for (int i = 0; i < initialCount; i++)
    //                {
    //                    removeItem(m_polygonTemp.last());
    //                    m_polygonTemp.pop_back();
    //                }
    //                QGraphicsPolygonItem *polyItem = new QGraphicsPolygonItem;
    //                polyItem->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsFocusable |
    //                                   QGraphicsItem::ItemIsSelectable);
    //                polyItem->setPolygon(*(new QPolygonF(m_polygonPoints)));
    //                QPen *pen = new QPen(QColor("green"));
    //                polyItem->setPen(*pen);
    //                addItem(polyItem);
    //                m_polygonPoints.clear();

    //                m_is_drawing_poly = false;
    //            }
    //        }
    //    }

    QGraphicsScene::mousePressEvent(event);
}

void DrawingBoardScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    //    if (typeRectangle == m_type)
    //    {
    //        if (m_need_draw && !m_items.empty())
    //        {
    //            m_end_point = event->scenePos();
    //            QGraphicsRectItem *rectItem = dynamic_cast<QGraphicsRectItem *>(m_items[0]);
    //            rectItem->setRect(*(new QRectF(m_start_point, m_end_point)));
    //            update(m_rect);
    //        }
    //    }
    QGraphicsScene::mouseMoveEvent(event);
}

void DrawingBoardScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    //    if (typeRectangle == m_type)
    //    {
    //        m_need_draw = false;
    //    }

    QGraphicsScene::mouseReleaseEvent(event);
}
