#ifndef AVICHARTVIEW_H
#define AVICHARTVIEW_H

#include "avichartwidget.h"
#include <QtCharts/QChartView>

QT_CHARTS_USE_NAMESPACE

class AVIChartView : public QChartView
{
    Q_OBJECT

public:
    explicit AVIChartView(AVIChartWidget *chart = nullptr, QWidget *parent = nullptr);
    ~AVIChartView();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

private:
    AVIChartWidget *m_chart;
    QPoint m_mouse_pos;
    QWidget *m_parent_widget = nullptr;
};

#endif  // AVICHARTVIEW_H
