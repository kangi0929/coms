#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTimer>
#include <InfraredComport.h>
#include <JoyStickComport.h>
#include <globalvar.h>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QTimer *m_tmOperateDelayTime;
    qint32 m_iCameraDeviceNo;
    qint32 m_iCameraMainWgtDeviceAdd;          // 1:可见光 2：红外
    qint32 m_iCameraZhouShiWgtDeviceAdd;       // 1:可见光 2：红外
    QInfraredComport *m_qCameraPanComport;  //云台
    QInfraredComport *m_qCameraComport;     //摄像头
    QJoyStickComport *m_qJoyStickComport;   //摇杆

    qint32 m_iCameraPanSpeed;
    qint32 m_iCameraSpeed;

signals:
    void signal_operateNo(int iOperateNo, int iParam0, int iParam1, int iParam2);

private slots:
    void SltRecvOperateNo();
    void SltOperateDelayTime();  //云台和摄像头调焦等操作，添加延时发送停止操作指令
    void SltRecvOperateNo(int iOperateNo, int iParam0, int iParam1, int iParam2);
    void on_pushButtonU_pressed();
    void on_pushButtonU_released();
    void on_pushButtonD_pressed();
    void on_pushButtonD_released();
    void on_pushButtonL_pressed();
    void on_pushButtonL_released();
    void on_pushButtonR_pressed();
    void on_pushButtonR_released();
    void on_pushButton_pressed();
    void on_pushButton_released();
    void on_pushButton_2_pressed();
    void on_pushButton_2_released();
    void on_pushButton_4_pressed();
    void on_pushButton_4_released();
    void on_pushButton_3_pressed();
    void on_pushButton_3_released();
    void on_pushButton_6_pressed();
    void on_pushButton_6_released();
    void on_pushButton_5_pressed();
    void on_pushButton_5_released();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
};
#endif // MAINWINDOW_H
