#include "procedurenavigationwidget.h"
#include "ui_procedurenavigationwidget.h"

const QString c_ready_pic = "D:\\projects\\widget-repository\\src\\icon\\ready.png";
const QString c_processing_pic = "D:\\projects\\widget-repository\\src\\icon\\processing.png";
const QString c_finish_pic = "D:\\projects\\widget-repository\\src\\icon\\finish.png";

ProcedureNavigationWidget::ProcedureNavigationWidget(QWidget *parent)
    : QWidget(parent), ui(new Ui::ProcedureNavigationWidget)
{
    ui->setupUi(this);
    initWidgets();
}

ProcedureNavigationWidget::~ProcedureNavigationWidget()
{
    delete ui;
}

void ProcedureNavigationWidget::initWidgets()
{
    ui->previousPushButton->setEnabled(false);

    m_stepControls =
        std::vector<StepControl>({StepControl(ui->label1, ui->steplabel1), StepControl(ui->label2, ui->steplabel2),
                                  StepControl(ui->label3, ui->steplabel3), StepControl(ui->label4, ui->steplabel4),
                                  StepControl(ui->label5, ui->steplabel5), StepControl(ui->label6, ui->steplabel6),
                                  StepControl(ui->label7, ui->steplabel7), StepControl(ui->label8, ui->steplabel8),
                                  StepControl(ui->label9, ui->steplabel9)});
    for (unsigned int i = 0; i < m_stepControls.size(); i++)
    {
        if (0 == i)
        {
            setProcessingStatus(i);
        }
        else
        {
            setReadyStatus(i);
        }
    }
}

void ProcedureNavigationWidget::on_previousPushButton_clicked()
{
    if (m_curstep >= 1)
    {
        if (m_curstep == m_stepControls.size() - 1)
        {
            ui->nextPushButton->setEnabled(true);
        }

        setReadyStatus(m_curstep);
        m_curstep--;
        setProcessingStatus(m_curstep);

        if (0 == m_curstep)
        {
            ui->previousPushButton->setEnabled(false);
        }
    }
}

void ProcedureNavigationWidget::on_nextPushButton_clicked()
{
    setFinishStatus(m_curstep);

    if (0 == m_curstep)
    {
        ui->previousPushButton->setEnabled(true);
    }

    m_curstep++;

    if (m_curstep == m_stepControls.size() - 1)
    {
        setFinishStatus(m_curstep);
        ui->nextPushButton->setEnabled(false);
    }
    else
    {
        setProcessingStatus(m_curstep);
    }
}

void ProcedureNavigationWidget::setReadyStatus(unsigned int step)
{
    m_stepControls[step].proclight->setPixmap(QPixmap(c_ready_pic));

    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::gray);
    m_stepControls[step].procdescription->setPalette(pe);
}

void ProcedureNavigationWidget::setProcessingStatus(unsigned int step)
{
    m_stepControls[step].proclight->setPixmap(QPixmap(c_processing_pic));

    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::black);
    m_stepControls[step].procdescription->setPalette(pe);
}

void ProcedureNavigationWidget::setFinishStatus(unsigned int step)
{
    m_stepControls[step].proclight->setPixmap(QPixmap(c_finish_pic));

    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::gray);
    m_stepControls[step].procdescription->setPalette(pe);
}
