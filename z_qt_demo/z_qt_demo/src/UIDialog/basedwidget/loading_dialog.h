#pragma once

#include <memory>
#include <QDialog>
#include <QMovie>
#include <QTimer>
#include "ui_loading_dialog.h"

class LoadingDialog : public QDialog
{
    Q_OBJECT

public:
    LoadingDialog(QWidget *parent = Q_NULLPTR);
    ~LoadingDialog();

    static LoadingDialog* instance();

    void showDlg(int timeout = 1000);
    void hideDlg();

public slots:
    void onLoadMsgTimeout();

private:
    void init();

private:
    Ui::LoadingDialog m_ui;
    std::shared_ptr<QMovie> m_movie = nullptr;
    std::shared_ptr<QTimer> m_spLoadMsgTimer = nullptr;
};
