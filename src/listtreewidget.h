#ifndef LISTTREEWIDGET_H
#define LISTTREEWIDGET_H

#include <QModelIndex>
#include <QWidget>

namespace Ui
{
class ListTreeWidget;
}

enum DataType
{
    typeInt = 0,
    typeFloat,
    typeEnum,
};

struct Data
{
    DataType type;
    std::vector<std::string> vec_element;
};

struct Param
{
    std::string param_name;
    std::vector<Data> vec_data;
};

struct ParamItem
{
    std::string item_name;
    std::vector<Param> vec_param;
};

struct DetectParameter
{
    std::string type_name;
    std::vector<std::string> vec_subtype;
    std::vector<ParamItem> vec_param_item;
};

class ListTreeWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ListTreeWidget(QWidget *parent = nullptr);
    ~ListTreeWidget();

private:
    void initWidgets();
    void initListWidget();
    void initTreeWidget();
    void refreshTreeWidget(int index);

private slots:
    void listWidgetClick(QModelIndex index);

private:
    Ui::ListTreeWidget *ui;

private:
    std::vector<DetectParameter> vec_param = {

        {
            "第一类参数",
            {"第一列参数", "第二列参数", "第三列参数", "第四列参数", "第五列参数", "第六列参数"},
            {{"第一个参数item",
              {{"第一个参数",
                {
                    {typeInt, {"1"}},
                    {typeInt, {"2"}},
                    {typeInt, {"3"}},
                    {typeInt, {"4"}},
                    {typeInt, {"5"}},
                    {typeInt, {"6"}},
                }},
               {"第二个参数",
                {
                    {typeEnum, {"TRUE", "FALSE"}},
                    {typeEnum, {"TRUE", "FALSE"}},
                    {typeEnum, {"TRUE", "FALSE"}},
                    {typeEnum, {"TRUE", "FALSE"}},
                    {typeEnum, {"TRUE", "FALSE"}},
                    {typeEnum, {"TRUE", "FALSE"}},
                }},
               {"第三个参数",
                {
                    {typeInt, {"21"}},
                    {typeInt, {"22"}},
                    {typeInt, {"23"}},
                    {typeInt, {"24"}},
                    {typeInt, {"25"}},
                    {typeInt, {"26"}},
                }}}},
             {"第二个参数item",
              {{"第一个参数",
                {
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.4"}},
                    {typeFloat, {"0.3"}},
                    {typeFloat, {"0.2"}},
                    {typeFloat, {"0.1"}},
                    {typeFloat, {"0.05"}},
                }},
               {"第二个参数",
                {
                    {typeInt, {"31"}},
                    {typeInt, {"32"}},
                    {typeInt, {"33"}},
                    {typeInt, {"34"}},
                    {typeInt, {"35"}},
                    {typeInt, {"36"}},
                }},
               {"第三个参数",
                {
                    {typeInt, {"41"}},
                    {typeInt, {"42"}},
                    {typeInt, {"43"}},
                    {typeInt, {"44"}},
                    {typeInt, {"45"}},
                    {typeInt, {"46"}},
                }}}}},

        },
        {
            "第二类参数",
            {"first column param", "second column param", "third column param", "fourth column param"},
            {{"fisr param item",
              {{"parameter 1",
                {
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                }},
               {"parameter 2",
                {
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                }},
               {"parameter 3",
                {
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                    {typeFloat, {"0.5"}},
                }}}},
             {"second param item",
              {{"parameter 1",
                {
                    {typeInt, {"9"}},
                    {typeInt, {"8"}},
                    {typeInt, {"7"}},
                    {typeInt, {"6"}},
                }},
               {"parameter 2",
                {
                    {typeInt, {"9"}},
                    {typeInt, {"8"}},
                    {typeInt, {"7"}},
                    {typeInt, {"6"}},
                }},
               {"parameter 3",
                {
                    {typeInt, {"9"}},
                    {typeInt, {"8"}},
                    {typeInt, {"7"}},
                    {typeInt, {"6"}},
                }}}}},
        },
        {
            "第三类参数",
            {"第一列参数", "第二列参数", "第三列参数", "第四列参数", "第五列参数"},
            {{"第一个参数item",
              {{"第一个参数",
                {
                    {typeFloat, {"1.1"}},
                    {typeFloat, {"1.2"}},
                    {typeFloat, {"1.3"}},
                    {typeFloat, {"1.4"}},
                    {typeFloat, {"1.5"}},
                }},
               {"第二个参数",
                {
                    {typeFloat, {"2.1"}},
                    {typeFloat, {"2.2"}},
                    {typeFloat, {"2.3"}},
                    {typeFloat, {"2.4"}},
                    {typeFloat, {"2.5"}},
                }},
               {"第三个参数",
                {
                    {typeFloat, {"32.1"}},
                    {typeFloat, {"32.2"}},
                    {typeFloat, {"32.3"}},
                    {typeFloat, {"32.4"}},
                    {typeFloat, {"32.5"}},
                }}}},
             {"第二个参数item",
              {{"第一个参数",
                {
                    {typeInt, {"1"}},
                    {typeInt, {"2"}},
                    {typeInt, {"3"}},
                    {typeInt, {"4"}},
                    {typeInt, {"5"}},
                }},
               {"第二个参数",
                {
                    {typeInt, {"1"}},
                    {typeInt, {"2"}},
                    {typeInt, {"3"}},
                    {typeInt, {"4"}},
                    {typeInt, {"5"}},
                }},
               {"第三个参数",
                {
                    {typeInt, {"1"}},
                    {typeInt, {"2"}},
                    {typeInt, {"3"}},
                    {typeInt, {"4"}},
                    {typeInt, {"5"}},
                }}}}},
        },
        //        {
        //            "第四类参数",
        //            {"第一列参数", "第二列参数"},
        //            {{"第一个参数item",
        //              {{"第一个参数", {122, 223, 345, 471, 545, 666, 789}},
        //               {"第二个参数", {112, 223, 347, 457, 531, 687, 745}},
        //               {"第三个参数", {131, 2123, 312, 42, 58, 67, 71}}}},
        //             {"第二个参数item",
        //              {{"第一个参数", {123, 22, 344, 412, 5.87, 6.85, 8.7}},
        //               {"第二个参数", {11, 23, 355, 42, 5.7, 6.2, 7.1}},
        //               {"第三个参数", {12, 23, 36, 43.0, 5.6, 6, 7.2}}}}},
        //        }

    };
};

#endif  // LISTTREEWIDGET_H
