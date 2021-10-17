#include "stdafx.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QLabel>
#include <QHBoxLayout>
#include "tips_widget.h"
#include "basedwidget/image_button.h"

TipsWidget::TipsWidget(int w, int h, const QString& title, QWidget *parent)
    : PopupWidget(title, parent)
{
    setFixedSize(w, h);
    initUi();
}

TipsWidget::~TipsWidget()
{
}

void TipsWidget::showTips(const QString& tips)
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();

    show();

    move((screen.width() - width()) / 2, (screen.height() - height()) / 2);

    m_QTextBrowser->setText(tips);
}

void TipsWidget::initUi()
{
    setTitleWidgetWidth(this->width());

    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    move(screen.width() / 3, screen.height() / 3);

    m_QTextBrowser = new QTextBrowser(this);
    m_QTextBrowser->resize(width() - 30, height() - 80);
    m_QTextBrowser->move(15, 60);
}
