#include "mainwindow.h"
#include "importfilewidget.h"
#include "layereditwidget.h"
#include "layerrenderwidget.h"
#include "listtreewidget.h"
#include "procedurenavigationwidget.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InitWidgets();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitWidgets()
{
    //    ListTreeWidget *list_tree_widget = new ListTreeWidget();
    //    ui->horizontalLayout->addWidget(list_tree_widget);

    LayerRenderWidget *widge1 = new LayerRenderWidget();
    ui->horizontalLayout_2->addWidget(widge1);

    LayerEditWidget *widget = new LayerEditWidget();
    ui->horizontalLayout->addWidget(widget);
}
