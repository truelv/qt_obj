#ifndef BACKTITLE_H
#define BACKTITLE_H

#include <QWidget>

namespace Ui {
class BackTitle;
}

class BackTitle : public QWidget
{
    Q_OBJECT

public:
    explicit BackTitle(QWidget *parent = 0);
    ~BackTitle();
    void clearTitle();
    void setTitle(const QString& title);
    void hideBackBt();

signals:
    void buttonBackClick();

private slots:
    void on_back_button_clicked();

private:
    Ui::BackTitle *ui;
};

#endif // BACKTITLE_H
