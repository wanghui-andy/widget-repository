#include "avichartwidget.h"
#include <QValueAxis>

AVIChartWidget::AVIChartWidget(QGraphicsItem *parent, Qt::WindowFlags wFlags) : QChart(parent, wFlags) {}

AVIChartWidget::~AVIChartWidget() {}

void AVIChartWidget::setMinLineSeries(QLineSeries *series)
{
    m_min_lineSeries = series;
    if (m_min_lineSeries)
    {
        addSeries(m_min_lineSeries);
        connect(m_min_lineSeries, &QLineSeries::hovered, this, &AVIChartWidget::slotMinLineHoverd);
        connect(m_min_lineSeries, &QLineSeries::pressed, this, &AVIChartWidget::slotMinLinePressed);
        connect(m_min_lineSeries, &QLineSeries::released, this, &AVIChartWidget::slotMinLineReleased);
    }
}

void AVIChartWidget::slotMinLineHoverd(const QPointF &point, bool state)
{
    QCursor cursor = state ? QCursor(Qt::SizeHorCursor) : QCursor(Qt::ArrowCursor);
    setCursor(cursor);
}

void AVIChartWidget::slotMinLinePressed(const QPointF &point)
{
    m_min_line_pressed = true;
    m_old_minline_points = m_min_lineSeries->points();
}

void AVIChartWidget::slotMinLineReleased(const QPointF &point)
{
    m_min_line_pressed = false;
}

bool AVIChartWidget::handleMouseMove(const QPoint &point)
{
    if (m_min_line_pressed)
    {
        //在视图坐标系中计算鼠标在表格区域中的相对坐标
        QPoint mapped_point = point;
        mapped_point.setX(point.x() - plotArea().x());
        mapped_point.setY(point.y() - plotArea().y());

        if (mapped_point.x() < 0 || mapped_point.x() > plotArea().x() + plotArea().width())
            return false;

        //获取x/y坐标轴，以便后面计算表格在坐标轴上的“单元格”数
        QAbstractAxis *axisx = axes(Qt::Horizontal).first();
        QValueAxis *haxis = nullptr;
        if (axisx->type() == QAbstractAxis::AxisTypeValue)
            haxis = qobject_cast<QValueAxis *>(axisx);

        QAbstractAxis *axisy = axes(Qt::Vertical).first();
        QValueAxis *vaxis = nullptr;
        if (axisy->type() == QAbstractAxis::AxisTypeValue)
            vaxis = qobject_cast<QValueAxis *>(axisy);

        if (haxis && vaxis)
        {
            //计算坐标轴单元格数
            double xunit = plotArea().width() / haxis->max();
            double yunit = plotArea().height() / vaxis->max();

            //将坐标转换为坐标轴上的刻度
            double x = mapped_point.x() / xunit;
            double y = vaxis->max() - mapped_point.y() / yunit;

            //更新刻度
            QList<QPointF> new_points;
            for (const auto &point : m_old_minline_points)
            {
                QPointF new_point(x, point.y());  //由于是水平拖动，只需要更新x方向刻度即可
                new_points.push_back(new_point);
            }
            m_min_lineSeries->replace(new_points);
            m_old_minline_points = new_points;

            return true;
        }
    }

    return false;
}
