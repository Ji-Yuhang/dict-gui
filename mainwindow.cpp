#include "mainwindow.hxx"
#include "ui_mainwindow.h"

#include <QNetworkRequest>

#include <QNetworkAccessManager>
#include <QTimer>
#include <QEventLoop>
#include <QFileInfo>
//#include <QMediaPlayer>

#include <QNetworkReply>
#include <iostream>
#include <QDebug>
#include <QFontMetricsF>
#include <QFontMetrics>
#include <QFont>
#include <QMenu>
#include "QtSingleApplication"
#include "addword.hxx"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    connect(ui->actionExportAnki, SIGNAL(triggered()), this, SLOT(export_triggered()));
//    setFixedSize(this->sizeHint());
    trayIcon.setIcon(QIcon(":/add.png"));
    trayIcon.show();
//    trayIcon.showMessage("title","Hello, this is message");
    QMenu * menu = new QMenu();
//        QAction *addAction(const QString &text);
    QAction * addAction = menu->addAction("add word");
    QAction * mainAction = menu->addAction("serarch word");
    QAction * quitAction = menu->addAction("quit");
    connect(addAction, SIGNAL(triggered()), this, SLOT(on_add_triggered()));
    connect(mainAction, SIGNAL(triggered()), this, SLOT(on_search_triggered()));

    connect(quitAction, SIGNAL(triggered()), this, SLOT(on_quit_triggered()));
//    qDebug() << addAction << quitAction<<endl;


    trayIcon.setContextMenu(menu);
    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(test_qapp_quit()));
    connect(qApp, SIGNAL(lastWindowClosed()), this, SLOT(test_qapp_last()));
    QKeySequence keySequence(Qt::CTRL + Qt::SHIFT+Qt::Key_C);

    qDebug() << keySequence.toString();
    globalAdd_.setShortcut(keySequence);
    connect(&globalAdd_, SIGNAL(activated()), this, SLOT(on_short_triggered()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    mp3_ = "";

    QString word = ui->word->text();
    if (word.isEmpty()) return;
    QString shanbayWord = getWord(word);
//    ui->textEdit->setHtml(shanbayWord);
}

QString MainWindow::getWord(const QString &word)
{
    QNetworkAccessManager manager_;
//    QString url = QString("https://api.shanbay.com/bdc/search/?word={%1}").arg(word);
    QString url = QString("https://api.shanbay.com/bdc/search/?word=%1").arg(word);
    QNetworkRequest request;
    request.setUrl(QUrl(url));
    QString tokenStr = QString("Bearer %1").arg("kIFgt2b3QJwkmZ8hpi0QwvCCs6m59c");
    request.setRawHeader("Authorization",tokenStr.toLatin1());
    QNetworkReply* reply = manager_.get(request);
    QEventLoop loop;
    QObject::connect(reply, SIGNAL(readyRead()), &loop, SLOT(quit()));
    QTimer::singleShot(3000, &loop, SLOT(quit()));
    loop.exec();
    QByteArray data = reply->readAll();
    if (!data.isEmpty()) {
        QString text = QString::fromUtf8(data);
        bool s = false;
        QtJson::JsonObject json = QtJson::parse(text, s).toMap();
        if (s) {
            if (json.contains("data")) {
                QtJson::JsonObject dataObj = json["data"].toMap();
                QString cnValue = dataObj["definition"].toString();
                std::cout<< cnValue.toLocal8Bit().data() << std::endl;
            }
            QString myJson = QtJson::serializeStr(json);
            std::cout<< myJson.toLocal8Bit().data() << std::endl;
            makeTree(json);
            return myJson;
        }
    }


    return word;
}

void MainWindow::makeTree(const QtJson::JsonObject &json)
{
//    QMapIterator<QString, QVariant> i(json);
//    while (i.hasNext()) {
//        i.next();
//        QString key = i.key();
//        QVariant value = i.value();
//        if (value.type() == QVariant::Map) {
//            qDebug() << key << endl;
//            QtJson::JsonObject obj = value.toMap();
//            makeTree(obj);
//        } else if (value.type() == QVariant::List) {
//            qDebug() << key << endl;
//            QtJson::JsonArray obj = value.toLine();
//            makeTree(obj);
//        }


//        std::cout << i.key() << ": " << i.value() << std::endl;
//    }

    if (!json.contains("msg")) {
        ui->statusBar->showMessage("shanbay return json havenot key msg");
        return ;
    }
    QString success = json["msg"].toString();
    if (success != "SUCCESS") {
        ui->statusBar->showMessage("shanbay's api get a error");
        return ;
    }
    if (!json.contains("data")) {
        ui->statusBar->showMessage("shanbay return json havenot key data");
        return ;
    }
    QtJson::JsonObject dataObj = json["data"].toMap();
    QString content = dataObj["content"].toString();
    QString definition = dataObj["definition"].toString();
    QString content_type = dataObj["content_type"].toString();
    QString pron = dataObj["pron"].toString();
    QtJson::JsonObject en_definitions = dataObj["en_definition"].toMap();
    QString en_definition = en_definitions["defn"].toString();
    QString us_audio = dataObj["us_audio"].toString();
//    QString cnValue = dataObj["definition"].toString();
    ui->content->setText(content);
    ui->pron->setText("<font face='Arial'>["+pron+"]</font>");
//    ui->type->setText(content_type);
    ui->cn->setText(definition);
#if 0
    {
        int fontWidth = ui->sent    ~AddWord();

        private slots:ence->fontMetrics().width(en_definition);
        int labelWidth = ui->sentence->width();

//        num/ size = labelWidth / fontWidth;
        int num = labelWidth * en_definition.size() / fontWidth;
        int i = en_definition.size() / num;
        while (i > 0) {
            en_definition.insert(num - 1 + num * i,'\n');
            i--;
        }
    }
#endif
    {
        en_definition.replace(";",";\n");
    }

    ui->sentence->setText(en_definition);
    mp3_ = us_audio;
    ui->statusBar->showMessage(content);


    WordInfo wordInfo;
    wordInfo.content = content;
    wordInfo.definition = definition;
    wordInfo.pron = pron;
    wordInfo.en_definition = en_definition;
    wordInfo.us_audio = us_audio;
    addWordWidget_.addWord(wordInfo.content);
    history_.appendWord(wordInfo);

}

void MainWindow::on_pushButton_2_clicked()
{

//    QString mplayer = "C:/mplayer.exe";
//    QFileInfo fileinfo(mplayer);
//    if (!fileinfo.exists()) mplayer = "D:/Anki/mplayer.exe";
//    QString command = QString("%1 %2").arg(mplayer).arg(mp3_);
//    system(command.toUtf8().data());
//    player_.setMedia(QUrl(mp3_));
//    player_.setVolume(100);
//    player_.play();
#ifdef Q_OS_UNIX
    QString mplayer = "mplayer";
    QString command = QString("%1 %2").arg(mplayer).arg(mp3_);
    system(command.toUtf8().data());
#endif
}

void MainWindow::export_triggered()
{
    exportWidget_.showNormal();
}

void MainWindow::on_pushButton_3_clicked()
{

}

void MainWindow::on_pushButton_4_clicked()
{
    history_.showNormal();
    
}

void MainWindow::on_add_triggered()
{


    addWordWidget_.activateWindow();
    QApplication::setActiveWindow(&addWordWidget_);
    addWordWidget_.raise();
    addWordWidget_.setFocus();
    addWordWidget_.goFocus();
    addWordWidget_.exec();


}

void MainWindow::on_search_triggered()
{
    this->setVisible(!this->isVisible());
}

void MainWindow::on_quit_triggered()
{
    qDebug("on_quit_triggered");
    qApp->quit();
}

void MainWindow::on_short_triggered()
{
    if (addWordWidget_.isHidden())
        on_add_triggered();
    else
        addWordWidget_.reject();

    qDebug()<< "on_short_triggered ";


}

void MainWindow::test_qapp_quit()
{
//    qDebug("test_qapp_quit");

}

void MainWindow::test_qapp_last()
{
//    qDebug("test_qapp_last");

}
//bool MainWindow::eventFilter(QObject *obj, QEvent *event)
//{
//    if (event->type() == QEvent::KeyPress) {
//        ;
//    }
//    return false;
//}

