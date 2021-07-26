#ifndef SVGPARSER_H
#define SVGPARSER_H

#include <QBrush>
#include <QPainterPath>
#include <QPen>
#include <QString>
#include <QXmlStreamAttributes>

struct SvgAttributes
{
    SvgAttributes(const QXmlStreamAttributes &xmlAttributes);

    QString id;

    QStringRef color;
    QStringRef colorOpacity;
    QStringRef fill;
    QStringRef fillRule;
    QStringRef fillOpacity;
    QStringRef stroke;
    QStringRef strokeDashArray;
    QStringRef strokeDashOffset;
    QStringRef strokeLineCap;
    QStringRef strokeLineJoin;
    QStringRef strokeMiterLimit;
    QStringRef strokeOpacity;
    QStringRef strokeWidth;
    QStringRef vectorEffect;
    QStringRef fontFamily;
    QStringRef fontSize;
    QStringRef fontStyle;
    QStringRef fontWeight;
    QStringRef fontVariant;
    QStringRef textAnchor;
    QStringRef transform;
    QStringRef visibility;
    QStringRef opacity;
    QStringRef compOp;
    QStringRef display;
    QStringRef offset;
    QStringRef stopColor;
    QStringRef stopOpacity;
};

struct SvgStyle
{
    QPen *pen;
    QBrush *brush;
    Qt::FillRule fillRule;
    qreal opacity;
    QTransform transform;
};

class SvgParser
{
public:
    SvgParser();

    static bool parsePathData(const QXmlStreamAttributes &attributes, QPainterPath &path);
    static bool parstStyle(const QXmlStreamAttributes &attributes, SvgStyle &style);
};

#endif  // SVGPARSER_H
