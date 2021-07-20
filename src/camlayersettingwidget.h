#ifndef CAMLAYERSETTINGWIDGET_H
#define CAMLAYERSETTINGWIDGET_H

#include <QWidget>

namespace Ui
{
class CAMLayerSettingWidget;
}

class CAMLayerSettingWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CAMLayerSettingWidget(QWidget *parent = nullptr);
    ~CAMLayerSettingWidget();

private slots:
    void on_importCAMPushButton_clicked();

    void on_resetPushButton_clicked();

    void on_checkBox_clicked(bool checked);

    void on_ressetPushButton2_clicked();

    void slotLevelCurrentIndexChanged(int index);
    void slotSideCurrentIndexChanged(int index);
    void slotDeleteButtonClicked();

    void on_deletaAllPushButton_clicked();

private:
    void initWidgets();

private:
    Ui::CAMLayerSettingWidget *ui;

    bool m_isFirstFile = true;

    struct ControlIndex
    {
        ControlIndex() {}
        ControlIndex(int r, int c) : row(r), col(c) {}
        ControlIndex &operator=(const ControlIndex &other)
        {
            row = other.row;
            col = other.col;
            return *this;
        }
        int row;
        int col;
    };
    std::map<QObject *, ControlIndex> m_control_map;
};

#endif  // CAMLAYERSETTINGWIDGET_H
