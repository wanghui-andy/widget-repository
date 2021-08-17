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
    setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    setRenderHint(QPainter::Antialiasing);  //去锯齿
    m_scene = new QGraphicsScene(parent);
    // m_scene->setRect(rect());
    setScene(m_scene);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //    setOptimizationFlags(QGraphicsView::DontSavePainterState);
    //    setDragMode(QGraphicsView::ScrollHandDrag);

    // loadSvgFile(c_svg_filename);

    //    QGraphicsLineItem *item = new QGraphicsLineItem();
    //    item->setZValue(0);
    //    //    item->setEnabled(true);
    //    //    item->setAcceptDrops(true);
    //    //    item->setAcceptHoverEvents(true);
    //    item->setFlags(QGraphicsItem::ItemIsMovable);
    //    item->setAcceptedMouseButtons(Qt::LeftButton);
    QVector<QLineF> lines;
    lines << QLineF(-35.101085, 1.767105, 1.99913, 1.767105) << QLineF(1.99913, 1.767105, 1.99913, -30.247722)
          << QLineF(1.99913, -30.247722, -35.101085, -30.247722) << QLineF(-35.101085, -30.247722, -35.101085, 1.767105)
        /*<< QLineF(30.444005, 463.170245, 30.595737, 462.988388) << QLineF(31.205573, 462.86261, 31.955268, 463.242798)
        << QLineF(33.479412, 463.56233, 35.906405, 463.42664) << QLineF(38.249672, 461.843535, 40.002075, 461.74556)
        << QLineF(42.507462, 463.057585, 43.50007, 463.002087) << QLineF(43.877165, 462.58033, 43.780805, 460.856838)
        << QLineF(42.904272, 460.080835, 42.38692, 460.10976) << QLineF(42.12342, 459.874165, 42.11443, 459.71338)
        << QLineF(40.726792, 458.900572, 36.37368, 459.143948) << QLineF(35.902235, 459.67096, 35.921775, 460.020425)
        << QLineF(35.686195, 460.284178, 34.837635, 460.33162) << QLineF(33.92418, 461.083808, 33.428888, 461.1115)
        << QLineF(33.1751, 461.058183, 30.915038, 459.91234) << QLineF(29.69532, 460.164257, 29.51635, 460.378718)
        << QLineF(28.812582, 460.44253, 22.973738, 455.574738) << QLineF(22.973738, 455.574738, 21.565155, 455.702335)
        << QLineF(21.565155, 455.702335, 20.681635, 456.762447)
        << QLineF(20.706907, 457.043815, 20.803097, 457.124023) << QLineF(20.290932, 457.73869, 20.194813, 457.658307)
        << QLineF(19.91324, 457.684095, 18.516897, 459.358737)*/
        ;

    QVector<Arc> arcs;

    arcs << Arc(18.516897, 459.358737, 18.542698, 459.640132, 18.670798, 459.486508, 0.200026, true);
    arcs << Arc(23.650757, 463.898617, 23.93208, 463.873175, 23.77865, 463.74471, 0.20011, true);
    arcs << Arc(24.94781, 462.654663, 25.15059, 462.548427, 25.177895, 462.84719, 0.30001, false);
    arcs << Arc(26.311935, 462.44303, 26.530847, 462.51122, 26.338898, 462.741952, 0.300137, false);
    arcs << Arc(27.627745, 463.425678, 30.444005, 463.170245, 28.908112, 461.889325, 1.99993, true);
    arcs << Arc(30.595737, 462.988388, 31.205573, 462.86261, 30.979703, 463.30876, 0.500068, false);
    arcs << Arc(31.955268, 463.242798, 33.479412, 463.56233, 33.311797, 460.567045, 2.999971, true);
    arcs << Arc(35.906405, 463.42664, 36.205275, 463.265622, 35.884032, 463.027232, 0.400034, true);
    arcs << Arc(36.205275, 463.265622, 38.249672, 461.843535, 39.33802, 465.588703, 3.900102, false);
    arcs << Arc(40.002075, 461.74556, 42.19249, 462.931157, 39.337983, 465.588705, 3.9001, false);
    arcs << Arc(42.19249, 462.931157, 42.507462, 463.057585, 42.484873, 462.6583, 0.399924, true);
    arcs << Arc(43.50007, 463.002087, 43.877165, 462.58033, 43.477738, 462.602662, 0.400051, true);
    arcs << Arc(43.780805, 460.856838, 43.622615, 460.519038, 43.281665, 460.884642, 0.499914, true);
    arcs << Arc(43.622615, 460.519038, 43.247527, 460.192133, 38.57929, 465.927043, 7.394704, true);
    arcs << Arc(43.247527, 460.192133, 42.904272, 460.080835, 42.93205, 460.580135, 0.500072, true);
    arcs << Arc(42.38692, 460.10976, 42.12342, 459.874165, 42.372965, 459.860213, 0.249937, false);
    arcs << Arc(42.11443, 459.71338, 41.83213, 459.290723, 41.615268, 459.741178, 0.499939, true);
    arcs << Arc(41.83213, 459.290723, 40.904628, 458.922765, 38.800718, 465.578948, 6.980776, true);
    arcs << Arc(40.904628, 458.922765, 40.726792, 458.900572, 40.754805, 459.399725, 0.499938, true);
    arcs << Arc(36.37368, 459.143948, 35.902235, 459.67096, 36.40146, 459.643173, 0.499998, true);
    arcs << Arc(35.921775, 460.020425, 35.686195, 460.284178, 35.67211, 460.034513, 0.250062, false);
    arcs << Arc(34.837635, 460.33162, 34.38082, 460.70806, 34.865458, 460.83078, 0.499935, true);
    arcs << Arc(34.38082, 460.70806, 33.92418, 461.083808, 33.896223, 460.584487, 0.500105, false);
    arcs << Arc(33.428888, 461.1115, 33.1751, 461.058183, 33.401235, 460.612457, 0.499808, false);
    arcs << Arc(30.915038, 459.91234, 29.69532, 460.164257, 30.463455, 460.804632, 1.000056, true);
    arcs << Arc(29.51635, 460.378718, 28.812582, 460.44253, 29.132525, 460.05835, 0.499957, false);
    arcs << Arc(20.681635, 456.762447, 20.706907, 457.043815, 20.835323, 456.890463, 0.200019, true);
    arcs << Arc(20.803097, 457.124023, 20.290932, 457.73869, 20.546933, 457.431288, 0.40004, false);
    arcs << Arc(20.194813, 457.658307, 19.91324, 457.684095, 20.066932, 457.812115, 0.200026, true);

    //    for (int i = 0; i < lines.size(); i++)
    //    {
    //        PathItem *item = new PathItem();
    //        item->setZValue(0);
    //        //    item->setEnabled(true);
    //        //    item->setAcceptDrops(true);
    //        //    item->setAcceptHoverEvents(true);
    //        item->setFlags(QGraphicsItem::ItemIsMovable);

    //        //        QPen pen(Qt::green);
    //        //        pen.setWidth(0.1);
    //        //        item->setPen(pen);
    //        //        item->setLine(lines.at(i));

    //        scene()->addItem(item);
    //    }

    struct Param
    {
        Param() {}
        Param(qreal xx, qreal yy, qreal a, int n)
        {
            x = xx;
            y = yy;
            angle = a;
            num = n;
        }
        qreal x;
        qreal y;
        qreal angle;
        int num;
    };

    //    QList<Param> param_list = {
    //        {-443.292957, 51.488933, 90},  {-425.292958, 51.488933, 90},  {-407.292957, 51.488933, 90},
    //        {-389.292957, 51.488933, 90},  {-371.292957, 51.488933, 90},  {-353.292957, 51.488933, 90},
    //        {469.29294, -3.488807, 270},   {487.29294, -3.488807, 270},   {505.29294, -3.488807, 270},
    //        {523.29294, -3.488807, 270},   {541.29294, -3.488807, 270},   {559.29294, -3.488807, 270},
    //        {-443.292957, 80.488932, 90},  {-425.292958, 80.488932, 90},  {-407.292957, 80.488932, 90},
    //        {-389.292957, 80.488932, 90},  {-371.292957, 80.488932, 90},  {-353.292957, 80.488932, 90},
    //        {469.29294, 25.511192, 270},   {487.29294, 25.511192, 270},   {505.29294, 25.511192, 270},
    //        {523.29294, 25.511192, 270},   {541.29294, 25.511192, 270},   {559.29294, 25.511192, 270},
    //        {-443.292957, 109.488933, 90}, {-425.292958, 109.488933, 90}, {-407.292957, 109.488933, 90},
    //        {-389.292957, 109.488933, 90}, {-371.292957, 109.488933, 90}, {-353.292957, 109.488933, 90},
    //        {469.29294, 54.511192, 270},   {487.29294, 54.511192, 270},   {505.29294, 54.511192, 270},
    //        {523.29294, 54.511192, 270},   {541.29294, 54.511192, 270},   {559.29294, 54.511192, 270},
    //        {-443.292957, 138.488933, 90}, {-425.292958, 138.488933, 90}, {-407.292957, 138.488933, 90},
    //        {-389.292957, 138.488933, 90}, {-371.292957, 138.488933, 90}, {-353.292957, 138.488933, 90},
    //        {469.29294, 83.511192, 270},   {487.29294, 83.511192, 270},   {505.29294, 83.511192, 270},
    //        {523.29294, 83.511192, 270},   {541.29294, 83.511192, 270},   {559.29294, 83.511192, 270}};

    QList<Param> param_list = {
        {5.607808, 9.493847, 180,1},  {44.708023, 9.493847, 180,2},  {83.808238, 9.493847, 180,3},
        {5.607808, 43.508675, 180,4}, {44.708023, 43.508675, 180,5}, {83.808238, 43.508675, 180,6}
        , {5.607808, 77.523502, 180,7}, {44.708023, 77.523502, 180,8}, {83.808238, 77.523502, 180,9}/*,  {-371.292957, 51.488933, 90},  {-353.292957, 51.488933, 90},
        {469.29294, -3.488807, 270},   {487.29294, -3.488807, 270},   {505.29294, -3.488807, 270},
        {523.29294, -3.488807, 270},   {541.29294, -3.488807, 270},   {559.29294, -3.488807, 270},
        {-443.292957, 80.488932, 90},  {-425.292958, 80.488932, 90},  {-407.292957, 80.488932, 90},
        {-389.292957, 80.488932, 90},  {-371.292957, 80.488932, 90},  {-353.292957, 80.488932, 90},
        {469.29294, 25.511192, 270},   {487.29294, 25.511192, 270},   {505.29294, 25.511192, 270},
        {523.29294, 25.511192, 270},   {541.29294, 25.511192, 270},   {559.29294, 25.511192, 270},
        {-443.292957, 109.488933, 90}, {-425.292958, 109.488933, 90}, {-407.292957, 109.488933, 90},
        {-389.292957, 109.488933, 90}, {-371.292957, 109.488933, 90}, {-353.292957, 109.488933, 90},
        {469.29294, 54.511192, 270},   {487.29294, 54.511192, 270},   {505.29294, 54.511192, 270},
        {523.29294, 54.511192, 270},   {541.29294, 54.511192, 270},   {559.29294, 54.511192, 270},
        {-443.292957, 138.488933, 90}, {-425.292958, 138.488933, 90}, {-407.292957, 138.488933, 90},
        {-389.292957, 138.488933, 90}, {-371.292957, 138.488933, 90}, {-353.292957, 138.488933, 90},
        {469.29294, 83.511192, 270},   {487.29294, 83.511192, 270},   {505.29294, 83.511192, 270},
        {523.29294, 83.511192, 270},   {541.29294, 83.511192, 270},   {559.29294, 83.511192, 270}*/};
    int num = 1;
    for (auto param : param_list)
    {
        PathItem *item = new PathItem();
        QPen pen(Qt::green);
        pen.setWidth(0.1);

        QPen pen1(Qt::red);
        pen1.setWidth(0.1);

        item->setElementPen(pen);
        item->setBoundingPen(pen1);

        item->setCoordinate(param.x, param.y);

        item->setFlags(QGraphicsItem::ItemIsMovable | QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable);
        item->setLines(lines);
        // item->setArcs(arcs);

        QTransform transform;
        transform.rotate(param.angle);

        // setTransform(transform);

        item->resetTransform();
        item->setTransform(transform);

        //        transform.rotate(180, Qt::YAxis);
        //        item->setTransform(transform);
        //        if (-90 == param.angle)
        //        {
        //            transform.translate(0, -4.18);
        //            item->setTransform(transform);
        //        }

        scene()->addItem(item);

        // 文字说明
        QGraphicsTextItem *textItem = new QGraphicsTextItem;
        textItem->setPlainText(QString::number(param.num));
        textItem->moveBy(param.x, param.y);
        num++;
        scene()->addItem(textItem);
    }

    PathItem *item = new PathItem();
    QPen pen(Qt::green);
    pen.setWidth(0.1);
    item->setBoundingRect(QRectF(0.00003, 0, 122.517942, 115.497965));
    scene()->addItem(item);

    // fitInView(item);
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
    if ((factor < 1 && currentZoom < 0.1) /* || (factor > 1 && currentZoom > 10)*/)
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

                // item->setPath(path);
                item->setStyle(style);
                item->setFlags(QGraphicsItem::ItemIsSelectable | QGraphicsItem::ItemIsFocusable |
                               QGraphicsItem::ItemIsMovable);
                item->setZValue(0);

                scene()->addItem(item);
            }
        }
    }
}
