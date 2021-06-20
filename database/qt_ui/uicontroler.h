#ifndef UICONTROLER_H
#define UICONTROLER_H

#include <QObject>


class UiControler
{
public:
    static UiControler* getInstance();

    void showHomeView();
    void showLogin();

private:
    UiControler();
    static UiControler* _intent;
};

#endif // UICONTROLER_H
