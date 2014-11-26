#include "mainwindow.hxx"
#include <QApplication>
#include <QTextCodec>
#include <QFont>
//#include <
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QFont f = a.font();
    f.setPointSize(18);
    a.setFont(f);

    MainWindow w;
    w.show();

    return a.exec();
}
