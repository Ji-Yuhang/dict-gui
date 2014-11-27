#include "mainwindow.hxx"
#include "ui_mainwindow.h"

#include <QNetworkRequest>

#include <QNetworkAccessManager>
#include <QTimer>
#include <QEventLoop>

#include <QNetworkReply>
#include <iostream>
#include <QDebug>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->actionExportAnki, SIGNAL(triggered()), this, SLOT(on_exportAnki_triggered()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    mp3_ = "";

    QString word = ui->word->text();
    QString shanbayWord = getWord(word);
    ui->textEdit->setHtml(shanbayWord);
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
                std::cout<< cnValue.toUtf8().data() << std::endl;
            }
            QString myJson = QtJson::serializeStr(json);
            std::cout<< myJson.toUtf8().data() << std::endl;
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
    ui->pron->setText(pron);
    ui->type->setText(content_type);
    ui->cn->setText(definition);
    ui->sentence->setText(en_definition);
    mp3_ = us_audio;


}

void MainWindow::on_pushButton_2_clicked()
{
    //http://media.shanbay.com/audio/us/content.mp3
    QString command = QString("mplayer %1").arg(mp3_);
    system(command.toUtf8().data());
}

void MainWindow::on_exportAnki_triggered()
{
    exportWidget_.showNormal();
}
