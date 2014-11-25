#include "mainwindow.hxx"
#include <QApplication>
#include <QTextCodec>
#include <QFont>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QFont f = a.font();
    f.setPointSize(10.5);
    a.setFont(f);

    MainWindow w;
    w.show();

    return a.exec();
}
