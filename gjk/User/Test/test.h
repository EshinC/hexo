#ifndef  __TEST_H
#define	 __TEST_H



#include "stm32f10x.h"



/********************************** �û���Ҫ���õĲ���**********************************/
#define      macUser_ESP8266_ApSsid                       "jjj"                //Ҫ���ӵ��ȵ������
#define      macUser_ESP8266_ApPwd                        "jh112358"           //Ҫ���ӵ��ȵ����Կ

#define      macUser_ESP8266_TcpServer_IP                 "192.168.8.101"      //Ҫ���ӵķ������� IP
#define      macUser_ESP8266_TcpServer_Port               "8080"               //Ҫ���ӵķ������Ķ˿�



/********************************** �ⲿȫ�ֱ��� ***************************************/
extern volatile uint8_t ucTcpClosedFlag;



/********************************** ���Ժ������� ***************************************/
void ESP8266_StaTcpClient_UnvarnishTest (char a[50]);



#endif
