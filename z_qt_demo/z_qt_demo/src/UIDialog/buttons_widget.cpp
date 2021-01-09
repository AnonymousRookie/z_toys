#include "stdafx.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QMenu>
#include <QLabel>
#include <QAction>
#include <QHBoxLayout>
#include "buttons_widget.h"
#include "defines.h"
#include "basedwidget/image_button.h"

ButtonsWidget::ButtonsWidget(QWidget *parent)
    : BasedStyleShetWidget(parent)
{
    ui_.setupUi(this);
    setAttribute(Qt::WA_TranslucentBackground);
    setObjectName("ButtonsWidget");
    init();
}

ButtonsWidget::~ButtonsWidget()
{

}

void ButtonsWidget::init()
{
    initUi();
    initConnect();
}

void ButtonsWidget::initUi()
{
    QDesktopWidget *desktop = QApplication::desktop();
    QRect screen = desktop->screenGeometry();
    resize(screen.width(), screen.height() - TITLE_HEIGHT);
    move(0, TITLE_HEIGHT);

    radioBtnGroup1_ = new QButtonGroup(this);
    radioBtnGroup1_->addButton(ui_.radioButtonA, 10001);
    radioBtnGroup1_->addButton(ui_.radioButtonB, 10002);
    radioBtnGroup1_->addButton(ui_.radioButtonC, 10003);

    radioBtnGroup2_ = new QButtonGroup(this);
    radioBtnGroup2_->addButton(ui_.radioButton1, 20001);
    radioBtnGroup2_->addButton(ui_.radioButton2, 20002);
    radioBtnGroup2_->addButton(ui_.radioButton3, 20003);
    for (int i = 0; i < radioBtnGroup2_->buttons().size(); ++i)
    {
        auto btn = radioBtnGroup2_->buttons()[i];
        btn->setProperty("group", "RadioBtnGroup2");
    }

    checkBoxGroup1_.push_back(ui_.checkBoxA);
    checkBoxGroup1_.push_back(ui_.checkBoxB);
    checkBoxGroup1_.push_back(ui_.checkBoxC);

    checkBoxGroup2_.push_back(ui_.checkBox1);
    checkBoxGroup2_.push_back(ui_.checkBox2);
    checkBoxGroup2_.push_back(ui_.checkBox3);
    for (int i = 0; i < checkBoxGroup2_.size(); ++i)
    {
        auto btn = checkBoxGroup2_[i];
        btn->setProperty("group", "CheckBoxGroup2");
    }
}

void ButtonsWidget::initConnect()
{
    connect(ui_.pushButton, &QPushButton::clicked, this, &ButtonsWidget::onPushButtonClicked);

    for (int i = 0; i < radioBtnGroup1_->buttons().size(); ++i)
    {
        connect(radioBtnGroup1_->buttons()[i], &QRadioButton::clicked, this, &ButtonsWidget::onGroup1RadionButtonClicked);
    }
    for (int i = 0; i < radioBtnGroup2_->buttons().size(); ++i)
    {
        connect(radioBtnGroup2_->buttons()[i], &QRadioButton::clicked, this, &ButtonsWidget::onGroup2RadionButtonClicked);
    }

    for (int i = 0; i < checkBoxGroup1_.size(); ++i)
    {
        connect(checkBoxGroup1_[i], &QCheckBox::clicked, this, &ButtonsWidget::onGroup1CheckBoxClicked);
    }
    for (int i = 0; i < checkBoxGroup2_.size(); ++i)
    {
        connect(checkBoxGroup2_[i], &QCheckBox::clicked, this, &ButtonsWidget::onGroup2CheckBoxClicked);
    }
}

void ButtonsWidget::onPushButtonClicked()
{
    ui_.textEdit->setText("PushButton");
}

void ButtonsWidget::onGroup1RadionButtonClicked()
{
    auto btn = radioBtnGroup1_->checkedButton();
    int id = radioBtnGroup1_->checkedId();

    QString text = QString("%1 %2").arg(btn->text()).arg(id);
    ui_.textEdit->setText(text);
}

void ButtonsWidget::onGroup2RadionButtonClicked()
{
    auto btn = radioBtnGroup2_->checkedButton();
    int id = radioBtnGroup2_->checkedId();

    QString text = QString("%1 %2").arg(btn->text()).arg(id);
    ui_.textEdit->setText(text);
}

void ButtonsWidget::onGroup1CheckBoxClicked()
{
    QString text;
    for (auto btn : checkBoxGroup1_)
    {
        if (btn->isChecked())
        {
            text += QString("%1 ").arg(btn->text());
        }
    }
    ui_.textEdit->setText(QString("%1").arg(text));
}

void ButtonsWidget::onGroup2CheckBoxClicked()
{
    QString text;
    for (auto btn : checkBoxGroup2_)
    {
        if (btn->isChecked())
        {
            text += QString("%1 ").arg(btn->text());
        }
    }
    ui_.textEdit->setText(QString("%1").arg(text));
}
