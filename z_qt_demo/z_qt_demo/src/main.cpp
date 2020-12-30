#include "stdafx.h"
#include <QtWidgets/QApplication>
#include <QFile>
#include <QTextStream>
#include <QTranslator>
#include <QSharedMemory>
#include <QMessageBox>
#include <QTimer>
#include <QDir>
#include "UIDialog/qt_qemo.h"
#include "string_util.h"

// 加载资源
void loadResource()
{
    // load stylesheet
    QFile file(":/qt_demo/qss");
    file.open(QFile::ReadOnly);
    QTextStream filetext(&file);
    QString stylesheet = filetext.readAll();
    qApp->setStyleSheet(stylesheet);
    file.close();
    // load icon
    qApp->setWindowIcon(QIcon(":/qt_demo/icon"));
}

int main(int argc, char *argv[])
{
    QFileInfo fileinfo(z::utils::str2qstr(argv[0]));
    QString pluginsPath = fileinfo.absolutePath() + "\\";

    QApplication a(argc, argv);

    QSharedMemory singleton(a.applicationName());
    if (!singleton.create(1)) {
        QString msg = "程序已经运行！";
        QMessageBox* warnBox = new QMessageBox(QMessageBox::Warning, "Waring", msg);
        warnBox->setAttribute(Qt::WA_DeleteOnClose);
        QTimer::singleShot(5000, warnBox, SLOT(accept()));
        warnBox->exec();
        return false;
    }

    loadResource();

    // fixme: 通过界面切换语言
    QTranslator translator;
    bool bload = translator.load(":/qm/qt_demo_zh");
    a.installTranslator(&translator);

    QtDemo w;
    w.show();
    return a.exec();
}
