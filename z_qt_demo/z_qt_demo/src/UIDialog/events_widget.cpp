﻿#include "stdafx.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include "events_widget.h"
#include "defines.h"
#include "basedwidget/image_button.h"

EventsWidget::EventsWidget(QWidget *parent)
    : BasedStyleShetWidget(parent)
{
    ui_.setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("EventsWidget");
    init();
}

EventsWidget::~EventsWidget()
{

}

void EventsWidget::init()
{
    initUi();
    initConnect();
}

void EventsWidget::initUi()
{
    int nWidth = this->parentWidget()->width();
    int nHeight = this->parentWidget()->height();
    setFixedSize(nWidth, nHeight);
    move(0, 0);

    scale_ = 1.0 * nHeight / DEFAULE_SCREEN_HEIGHT;  // 缩放比

    setFocusPolicy(Qt::FocusPolicy::ClickFocus);

    ui_.label->setProperty("parent", "EventsWidget");
}

void EventsWidget::initConnect()
{

}

void EventsWidget::drawRectNode(QPainter& painter, const RectNode& node)
{
    QColor color(80, 123, 175);

    // 绘制总线
    QPen oldPen = painter.pen();
    QFont oldFont = painter.font();

    QFont font = painter.font();
    font.setPixelSize(node.fontSize_);
    painter.setFont(font);
    oldPen = painter.pen();

    QColor c = Qt::green;
    painter.setPen(QPen(c, 4));
    painter.drawRect(node.rect_);
    painter.setPen(oldPen);

    oldPen = painter.pen();
    painter.setPen(QPen(Qt::white, 2));
    painter.drawText(node.rect_, Qt::AlignCenter, node.name_);
    painter.setPen(oldPen);

    painter.setFont(oldFont);
    painter.setPen(oldPen);
}

void EventsWidget::paintEvent(QPaintEvent *e)
{
    QPainter painter(this);
    painter.setTransform(transform_);
    drawRectNode(painter, rectNode_);
}

void EventsWidget::mousePressEvent(QMouseEvent *e)
{
    mousePressedPoint_ = e->windowPos();
    mouseClickedPoint_ = e->windowPos();
    mouseClickedPoint_.setY(mouseClickedPoint_.ry() - TITLE_HEIGHT);
    mouseClickedPoint_.setX(mouseClickedPoint_.rx() * winPosScale_ - dragX_);
    mouseClickedPoint_.setY(mouseClickedPoint_.ry() * winPosScale_ - dragY_);

    if (rectNode_.rect_.contains(mouseClickedPoint_))
    {
        ui_.label->setText("选中正方形！");
    }
    else 
    {
        QString pos = QString("%1 %2").arg(mouseClickedPoint_.rx()).arg(mouseClickedPoint_.ry());
        ui_.label->setText(pos + "未选中正方形！");
    }
}

void EventsWidget::mouseReleaseEvent(QMouseEvent *e)
{
    mouseReleasedPoint_ = e->windowPos();

    double dragX = mouseReleasedPoint_.rx() - mousePressedPoint_.rx();
    double dragY = mouseReleasedPoint_.ry() - mousePressedPoint_.ry();

    dragX *= winPosScale_;
    dragY *= winPosScale_;

    if (abs(dragX) > 1 || abs(dragY) > 1)
    {
        dragX_ += dragX;
        dragY_ += dragY;

        transform_.translate(dragX, dragY);
        update();
    }
}

void EventsWidget::wheelEvent(QWheelEvent *e)
{
    if (!bCtrlPressed_) {
        return;
    }

    int nWidth = this->parentWidget()->width();
    int nHeight = this->parentWidget()->height();

    if (e->delta() < 0)
    {
        scale_ = 0.8;
        winPosScale_ /= scale_;
        dragX_ /= scale_;
        dragY_ /= scale_;
        transform_.scale(scale_, scale_);
    }
    else
    {
        scale_ = (1 / 0.8);
        winPosScale_ /= scale_;
        dragX_ /= scale_;
        dragY_ /= scale_;
        transform_.scale(scale_, scale_);
    }
    e->accept();
    update();
}

void EventsWidget::keyPressEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Control)
    {
        bCtrlPressed_ = true;
    }
}

void EventsWidget::keyReleaseEvent(QKeyEvent* e)
{
    if (e->key() == Qt::Key_Control)
    {
        bCtrlPressed_ = false;
    }
}

