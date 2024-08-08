#ifndef QINFRAREDCOMPORT_H
#define QINFRAREDCOMPORT_H

#include <QObject>
#include <QThread>
#include "Comport.h"

class QInfraredComport : public QThread
{
    Q_OBJECT
public:
    explicit QInfraredComport(QObject *parent = nullptr);
    void run();
    void InitParameter();
    void InitParameter(QString strDeviceNo, int iSpeed);
    void Infrared_ComparameterSetting(unsigned char ucAddr, unsigned int uiOperateId,
                                      unsigned char ucValue, unsigned short usAngle);
    void DecordCameraInfor(int iLen, char *buff);
signals:
    void signal_InfraredComport_operate(int iOperateNo, int iParam0, int iParam1, int iParam2);

private:
    QComport m_qComCommuInfrared;
    int m_iInfraredFd;
    bool m_bStop;
    char m_cRevInforBuf[16];
    int m_iRevIndex;
};

#endif  // QINFRAREDCOMPORT_H
