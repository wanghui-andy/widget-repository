#ifndef AVICHARTWIDGET_H
#define AVICHARTWIDGET_H
#include <QChart>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsView>
#include <QLineSeries>]

QT_CHARTS_USE_NAMESPACE
class AVIChartWidget : public QChart
{
    Q_OBJECT

public:
    explicit AVIChartWidget(QGraphicsItem *parent = nullptr, Qt::WindowFlags wFlags = Qt::WindowFlags());
    ~AVIChartWidget();

    void setMinLineSeries(QLineSeries *series);

    bool handleMouseMove(const QPoint &point);

public slots:
    void slotMinLineHoverd(const QPointF &point, bool state);
    void slotMinLinePressed(const QPointF &point);
    void slotMinLineReleased(const QPointF &point);

private:
    QLineSeries *m_min_lineSeries = nullptr;
    bool m_min_line_pressed = false;
    QList<QPointF> m_old_minline_points;
};

#endif  // AVICHARTWIDGET_H
