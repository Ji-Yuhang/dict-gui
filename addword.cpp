#include "addword.hxx"
#include "ui_addword.h"

#include <QFile>
#include <QMessageBox>

AddWord::AddWord(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddWord)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::WindowStaysOnTopHint);
    this->setFocusPolicy(Qt::StrongFocus);
    ui->lineEdit->setFocusPolicy(Qt::StrongFocus);
}

AddWord::~AddWord()
{
    delete ui;

}

bool AddWord::addWord(const QString &word)
{
    QFile file("/home/jiyuhang/words.txt");
    if (file.open(QIODevice::Append)) {
        file.write(word.toUtf8());
        file.write("\r\n");
        file.close();
        Q_EMIT addFinished();
    } else {
        QMessageBox::warning(0, "Cannot open file", "Cannot open file /home/jiyuhang/words.txt");
    }
}

void AddWord::goFocus()
{
    this->setFocus();
    ui->lineEdit->setFocus();
}

void AddWord::on_pushButton_clicked()
{
    QString word = ui->lineEdit->text();
    if (!word.isEmpty()) {
        addWord(word);
    }
    this->accept();

}
