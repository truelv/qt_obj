#ifndef WIDGET_BASE_H
#define WIDGET_BASE_H

#include <QWidget>

#include "items/backtitle.h"
#include "signalsender.h"
// 顶边距
#define TOP_PADING 180

class Widget_Base : public QWidget
{
    Q_OBJECT

public:
    explicit Widget_Base(QWidget *parent = 0, const QString& title="");
    ~Widget_Base();
    void setBackPage(QWidget* w=0);
    virtual void autoToBack();

protected slots:
    virtual void slotPageBack();
    virtual void slotRestToRun();

protected:
    QWidget* _backPage;
    BackTitle _backTitle;

    SignalSender* _sender;

private:


};

#endif // WIDGET_BASE_H
