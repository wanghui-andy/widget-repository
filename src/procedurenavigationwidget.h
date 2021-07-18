#ifndef PROCEDURENAVIGATIONWIDGET_H
#define PROCEDURENAVIGATIONWIDGET_H

#include <QLabel>
#include <QWidget>
#include <vector>

namespace Ui
{
class ProcedureNavigationWidget;
}

class ProcedureNavigationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ProcedureNavigationWidget(QWidget *parent = nullptr);
    ~ProcedureNavigationWidget();

private slots:
    void on_previousPushButton_clicked();

    void on_nextPushButton_clicked();

private:
    void initWidgets();
    void setReadyStatus(unsigned int step);
    void setProcessingStatus(unsigned int step);
    void setFinishStatus(unsigned int step);

private:
    Ui::ProcedureNavigationWidget *ui;

    struct StepControl
    {
        StepControl(QLabel *light, QLabel *description) : proclight(light), procdescription(description) {}
        QLabel *proclight;
        QLabel *procdescription;
    };

    std::vector<StepControl> m_stepControls;
    unsigned int m_curstep = 0;
};

#endif  // PROCEDURENAVIGATIONWIDGET_H
