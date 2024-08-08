#include "JoyStickComport.h"
#include <QDebug>

QJoyStickComport::QJoyStickComport(QObject *parent) : QThread(parent)
{

    InitParameter();
}

void QJoyStickComport::run()
{
    char buff[1024];

    if (m_iJoyStick > 0)
    {
        while (!m_bStop)
        {
            memset(buff, 0, 1024);  //全部填0
            int nlen = read(m_iJoyStick, buff, 1024);

            if (nlen > 0)
            {
                //                qDebug() << "receive data len:" << nlen<< "receive data:" << buff[0];
                DecordCameraInfor(nlen, buff);
            }
//            else
//            {
//                printf("nlen = %d\n",nlen);
//            }
            usleep(1000);
        }
    }
}

void QJoyStickComport::InitParameter()
{
    // m_iInfraredFd = m_qComCommuInfrared.open_uart_full("/dev/tty1",9600,8,1,'n');
    m_bStop                  = false;
    m_iJoyStick              = -1;
    m_iCameraPanSpeed        = 0x10;
    m_iBeforeCameraPanSpeed  = -1;
    m_iCurrentCameraPanState = -1;
    m_iCurrentCameraState    = -1;
    m_iXX_forwordValue = -1;
    m_iYY_forwordValue = -1;
    m_iZZ_forwordValue = -1;
}

void QJoyStickComport::InitParameter(QString strDeviceNo, int iSpeed)
{
    if (m_iJoyStick > 0)
    {
        int iCloseRet = close(m_iJoyStick);
        //        qDebug() << "iCloseRet:" << iCloseRet;
    }
    QByteArray baBuff = strDeviceNo.toLocal8Bit();
    char *cBuff       = baBuff.data();
    qDebug() << "cBuff:" << cBuff;
    m_iJoyStick = m_qComJoyStick.open_uart_full(cBuff, iSpeed, 8, 1, 'n');

    //    unsigned char cSendBuff[] = {0xAF,0x05,0x02,0x00,0x00,0x00,0xF5};
//    unsigned char cSendBuff[] = {0xaf,0x11,0x00,0x00,0x00,0x64,0xf5};
//    int iSendLen = write(m_iJoyStick,cSendBuff,7);
//    qDebug() << "QJoyStickComport::iSendLen:" << iSendLen;
}

void QJoyStickComport::DecordCameraInfor(int iLen, char *buff)
{
    int icount;
    static int iHead     = -1;
    char checkNum = 0x00;
    icount = 0;
//    int i;
    //qDebug() << "iLen" << iLen;
//    printf("iLen=%d\n",iLen);
//    for (i = 0; i < iLen; i++)
//    {
////        qDebug() << "iLen:" << hex << buff[i];
//        printf("%x ",buff[i]);
//    }
//    printf("\n");
//    return;

    while (icount < iLen)
    {
        if (buff[icount] == 0xFF)
        {
            iHead       = 1;
            m_iRevIndex = 0;
            checkNum    = 0x00;
        }
        else if(iHead != 1)
        {
            icount++;
            continue;
        }
        if (iHead == 1)
        {
//            if(m_iRevIndex < 9 && (icount + 9) < iLen )
//            {
//                memcpy(&m_cRevInforBuf,&buff[icount],9*sizeof(char));
//                m_iRevIndex = 8;
//                checkNum = checkNum + m_cRevInforBuf[1]+ m_cRevInforBuf[2]+ m_cRevInforBuf[3]+ m_cRevInforBuf[4]+ m_cRevInforBuf[5]+ m_cRevInforBuf[6]+ m_cRevInforBuf[7];
//                icount += 9;//10
//            }
//            else if((icount + 9) >= iLen)
//            {
//                iHead       = -1;
//                m_iRevIndex = 0;
//                checkNum    = 0x00;
//                return;
//            }
//            m_iRevIndex++;

//            ff 00 2
//            20 20 06 20 20 30 30 7

//            while (icount < iLen)
//            {
//                m_cRevInforBuf[m_iRevIndex] = buff[icount];
//                icount++;
//                m_iRevIndex++;
//                if(m_iRevIndex == 9)
//                {
//                    checkNum = checkNum + m_cRevInforBuf[1]+ m_cRevInforBuf[2]+ m_cRevInforBuf[3]+ m_cRevInforBuf[4]+ m_cRevInforBuf[5]+ m_cRevInforBuf[6]+ m_cRevInforBuf[7];
//                    break;
//                }
//            }
//            printf("iLen=%d,m_iRevIndex = %d\n",iLen,m_iRevIndex);
            int iCopyCount = 9 - m_iRevIndex;

            if(iCopyCount <= iLen)
            {
                memcpy(&m_cRevInforBuf[m_iRevIndex],&buff[icount],iCopyCount*sizeof(char));
            }
            else
            {
                iCopyCount = iLen;
                memcpy(&m_cRevInforBuf[m_iRevIndex],&buff[icount],iCopyCount*sizeof(char));
            }
//            printf("iCopyCount=%d,m_iRevIndex = %d\n",iCopyCount,m_iRevIndex);
            m_iRevIndex = m_iRevIndex + iCopyCount;
            icount = icount + iCopyCount;
            if(m_iRevIndex == 9)
            {
                checkNum = checkNum + m_cRevInforBuf[1]+ m_cRevInforBuf[2]+ m_cRevInforBuf[3]+ m_cRevInforBuf[4]+ m_cRevInforBuf[5]+ m_cRevInforBuf[6]+ m_cRevInforBuf[7];
            }
            else if(m_iRevIndex < 9)
            {
                return;
            }

//            m_cRevInforBuf[m_iRevIndex] = buff[i];
//            if (m_iRevIndex > 0 && m_iRevIndex < 8)
//            {
//                checkNum = checkNum + m_cRevInforBuf[m_iRevIndex];
//            }

        }
        if (m_iRevIndex == 9 && checkNum == m_cRevInforBuf[m_iRevIndex - 1])
        {
//            qDebug() << "receive data len:"<< hex << (int)(m_cRevInforBuf[3]);

            int iYY = (m_cRevInforBuf[1] << 8) | m_cRevInforBuf[2];
            int iXX = (m_cRevInforBuf[3] << 8) | m_cRevInforBuf[4];
            int iZZ = (m_cRevInforBuf[5] << 8) | m_cRevInforBuf[6];

            if(m_iXX_forwordValue == iXX && m_iYY_forwordValue == iYY && m_iZZ_forwordValue == iZZ)
            {
                iHead       = -1;
                m_iRevIndex = 0;
                checkNum    = 0x00;
                continue;
            }
            else
            {
                m_iXX_forwordValue = iXX;
                m_iYY_forwordValue = iYY;
                m_iZZ_forwordValue = iZZ;
            }

            int iSubXXValue, iSubYYValue;
            iSubXXValue = abs(iXX - 512);
            iSubYYValue = abs(iYY - 512);

            if (iSubXXValue != 0 || iSubYYValue != 0)
            {
                if (iSubXXValue > iSubYYValue)
                {
                    if (iXX > 832)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_high;
                    }
                    else if (iXX > 672)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_mid;
                    }
                    else if (iXX > 512)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_low;
                    }
                    else if (iXX > 352)  // 512-160
                    {
                        m_iCameraPanSpeed = CameraPan_speed_low;
                    }
                    else if (iXX > 160)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_mid;
                    }
                    else
                    {
                        m_iCameraPanSpeed = CameraPan_speed_high;
                    }

                    if (m_iBeforeCameraPanSpeed != m_iCameraPanSpeed)
                    {
                        m_iCurrentCameraPanState = -1;
                        m_iBeforeCameraPanSpeed  = m_iCameraPanSpeed;
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo3, 0,
                                                            Camera_speed_low, m_iCameraPanSpeed);
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo4, 0,
                                                            Camera_speed_low, m_iCameraPanSpeed);
                    }

                    if (iXX > 512 && m_iCurrentCameraPanState != 1)
                    {
                        m_iCurrentCameraPanState = 1;
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo7,
                                                            CameraPan_device_number, 4,
                                                            m_iCameraPanSpeed);  //右
//                        qDebug() << "右:iXX " << iXX;
                    }
                    else if (m_iCurrentCameraPanState != 1 && m_iCurrentCameraPanState != 2)
                    {

                        m_iCurrentCameraPanState = 2;
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo7,
                                                            CameraPan_device_number, 3,
                                                            m_iCameraPanSpeed);  //左
//                        qDebug() << "左:iXX " << iXX;
                    }
                }
                else
                {
                    if (iYY > 832)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_high;
                    }
                    else if (iYY > 672)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_mid;
                    }
                    else if (iYY > 512)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_low;
                    }
                    else if (iYY > 352)  // 512-160
                    {
                        m_iCameraPanSpeed = CameraPan_speed_low;
                    }
                    else if (iYY > 160)
                    {
                        m_iCameraPanSpeed = CameraPan_speed_mid;
                    }
                    else
                    {
                        m_iCameraPanSpeed = CameraPan_speed_high;
                    }

                    if (m_iBeforeCameraPanSpeed != m_iCameraPanSpeed)
                    {
                        m_iCurrentCameraPanState = -1;
                        m_iBeforeCameraPanSpeed  = m_iCameraPanSpeed;
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo3, 0,
                                                            Camera_speed_low, m_iCameraPanSpeed);
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo4, 0,
                                                            Camera_speed_low, m_iCameraPanSpeed);
                    }

                    if (iYY > 512 && m_iCurrentCameraPanState != 3)
                    {
                        m_iCurrentCameraPanState = 3;
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo7,
                                                            CameraPan_device_number, 1,
                                                            m_iCameraPanSpeed);  //上
//                        qDebug() << "上:iYY " << iYY;
                    }
                    else if (m_iCurrentCameraPanState != 3 && m_iCurrentCameraPanState != 4)
                    {

                        m_iCurrentCameraPanState = 4;
                        emit signal_JoyStickComport_operate(Mainwidow_OperateNo7,
                                                            CameraPan_device_number, 2,
                                                            m_iCameraPanSpeed);  //下
//                        qDebug() << "下:iYY " << iYY;
                    }
                }
            }
            else
            {
                if (m_iCurrentCameraPanState != 5)
                {
                    m_iCurrentCameraPanState = 5;
                    emit signal_JoyStickComport_operate(0, CameraPan_device_number, 0, 0);  //停
                    emit signal_JoyStickComport_operate(Mainwidow_OperateNo3, 0, Camera_speed_low,
                                                        CameraPan_speed_low);
                    emit signal_JoyStickComport_operate(Mainwidow_OperateNo4, 0, Camera_speed_low,
                                                        CameraPan_speed_low);
//                    qDebug() << "停:m_iCurrentCameraPanState " << m_iCurrentCameraPanState;
                }
            }

            if (iZZ != 512)
            {
                if (iZZ > 512 && m_iCurrentCameraState != 1)
                {
                    m_iCurrentCameraState = 1;
                    emit signal_JoyStickComport_operate(Mainwidow_OperateNo8, 0, 6, 0);
                    //qDebug() << "iZZ:m_iCurrentCameraState = 1 " << iZZ;
                }
                else if (m_iCurrentCameraState != 1 && m_iCurrentCameraState != 2)
                {
                    m_iCurrentCameraState = 2;
                    emit signal_JoyStickComport_operate(Mainwidow_OperateNo8, 0, 5, 0);
                   // qDebug() << "iZZ:m_iCurrentCameraState = 2 " << iZZ;
                }
            }
            else if (m_iCurrentCameraState != 3)
            {
                m_iCurrentCameraState = 3;
                emit signal_JoyStickComport_operate(0, Camera_device_number, 0, 0);  //停
                emit signal_JoyStickComport_operate(Mainwidow_OperateNo3, 0, Camera_speed_low,
                                                    CameraPan_speed_low);
                emit signal_JoyStickComport_operate(Mainwidow_OperateNo4, 0, Camera_speed_low,
                                                    CameraPan_speed_low);
                //qDebug() << "iZZ:停 " << iZZ;
            }

            //            if(m_cRevInforBuf[3] == 0x59)
            //            {
            //                int iTempAzimuth = (m_cRevInforBuf[4] << 8) | m_cRevInforBuf[5];
            //                //            memcpy(&iTempSpeed,&m_cRevInforBuf[4],2*sizeof(char));
            //                qDebug() << "receive data iTempAzimuth:"<<iTempAzimuth;
            //                emit signal_InfraredComport_operate(5,iTempAzimuth,0,0);
            //            }
            //            else if(m_cRevInforBuf[3] == 0x5B)
            //            {
            //                int iTempPitch = (m_cRevInforBuf[4] << 8) | m_cRevInforBuf[5];
            //                //            memcpy(&iTempSpeed,&m_cRevInforBuf[4],2*sizeof(char));
            //                qDebug() << "receive data iTempPitch:"<<iTempPitch;
            //                emit signal_InfraredComport_operate(6,iTempPitch,0,0);
            //            }
            iHead       = -1;
            m_iRevIndex = 0;
            checkNum    = 0x00;
        }
        else //if (m_iRevIndex > 9)
        {
            iHead       = -1;
            m_iRevIndex = 0;
            checkNum    = 0x00;
            qDebug() << "error receive data len:" << m_iRevIndex;
        }
    }
}

void QJoyStickComport::JoystickUpdate()
{
    unsigned char cSendBuff[] = {0xaf,0x11,0x00,0x00,0x00,0x64,0xf5};
    int iSendLen = write(m_iJoyStick,cSendBuff,7);
    qDebug() << "QJoyStickComport::iSendLen:" << iSendLen;
}

void QJoyStickComport::JoystickReset()
{
    unsigned char cSendBuff[] = {0xaf,0x15,0x00,0x00,0x00,0x00,0xf5};
    int iSendLen = write(m_iJoyStick,cSendBuff,7);
    qDebug() << "QJoyStickComport::iSendLen:" << iSendLen;
}
