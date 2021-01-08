#pragma once

#include <map>
#include <string>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_buttons.h"

class QLabel;
class QMenu;

class ButtonsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit ButtonsWidget(QWidget *parent = 0);
    ~ButtonsWidget();

signals:

public slots:

private:
    void initUi();

private:
    Ui::Buttons ui_;
};
