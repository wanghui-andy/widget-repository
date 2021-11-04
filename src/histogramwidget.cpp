#include "histogramwidget.h"
#include "ui_histogramwidget.h"
#include <QAreaSeries>
#include <QChart>
#include <QDebug>
#include <QScatterSeries>
#include <QSplineSeries>

HistogramWidget::HistogramWidget(QWidget *parent) : QWidget(parent), ui(new Ui::HistogramWidget)
{
    ui->setupUi(this);

    m_chart = new AVIChartWidget();
    m_chart_view = new AVIChartView(m_chart, this);
    m_chart_view->setRenderHint(QPainter::Antialiasing);
    ui->chartLayout->addWidget(m_chart_view);

    QLineSeries *min_lineSeries = new QLineSeries();
    min_lineSeries->append(50, 10);
    min_lineSeries->append(50, 0);
    m_chart->setMinLineSeries(min_lineSeries);

    QLineSeries *lineSeries_max = new QLineSeries();
    lineSeries_max->append(200, 10);
    lineSeries_max->append(200, 0);

    QSplineSeries *splineSeries = new QSplineSeries();
    splineSeries->setName("spline");
    splineSeries->append(50, 0);
    splineSeries->append(125, 10);
    splineSeries->append(200, 0);
    //    *splineSeries << QPointF(11, 1) << QPointF(17, 2) << QPointF(20, 2);
    //    // 标记点
    //    QScatterSeries *scatterSeries = new QScatterSeries();
    //    scatterSeries->setPointLabelsFormat("@yPoint");
    //    scatterSeries->setPointLabelsVisible();
    //    scatterSeries->setMarkerSize(8);
    //    scatterSeries->append(0, 6);
    //    scatterSeries->append(2, 4);
    //    scatterSeries->append(3, 8);
    //    scatterSeries->append(7, 4);
    //    scatterSeries->append(10, 5);
    //    *scatterSeries << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);

    //区域填充
    QAreaSeries *series = new QAreaSeries(splineSeries);
    series->setName("Batman");
    //    QPen pen(0x059605);
    //    pen.setWidth(3);
    //    series->setPen(pen);
    series->setBrush(Qt::red);

    m_chart->legend()->hide();
    m_chart->addSeries(splineSeries);
    m_chart->addSeries(lineSeries_max);
    m_chart->addSeries(series);
    m_chart->createDefaultAxes();
    m_chart->axisX()->setRange(0, 255);
    m_chart->axisX()->setVisible(false);
    m_chart->axisY()->setVisible(false);
    QMargins margin;
    margin.setLeft(0);
    margin.setRight(0);
    m_chart->setMargins(margin);
}

HistogramWidget::~HistogramWidget()
{
    delete ui;
}

void HistogramWidget::updateMinLabelPos(const QPoint &point)
{
    ui->minLabel->move(point.x() - 20, ui->minLabel->pos().y());
}
