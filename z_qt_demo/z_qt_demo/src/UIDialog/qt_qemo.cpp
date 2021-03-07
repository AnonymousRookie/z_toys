#include "stdafx.h"
#include "qt_qemo.h"
#include "top_widget.h"
#include "body_widget.h"
#include "defines.h"
#include "buttons_widget.h"
#include "display_widgets_widget.h"
#include "input_widgets_widget.h"
#include "item_views_widget.h"
#include "item_widgets_widget.h"
#include "events_widget.h"

QtDemo::QtDemo(QWidget *parent)
    : QWidget(parent)
{
    m_ui.setupUi(this);
    setObjectName("QtDemoWidget");
    showFullScreen();
    init();
}

QtDemo::~QtDemo()
{
    uninit();
}

void QtDemo::init()
{
    initUi();
    initConnect();
}

void QtDemo::uninit()
{
    if (!m_bodyWidget) {
        delete m_bodyWidget;
        m_bodyWidget = nullptr;
    }
}

void QtDemo::initUi()
{
    int xOffset = 0;
    int yOffset = 0;

    m_topWidget = std::make_unique<TopWidget>(this);
    m_topWidget->show();

    m_bodyWidget = new BodyWidget(this);
    m_bodyWidget->show();

    m_buttonsWidget = std::make_unique<ButtonsWidget>(m_bodyWidget);
    m_displayWidgetsWidget = std::make_unique<DisplayWidgetsWidget>(m_bodyWidget);
    m_inputWidgetsWidget = std::make_unique<InputWidgetsWidget>(m_bodyWidget);
    m_itemViewsWidget = std::make_unique<ItemViewsWidget>(m_bodyWidget);
    m_itemWidgetsWidget = std::make_unique<ItemWidgetsWidget>(m_bodyWidget);
    m_eventsWidget = std::make_unique<EventsWidget>(m_bodyWidget);
}

void QtDemo::initConnect()
{
    connect(m_topWidget.get(), SIGNAL(menuBtnClicked(int)), this, SLOT(onMenuBtnClicked(int)));
}

void QtDemo::setTranslator(std::shared_ptr<QTranslator> translator)
{
    m_translator = translator;
}

void QtDemo::switchLanguage(Language language)
{
    QString language_qm;
    switch(language)
    {
    case Language_ZH:
        language = Language_ZH;
        language_qm = QString(":/qm/qt_demo_zh");
        break;

    case Language_EN:
        language = Language_EN;
        language_qm = QString(":/qm/qt_demo_en");
        break;

    default:
        language = Language_ZH;
        language_qm = QString(":/qm/qt_demo_zh");
    }
}

void QtDemo::onMenuBtnClicked(int btnId)
{
    switch (btnId)
    {
    case FunctionType_Buttons:
        m_buttonsWidget->show();
        break;
    case FunctionType_DisplayWidgets:
        m_displayWidgetsWidget->show();
        break;
    case FunctionType_ItemViews:
        m_itemViewsWidget->show();
        break;
    case FunctionType_ItemWidgets:
        m_itemWidgetsWidget->show();
        break;
    case FunctionType_InputWidgets:
        m_inputWidgetsWidget->show();
        break;
    case FunctionType_Events:
        m_eventsWidget->show();
        break;
    default:
        break;
    }
    hideOtherWidget(btnId);
}

void QtDemo::hideOtherWidget(int showId)
{
    int btnId = FunctionType_Buttons;
    for (; btnId <= FunctionType_Others3; ++btnId)
    {
        if (showId == btnId) {
            continue;
        }

        switch (btnId)
        {
        case FunctionType_Buttons:
            m_buttonsWidget->hide();
            break;
        case FunctionType_DisplayWidgets:
            m_displayWidgetsWidget->hide();
            break;
        case FunctionType_ItemViews:
            m_itemViewsWidget->hide();
            break;
        case FunctionType_ItemWidgets:
            m_itemWidgetsWidget->hide();
            break;
        case FunctionType_InputWidgets:
            m_inputWidgetsWidget->hide();
            break;
        case FunctionType_Events:
            m_eventsWidget->hide();
            break;
        default:
            break;
        }
    }
}
