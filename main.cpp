#include "mainwindow.hxx"
#include <QApplication>
#include <QTextCodec>
#include <QFont>
#include <QSystemTrayIcon>
#include <QMenu>
#include "QtSingleApplication"
#include <QAbstractEventDispatcher>
#include <QDebug>
#include <QxtTreeWidget>
#include <X11/Xlib.h>

//class App: public QtSingleApplication {
//public:
//    App(int argc, char **argv): QtSingleApplication(argc, argv) { }
//#if defined(Q_WS_X11)
////    bool x11EventFilter(XEvent *xe) {
//////        switch (xe->type) {
//////        case ClientMessage:
//////            printf("Caught ClientMessage XEvent from Window %d \n", xe->xclient.window);
//////            printf("Receive message: %s\n", xe->xclient.data.s);
//////        }
////        return QtSingleApplication::x11EventFilter(xe);
////    }
//#endif
//};

int main(int argc, char *argv[])
{
    try {
    QtSingleApplication a(argc, argv);
    if (a.isRunning()) {
        a.sendMessage("bringToFront");
        return 0;
    }

    QtSingleApplication::setQuitOnLastWindowClosed(false);

#if (QT_VERSION < QT_VERSION_CHECK(5, 0, 0))
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    QFont f = a.font();
#ifdef Q_OS_UNIX
    f.setPointSize(13);
#endif
    a.setFont(f);

    MainWindow w;
//    a.installEventFilter(&w);
//    w.show();




    int r = a.exec();
    return r;
    } catch (std::exception& e) {
        qDebug() <<"catch a exception"<< e.what();
    }


}
