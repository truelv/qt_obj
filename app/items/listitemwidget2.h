#ifndef LISTITEMWIDGET2_H
#define LISTITEMWIDGET2_H

#include <QWidget>

namespace Ui {
class LIstItemWidget2;
}

class LIstItemWidget2 : public QWidget
{
    Q_OBJECT

public:
    explicit LIstItemWidget2(QWidget *parent = 0);
    ~LIstItemWidget2();
    void setKV(const QString& key, const QString& value);
    void setBackColor(const QString& qss);

private:
    Ui::LIstItemWidget2 *ui;
};

#endif // LISTITEMWIDGET2_H
