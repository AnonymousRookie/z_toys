﻿#pragma once

#include <memory>
#include <QtWidgets/QWidget>
#include "ui_qt_demo.h"
#include "defines.h"

class QTranslator;

class TopWidget;
class BodyWidget;

class QtDemo : public QWidget
{
    Q_OBJECT

public:
    QtDemo(QWidget *parent = 0);
    ~QtDemo();

signals:
    void dataArrived(void*, int);

public slots:
    void onMenuBtnClicked(int);

private:
    void init();
    void uninit();
    void initUi();
    void initConnect();
    void switchLanguage(Language language);
    void hideOtherWidget(int showId);

public:
    void setTranslator(std::shared_ptr<QTranslator> translator);

private:
    Ui::QtDemoClass m_ui;
    std::shared_ptr<QTranslator> m_translator = nullptr;

    std::shared_ptr<TopWidget> m_topWidget = nullptr;
    BodyWidget* m_bodyWidget = nullptr;
};

