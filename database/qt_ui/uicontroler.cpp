#include "uicontroler.h"
#include "testscreenpush.h"
#include "login.h"

UiControler* UiControler::_intent = NULL;

UiControler *UiControler::getInstance()
{
    if (NULL==_intent)
        _intent = new UiControler;

    return _intent;
}

void UiControler::showHomeView()
{
    QWidget* w = new TestScreenPush;
    w->show();
}

void UiControler::showLogin()
{
    QWidget* w = new Login;
    w->show();
}

UiControler::UiControler()
{

}

