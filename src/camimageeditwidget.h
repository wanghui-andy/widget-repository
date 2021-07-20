#ifndef CAMIMAGEEDITWIDGET_H
#define CAMIMAGEEDITWIDGET_H

#include <QWidget>

namespace Ui
{
class CAMImageEditWidget;
}

class CAMImageEditWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CAMImageEditWidget(QWidget *parent = nullptr);
    ~CAMImageEditWidget();

private:
    void initWidgets();

private:
    Ui::CAMImageEditWidget *ui;
};

#endif  // CAMIMAGEEDITWIDGET_H
