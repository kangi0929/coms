#include "Comport.h"

#include <stdio.h>
#include <stdlib.h>

QComport::QComport()
{

}
//###########################################################
/**
 * open_uart
 * 打开串口设备，返回打开的句柄
 * */
int QComport::open_uart(const char* name)
{
    int fd;

    fd = open(name, O_RDWR | O_NOCTTY | O_NDELAY);

    if(fd < 0)
    {
        return -1;
    }


//    //是否为阻塞状态
//    if(fcntl(fd, F_SETFL,FNDELAY) < 0)
//    {
//        return -1;
//    }
//    //是否为终端设备
//    if(0 == isatty(STDIN_FILENO))
//    {
//        return -1;
//    }

    return fd;
}

//###########################################################
/**
 * set_uart_speed
 * 设置串口的速率
 * @fd:		已经打开串口的文件描述符
 * @speed:	输入的速率参数
 * 返回值:	成功返回0，失败返回-1，只有在速率参数不正确的情况下才会失败
 * */
int QComport::set_uart_speed(int fd, int speed)
{
        speed_t real_speed;
        struct termios options;

        tcgetattr(fd, &options);
        switch(speed)
        {
        case 1200:
                real_speed	= B1200;
                break;
        case 2400:
                real_speed	= B2400;
                break;
        case 4800:
                real_speed	= B4800;
                break;
        case 9600:
                real_speed	=  B9600;
                break;
        case 19200:
                real_speed	=  B19200;
                break;
        case 38400:
                real_speed	=  B38400;
                break;
        case 115200:
                real_speed	=  B115200;
                break;
        case 230400:
                real_speed      =  B230400;
                break;
        case 460800:
                real_speed      =  B460800;
                break;
        case 576000:
                real_speed      =  B576000;
                break;
        case 921600:
                real_speed     =   B921600;
                break;
        case 1152000:
                real_speed     =   B1152000;
                break;
        default:
                return -1;
        }

        cfsetispeed(&options,real_speed);
        cfsetospeed(&options,real_speed);
        tcsetattr(fd, TCSANOW, &options);

        return 0;
}

//###########################################################
/**
 * set_uart_bits
 * 设置串口的数据位和停止位
 * @fd:		        已经打开串口的描述符
 * @data_bits:		数据位个数，取值为5/6/7/8
 * @stop_bits:		停止位个数，取值位1/2
 * */
int QComport::set_uart_bits(int fd, char data_bits, char stop_bits)
{
        struct termios options;

        tcgetattr(fd, &options);
        options.c_cflag	&= ~CSIZE;

        switch(data_bits)
        {
        case 5:
                options.c_cflag	|= CS5;
                break;
        case 6:
                options.c_cflag	|= CS6;
                break;
        case 7:
                options.c_cflag	|= CS7;
                break;
        case 8:
                options.c_cflag	|= CS8;
                break;
        default:
                return -1;
        }
        switch(stop_bits)
        {
        case 1:
                options.c_cflag	&= ~CSTOPB;
                break;
        case 2:
                options.c_cflag	|= CSTOPB;
                break;
        default:
                return -1;
        }

        options.c_iflag	    = 0;
        options.c_lflag    &= ~(ICANON | ECHO | ECHOE | ISIG); /*Input*/
        options.c_oflag    &= ~OPOST;

        options.c_cc[VTIME]  =  0;
        options.c_cc[VMIN]   =  0;

        tcflush(fd,TCIFLUSH);
        tcflush(fd,TCOFLUSH);
        tcsetattr(fd, TCSANOW, &options);

        return 0;
    }

//###########################################################
/**
 * set_uart_parity
 * 设置串口的校验
 * @fd:			已打开串口的描述符
 * @parity:		校验类型'n'/'o'/'e' 无/奇/偶
 * */
int QComport::set_uart_parity(int fd, char parity)
{
    struct termios options;

    tcgetattr(fd, &options);
    switch(parity)
    {
    case 'n':
    case 'N':
        options.c_cflag	&= ~PARENB;
        options.c_iflag	&= ~INPCK;
        break;
    case 'o':
    case 'O':
        options.c_cflag	 |= (PARODD|PARENB);
        options.c_iflag  |= INPCK;
        break;
    case 'e':
    case 'E':
        options.c_cflag	|= PARENB;
        options.c_cflag	&= ~PARODD;
        options.c_iflag	|= INPCK;
        break;
    default:
        return -1;;
    }

    options.c_lflag         &= ~(ICANON | ECHO | ECHOE | ISIG);           /*Input*/
    options.c_oflag         &= ~OPOST;

    options.c_cc[VTIME]     = 0;
    options.c_cc[VMIN]      = 0;


    tcflush(fd,TCIFLUSH);
    tcflush(fd,TCOFLUSH);
    tcsetattr(fd, TCSANOW, &options);

    return 0;
}

//###########################################################
/**
 * open_uart_full
 * linux下打开串口的工具函数,打开串口，并且将打开的串口配置好
 * @name:			要打开的串口的名字
 * @speed:			串口速率
 * @data_bits:		数据位个数,5/6/7/8
 * @stop_bits:		串口的停止位个数，取值为1/2
 * @parity:			校验类型，'n'为无校验，'o'为奇校验，'e'为偶校验
 * 返回值:			正常打开，返回打开后的描述符；打开失败，返回-1
 * */
int QComport::open_uart_full(const char* name,
                             int  speed,
                             char data_bits,
                             char stop_bits,
                             char parity)
{
        int fd;
        fd = open_uart(name);
        if(fd < 0)
        {
                return -1;
        }
        if(set_uart_speed(fd,speed) < 0)
        {
                close(fd);
                return -1;
        }
        if(set_uart_bits(fd,data_bits,stop_bits) < 0)
        {
                close(fd);
                return -1;
        }
        if(set_uart_parity(fd,parity) < 0)
        {
                return -1;
        }

        return fd;
}



/*******************************************************************
* 名称:
* 功能: 接收串口数据
* 入口参数: * fd:文件描述符
*                    rcv_buf :接收串口中数据存入rcv_buf缓冲区中
*                    data_len :一帧数据的长度
* 出口参数: 正确返回为1,错误返回为0
*******************************************************************/
int QComport::recv_uart(int fd, char *rcv_buf,int data_len)
{
    int len,fs_sel;
    fd_set fs_read;

    struct timeval time;

    FD_ZERO(&fs_read);
    FD_SET(fd,&fs_read);

    time.tv_sec = 0;
    time.tv_usec = 1000;

    //使用select实现串口的多路通信
    fs_sel = select(fd+1,&fs_read,NULL,NULL,&time);

    if(fs_sel)
    {
        len =  read(fd,rcv_buf,data_len);
    }
    else
    {
        return false;
    }
    return len;
}

