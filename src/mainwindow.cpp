#include "mainwindow.h"
#include "camimageeditwidget.h"
#include "camlayersettingwidget.h"
#include "graphicviewwidget.h"
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
    ListTreeWidget *list_tree_widget = new ListTreeWidget();
    ui->horizontalLayout_3->addWidget(list_tree_widget);

    //    CAMImageEditWidget *widge1 = new CAMImageEditWidget();
    //    ui->horizontalLayout_2->addWidget(widge1);

    //    LayerEditWidget *widget = new LayerEditWidget();
    //    ui->horizontalLayout->addWidget(widget);

    //    GraphicViewWidget *view_widget = new GraphicViewWidget();
    //    ui->horizontalLayout_3->addWidget(view_widget);
}
