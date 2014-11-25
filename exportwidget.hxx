#ifndef EXPORTWIDGET_HXX
#define EXPORTWIDGET_HXX

#include <QWidget>

namespace Ui {
class ExportWidget;
}

class ExportWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ExportWidget(QWidget *parent = 0);
    ~ExportWidget();

private:
    Ui::ExportWidget *ui;
};

#endif // EXPORTWIDGET_HXX
