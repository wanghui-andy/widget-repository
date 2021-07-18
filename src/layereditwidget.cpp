#include "layereditwidget.h"
#include "ui_layereditwidget.h"

LayerEditWidget::LayerEditWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerEditWidget)
{
    ui->setupUi(this);
}

LayerEditWidget::~LayerEditWidget()
{
    delete ui;
}
