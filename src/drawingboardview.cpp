#include "drawingboardview.h"
#include "pathitem.h"
#include "svgparser.h"
#include <QDebug>
#include <QGraphicsSvgItem>
#include <QPainter>
#include <QSvgRenderer>
#include <QtXml/QDomDocument>
#include <qmath.h>

const QString c_svg_filename =
    "C:\\Qt\\Qt5.14.1\\5.14.1\\Src\\qtsvg\\examples\\svg\\svggenerator\\resources\\new - all.svg";

DrawingBoardView::DrawingBoardView(QWidget *parent) : QGraphicsView(parent)
{
    setAlignment(Qt::AlignLeft | Qt::AlignTop);
    setRenderHint(QPainter::Antialiasing);  //去锯齿
    m_scene = new DrawingBoardScene(parent);
    m_scene->setRect(rect());
    setScene(m_scene);
    //    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    //    setDragMode(QGraphicsView::RubberBandDrag);

    // loadSvgFile(c_svg_filename);
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

    QGraphicsView::wheelEvent(event);
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

void DrawingBoardView::loadSvgFile(const QString &file_name)
{
    QFile file(file_name);
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
                SvgParser::parsePathData(xml.attributes(), path);

                SvgStyle style;
                SvgParser::parstStyle(xml.attributes(), style);

                path.setFillRule(style.fillRule);

                item->setPath(path);
                item->setStyle(style);
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable |
                               QGraphicsItem::ItemIsMovable);
                item->setZValue(0);

                scene()->addItem(item);
            }
        }
    }
}
