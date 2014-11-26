#ifndef WORDHISTORY_HXX
#define WORDHISTORY_HXX

#include <QWidget>

namespace Ui {
class WordHistory;
}
struct WordInfo {
    QString content;
    QString definition;
    QString pron;
    QString en_definition;
    QString us_audio;
};

class WordHistory : public QWidget
{
    Q_OBJECT
    
public:
    explicit WordHistory(QWidget *parent = 0);
    ~WordHistory();
    void appendWord(const WordInfo& word);
    
private slots:
    void on_pushButton_clicked();
    
private:
    Ui::WordHistory *ui;
    QList<WordInfo> wordList_;
};

#endif // WORDHISTORY_HXX
