/*
    Item Views(Model-Based):

    - List View
    - Tree View
    - Table View
    - Column View
*/

#pragma once

#include <map>
#include <string>
#include <memory>
#include <QStandardItemModel>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_item_views.h"

class QLabel;
class QMenu;

struct StudentInfo
{
    StudentInfo(const QString& name, int age) : name_(name), age_(age) {}
    QString name_;
    int age_;
};

Q_DECLARE_METATYPE(StudentInfo*);

class ItemViewsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit ItemViewsWidget(QWidget *parent = 0);
    ~ItemViewsWidget();

signals:

public slots:
    void onStudentInfoListViewClicked(const QModelIndex& index);

private:
    void init();
    void uinit();
    void initUi();
    void initConnect();

    void initStudentInfoListView();

    void initTableView();

private:
    Ui::ItemViews ui_;
    QStandardItemModel* studentInfoListViewModel_ = nullptr;
    std::vector<StudentInfo*> studentInfos_;

    QStandardItemModel* tableViewModel_ = nullptr;
};
