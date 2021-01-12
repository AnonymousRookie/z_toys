#include "stdafx.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QVariant>
#include <QHBoxLayout>
#include "item_views_widget.h"
#include "defines.h"
#include "basedwidget/image_button.h"


ItemViewsWidget::ItemViewsWidget(QWidget *parent)
    : BasedStyleShetWidget(parent)
{
    ui_.setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("ItemViewsWidget");
    init();
}

ItemViewsWidget::~ItemViewsWidget()
{
    uinit();
}

void ItemViewsWidget::init()
{
    initUi();
    initConnect();
}

void ItemViewsWidget::uinit()
{
    studentInfoListViewModel_->clear();
    for (auto stu : studentInfos_)
    {
        delete stu;
        stu = nullptr;
    }
}

void ItemViewsWidget::initUi()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    resize(screen.width(), screen.height() - TITLE_HEIGHT);
    move(0, TITLE_HEIGHT);

    initStudentInfoListView();
}

void ItemViewsWidget::initConnect()
{
    connect(ui_.listView_studentInfo, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onStudentInfoListViewClicked(const QModelIndex&)));
}

void ItemViewsWidget::initStudentInfoListView()
{
    studentInfoListViewModel_ = new QStandardItemModel(this);
    ui_.listView_studentInfo->setModel(studentInfoListViewModel_);

    studentInfos_.push_back(new StudentInfo("Jason", 11));
    studentInfos_.push_back(new StudentInfo("Peter", 22));

    int index = 0;
    for (auto stu : studentInfos_)
    {
        QVariant itemData = QVariant::fromValue<StudentInfo*>(stu);
        auto item = new QStandardItem(stu->name_);
        item->setTextAlignment(Qt::AlignCenter);
        item->setData(itemData);
        studentInfoListViewModel_->insertRow(index++, item);
    }
}

void ItemViewsWidget::onStudentInfoListViewClicked(const QModelIndex& index)
{
    auto item = studentInfoListViewModel_->item(index.row());
    auto itemdata = item->data();
    StudentInfo* stu = *(StudentInfo**)(itemdata.data());

    QString text = QString("name:%1 age:%2").arg(stu->name_).arg(stu->age_);
    ui_.textEdit->setText(text);
}
