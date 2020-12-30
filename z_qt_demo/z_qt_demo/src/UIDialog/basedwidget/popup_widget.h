/**
 * µ¯³öÊ½´°¿Ú
 */
#ifndef POPUP_WIDGET_H
#define POPUP_WIDGET_H

#include <map>
#include <string>
#include <memory>
#include <QProcess>
#include <QLabel>
#include <QPushButton>
#include <QtWidgets/QMainWindow>
#include "based_widget.h"
#include "based_styleshet_widget.h"

class PopupWidgetTitle : public BasedStyleShetWidget
{
    Q_OBJECT

public:
    explicit PopupWidgetTitle(QWidget *parent = 0);
    ~PopupWidgetTitle();

signals:
    void closeClicked();

private:
    void initUi();
};

class PopupWidget : public BasedWidget
{
    Q_OBJECT

public:
    explicit PopupWidget(QWidget *parent = 0);
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

private:
    std::shared_ptr<PopupWidgetTitle> m_spTitleWidget;
};

#endif // POPUP_WIDGET_H