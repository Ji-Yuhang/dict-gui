#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <QSystemTrayIcon>
//#include <QMediaPlayer>
#include <json.h>
#include "exportwidget.hxx"
#include "wordhistory.hxx"
#include "addword.hxx"
#include "QxtGlobalShortcut"
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


private slots:
    void on_pushButton_clicked();
    QString getWord(const QString& word);
    void makeTree(const QtJson::JsonObject& json);
    void on_pushButton_2_clicked();
    void export_triggered();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_add_triggered();
    void on_search_triggered();

    void on_quit_triggered();
    void on_short_triggered();
    void test_qapp_quit();
    void test_qapp_last();

//    bool eventFilter(QObject *obj, QEvent *event);
    
private:
    QSystemTrayIcon trayIcon;

    Ui::MainWindow *ui;
    QString mp3_;
    ExportWidget exportWidget_;
//    QMediaPlayer player_;
    WordHistory history_;
    AddWord addWordWidget_;
    QWidget testWidget_;
    QxtGlobalShortcut globalAdd_;
};

#endif // MAINWINDOW_HXX
