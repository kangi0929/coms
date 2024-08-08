#ifndef QJOYSTICKCOMPORT_H
#define QJOYSTICKCOMPORT_H

#include <QObject>
#include <QThread>
#include "Comport.h"
#include "globalvar.h"

class QJoyStickComport : public QThread
{
    Q_OBJECT
public:
    explicit QJoyStickComport(QObject *parent = nullptr);
    void run();
    void InitParameter();
    void InitParameter(QString strDeviceNo, int iSpeed);
    void DecordCameraInfor(int iLen, char *buff);
    void JoystickUpdate();
    void JoystickReset();
signals:
    void signal_JoyStickComport_operate(int iOperateNo, int iParam0, int iParam1, int iParam2);

private:
    QComport m_qComJoyStick;
    int m_iJoyStick;
    bool m_bStop;
    char m_cRevInforBuf[16];
    int m_iRevIndex;
    int m_iCameraPanSpeed;
    int m_iBeforeCameraPanSpeed;
    int m_iCurrentCameraPanState;
    int m_iCurrentCameraState;
    int m_iXX_forwordValue;
    int m_iYY_forwordValue;
    int m_iZZ_forwordValue;
};
#endif  // QJOYSTICKCOMPORT_H
