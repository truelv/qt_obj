#ifndef _SIGNALSENDER_INTERFACE_H_
#define _SIGNALSENDER_INTERFACE_H_
#ifdef __cplusplus
extern "C" {
#endif
// 485信号
void sendSignalRs485Online(int sta);
// 人脸检测结果信号
void sendSignalForDraw();
// wifi状态变化信号
void sendSignalWifiScanFailed();
void sendSignalUpdateListWifi();
void sendSignalClearListWifi();
void sendSignalWifiConnected();
void sendSignalWifiDisConnected();
// 以太网状态变化信号
void sendSignalEthOnline();
void sendSignalEthOffline();
// 服务状态
void sendSignalBeatSuccess();
void sendSignalBeatFailed();
// 通知亮屏/熄屏
void sendSignalScreenOff();
void sendSignalScreenOn();
void sendSignalScreenOnTimeout();
// 日志上传成功/失败
void sendSignalUploadLogsSuccess();
void sendSignalUploadLogsFailed();

void sendSignalShowInfo(char cResult, char cShowInfo[16]);
void sendSignalShowInfo2(char cShowInfo[16]);
//
void appExit();
//
void sendSignalFaceUnregistered();
#ifdef __cplusplus
}
#endif
#endif



