#ifndef HISTOGRAMWIDGET_H
#define HISTOGRAMWIDGET_H

#include "avichartview.h"
#include "avichartwidget.h"
#include <QLineSeries>
#include <QTimer>
#include <QWidget>

namespace Ui
{
class HistogramWidget;
}

class HistogramWidget : public QWidget
{
    Q_OBJECT

public:
    explicit HistogramWidget(QWidget *parent = nullptr);
    ~HistogramWidget();
    void updateMinLabelPos(const QPoint &point);

private:
    Ui::HistogramWidget *ui;
    QTimer *m_timer;  //定时器
    AVIChartView *m_chart_view = nullptr;
    AVIChartWidget *m_chart = nullptr;

    QPoint m_min_mousemove_old_point;
    bool m_is_minline_pressed = false;
};

#endif  // HISTOGRAMWIDGET_H
