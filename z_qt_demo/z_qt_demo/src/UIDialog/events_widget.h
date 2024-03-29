﻿/*
    图形绘制，响应鼠标点击、拖拽、滚动（选中、放大、缩小），
    支持鼠标右击菜单（放大、缩小、还原）。
*/

#pragma once

#include <map>
#include <string>
#include <QPainter>
#include <QString>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include <QKeyEvent>
#include <QMenu>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_events_widget.h"

struct RectNode 
{
    QRectF rect_{ 300, 300, 100, 100 };
    QString name_ = "正方形";
    int fontSize_ = 14;
};

class EventsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit EventsWidget(QWidget *parent = 0);
    ~EventsWidget();

signals:

public slots:
    // 放大
    void onEnlarge();
    // 缩小
    void onNarrow();
    // 还原
    void onRestore();

private:
    void init();
    void initUi();
    void initConnect();
    void drawRectNode(QPainter& painter, const RectNode& node);
    void initAction();

private:
    void paintEvent(QPaintEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void wheelEvent(QWheelEvent *e);
    void keyPressEvent(QKeyEvent* e);
    void keyReleaseEvent(QKeyEvent* e);

private:
    Ui::EventsWidget ui_;
    QPointF mouseClickedPoint_;

    QPointF mousePressedPoint_;
    QPointF mouseReleasedPoint_;

    double scale_ = 1.0;
    double winPosScale_ = 1.0;

    double dragX_ = 0.0;
    double dragY_ = 0.0;

    bool bCtrlPressed_ = false;

    QTransform transform_;

    RectNode rectNode_;

    QMenu* menu_ = nullptr;
};
