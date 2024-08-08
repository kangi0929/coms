#include "InfraredComport.h"
#include <QDebug>

QInfraredComport::QInfraredComport(QObject *parent) : QThread(parent)
{

    InitParameter();
}

void QInfraredComport::run()
{
    char buff[1024];

    if (m_iInfraredFd > 0)
    {
        while (!m_bStop)
        {
            memset(buff, 0, 1024);
            int nlen = read(m_iInfraredFd, buff, 1024);

            if (nlen > 0)
            {
                //qDebug() << "receive data len:" << nlen<< "receive data:" << buff[0];
                DecordCameraInfor(nlen, buff);
            }
            usleep(1000);
        }
    }
}
void QInfraredComport::DecordCameraInfor(int iLen, char *buff)
{
    int i;
    int iHead     = -1;
    char checkNum = 0x00;
    for (i = 0; i < iLen; i++)
    {
        if (buff[i] == 0xFF)
        {
            iHead       = 1;
            m_iRevIndex = 0;
            checkNum    = 0x00;
        }
        if (iHead == 1)
        {
            m_cRevInforBuf[m_iRevIndex] = buff[i];
            if (m_iRevIndex > 0 && m_iRevIndex < 6)
            {
                checkNum = checkNum + m_cRevInforBuf[m_iRevIndex];
            }
            m_iRevIndex++;
        }
        if (m_iRevIndex == 7 && checkNum == m_cRevInforBuf[m_iRevIndex - 1])
        {
            //            qDebug() << "receive data len:"<< hex << (int)(m_cRevInforBuf[3]);

            if (m_cRevInforBuf[3] == 0x59)
            {
                int iTempAzimuth = (m_cRevInforBuf[4] << 8) | m_cRevInforBuf[5];
                //            memcpy(&iTempSpeed,&m_cRevInforBuf[4],2*sizeof(char));
                //                qDebug() << "receive data iTempAzimuth:"<<iTempAzimuth;
                emit signal_InfraredComport_operate(5, iTempAzimuth, 0, 0);
            }
            else if (m_cRevInforBuf[3] == 0x5B)
            {
                int iTempPitch = (m_cRevInforBuf[4] << 8) | m_cRevInforBuf[5];
                //            memcpy(&iTempSpeed,&m_cRevInforBuf[4],2*sizeof(char));
                //                qDebug() << "receive data iTempPitch:"<<iTempPitch;
                emit signal_InfraredComport_operate(6, iTempPitch, 0, 0);
            }
            //设备状态报文，它会每五秒发给本地一次
            else if(m_cRevInforBuf[2] == 0x8E && m_cRevInforBuf[3] == 0xE9)
            {
                int optical = m_cRevInforBuf[4];
                int infrared = m_cRevInforBuf[5];
                //qDebug() << "optical  " << optical << ",  " << "infrared  " << infrared;
                emit signal_InfraredComport_operate(10, optical, infrared, 0);
            }
            iHead       = -1;
            m_iRevIndex = 0;
            checkNum    = 0x00;
        }
        else if (m_iRevIndex > 7)
        {
            iHead       = -1;
            m_iRevIndex = 0;
            checkNum    = 0x00;
            //            qDebug() << "error receive data len:" << m_iRevIndex;
        }
    }
}

void QInfraredComport::InitParameter()
{
    // m_iInfraredFd = m_qComCommuInfrared.open_uart_full("/dev/tty1",9600,8,1,'n');
    m_bStop       = false;
    m_iInfraredFd = -1;
    memset(&m_cRevInforBuf, 0, 16 * sizeof(char));
    m_iRevIndex = 0;
}

void QInfraredComport::InitParameter(QString strDeviceNo, int iSpeed)
{
    if (m_iInfraredFd > 0)
    {
        int iCloseRet = close(m_iInfraredFd);
        qDebug() << "iCloseRet:" << iCloseRet;
    }
    QByteArray baBuff = strDeviceNo.toLocal8Bit();
    char *cBuff       = baBuff.data();
    qDebug() << "cBuff:" << cBuff;
    m_iInfraredFd = m_qComCommuInfrared.open_uart_full(cBuff, iSpeed, 8, 1, 'n');
}

//水平向右控制	FF Addr 00 02 HSPD 00 Checksum
//水平向左控制	FF Addr 00 04 HSPD 00 Checksum
//俯仰向上控制	FF Addr 00 08 00 VSPD Checksum
//俯仰向下控制	FF Addr 00 10 00 VSPD Checksum
//变倍加控制	    FF Addr 00 20 00 00 Checksum
//变倍减控制	    FF Addr 00 40 00 00 Checksum
//聚焦远控制	    FF Addr 00 80 00 00 Checksum
//聚焦近控制	    FF Addr 01 00 HSPD 00 Checksum
//光圈开控制	    FF Addr 02 00 00 00 Checksum
//光圈关控制	    FF Addr 04 00 00 00 Checksum
//停止指令	    FF Addr 00 00 00 00 Checksum
//水平角度定位	FF Addr 00 4B DataH DataL Checksum
//俯仰角度定位	FF Addr 00 4D DataH DataL Checksum
//停止指令	FF Addr 00 00 00 00 Checksum
//注1： ①HSPD:水平速度级，取值范围0x00~0x40，共64级
//②VSPD:俯仰速度级，取值范围0x00~0x40，共64级
//③DataH、DataL 为0~36000间的十六进制数，对应水平0~360度
//④俯仰角度格式：0=horizontally；90=straight down；270=straight up
// Range:0~9000 and 27000~35999 （实际角度范围以技术要求为准）
//⑤逐行扫描俯仰步长：angle =（DataH*256+DataL）/100，默认为5度
//⑥ time为1-8，对应的巡航停留间隔时间为4S,10S,20S,30S,1min,2min,3min,4min；
//⑦ time为1-60，对应的自动归位时间为1-60min
//注2：以上指令中，Byte3决定执行的指令，DataH、DataL为指令对应数值的高字节和低字节;其他基本运动和镜头控制指令参考标准Pelco协议
void QInfraredComport::Infrared_ComparameterSetting(unsigned char ucAddr, unsigned int uiOperateId,
                                                    unsigned char ucValue, unsigned short usAngle)
{
    QString strValue;
    unsigned char cSendBuff[] = {0xFF, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00};
    switch (uiOperateId)
    {
        case 0:  //停止指令
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x00;
            //        cSendBuff[5] = ucValue;
        }
        break;
        case 1:  //俯仰向上控制
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x08;
            cSendBuff[5] = ucValue;
        }
        break;
        case 2:  //俯仰向下控制
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x10;
            cSendBuff[5] = ucValue;
        }
        break;
        case 3:  //水平向左控制
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x04;
            cSendBuff[4] = ucValue;
        }
        break;
        case 4:  //水平向右控制
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x02;
            cSendBuff[4] = ucValue;
        }
        break;
        case 5:  //变倍长
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x20;
        }
        break;
        case 6:  //变倍短
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x40;
        }
        break;
        case 7:  //聚焦远
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x80;
        }
        break;
        case 8:  //聚焦近
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x01;
            cSendBuff[3] = 0x00;
            cSendBuff[4] = ucValue;
        }
        break;
        case 9:  //光圈小
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x02;
            cSendBuff[3] = 0x00;
        }
        break;
        case 10:  //光圈大
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x04;
            cSendBuff[3] = 0x00;
        }
        break;
        case 11:  //云台转换水平
        {
            //水平角度定位	FF Addr 00 4B DataH DataL Checksum
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x4B;
            cSendBuff[4] = (usAngle & 0xff00) >> 8;  // 取高8位
            // qDebug() << "&*&*&*&*&*&*&*&*";
            // qDebug() << (unsigned short)((usAngle & 0xff00) >> 8);
            cSendBuff[5] = usAngle & 0x00ff;  //取低8位
            // qDebug() << (unsigned short)(usAngle & 0x00ff);
            // qDebug() << "&*&*&*&*&*&*&*&*";
        }
        break;
        case 12:  //云台转换垂直
        {
            //俯仰角度定位	FF Addr 00 4D DataH DataL Checksum
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x4D;
            cSendBuff[4] = (usAngle & 0xff00) >> 8;  // 取高8位
            cSendBuff[5] = usAngle & 0x00ff;         //取低8位
        }
        break;
        case 15: //云台归零
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x07;
            cSendBuff[4] = 0x00;
            cSendBuff[5] = 0x00;
        }
        break;
        case 16:  //设置云台归零
        {
            cSendBuff[1] = ucAddr;
            cSendBuff[2] = 0x00;
            cSendBuff[3] = 0x03;
            cSendBuff[4] = 0x00;
            cSendBuff[5] = 0x00;
        }
        break;
    case 17:  //自动补光
    {
        cSendBuff[1] = ucAddr;
        cSendBuff[2] = 0x00;
        cSendBuff[3] = 0x07;
        cSendBuff[4] = 0x00;
        cSendBuff[5] = 0xf2;
    }
    break;
    case 18:  //手动开启补光
    {
        cSendBuff[1] = ucAddr;
        cSendBuff[2] = 0x00;
        cSendBuff[3] = 0x03;
        cSendBuff[4] = 0x00;
        cSendBuff[5] = 0xf2;
    }
    break;
    case 19:  //手动关闭补光
    {
        cSendBuff[1] = ucAddr;
        cSendBuff[2] = 0x00;
        cSendBuff[3] = 0x05;
        cSendBuff[4] = 0x00;
        cSendBuff[5] = 0xf2;
    }
    break;
        default:
        {
            return;
        }
        break;
    }

    cSendBuff[6] = (cSendBuff[1] + cSendBuff[2] + cSendBuff[3] + cSendBuff[4] + cSendBuff[5]) & 0xFF;
    //    m_qComCommuInfrared->SendComData((char *)cSendBuff,7);
//    msleep(100);//lqr20220920
    int iSendLen = write(m_iInfraredFd, cSendBuff, 7);
    //    unsigned char cSendBuff1[] = {0xFF,0x01,0x00,0x51,0x00,0x00,0x52};
    //    write(m_iInfraredFd,cSendBuff1,7);
    qDebug() << "iSendLen" << iSendLen;
}
