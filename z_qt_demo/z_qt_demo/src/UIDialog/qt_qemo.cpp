#include "stdafx.h"
#include "qt_qemo.h"
#include "top_widget.h"
#include "body_widget.h"
#include "defines.h"

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

    m_topWidget = std::make_shared<TopWidget>(this);
    m_topWidget->show();

    m_bodyWidget = new BodyWidget(this);
    m_bodyWidget->show();

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
            break;
        default:
            break;
        }
    }
}
