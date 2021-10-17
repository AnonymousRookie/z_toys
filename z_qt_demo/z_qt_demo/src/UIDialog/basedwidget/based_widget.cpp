#include <QMouseEvent>
#include "based_widget.h"

BasedWidget::BasedWidget(QWidget* parent/* = 0*/)
    : QWidget(parent)
    , m_isPressed(false)
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
}

BasedWidget::~BasedWidget()
{

}

void BasedWidget::mousePressEvent(QMouseEvent* e)
{
    if (e->button() != Qt::LeftButton) {
        m_isPressed = false;
        e->ignore();
    } else {
        m_isPressed = true;
        m_pos = e->globalPos() - pos();
    }
}

void BasedWidget::mouseReleaseEvent(QMouseEvent* /*e*/)
{
    m_isPressed = false;
}

void BasedWidget::mouseMoveEvent(QMouseEvent* e)
{
    if (m_isPressed) {
        move(e->globalPos() - m_pos);
    }
    QWidget::mouseMoveEvent(e);
}
