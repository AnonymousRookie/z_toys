#pragma once

#include <map>
#include <string>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_item_widgets.h"

class QLabel;
class QMenu;

class ItemWidgetsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit ItemWidgetsWidget(QWidget *parent = 0);
    ~ItemWidgetsWidget();

signals:

public slots:

private:
    void initUi();

private:
    Ui::ItemWidgets ui_;
};
