#include "signalsender_interface.h"
#include "signalsender.h"
#include <QApplication>

void sendSignalForDraw()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalForDraw();
}

void sendSignalWifiScanFailed()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalWifiScanFailed();
}

void sendSignalUpdateListWifi()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalUpdateListWifi();
}

void sendSignalClearListWifi()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalClearListWifi();
}

void sendSignalWifiConnected()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalWifiConnected();
}

void sendSignalWifiDisConnected()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalWifiDisConnected();
}

void sendSignalEthOnline()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalEthOnline();
}

void sendSignalEthOffline()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalEthOffline();
}

void sendSignalBeatSuccess()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalBeatSuccess();
}

void sendSignalBeatFailed()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalBeatFailed();
}

void sendSignalScreenOff()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalScreenOff();
}

void sendSignalScreenOn()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalScreenOn();
}

void sendSignalScreenOnTimeout()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalScreenOnTimeout();
}

void sendSignalRs485Online(int sta)
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalRs485Online(sta);
}

void appExit()
{
    qApp->quit();
}

void sendSignalFaceUnregistered()
{
    SignalSender* sender = SignalSender::getInstance();
    sender->sendSignalFaceUnregistered();
}
