#pragma once

#include <QWidget>

class QPoint;

class BasedWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BasedWidget(QWidget* parent = 0);
    ~BasedWidget();

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseReleaseEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);

private:
    QPoint m_pos;
    bool m_isPressed;
};
