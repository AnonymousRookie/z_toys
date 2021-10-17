#include <QPainter>
#include <QStyleOption>
#include <QHeaderView>
#include "based_styleshet_widget.h"

BasedStyleShetWidget::BasedStyleShetWidget(QWidget* parent/* = 0*/)
    : QWidget(parent)
{

}

BasedStyleShetWidget::~BasedStyleShetWidget()
{

}

void BasedStyleShetWidget::setTableViewStyle(QTableView* tv)
{
    if (!tv) {
        return;
    }
    // 设置整行选中
    tv->setSelectionBehavior(QAbstractItemView::SelectRows);
    // 设置不可编辑
    tv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    // 取消QTableView选中后的虚线框
    tv->setFocusPolicy(Qt::NoFocus);
    tv->horizontalHeader()->setHighlightSections(false);
}

void BasedStyleShetWidget::setListViewStyle(QListView* lv)
{
    if (!lv) {
        return;
    }
    lv->setSelectionMode(QAbstractItemView::SingleSelection);
    lv->setSelectionBehavior(QAbstractItemView::SelectRows);
    lv->setEditTriggers(QAbstractItemView::NoEditTriggers);
    lv->setFocusPolicy(Qt::NoFocus);
}

void BasedStyleShetWidget::paintEvent(QPaintEvent* /*e*/)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}
