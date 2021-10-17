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

    tableViewModel_ = new QStandardItemModel(this);
    initTableView();
}

void ItemViewsWidget::initConnect()
{
    connect(ui_.listView_studentInfo, SIGNAL(clicked(const QModelIndex&)), this, SLOT(onStudentInfoListViewClicked(const QModelIndex&)));
}

void ItemViewsWidget::initStudentInfoListView()
{
    studentInfoListViewModel_ = new QStandardItemModel(this);
    ui_.listView_studentInfo->setModel(studentInfoListViewModel_);
    setListViewStyle(ui_.listView_studentInfo);

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

void ItemViewsWidget::initTableView()
{
    tableViewModel_->clear();
    enum { INFO_COL_NUMBER = 7 };
    tableViewModel_->setColumnCount(INFO_COL_NUMBER);

    tableViewModel_->setHeaderData(0, Qt::Horizontal, tr("序号"));
    tableViewModel_->setHeaderData(1, Qt::Horizontal, tr("时间"));
    tableViewModel_->setHeaderData(2, Qt::Horizontal, tr("来源"));
    tableViewModel_->setHeaderData(3, Qt::Horizontal, tr("信息名称/内容"));
    tableViewModel_->setHeaderData(4, Qt::Horizontal, tr("状态"));
    tableViewModel_->setHeaderData(5, Qt::Horizontal, tr("类型"));
    tableViewModel_->setHeaderData(6, Qt::Horizontal, tr("子类型"));
    ui_.tableView->setModel(tableViewModel_);

    ui_.tableView->horizontalHeader()->resizeSection(0, 60);
    ui_.tableView->horizontalHeader()->resizeSection(1, 100);
    ui_.tableView->horizontalHeader()->resizeSection(2, 100);
    ui_.tableView->horizontalHeader()->setSectionResizeMode(3, QHeaderView::Stretch);
    ui_.tableView->horizontalHeader()->resizeSection(4, 100);
    ui_.tableView->horizontalHeader()->resizeSection(5, 100);
    ui_.tableView->horizontalHeader()->resizeSection(6, 100);

    // 内容较多时多行显示
    ui_.tableView->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    setTableViewStyle(ui_.tableView);


    auto index = 1;
    int rowIndex = 0;
    QList<QStandardItem*> valList;
    valList << new QStandardItem(QString("%1").arg(index++))
        << new QStandardItem("a")
        << new QStandardItem("b")
        << new QStandardItem("QStandardItem, QStandardItem, QStandardItem, QStandardItem")
        << new QStandardItem("c")
        << new QStandardItem("d")
        << new QStandardItem("e");

    for (auto item : valList) {
        item->setTextAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    }
    tableViewModel_->insertRow(rowIndex++, valList);
}

void ItemViewsWidget::onStudentInfoListViewClicked(const QModelIndex& index)
{
    auto item = studentInfoListViewModel_->item(index.row());
    auto itemdata = item->data();
    StudentInfo* stu = *(StudentInfo**)(itemdata.data());

    QString text = QString("name:%1 age:%2").arg(stu->name_).arg(stu->age_);
    ui_.textEdit->setText(text);
}
