#pragma once

#include <memory>
#include <map>
#include <string>
#include <QProcess>
#include <QTimer>
#include <QLabel>
#include "basedwidget/based_styleshet_widget.h"
#include "basedwidget/image_button.h"

class QLabel;
class QMenu;
class PreAlarmBtn;
class PreAlarmWidget;
class TipsWidget;

struct FunctionBtnInfo
{
    FunctionBtnInfo() {}
    FunctionBtnInfo(int idx, int tp, std::string name)
        : index(idx), type(tp), showname(name) {}
    ~FunctionBtnInfo() {}
    int index;
    int type;
    std::string showname;
};

class TopWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit TopWidget(QWidget *parent = 0);
    ~TopWidget();

signals:
    void menuBtnClicked(int);

public slots:
    void onMenuBtnClicked(int);
    void onTimeOut();
    void onPreAlarmBtnClicked();

private:
    void initUi();
    void initTitle();
    void initMenuBar();

    void setCurrentTimeToLabel();

private:
    std::shared_ptr<QLabel> m_softNameLabel;
    std::shared_ptr<QLabel> m_stationNameLabel;
    std::shared_ptr<QLabel> m_phoneLabel;
    std::shared_ptr<QLabel> m_phoneIconLabel;
    std::shared_ptr<QLabel> m_datetimeLabel;
    std::shared_ptr<QTimer> m_Timer;
    std::shared_ptr<PreAlarmBtn> m_preAlarmBtn;
    std::map<int, std::shared_ptr<ImageButton>> m_mainFunctionBtnMap;

    std::shared_ptr<TipsWidget> m_spTipsWidget = nullptr;
};

class PreAlarmBtn : public QWidget
{
    Q_OBJECT

public:
    PreAlarmBtn(QWidget *parent = 0);
    ~PreAlarmBtn();

    void init();
    void updatePreAlarmNum(int n);

    void mouseReleaseEvent(QMouseEvent *e);

signals:
    void clicked();

private:
    std::shared_ptr<QLabel> m_leftIcon;
    std::shared_ptr<QLabel> m_topText;
    std::shared_ptr<QLabel> m_BottomText;
};