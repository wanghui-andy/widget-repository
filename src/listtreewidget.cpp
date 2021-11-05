#include "listtreewidget.h"
#include "ui_listtreewidget.h"
#include <QComboBox>
#include <QDebug>
#include <QLineEdit>

ListTreeWidget::ListTreeWidget(QWidget *parent) : QWidget(parent), ui(new Ui::ListTreeWidget)
{
    ui->setupUi(this);
    initWidgets();
}

ListTreeWidget::~ListTreeWidget()
{
    delete ui;
}

void ListTreeWidget::initWidgets()
{
    initListWidget();
    initTreeWidget();
}

void ListTreeWidget::initListWidget()
{
    for (auto &param : vec_param)
    {
        ui->listWidget->addItem(QString::fromLocal8Bit(param.type_name.data()));
    }

    connect(ui->listWidget, SIGNAL(clicked(QModelIndex)), this, SLOT(listWidgetClick(QModelIndex)));
}

void ListTreeWidget::initTreeWidget()
{
    ui->treeWidget->header()->setSectionsClickable(true);
    connect(ui->treeWidget->header(), &QHeaderView::sectionClicked, this, &ListTreeWidget::slotHeadClicked);
    refreshTreeWidget(0);
}

void ListTreeWidget::refreshTreeWidget(int index)
{
    ui->treeWidget->clear();
    QTreeWidgetItem *header = new QTreeWidgetItem(QStringList() << "");
    ui->treeWidget->setHeaderItem(header);
    // header
    std::vector<std::string> vec_subtype = vec_param[index].vec_subtype;
    const int cols = vec_subtype.size();
    QStringList list_header;
    list_header << "";
    for (auto &header : vec_subtype)
    {
        list_header << QString::fromLocal8Bit(header.data());
    }
    header = new QTreeWidgetItem(list_header);
    ui->treeWidget->setHeaderItem(header);

    // item
    std::vector<ParamItem> paramitems = vec_param[index].vec_param_item;
    const int item_num = paramitems.size();
    for (int item_index = 0; item_index < item_num; ++item_index)
    {
        QTreeWidgetItem *parent_item =
            new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit(paramitems[item_index].item_name.data()));
        ui->treeWidget->addTopLevelItem(parent_item);

        // parameters
        std::vector<Param> params = paramitems[item_index].vec_param;
        const int param_num_in_item = params.size();
        for (int i = 0; i < param_num_in_item; ++i)
        {
            QTreeWidgetItem *param =
                new QTreeWidgetItem(QStringList() << QString::fromLocal8Bit(params[i].param_name.data()));
            parent_item->addChild(param);

            for (int col = 1; col < cols + 1; ++col)
            {
                std::vector<Data> vec_data = params[i].vec_data;
                Data data = vec_data[col - 1];
                if (typeInt == data.type || typeFloat == data.type)
                {
                    QString editor_str = QString::fromLocal8Bit(data.vec_element[0].data());
                    QLineEdit *editor = new QLineEdit(editor_str);
                    ui->treeWidget->setItemWidget(param, col, editor);
                }
                else if (typeEnum == data.type)
                {
                    QComboBox *combobox = new QComboBox();
                    QStringList comb_str_list;
                    for (auto &str : data.vec_element)
                    {
                        comb_str_list << QString::fromLocal8Bit(str.data());
                    }
                    combobox->addItems(comb_str_list);
                    ui->treeWidget->setItemWidget(param, col, combobox);
                }
                else
                {
                }
            }
        }
    }
    ui->treeWidget->expandAll();

    //    ui->treeWidget->setStyleSheet(QString::fromUtf8(
    //        "::item  {\n"
    //        "    border-right:1px solid light-gray; border-bottom:1px solid light-gray;\n"
    //        "}"
    //        "::branch{ \n"
    //        "border-bottom:1px solid light-gray;}"
    //        "::branch:has-children:closed{\n"
    //        "image: url('C:/Qt/Qt5.14.1/5.14.1/Src/qtbase/src/widgets/doc/images/stylesheet-branch-closed.png');"
    //        "}"
    //        "::branch:has-children:closed:hover{\n"
    //        "image: url('C:/Qt/Qt5.14.1/5.14.1/Src/qtbase/src/widgets/doc/images/stylesheet-branch-closed.png');"
    //        "}"
    //        "::branch:has-children:open{\n"
    //        "image: url('C:/Qt/Qt5.14.1/5.14.1/Src/qtbase/src/widgets/doc/images/stylesheet-branch-open.png');"
    //        "}"
    //        "::branch:has-children:open:hover{\n"
    //        "image: url('C:/Qt/Qt5.14.1/5.14.1/Src/qtbase/src/widgets/doc/images/stylesheet-branch-open.png');"
    //        "}"));
}

void ListTreeWidget::listWidgetClick(QModelIndex index)
{
    refreshTreeWidget(index.row());
}

void ListTreeWidget::slotHeadClicked(int index)
{
    qDebug() << "head clicked: " << index;
}
