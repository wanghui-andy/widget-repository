#ifndef IMPORTFILEWIDGET_H
#define IMPORTFILEWIDGET_H

#include <QTreeWidgetItem>
#include <QWidget>
#include <map>

namespace Ui
{
class ImportFileWidget;
}

class ImportFileWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ImportFileWidget(QWidget *parent = nullptr);
    ~ImportFileWidget();

private slots:
    void on_importPushButton_clicked();

    void on_resetPushButton_clicked();

    void on_selectAllCheckBox_clicked(bool checked);

    void on_deleteAllPushButton_clicked();

private:
    void initWidgets();

private slots:
    void slotLevelCurrentIndexChanged(int index);
    void slotSideCurrentIndexChanged(int index);
    void slotDeleteButtonClicked();

private:
    Ui::ImportFileWidget *ui;

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

#endif  // IMPORTFILEWIDGET_H
