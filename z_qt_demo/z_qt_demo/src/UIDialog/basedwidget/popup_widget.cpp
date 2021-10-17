#include "stdafx.h"
#include <QAction>
#include <QHBoxLayout>
#include "popup_widget.h"
#include "image_button.h"

PopupWidgetTitle::PopupWidgetTitle(const QString& title, QWidget *parent)
    : BasedStyleShetWidget(parent)
    , m_title(title)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("PopupWidgetTitle");
    initUi();
}

PopupWidgetTitle::~PopupWidgetTitle()
{
    if (m_titleLabel)
    {
        delete m_titleLabel;
        m_titleLabel = nullptr;
    }
}

void PopupWidgetTitle::updateTitle(const QString& title)
{
    m_title = title;
    m_titleLabel->setText(title);
}

void PopupWidgetTitle::initUi()
{
    m_titleLabel = new QLabel(m_title);
    m_titleLabel->setObjectName("PopupWidgetTitle");

    QWidget *titleWidget = new QWidget(this);
    QHBoxLayout *titleLayout = new QHBoxLayout(titleWidget);
    titleLayout->addWidget(m_titleLabel, 0, Qt::AlignVCenter);
    titleLayout->setContentsMargins(10, 10, 10, 10);

    ImageButton *closeButton = new ImageButton(":/qt_demo/close");
    closeButton->setCursorEnable(true);
    connect(closeButton, SIGNAL(clicked(int)), this, SIGNAL(closeClicked()));

    QWidget *buttonWidget = new QWidget;
    QHBoxLayout *buttnLayout = new QHBoxLayout(buttonWidget);
    buttnLayout->addWidget(closeButton, 0, Qt::AlignVCenter);
    buttnLayout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *mainLayout = new QHBoxLayout(this);
    mainLayout->addWidget(titleWidget, 0, Qt::AlignLeft | Qt::AlignTop);
    mainLayout->addStretch();
    mainLayout->addWidget(buttonWidget, 0, Qt::AlignRight | Qt::AlignVCenter);
    mainLayout->setContentsMargins(5, 5, 5, 5);
}

PopupWidget::PopupWidget(const QString& title/* = ""*/, QWidget *parent/* = 0*/)
    : BasedWidget(parent)
    , m_title(title)
{
    // 窗口最前显示
    setWindowFlags(Qt::Widget 
        | Qt::FramelessWindowHint 
        | Qt::WindowSystemMenuHint 
        | Qt::WindowStaysOnTopHint);
    setProperty("type", "PopUpWidget");
    initUi();
    initConnect();
}

PopupWidget::~PopupWidget()
{

}

void PopupWidget::onCloseBtnClicked()
{
    m_show = false;
    close();
}

void PopupWidget::closeEvent(QCloseEvent*)
{

}

void PopupWidget::initUi()
{
    // 标题widget
    m_spTitleWidget = std::make_shared<PopupWidgetTitle>(m_title, this);
    m_spTitleWidget->show();
    m_spTitleWidget->move(0, 0);
}

void PopupWidget::initConnect()
{
    connect(m_spTitleWidget.get(), SIGNAL(closeClicked()), this, SLOT(onCloseBtnClicked()));
}

void PopupWidget::setLabel(const QString& content)
{
 
}

void PopupWidget::setTitleWidgetWidth(int width)
{
    m_spTitleWidget->setFixedWidth(width);
}

void PopupWidget::setTitleWidgetHeight(int height)
{
    m_spTitleWidget->setFixedHeight(height);
}

void PopupWidget::updateTitle(const QString& title)
{
    m_title = title;
    m_spTitleWidget->updateTitle(title);
}
