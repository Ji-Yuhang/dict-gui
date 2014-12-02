#ifndef ADDWORD_HXX
#define ADDWORD_HXX

#include <QWidget>
#include <QDialog>
namespace Ui {
class AddWord;
}

class AddWord : public QDialog
{
    Q_OBJECT

public:
    explicit AddWord(QWidget *parent = 0);
    ~AddWord();
    bool addWord(const QString& word);
//    void setFocusPolicy(Qt::FocusPolicy policy)
    void goFocus();
Q_SIGNALS:
    void addFinished();
private slots:
    void on_pushButton_clicked();

private:
    Ui::AddWord *ui;
};

#endif // ADDWORD_HXX
