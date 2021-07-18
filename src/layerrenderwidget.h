#ifndef LAYERRENDERWIDGET_H
#define LAYERRENDERWIDGET_H

#include <QWidget>

namespace Ui {
class LayerRenderWidget;
}

class LayerRenderWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LayerRenderWidget(QWidget *parent = nullptr);
    ~LayerRenderWidget();

private:
    Ui::LayerRenderWidget *ui;
};

#endif // LAYERRENDERWIDGET_H
