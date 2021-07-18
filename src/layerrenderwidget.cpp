#include "layerrenderwidget.h"
#include "ui_layerrenderwidget.h"

LayerRenderWidget::LayerRenderWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::LayerRenderWidget)
{
    ui->setupUi(this);
}

LayerRenderWidget::~LayerRenderWidget()
{
    delete ui;
}
