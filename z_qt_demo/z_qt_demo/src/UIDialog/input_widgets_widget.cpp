﻿#include "stdafx.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include "input_widgets_widget.h"
#include "defines.h"
#include "basedwidget/image_button.h"


InputWidgetsWidget::InputWidgetsWidget(QWidget *parent)
    : BasedStyleShetWidget(parent)
{
    ui_.setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("InputWidgetsWidget");
    initUi();
}

InputWidgetsWidget::~InputWidgetsWidget()
{

}

void InputWidgetsWidget::initUi()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    resize(screen.width(), screen.height() - TITLE_HEIGHT);
    move(0, TITLE_HEIGHT);
}
