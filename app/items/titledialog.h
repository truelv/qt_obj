#ifndef TITLEDIALOG_H
#define TITLEDIALOG_H

#include <QDialog>

#define BT_CANCEL  0
#define BT_CONFIRM 1

namespace Ui {
class TitleDialog;
}

typedef struct {
    QString passwd;
} dialog_retV;

class TitleDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TitleDialog(QWidget *parent = 0, int* button=0);
    ~TitleDialog();

private slots:
    virtual void on_sure_bt_clicked();
    virtual void on_cancel_bt_clicked();

protected:
    int* _clickBt;
    Ui::TitleDialog *ui;
};

#endif // TITLEDIALOG_H
