#include "graphicviewwidget.h"
#include "ui_graphicviewwidget.h"

GraphicViewWidget::GraphicViewWidget(QWidget *parent) : QWidget(parent), ui(new Ui::GraphicViewWidget)
{
    ui->setupUi(this);
}

GraphicViewWidget::~GraphicViewWidget()
{
    delete ui;
}
