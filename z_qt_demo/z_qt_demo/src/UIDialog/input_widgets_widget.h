/*
Item Widgets(Item-Based):

- List Widget
- Tree Widget
- Table Widget
*/

#pragma once

#include <map>
#include <string>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_input_widgets.h"

class QLabel;
class QMenu;

class InputWidgetsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit InputWidgetsWidget(QWidget *parent = 0);
    ~InputWidgetsWidget();

signals:

public slots:

private:
    void initUi();

private:
    Ui::InputWidgets ui_;
};
