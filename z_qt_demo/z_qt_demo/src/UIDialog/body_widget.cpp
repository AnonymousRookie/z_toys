#include "stdafx.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include "body_widget.h"
#include "defines.h"
#include "basedwidget/image_button.h"


BodyWidget::BodyWidget(QWidget *parent)
    : BasedStyleShetWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("BodyWidget");
    initUi();
}

BodyWidget::~BodyWidget()
{

}

void BodyWidget::initUi()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    resize(screen.width(), screen.height() - TITLE_HEIGHT);
    move(0, TITLE_HEIGHT);
}
