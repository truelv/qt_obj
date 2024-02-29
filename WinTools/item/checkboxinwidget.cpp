#include "checkboxinwidget.h"

CheckboxInWidget::CheckboxInWidget()
{
    this->setLayout(&lay);
    lay.addWidget(&checkbox);
}

CheckboxInWidget::~CheckboxInWidget()
{

}

void CheckboxInWidget::setCheckboxChecked(bool checked)
{
    checkbox.setChecked(checked);
}

void CheckboxInWidget::setCheckboxSlot(const QObject *receiver, const char *member)
{
    connect(&checkbox, SIGNAL(stateChanged(int)), receiver, member);
}

void CheckboxInWidget::setCheckProperty(const char *name, const QVariant &value)
{
    checkbox.setProperty(name, value);
}
