#pragma once

#include <map>
#include <string>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_display_widgets.h"

class QLabel;
class QMenu;

class DisplayWidgetsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit DisplayWidgetsWidget(QWidget *parent = 0);
    ~DisplayWidgetsWidget();

signals:

public slots:

private:
    void initUi();

private:
    Ui::DisplayWidgets ui_;
};
