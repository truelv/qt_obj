/**
 * widgetConfig定义了设置菜单的model数据，并导出给需要的控件使用
*/
#ifndef __WIDGETCONFIG_H__
#define __WIDGETCONFIG_H__
#include <QMetaType>

// 方块按键菜单类型定义
typedef enum {
    BOX_NULL = 0,       // 表示数组结束
    BOX_NONE,           // 无功能
    BOX_SETTING,
    BOX_QUERY,
} box_type;
typedef struct {
    box_type type;      // 类型
    const char* name;      // 显示名字
    const char* iconURl;   // 使用图标路径
} item_box;
Q_DECLARE_METATYPE(item_box)
// 方块按键菜单类型定义 end

// 按键列表菜单按键类型定义
typedef enum {
    BUTTON_NULL = 0,            // 表示数组结束
    BUTTON_NONE,                // 无功能
    BUTTON_DEVICE_SETTING,      // 进入本机设置界面
    BUTTON_HARDWARE_CONF,       // 进入硬件设置界面
    BUTTON_QUERY_INFO,          // 进入查询界面
    BUTTON_DEVICE_INFO,         // 进入设备信息查询
    BUTTON_NETPARAM_INFO,       // 进入网络信息界面
    BUTTON_FACEFEAT_INFO,       // 进入人脸信息界面
    BUTTON_VOLUME_SETTING,      // 进入音量设置
    BUTTON_BACKLIGHT_SETTING,   // 进入背光设置
    BUTTON_DATE_SETTING,        // 进入日期设置
    BUTTON_NETPARAM_SETTING,    // 进入网络设置
    BUTTON_WIFI_SETTING,        // 进入wifi设置
    BUTTON_WIFI_SCANC,          // 进入wifi扫码连接
    BUTTON_WIFI_HOTAP,          // 进入wifi热点
    BUTTON_ADVANCED_SETTING,    // 进入高级设置界面
    BUTTON_UPLOAD_LOGS,         // 启动上传日志
    BUTTON_RFIDSIGNAL_SETTING,  // 天线信号设置
    BUTTON_FACE_SETTING,        // 进入人脸检测参数设置
    BUTTON_MODE_SETTING,        // 进入控制器传输模式设置
    BUTTON_DEVICE_REBOOT,       // 启动设备重启
    BUTTON_DEVICE_INIT,         // 启动设备初始化（清除人脸识别相关信息）
    BUTTON_CLEAR_ALL,           // 恢复出厂设置
    BUTTON_TIMREBOOT_SWITCH,    // 凌晨重启开关
    BUTTON_WHITELED_SWITCH,     // 白灯开关
    BUTTON_SHOWTEXT_SETTING,    // 显示模式
    BUTTON_SOUND_SETTING,       // 音频模式
    BUTTON_DATCNT_INFO,         // 数据数量查询
    BUTTON_DATVER_INFO,         // 参数版本查询
    BUTTON_DEVPAR_INFO,         // 设备参数状态查询
    BUTTON_FACEEVT_INFO,        // 人脸事件记录查询
} button_type;
// 按键列表model定义
typedef struct {
    button_type type;   // 类型
    const char* name;      // 显示名字
} item_button;
Q_DECLARE_METATYPE(item_button)
// 按键列表菜单按键类型定义 end

// 展示信息类型定义（定义这个类型展示什么内容信息）
typedef enum {
    INFO_NULL = 0,          // 表示数组结束
    INFO_NONE,              // 未定义功能
    INFO_CHAR,
    INFO_INT,
    INFO_LONG,
    INFO_SHORT,
    INFO_FLOAT,
    INFO_STRING,
    INFO_IP,
    INFO_FACE_COUNT,
    INFO_AGENT_GUEST,
    INFO_HTTP_ADDR,
    INFO_FACE_INIT,
    INFO_LIVING_DET,
} info_type;
// 展示信息model定义
typedef struct {
    info_type type;
    const char* name;
    void* p;
} item_info;
Q_DECLARE_METATYPE(item_info)
// 展示信息类型定义（定义这个类型展示什么内容信息） end

extern item_box model_mainmenu[];           // 主设置界面
// 主设置界面按键
extern item_button model_queryInfo[];       // 信息查询界面
extern item_button model_setting[];         // 系统设置界面
// 信息查询界面按键
extern item_info model_datlocalverinfo[];        // 版本信息（本地）
#if 0
extern item_info model_datplatverinfo[];    // 版本信息（平台）
#endif
extern item_info model_datcountinfo[];      // 存储数据量信息
extern item_info model_netparaminfo[];      // 网络参数信息
extern item_info model_facedetinfo[];       // 人脸配置信息
extern item_info model_deviceinfo[];        // 设备信息
// 设置界面菜单
extern item_button model_hardwareconf[];    // 硬件设置
extern item_button model_deviceSetting[];   // 本机设置
extern item_button model_advancedSetting[]; // 高级菜单
#endif
