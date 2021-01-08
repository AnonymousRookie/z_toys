#include "stdafx.h"
#include <QApplication>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QPushButton>
#include <QHBoxLayout>
#include <QDesktopWidget>
#include <QPixmap>
#include <QDateTime>
#include <QMouseEvent>
#include "top_widget.h"
#include "defines.h"
#include "basedwidget/image_button.h"
#include "../string_util.h"


TopWidget::TopWidget(QWidget *parent)
    : BasedStyleShetWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("TopWidget");
    initUi();
}

TopWidget::~TopWidget()
{

}

void TopWidget::onMenuBtnClicked(int typeId)
{
    auto iter = m_mainFunctionBtnMap.begin();
    for (; iter != m_mainFunctionBtnMap.end(); ++iter) {
        auto btn = iter->second;
        if (iter->first == typeId) {
            btn->setPressed();
        }
        else {
            btn->setPressed(false);
        }
    }
}

void TopWidget::initUi()
{
    initTitle();
    initMenuBar();

}

void TopWidget::initTitle()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    setFixedSize(screen.width(), TITLE_HEIGHT);

    m_softNameLabel = std::make_shared<QLabel>(this);
    m_softNameLabel->resize(277, 26);
    m_softNameLabel->move(10, 3);
    m_softNameLabel->setObjectName("SoftNameLabel");
    m_softNameLabel->setText(tr("ZQtDemo"));
    m_softNameLabel->setAlignment(Qt::AlignCenter);

    m_stationNameLabel = std::make_shared<QLabel>(this);
    m_stationNameLabel->resize(200, 26);
    m_stationNameLabel->move(screen.width() / 2 - m_stationNameLabel->width() / 2, 3);
    m_stationNameLabel->setObjectName("StationNameLabel");
    m_stationNameLabel->setText(tr("ZQtDemo"));
    m_stationNameLabel->setAlignment(Qt::AlignCenter);

    m_datetimeLabel = std::make_shared<QLabel>(this);
    m_datetimeLabel->resize(201, 32);
    m_datetimeLabel->move(screen.width() - m_datetimeLabel->width(), 0);
    m_datetimeLabel->setObjectName("DatetimeLabel");
    setCurrentTimeToLabel();
    m_datetimeLabel->setAlignment(Qt::AlignCenter);

    m_Timer = std::make_shared<QTimer>(this);
    connect(m_Timer.get(), SIGNAL(timeout()), this, SLOT(onTimeOut()));
    m_Timer->start(1000);

    m_phoneLabel = std::make_shared<QLabel>(this);
    m_phoneLabel->resize(245, 32);
    m_phoneLabel->move(screen.width() - m_datetimeLabel->width() - m_phoneLabel->width() - 2, 0);
    m_phoneLabel->setObjectName("PhoneLabel");
    m_phoneLabel->setText(tr("020-12345678"));
    m_phoneLabel->setAlignment(Qt::AlignCenter);
    m_phoneLabel->installEventFilter(this);

    m_phoneIconLabel = std::make_shared<QLabel>(this);
    QPixmap pix = QPixmap(":/qt_demo/phone_icon");
    m_phoneIconLabel->setPixmap(pix);
    m_phoneIconLabel->setFixedSize(pix.size());
    m_phoneIconLabel->move(screen.width() - m_datetimeLabel->width() - m_phoneLabel->width() + 30, (m_phoneLabel->height() - m_phoneIconLabel->height()) / 2);
}

void TopWidget::initMenuBar()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();

    int xoffset = 0;
    int yoffset = 32;

    int nspace = 12;

    std::vector<FunctionBtnInfo> mainFunctions = {
        { FunctionBtnInfo(1, 1000, "Buttons") },
        { FunctionBtnInfo(2, 1001, "ItemViews") },
        { FunctionBtnInfo(3, 1002, "ItemWidgets") },
        { FunctionBtnInfo(4, 1003, "InputWidgets") },
        { FunctionBtnInfo(5, 1004, "DisplayWidgets") },
        { FunctionBtnInfo(6, 1005, "Others") },
        { FunctionBtnInfo(7, 1006, "Others") },
        { FunctionBtnInfo(8, 1007, "Others") }
    };

    auto it = mainFunctions.begin();
    for (; it != mainFunctions.end(); ++it)
    {
        int typeId = it->type;
        const std::string& showname = it->showname;

        auto btn = std::make_shared<ImageButton>(this);
        btn->setButtonInfo(BUTTON_STATUS_NORMAL, ":/func_btn/func_btn_normal");
        btn->setButtonInfo(BUTTON_STATUS_HOVER, ":/func_btn/func_btn_hover");
        btn->setButtonInfo(BUTTON_STATUS_PRESS, ":/func_btn/func_btn_press");
        btn->setButtonInfo(BUTTON_STATUS_DISABLE, ":/func_btn/func_btn_disable");
        btn->setButtonInfo(BUTTON_STATUS_ALARM, ":/func_btn/func_btn_alarm");
        btn->setButtonStatus(BUTTON_STATUS_NORMAL);

        btn->move(xoffset, yoffset);

        QString icon = QString(":/func_btn/func_btn_icon_%1").arg(typeId);
        btn->setIcon(icon);

        btn->setText(showname.c_str());
        btn->setTypeId(typeId);

        m_mainFunctionBtnMap[typeId] = btn;

        connect(btn.get(), SIGNAL(clicked(int)), this, SIGNAL(menuBtnClicked(int)));
        connect(btn.get(), SIGNAL(clicked(int)), this, SLOT(onMenuBtnClicked(int)));

        xoffset += (btn->width() + nspace);
    }

    m_preAlarmBtn = std::make_shared<PreAlarmBtn>(this);
    m_preAlarmBtn->move(screen.width() - 80, yoffset + 1);
    connect(m_preAlarmBtn.get(), SIGNAL(clicked()), this, SLOT(onPreAlarmBtnClicked()));
}

void TopWidget::onTimeOut()
{
    setCurrentTimeToLabel();
}

void TopWidget::onPreAlarmBtnClicked()
{
}

void TopWidget::setCurrentTimeToLabel()
{
    QDateTime CurrentTime = QDateTime::currentDateTime();
    QByteArray _ByteArray = CurrentTime.toString("yyyy-MM-dd hh:mm:ss").toLocal8Bit();
    m_datetimeLabel->setText(tr(_ByteArray.data()));
}

PreAlarmBtn::PreAlarmBtn(QWidget *parent)
    : QWidget(parent)
{
    init();
}

PreAlarmBtn::~PreAlarmBtn()
{

}

void PreAlarmBtn::init()
{
    resize(60, 30);

    QPixmap pix = QPixmap(":/qt_demo/prealarm");
    m_leftIcon = std::make_shared<QLabel>(this);
    m_leftIcon->setPixmap(pix);
    m_leftIcon->setFixedSize(pix.size());
    m_leftIcon->move(0, 0);

    m_topText = std::make_shared<QLabel>(this);
    m_BottomText = std::make_shared<QLabel>(this);
    m_topText->move(30, 0);
    m_topText->resize(30, 10);
    m_BottomText->move(30, 15);
    m_BottomText->resize(30, 15);
    m_topText->setObjectName("PreAlarmNum");
    m_BottomText->setProperty("parent", "ImageButton");
    m_topText->setAlignment(Qt::AlignCenter);
    m_BottomText->setAlignment(Qt::AlignCenter);
    m_topText->setText("0");
    m_BottomText->setText(tr("Tips"));
}

void PreAlarmBtn::updatePreAlarmNum(int n)
{
    m_topText->setText(QString("%1").arg(n));
}

void PreAlarmBtn::mouseReleaseEvent(QMouseEvent *e)
{
    if (e->button() != Qt::LeftButton) {
        e->ignore();
        return;
    }
    if (rect().contains(e->pos())) {
        if (isEnabled()) {
            emit clicked();
        }
        e->accept();
    }
    else {
        e->ignore();
    }
}
