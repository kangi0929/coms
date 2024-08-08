#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    m_tmOperateDelayTime = new QTimer(this);
    connect(m_tmOperateDelayTime, SIGNAL(timeout()), this, SLOT(SltOperateDelayTime()));

    m_qCameraPanComport = new QInfraredComport(this);
    m_qCameraPanComport->InitParameter("/dev/ttyUSB0", 9600);
    m_qCameraPanComport->start();
    connect(m_qCameraPanComport, SIGNAL(signal_InfraredComport_operate(int, int, int, int)), this,
            SLOT(SltRecvOperateNo(int, int, int, int)));
    connect(this, SIGNAL(signal_operateNo(int, int, int, int)), this,
            SLOT(SltRecvOperateNo(int, int, int, int)));

    m_iCameraPanSpeed = CameraPan_speed_low;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::SltRecvOperateNo(int iOperateNo, int iParam0, int iParam1, int iParam2)
{
    //qDebug() << "iOperatoNO:   " << iOperateNo;

    int iii = 0;

    switch (iOperateNo)
    {
    case Mainwidow_OperateNo0:  // send camera and cameraPan stop
    {
        m_iCameraDeviceNo = iParam0;
        m_tmOperateDelayTime->start(200);
    }
    break;
    case Mainwidow_OperateNo1:  // CameraPan 云台控制
    {
        //        m_iCameraDeviceNo = iParam0;
        m_qCameraPanComport->Infrared_ComparameterSetting(iParam0, iParam1, iParam2, 0);
    }
    break;
    case Mainwidow_OperateNo2:  // Camera 摄像头控制
    {
        m_qCameraComport->Infrared_ComparameterSetting(iParam0, iParam1, iParam2, 0);
    }
    break;
    case Mainwidow_OperateNo3:  //全景云台设置
    {
        // m_QMainWgt->setCameraPanSpeed(iParam1, iParam2);
    }
    break;
    case Mainwidow_OperateNo4:  //周视云台设置
    {
        // m_QZhouShiWgt->setCameraPanSpeed(iParam1, iParam2);
    }
    break;
    case Mainwidow_OperateNo5:  //云台和摄像头方位设置
    {
        // m_QMainWgt->setCameraPanAzimuthParam(iParam0);
        // m_QZhouShiWgt->setCameraPanAzimuthParam(iParam0);
    }
    break;
    case Mainwidow_OperateNo6:  //云台和摄像头俯仰
    {
        // m_QMainWgt->setCameraPanPitchParam(iParam0);
        // m_QZhouShiWgt->setCameraPanPitchParam(iParam0);
    }
    break;
    case Mainwidow_OperateNo7:  //摇杆云台控制
    {
        m_qCameraPanComport->Infrared_ComparameterSetting(iParam0, iParam1, iParam2, 0);
    }
    break;
    case Mainwidow_OperateNo8:  //摇杆摄像头控制
    {
        // if (m_iCurrentWindowID == 1)
        // {
        //     m_qCameraComport->Infrared_ComparameterSetting(m_iCameraMainWgtDeviceAdd, iParam1,
        //                                                    iParam2, 0);
        // }
        // else if (m_iCurrentWindowID == 2)
        // {
        //     m_qCameraComport->Infrared_ComparameterSetting(m_iCameraZhouShiWgtDeviceAdd,
        //                                                    iParam1, iParam2, 0);
        // }
    }
    break;
    case Mainwidow_OperateNo9:  //可见光和红外切换
    {
        if (iParam0 == 1)
        {
            m_iCameraZhouShiWgtDeviceAdd = iParam1;  // 1:可见光 2：红外
        }
        else if (iParam0 == 2)
        {
            m_iCameraMainWgtDeviceAdd = iParam1;  // 1:可见光 2：红外
        }
    }
    break;
    case Mainwidow_OperateNo10:  //故障报文
    {
        // m_flag = m_beat;
        if (iParam0 != 0)//可见光故障
        {
            // m_QMainWgt->setState(0, iParam0);
        }
        else
        {
            // m_QMainWgt->setState(0, 0);
        }

        if(iParam1 != 0)//红外热像故障
        {
            // m_QMainWgt->setState(1, iParam1);
        }
        else
        {
            // m_QMainWgt->setState(1, 0);
        }
    }
    break;
    case Mainwidow_OperateNo11:
    {
        m_qCameraComport->Infrared_ComparameterSetting(iParam0, iParam1, 0, 0);

    }
    break;
    case Mainwidow_OperateNo12:
    {
        if(iParam0 == 1)
        {
            m_qJoyStickComport->JoystickUpdate();
        }
        else if(iParam0 == 2)
        {
            m_qJoyStickComport->JoystickReset();
        }
    }
    break;
    default:
        break;
    }
}

void MainWindow::SltRecvOperateNo()
{
    //do something
}

void MainWindow::SltOperateDelayTime()
{
    m_tmOperateDelayTime->stop();

    if (1 == m_iCameraDeviceNo)
    {
        m_qCameraPanComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
        m_qCameraComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
    }
    else
    {
        m_qCameraPanComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
        m_qCameraComport->Infrared_ComparameterSetting(m_iCameraDeviceNo, 0, 0, 0);
    }
}

void MainWindow::on_pushButtonU_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 1, m_iCameraPanSpeed);
}


void MainWindow::on_pushButtonU_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButtonD_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 2, m_iCameraPanSpeed);
}


void MainWindow::on_pushButtonD_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButtonL_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 3, m_iCameraPanSpeed);
}


void MainWindow::on_pushButtonL_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButtonR_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 4, m_iCameraPanSpeed);
}


void MainWindow::on_pushButtonR_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButton_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 5, m_iCameraPanSpeed);
}


void MainWindow::on_pushButton_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButton_2_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 6, m_iCameraPanSpeed);
}


void MainWindow::on_pushButton_2_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButton_4_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 7, m_iCameraPanSpeed);
}


void MainWindow::on_pushButton_4_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButton_3_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 8, m_iCameraPanSpeed);
}


void MainWindow::on_pushButton_3_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButton_6_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 9, m_iCameraPanSpeed);
}


void MainWindow::on_pushButton_6_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButton_5_pressed()
{
    emit signal_operateNo(1, CameraPan_device_number, 10, m_iCameraPanSpeed);
}


void MainWindow::on_pushButton_5_released()
{
    emit signal_operateNo(0, CameraPan_device_number, 0, 0);
}


void MainWindow::on_pushButton_7_clicked()
{
    emit signal_operateNo(1, CameraPan_device_number, 15, m_iCameraPanSpeed);
}


void MainWindow::on_pushButton_8_clicked()
{
    emit signal_operateNo(1, CameraPan_device_number, 16, m_iCameraPanSpeed);
}

