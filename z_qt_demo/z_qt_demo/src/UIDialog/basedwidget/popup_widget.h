/**
 * µ¯³öÊ½´°¿Ú
 */
#ifndef POPUP_WIDGET_H
#define POPUP_WIDGET_H

#include <map>
#include <string>
#include <memory>
#include <QLabel>
#include <QPushButton>
#include <QtWidgets/QMainWindow>
#include "based_widget.h"
#include "based_styleshet_widget.h"

class PopupWidgetTitle : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit PopupWidgetTitle(const QString& title, QWidget *parent = 0);
    ~PopupWidgetTitle();

    void updateTitle(const QString& title);

signals:
    void closeClicked();

private:
    void initUi();

private:
    QString m_title;
    QLabel* m_titleLabel;
};

class PopupWidget : public BasedWidget
{
    Q_OBJECT

public:
    explicit PopupWidget(const QString& title/* = ""*/, QWidget *parent = 0);
    ~PopupWidget();

signals:

public slots :
    void onCloseBtnClicked();


protected:
    void closeEvent(QCloseEvent*);

private:
    void initUi();
    void initConnect();

public:
    void setLabel(const QString& content);
    void setTitleWidgetWidth(int width);
    void setTitleWidgetHeight(int height);
    void updateTitle(const QString& title);

private:
    std::shared_ptr<PopupWidgetTitle> m_spTitleWidget;
    QString m_title;

public:
    bool m_show = false;
};

#endif // POPUP_WIDGET_H