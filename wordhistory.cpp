#include "wordhistory.hxx"
#include "ui_wordhistory.h"

WordHistory::WordHistory(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WordHistory)
{
    ui->setupUi(this);
}

WordHistory::~WordHistory()
{
    delete ui;
}

void WordHistory::appendWord(const WordInfo &word)
{
    wordList_.append(word);
    QListWidgetItem* item = new QListWidgetItem;
    item->setText(word.content);
    ui->listWidget->addItem(item);
}

void WordHistory::on_pushButton_clicked()
{
    this->hide();
}
