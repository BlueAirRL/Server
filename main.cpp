#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLibraryInfo>
#include "logger/st_logger.h"

STMsgLogger::st_logger logger;
//日志信息输出
void myMessageOutput(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    logger.MessageOutput(type, context, msg);
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qInstallMessageHandler(myMessageOutput);

    //国际化转义
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);

    QTranslator appTranslator;
    QString strTransLocalFile =
            QCoreApplication::applicationDirPath()+"/" +
            QCoreApplication::applicationName()+"_"+
            QLocale::system().name()+".qm";
    appTranslator.load(strTransLocalFile );
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
