#include "avichartview.h"
#include "histogramwidget.h"

AVIChartView::AVIChartView(AVIChartWidget *chart, QWidget *parent) : QChartView(chart, parent), m_chart(chart)
{
    m_parent_widget = parent;
}

AVIChartView::~AVIChartView() {}

void AVIChartView::mousePressEvent(QMouseEvent *event)
{
    QChartView::mousePressEvent(event);
}
void AVIChartView::mouseMoveEvent(QMouseEvent *event)
{
    if (m_chart)
    {
        if (m_chart->handleMouseMove(event->pos()))
        {
            auto parent = dynamic_cast<HistogramWidget *>(m_parent_widget);
            if (parent)
            {
                parent->updateMinLabelPos(event->pos());
            }
        }
    }

    QChartView::mouseMoveEvent(event);
}
void AVIChartView::mouseReleaseEvent(QMouseEvent *event)
{
    QChartView::mouseReleaseEvent(event);
}
