#ifndef LAYEREDITWIDGET_H
#define LAYEREDITWIDGET_H

#include <QWidget>

namespace Ui {
class LayerEditWidget;
}

class LayerEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LayerEditWidget(QWidget *parent = nullptr);
    ~LayerEditWidget();

private:
    Ui::LayerEditWidget *ui;
};

#endif // LAYEREDITWIDGET_H
