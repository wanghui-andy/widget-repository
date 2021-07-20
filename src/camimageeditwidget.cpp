#include "camimageeditwidget.h"
#include "ui_camimageeditwidget.h"
#include <QLabel>

const int c_layer_col = 1;
const int c_side_col = 2;

CAMImageEditWidget::CAMImageEditWidget(QWidget *parent) : QWidget(parent), ui(new Ui::CAMImageEditWidget)
{
    ui->setupUi(this);
    initWidgets();
}

CAMImageEditWidget::~CAMImageEditWidget()
{
    delete ui;
}

void CAMImageEditWidget::initWidgets()
{
    QTreeWidgetItem *header =
        new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("文件名") << QString::fromLocal8Bit("层别")
                                          << QString::fromLocal8Bit("正反面"));
    ui->treeWidget->setHeaderItem(header);

    {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << "1.gbr");
        // check
        item->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(item);

        QLabel *layer_lebel = new QLabel();
        layer_lebel->setText(QString::fromLocal8Bit("金面"));
        ui->treeWidget->setItemWidget(item, c_layer_col, layer_lebel);

        QLabel *side_lebel = new QLabel();
        side_lebel->setText(QString::fromLocal8Bit("正面"));
        ui->treeWidget->setItemWidget(item, c_side_col, side_lebel);
    }

    {
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << "2.gbr");
        // check
        item->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(item);

        QLabel *layer_lebel = new QLabel();
        layer_lebel->setText(QString::fromLocal8Bit("V-cut"));
        ui->treeWidget->setItemWidget(item, c_layer_col, layer_lebel);

        QLabel *side_lebel = new QLabel();
        side_lebel->setText(QString::fromLocal8Bit("双面"));
        ui->treeWidget->setItemWidget(item, c_side_col, side_lebel);
    }
}
