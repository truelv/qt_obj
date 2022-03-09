#include "widget/widgetConfig.h"
#include "widget_common_typedef.h"

// 设置主界面的box按键
item_box model_mainmenu[] = {
    BOX_QUERY, "查询", "query_icon.png",
    BOX_SETTING, "设置", "setting_icon.png",
    {BOX_NULL, 0, 0},
};

// 查询信息界面的所有按键
item_button model_queryInfo[] = {
    BUTTON_DEVICE_INFO, "设备信息",
    BUTTON_NETPARAM_INFO, "网络信息",
    BUTTON_FACEFEAT_INFO, "人脸信息",
    BUTTON_DATCNT_INFO, "存储数据量信息",
    BUTTON_DATVER_INFO, "数据版本信息",
    BUTTON_NONE, "设备参数状态",
    BUTTON_NONE, "人脸事件记录",
    {BUTTON_NULL, 0},
};
// 设置界面的所有按键
item_button model_setting[] =
{
    BUTTON_DEVICE_SETTING,      "本机配置",
    BUTTON_HARDWARE_CONF,       "硬件配置",
#if (DEVICE_USE_TYPE==READER)
    BUTTON_MODE_SETTING,        "模式配置",
#endif
    BUTTON_FACE_SETTING,        "人脸检测设置",
    BUTTON_ADVANCED_SETTING,    "高级参数",
    BUTTON_UPLOAD_LOGS,         "日志上传",
    {BUTTON_NULL, 0},
};

// 设备信息参数显示列表
item_info model_deviceinfo[] =
{
    INFO_STRING, "固 件 版 本 号", (void*)APP_VERSION,
    INFO_STRING, "软 件 版 本 号", g_BaseInfo.platSoftWareVer,
    INFO_STRING, "终 端 序 列 号", g_BaseInfo.serialNum,
    INFO_AGENT_GUEST, "代 理 客 户 号", NULL,
    INFO_INT, "控制器站点号", &g_BaseInfo.controlNum,
    {INFO_NULL, 0, 0},
};
// 人脸参数显示列表
item_info model_facedetinfo[] = {
    INFO_FACE_INIT, "人 脸 初 始 化", &g_FaceInfo.faceInit,
    INFO_FLOAT, "人 脸 相 识 度", &g_FaceInfo.faceRegcThreshold,
    INFO_LIVING_DET, "活  体  检  测", &g_FaceInfo.faceLive,
    INFO_INT, "人脸本机版本", &g_platParam.faceInfoLocalVer,
    INFO_INT, "人脸平台版本", &g_platParam.faceInfoPlatVer,
    INFO_HTTP_ADDR, "  人 脸 http 地 址", g_platParam.faceInfoUrl,
    INFO_LONG, "黑白名单本机版本", &g_platParam.authLocalVer,
    INFO_LONG, "黑白名单平台版本", &g_platParam.authPlatVer,
    INFO_HTTP_ADDR, "黑白名单http地址", g_platParam.authInfoUrl,
    {INFO_NULL, 0, 0},
};
// 网络信息展示数据列表
item_info model_netparaminfo[] = {
    INFO_IP, "服务器IP", g_LocalNetInfo.ServerIP,
    INFO_INT, "服务器端口", &g_LocalNetInfo.ServerPort,
    INFO_IP, "以 太 网 IP", g_LocalNetInfo.LocalIP,
    INFO_IP, "以太网掩码", g_LocalNetInfo.SubNetMask,
    INFO_IP, "DNS 地址", g_LocalNetInfo.MasterDNS,
    INFO_STRING, "WIFI IP地址", g_WifiInfo.wifi_IP,
    INFO_STRING, "WIFI  掩码", g_WifiInfo.wifi_Mask,
    {INFO_NULL, 0, 0},
};
// 存储数据量信息
item_info model_datcountinfo[] = {
    INFO_INT, "注册人脸数量", &g_FaceInfo.faceVaildCnt,
    INFO_INT, "人脸信息数量", &g_FaceInfo.faceTotalCnt,
    INFO_INT, "卡户信息数量", &g_platParam.cardAccCount,
    INFO_INT, "进门权限数量", &g_FaceInfo.authCnt,
    INFO_INT, "临时权限数量", &g_platParam.tmpAuthCount,
    INFO_INT, "记录流水数量", &g_eventReport.eventCount,
    INFO_INT, "上传流水数量", &g_eventReport.evnReportCount,
    INFO_INT, "人脸流水数量", &g_FaceInfo.faceVaildCnt,
    INFO_INT, "上传人脸流水数", &g_FaceInfo.faceVaildCnt,
    {INFO_NULL, 0, 0},
};
// 数据版本信息（本地）
item_info model_datlocalverinfo[] = {
    // 设备端
    INFO_INT, "设备参数版本", &g_platParam.devParamPlatVer,
    INFO_INT, "权限本地版本", &g_platParam.authLocalVer,
    INFO_INT, "人脸信息版本", &g_platParam.faceInfoLocalVer,
#if (DEVICE_USE_TYPE==DCTR_40 || DEVICE_USE_TYPE==DCTR_YT)
    INFO_INT, "系统参数版本", &g_platParam.sysParamLocalVer,
    INFO_INT, "门参数版本号", &g_platParam.doorParamLocalVer,
    INFO_INT, "时段组版本号", &g_platParam.timeGroupLocalVer,
#if (DEVICE_USE_TYPE==DCTR_40)
    INFO_INT, "时段模板版本", &g_platParam.timeTempLocalVer,
#endif
    INFO_INT, "门假日版本号", &g_platParam.doorHolidayLocalVer,
    INFO_INT, "卡号帐号版本", &g_platParam.cardAccLocalVer,
#if (DEVICE_USE_TYPE==DCTR_YT)
    INFO_INT, "帐号信息版本", &g_platParam.accInfoLocalVer,
#endif
    INFO_INT, "临时权限版本", &g_platParam.accTmpAuthLocalVer,
#if (DEVICE_USE_TYPE==DCTR_YT)
    INFO_INT, "读头参数版本", &g_platParam.readerLocalVer,
#endif
#endif
    {INFO_NULL, 0, 0},
};
#if 0
// 数据版本信息（平台）
item_info model_datplatverinfo[] = {
    // 平台端
    INFO_INT, "设备参数版本（平台）", &g_FaceInfo.faceTotalCnt,
    INFO_INT, "权限本地版本（平台）", &g_FaceInfo.authCnt,
    INFO_INT, "人脸信息版本（平台）", &g_FaceInfo.authCnt,
#if (DEVICE_USE_TYPE==DCTR_40 || DEVICE_USE_TYPE==DCTR_YT)
    INFO_INT, "系统参数版本（平台）", &g_FaceInfo.authCnt,
    INFO_INT, "门参数版本号（平台）", &g_FaceInfo.authCnt,
    INFO_INT, "时段组版本号（平台）", &g_FaceInfo.authCnt,
#if (DEVICE_USE_TYPE==DCTR_40)
    INFO_INT, "时段模板版本（平台）", &g_FaceInfo.authCnt,
#endif
    INFO_INT, "门假日版本号（平台）", &g_FaceInfo.authCnt,
    INFO_INT, "卡号帐号版本（平台）", &g_FaceInfo.authCnt,
#if (DEVICE_USE_TYPE==DCTR_YT)
    INFO_INT, "帐号信息版本（平台）", &g_FaceInfo.authCnt,
#endif
    INFO_INT, "临时权限版本（平台）", &g_FaceInfo.authCnt,
#if (DEVICE_USE_TYPE==DCTR_YT)
    INFO_INT, "读头参数版本（平台）", &g_FaceInfo.authCnt,
#endif
#endif

    {INFO_NULL, 0, 0},
};
#endif
// 设备参数状态信息
// 人脸事件信息

// 硬件配置菜单
item_button model_hardwareconf[] = {
    BUTTON_WHITELED_SWITCH,     "白光开关（关）",
    BUTTON_RFIDSIGNAL_SETTING,  "天线信号设置",
    BUTTON_SHOWTEXT_SETTING,    "显示模式设置",
    BUTTON_SOUND_SETTING,       "语音模式设置",
    {BUTTON_NULL, 0},
};
// 本机设置菜单
item_button model_deviceSetting[] = {
    BUTTON_WIFI_SETTING, "wifi设置",
    BUTTON_WIFI_SCANC, "wifi卡设置",
    BUTTON_WIFI_HOTAP, "运维助手",
    BUTTON_NETPARAM_SETTING, "网络配置",
    BUTTON_DATE_SETTING, "时钟配置",
    BUTTON_VOLUME_SETTING, "音量调节",
    BUTTON_BACKLIGHT_SETTING, "亮度调节",
    {BUTTON_NULL, 0},
};
// 高级设置菜单列表
// 恢复出厂设置，删除所有的data目录下的文件，所有的参数（包括本地设置的参数）被初始化
// 初始化设备，删除指定的数据库表，表现为重新获取从平台获取的参数，本地设置的参数保留
item_button model_advancedSetting[] = {
    BUTTON_CLEAR_ALL, "恢复出厂设置",
    BUTTON_DEVICE_INIT, "初始化设备",
    BUTTON_DEVICE_REBOOT, "重启设备",
#if 0
    BUTTON_NONE, "切换到工厂程序",
    BUTTON_NONE, "服务控制设置",
#endif
    BUTTON_TIMREBOOT_SWITCH, "凌晨重启（关）",
    {BUTTON_NULL, 0},
};


