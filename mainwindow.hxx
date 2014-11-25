#ifndef MAINWINDOW_HXX
#define MAINWINDOW_HXX

#include <QMainWindow>
#include <json.h>
#include "exportwidget.hxx"
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

private:
    Ui::MainWindow *ui;
    QString mp3_;
    ExportWidget exportWidget_;
};

#endif // MAINWINDOW_HXX
