#ifndef LISTITEMWIDGET_H
#define LISTITEMWIDGET_H

#include <QWidget>
#define LIST_ITEM_HEIGHT    70
#define LIST_ITEM_HEIGHT2   90
#define LIST_ITEM_WIDTH     600
namespace Ui {
class LIstItemWidget;
}

class LIstItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit LIstItemWidget(QWidget *parent = 0);
    ~LIstItemWidget();
    void setBackColor(const QString& qss);
    void setSize(const QSize& size);
    void setKV(const QString& key, const QString& value);

private:
    Ui::LIstItemWidget *ui;
};

#endif // LISTITEMWIDGET_H
