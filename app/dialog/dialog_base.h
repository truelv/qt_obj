#ifndef DIALOG_BASE_H
#define DIALOG_BASE_H

#include <QDialog>
#include <QFrame>

namespace Ui {
class Dialog_Base;
}

class Dialog_Base : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_Base(QWidget *parent = 0, const QString& title="");
    ~Dialog_Base();
    void hideKeyBoard();

protected:
    QWidget* getContentWidget();
    void setContentWidget(QWidget *w);

    void hideConfirmButton();
    void setCancelText(const QString& text);

protected slots:
    void on_bt_cancel_clicked();
    virtual void on_bt_confirm_clicked();

protected:
    QWidget _w;

private:
    Ui::Dialog_Base *ui;

};

#endif // DIALOG_BASE_H
