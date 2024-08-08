#ifndef GLOBALVAR_H
#define GLOBALVAR_H

#define CameraPan_device_number       1
#define Camera_device_number          1
#define Camera_infrared_device_number 2

#define CameraPan_speed_low  0x10
#define CameraPan_speed_mid  0x20
#define CameraPan_speed_high 0x40

#define CameraPan_speed_low_Display  3.89
#define CameraPan_speed_mid_Display  9.03
#define CameraPan_speed_high_Display 20.00

#define Camera_speed_low  0x10
#define Camera_speed_mid  0x20
#define Camera_speed_high 0x40

#define Mainwidow_OperateNo0  0   //云台和摄像头停止命令
#define Mainwidow_OperateNo1  1   // CameraPan 云台控制
#define Mainwidow_OperateNo2  2   // Camera 摄像头控制
#define Mainwidow_OperateNo3  3   //全景云台设置
#define Mainwidow_OperateNo4  4   //周视云台设置
#define Mainwidow_OperateNo5  5   //云台和摄像头方位设置
#define Mainwidow_OperateNo6  6   //云台和摄像头俯仰
#define Mainwidow_OperateNo7  7   //摇杆云台控制
#define Mainwidow_OperateNo8  8   //摇杆摄像头控制
#define Mainwidow_OperateNo9  9   //视口切换
#define Mainwidow_OperateNo10 10  //可见光状态, 热像状态
#define Mainwidow_OperateNo11 11  //可见光补光
#define Mainwidow_OperateNo12 12  //摇杆设置

#define JSON_KEY_DEVICE        "device"
#define JSON_KEY_MAC           "mac"
#define JSON_KEY_MODE          "mode"
#define JSON_KEY_RESULT        "result"
#define JSON_KEY_MSG           "msg"
#define JSON_KEY_ID            "id"
#define JOSN_KEY_DATA          "data"
#define JSON_KEY_PANORAMA_IP   "panorama_ip"
#define JSON_KEY_TARGET_INFO   "target_info"
#define JSON_KEY_ORIENTATION   "orientation"
#define JSON_KEY_TYPE          "type"
#define JSON_KEY_DEGREE        "degree"
#define JSON_KEY_PITCH         "pitch"
#define JOSN_KEY_DIRECTION     "direction"
#define JSON_KEY_TARGET_DEVICE "target_device"
#define JSON_KEY_DEVICE_TYPE   "device_type"
#define JSON_KEY_OPERATION     "operation"
#define JSON_KEY_VALUE         "value"
#define JSON_KEY_STATUS        "status"
#define JSON_KEY_DEVICE_ID     "device_id"
#define JSON_KEY_POSITION      "position"
#define JSON_KEY_AREA_DATA     "area_data"
#define JSON_KEY_AREA_ID       "area_id"
#define JSON_KEY_POINT_DATA    "point_data"
#define JSON_KEY_ORDER_NO      "order_no"
#define JSON_KEY_X_POS         "x_pos"
#define JSON_KEY_Y_POS         "y_pos"

#define JSON_KEY_HORIZONTAL "horizontal"
#define JSON_KEY_VERTICAL   "vertical"

//云台控制
#define URI_TRACE_SET_MODE      "api/trace/set_mode"
#define URI_TRACE_GET_MODE      "api/trace/get_mode"
#define URI_TRACE_SET_POS       "api/trace/set_pos"
#define URI_TRACE_MANUAL        "api/trace/manual"
#define URI_TRACE_REPORT        "api/trace/report"
#define URI_TRACE_REPORT_STATUS "api/trace/report_status"
#define URI_TARGET_REPORT       "api/target/report"
#define URI_TRACE_SET_AREA      "api/trace/set_area"

#define URI_COMMON_CTRL   "api/common/ctrl"
#define URI_COMMON_GET    "api/common/get"
#define URI_COMMON_REPORT "api/common/report"

#define URI_BIT_REPORT "api/bit/report"

#define URI_PANORAMA_GET_ORIENTATION "api/panorama/get_orientation"

// NVR
#define NVR_SAVE_VIDEO_CAPTURE "/nvr/save_video_capture"
#define NVR_SAVE_LOG           "/nvr/save_log"

enum TARGET_DEVICE_ID
{
    QUANJING_DEVICE = 1,  //全景相机
    ZHOUSHI_DEVICE,  //周视设备，主要控制红外和可见光的 焦距等信息，通过串口
    ZHOUSHI_PROCESSOR,  //周视处理板
    NVR_DEVICE,
    QIANGSHENG_DEVCIE,  //强声设备
    QIANGGUANG_DEVICE,  //强光设备
};

#endif  // GLOBALVAR_H
