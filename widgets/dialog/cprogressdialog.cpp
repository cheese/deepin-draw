#include "cprogressdialog.h"

#include <DLabel>

#include <QVBoxLayout>
#include <QApplication>
#include <QDesktopWidget>
#include <QDebug>

CProgressDialog::CProgressDialog(DWidget *parent)
    : DDialog(parent)
{
    initUI();
}

void CProgressDialog::initUI()
{
    setFixedSize(QSize(400, 80));
    setModal(true);
    setCloseButtonVisible(false);

    m_label = new DLabel(this);
    m_label->setText(tr("正在导出"));

    m_progressBar = new DProgressBar(this);
    m_progressBar->setMinimum(0);
    m_progressBar->setMaximum(100);
    m_progressBar->setValue(0);
    m_progressBar->setAlignment(Qt::AlignHCenter);


    DWidget *widget = new DWidget(this);

    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    hLayout->addStretch();
    hLayout->addWidget(m_label);
    hLayout->addStretch();


    QVBoxLayout *layout = new QVBoxLayout(widget);
    layout->setContentsMargins(0, 0, 0, 0);
    layout->setSpacing(8);
    layout->addStretch();
    layout->addLayout(hLayout);
    layout->addWidget(m_progressBar);
    layout->addStretch();

    addContent(widget);
}

void CProgressDialog::slotupDateProcessBar(int value)
{
    m_progressBar->setValue(value);
}

void CProgressDialog::showProgressDialog(EProgressDialogType type, bool isOpenByDDF)
{
    if (SaveDDF == type) {
        m_label->setText(tr("正在导出"));
    } else if (LoadDDF == type) {
        m_label->setText(tr("正在导入"));
    }
    m_progressBar->reset();

    if (isOpenByDDF) {
        showInCenter();
    } else {
        show();

        QWidget *mainWindow = this->parentWidget()->parentWidget()->window();
        QPoint gp = mainWindow->mapToGlobal(QPoint(0, 0));
        move((mainWindow->width() - this->width()) / 2 + gp.x(),
             (mainWindow->height() - this->sizeHint().height()) / 2 + gp.y());
    }
}

void CProgressDialog::showInCenter()
{
    show();

    QRect rect = qApp->desktop()->screenGeometry();

    QPoint center = rect.center();
    QPoint pos = center - QPoint(this->width() / 2, this->height() / 2);
    this->move(pos);

}
