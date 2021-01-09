#pragma once

#include <map>
#include <string>
#include <QCheckBox>
#include <QButtonGroup>
#include "basedwidget/based_styleshet_widget.h"
#include "ui_buttons.h"

class QLabel;
class QMenu;

class ButtonsWidget : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit ButtonsWidget(QWidget *parent = 0);
    ~ButtonsWidget();

signals:

public slots :
    void onPushButtonClicked();
    void onGroup1RadionButtonClicked();
    void onGroup2RadionButtonClicked();
    void onGroup1CheckBoxClicked();
    void onGroup2CheckBoxClicked();

private:
    void init();
    void initUi();
    void initConnect();

private:
    Ui::Buttons ui_;
    QButtonGroup* radioBtnGroup1_;
    QButtonGroup* radioBtnGroup2_;

    std::vector<QCheckBox*> checkBoxGroup1_;
    std::vector<QCheckBox*> checkBoxGroup2_;
};
