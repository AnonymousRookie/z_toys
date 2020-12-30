#include <QPainter>
#include <QStyleOption>
#include "based_styleshet_widget.h"

BasedStyleShetWidget::BasedStyleShetWidget(QWidget* parent/* = 0*/)
    : QWidget(parent)
{

}

BasedStyleShetWidget::~BasedStyleShetWidget()
{

}

void BasedStyleShetWidget::paintEvent(QPaintEvent* /*e*/)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
