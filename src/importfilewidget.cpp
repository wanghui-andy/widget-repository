#include "importfilewidget.h"
#include "ui_importfilewidget.h"
#include <QComboBox>
#include <QFileDialog>

const std::vector<std::string> c_levels = {"第一层", "第二层", "第三层"};

const std::vector<std::string> c_sides = {"正面", "反面"};

const int c_level_combobox_col = 1;
const int c_side_combobox_col = 2;
const int c_delete_button_col = 3;

ImportFileWidget::ImportFileWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ImportFileWidget)
{
    ui->setupUi(this);
    initWidgets();
}

ImportFileWidget::~ImportFileWidget()
{
    delete ui;
}

void ImportFileWidget::initWidgets()
{
    ui->treeWidget->header()->setVisible(false);
}

void ImportFileWidget::on_importPushButton_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, QString::fromLocal8Bit("选择文件"), "C:", tr("AllFiles(*)"));

    if (m_isFirstFile && !filePath.isEmpty())
    {
        m_isFirstFile = false;

        // header
        ui->treeWidget->header()->setVisible(true);
        QTreeWidgetItem *header =
            new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit("文件名") << QString::fromLocal8Bit("层别")
                                              << QString::fromLocal8Bit("正反面") << QString::fromLocal8Bit("删除"));
        ui->treeWidget->setHeaderItem(header);
    }

    if (!filePath.isEmpty())
    {
        QFileInfo fileInfo(filePath);
        QTreeWidgetItem *item = new QTreeWidgetItem(QStringList() << fileInfo.fileName());
        // check
        item->setCheckState(0, Qt::Unchecked);
        ui->treeWidget->addTopLevelItem(item);

        // combobox
        QComboBox *level_combobox = new QComboBox();
        QStringList comb_str_list;
        for (auto &str : c_levels)
        {
            comb_str_list << QString::fromLocal8Bit(str.data());
        }
        level_combobox->addItems(comb_str_list);
        connect(level_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotLevelCurrentIndexChanged(int)));
        ui->treeWidget->setItemWidget(item, c_level_combobox_col, level_combobox);
        int row = ui->treeWidget->indexOfTopLevelItem(item);
        ControlIndex index = ControlIndex(row, c_level_combobox_col);
        m_control_map.insert(std::make_pair((QObject *)level_combobox, index));

        QComboBox *side_combobox = new QComboBox();
        comb_str_list.clear();
        for (auto &str : c_sides)
        {
            comb_str_list << QString::fromLocal8Bit(str.data());
        }
        side_combobox->addItems(comb_str_list);
        connect(side_combobox, SIGNAL(currentIndexChanged(int)), this, SLOT(slotSideCurrentIndexChanged(int)));
        ui->treeWidget->setItemWidget(item, c_side_combobox_col, side_combobox);
        row = ui->treeWidget->indexOfTopLevelItem(item);
        index = ControlIndex(row, c_side_combobox_col);
        m_control_map.insert(std::make_pair((QObject *)side_combobox, index));

        // button
        QPushButton *deleteButton = new QPushButton();
        connect(deleteButton, SIGNAL(clicked()), this, SLOT(slotDeleteButtonClicked()));
        ui->treeWidget->setItemWidget(item, c_delete_button_col, deleteButton);
        row = ui->treeWidget->indexOfTopLevelItem(item);
        index = ControlIndex(row, c_delete_button_col);
        m_control_map.insert(std::make_pair((QObject *)deleteButton, index));
    }
}

void ImportFileWidget::slotLevelCurrentIndexChanged(int index)
{
    ControlIndex control_index = m_control_map[sender()];
}

void ImportFileWidget::slotSideCurrentIndexChanged(int index)
{
    ControlIndex control_index = m_control_map[sender()];
}

void ImportFileWidget::on_resetPushButton_clicked() {}

void ImportFileWidget::on_selectAllCheckBox_clicked(bool checked)
{
    int count = ui->treeWidget->topLevelItemCount();
    for (int index = 0; index < count; index++)
    {
        if (checked)
        {
            ui->treeWidget->topLevelItem(index)->setCheckState(0, Qt::Checked);
        }
        else
        {
            ui->treeWidget->topLevelItem(index)->setCheckState(0, Qt::Unchecked);
        }
    }
}

void ImportFileWidget::on_deleteAllPushButton_clicked()
{
    ui->treeWidget->clear();
}

void ImportFileWidget::slotDeleteButtonClicked()
{
    ControlIndex index = m_control_map[sender()];

    ui->treeWidget->takeTopLevelItem(index.row);

    // refresh row
    for (auto &control_index : m_control_map)
    {
        if (control_index.second.row > index.row)
        {
            control_index.second.row--;
        }
    }
}
