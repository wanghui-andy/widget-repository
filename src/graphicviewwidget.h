#ifndef GRAPHICVIEWWIDGET_H
#define GRAPHICVIEWWIDGET_H

#include <QMouseEvent>
#include <QPoint>
#include <QWidget>

namespace Ui
{
class GraphicViewWidget;
}

class GraphicViewWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphicViewWidget(QWidget *parent = nullptr);
    ~GraphicViewWidget();

private:
    Ui::GraphicViewWidget *ui;
};

#endif  // GRAPHICVIEWWIDGET_H
