#ifndef QCOMPORT_H
#define QCOMPORT_H
//串口相关的头文件
#include<stdio.h> /*标准输入输出定义*/
#include<stdlib.h> /*标准函数库定义*/
#include<unistd.h> /*Unix 标准函数定义*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>                             /*文件控制定义*/
#include<termios.h>
#include<errno.h>
#include<string.h>

class QComport
{
public:
    QComport();

    int open_uart      (const char* name);                         //打开串口
    int set_uart_speed (int fd, int speed);                        //设置波特率
    int set_uart_bits  (int fd, char data_bits, char stop_bits);   //设置数据位
    int set_uart_parity(int fd, char parity);                     //设置校验

    //打开串口
    int open_uart_full(const char* name,                            //串口名
                       int         speed,                           //波特率
                       char        data_bits,                       //数据位
                       char        stop_bits,                       //停止位
                       char        parity                           //波特率
                       );

    int recv_uart(int fd, char *rcv_buf,int data_len);              //串口接收
};

#endif // QCOMPORT_H
