#pragma once

#include <map>
#include <string>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_item_views.h"

class QLabel;
class QMenu;

class ItemViewsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit ItemViewsWidget(QWidget *parent = 0);
    ~ItemViewsWidget();

signals:

public slots:

private:
    void initUi();

private:
    Ui::ItemViews ui_;
};
