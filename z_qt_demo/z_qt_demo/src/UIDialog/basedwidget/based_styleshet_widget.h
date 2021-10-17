#pragma once

#include <QWidget>
#include <QTableView>
#include <QListView>

class BasedStyleShetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit BasedStyleShetWidget(QWidget* parent = 0);
    ~BasedStyleShetWidget();

    void setTableViewStyle(QTableView* tv);
    void setListViewStyle(QListView* lv);

protected:
    void paintEvent(QPaintEvent* e);
};
