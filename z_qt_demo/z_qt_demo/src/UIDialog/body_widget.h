#pragma once

#include <map>
#include <string>
#include "basedwidget/based_styleshet_widget.h"

class QLabel;
class QMenu;

class BodyWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit BodyWidget(QWidget *parent = 0);
    ~BodyWidget();

signals:

public slots:

private:
    void initUi();
};
