#include "globalsignal.h"

GlobalSignal* GlobalSignal::_Itent = nullptr;
GlobalSignal *GlobalSignal::GetInstance()
{
    if (nullptr==_Itent)
        _Itent = new GlobalSignal;
    return _Itent;
}

GlobalSignal::~GlobalSignal()
{
    _Itent = nullptr;
}

void GlobalSignal::SendSigSftpSta(SFTP_STA sta)
{
    emit SigSftpSta(sta);
}

void GlobalSignal::SendSigCftpEnd()
{
    emit SigCftpEnd();
}

GlobalSignal::GlobalSignal(QObject *parent) : QObject(parent)
{

}
