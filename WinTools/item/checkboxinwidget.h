#ifndef CHECKBOXINWIDGET_H
#define CHECKBOXINWIDGET_H

#include <QWidget>
#include <QCheckBox>
#include <QHBoxLayout>

class CheckboxInWidget : public QWidget
{
    Q_OBJECT
public:
    CheckboxInWidget();
    ~CheckboxInWidget();

    void setCheckboxChecked(bool checked);
    void setCheckboxSlot(const QObject *receiver, const char *member);
    void setCheckProperty(const char *name, const QVariant &value);

    QCheckBox checkbox;
    QHBoxLayout lay;
};

#endif // CHECKBOXINWIDGET_H
