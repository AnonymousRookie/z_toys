#pragma once

#include <QWidget>

class BasedStyleShetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BasedStyleShetWidget(QWidget* parent = 0);
    ~BasedStyleShetWidget();

protected:
    void paintEvent(QPaintEvent* e);
};
