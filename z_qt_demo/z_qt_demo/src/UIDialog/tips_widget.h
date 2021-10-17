#pragma once

#include <map>
#include <string>
#include <memory>
#include <QTableWidget>
#include <QTextBrowser>
#include "basedwidget/popup_widget.h"

class TipsWidget : public PopupWidget
{
    Q_OBJECT

public:
    explicit TipsWidget(int w, int h, const QString& title, QWidget *parent = 0);
    ~TipsWidget();

    void showTips(const QString& tips);

private:
    void initUi();

private:
    QTextBrowser* m_QTextBrowser;
};
