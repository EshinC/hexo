---
title: 完成之HC-05与STM32WIFI模块通信
date: 2018-07-27 20:26:13
tags: 
	- HC-05蓝牙模块
	- STM32
categories: 嵌入式开发
---

## 接上篇

继昨天未完成的HC-05与板载WIFI通信未完成后，今天终于搞定了！！！有点小激动 ~~

## 正文

毕竟是搞了两天的东西，容我兴奋一会儿；想做的东西是：图书馆座位管理系统，使用压感传感器和红外传感器检测座位是否有人，然后用蓝牙传给开发板，通过板载WIFI传到云端处理数据，通过微信小程序查看座位是否有人。

使用的东西有：压感和红外传感器、蓝牙模块、arduino nano作为连接传感器和蓝牙的开发板、秉火STM32f103x指南者的开发板，有板载WIFI。

自己买的蓝牙模块，然后用arduino nano写的一个主一个从模式两块蓝牙模块，一个接传感器，一个接STM32板，传输感应到位置是否有人；STM32板再写接收的蓝牙数据，通过板载WIFI传到电脑；整个过程大概就是这样。

本来想的是，有卖家提供的蓝牙接收数据的程序和WIFI透传发送到电脑数据的程序，直接合并就完事了，没想到在这里卡了两天时间。由于之前并没有接触过单片机，甚至51的也是一周之前刚学过三天皮毛，总感觉整个程序都是混乱的，没有头绪。出了问题以后发现，必须要重新把程序再过一遍，一个头文件一个头文件的过。

最终排查出在stm32f10x_it.c文件中缺少了蓝牙传输的函数BLT_USART_IRQHandler，添加进去就可以了。最后，上代码：

### stm32f10x.c

> #include "stm32f10x_it.h"
> #include "./systick/bsp_SysTick.h" 
> #include "./usart/bsp_usart_blt.h"
> #include "bsp_esp8266.h"
> #include "test.h"
>
>
> extern unsigned int Task_Delay[];
> extern void TimingDelay_Decrement(void);
> /** @addtogroup STM32F10x_StdPeriph_Template
>   * @{
>       */
>
> /* Private typedef -----------------------------------------------------------*/
> /* Private define ------------------------------------------------------------*/
> /* Private macro -------------------------------------------------------------*/
> /* Private variables ---------------------------------------------------------*/
> /* Private function prototypes -----------------------------------------------*/
> /* Private functions ---------------------------------------------------------*/
>
> /******************************************************************************/
> /*            Cortex-M3 Processor Exceptions Handlers                         */
> /******************************************************************************/
>
> /**
>   * @brief  This function handles NMI exception.
>   * @param  None
>   * @retval None
>       */
>       void NMI_Handler(void)
>       {
>       }
>
> /**
>   * @brief  This function handles Hard Fault exception.
>   * @param  None
>   * @retval None
>       */
>       void HardFault_Handler(void)
>       {
>         /* Go to infinite loop when Hard Fault exception occurs */
>         while (1)
>         {
>         }
>       }
>
> /**
>   * @brief  This function handles Memory Manage exception.
>   * @param  None
>   * @retval None
>       */
>       void MemManage_Handler(void)
>       {
>         /* Go to infinite loop when Memory Manage exception occurs */
>         while (1)
>         {
>         }
>       }
>
> /**
>   * @brief  This function handles Bus Fault exception.
>   * @param  None
>   * @retval None
>       */
>       void BusFault_Handler(void)
>       {
>         /* Go to infinite loop when Bus Fault exception occurs */
>         while (1)
>         {
>         }
>       }
>
> /**
>   * @brief  This function handles Usage Fault exception.
>   * @param  None
>   * @retval None
>       */
>       void UsageFault_Handler(void)
>       {
>         /* Go to infinite loop when Usage Fault exception occurs */
>         while (1)
>         {
>         }
>       }
>
> /**
>   * @brief  This function handles SVCall exception.
>   * @param  None
>   * @retval None
>       */
>       void SVC_Handler(void)
>       {
>       }
>
> /**
>   * @brief  This function handles Debug Monitor exception.
>   * @param  None
>   * @retval None
>       */
>       void DebugMon_Handler(void)
>       {
>       }
>
> /**
>   * @brief  This function handles PendSVC exception.
>   * @param  None
>   * @retval None
>       */
>       void PendSV_Handler(void)
>       {
>       }
>
> /**
>   * @brief  This function handles SysTick Handler.
>   * @param  None
>   * @retval None
>       */
>       void SysTick_Handler(void)
>       {
>       unsigned char i;
>
>       TimingDelay_Decrement();  
>       TimeStamp_Increment(); 
>
>       for(i=0;i<NumOfTask;i++)
>       {
>       	if(Task_Delay[i])
>       	{
>       		Task_Delay[i]--;
>       	}
>       }
>       }
>
> /******************************************************************************/
> /*                 STM32F10x Peripherals Interrupt Handlers                   */
> /*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
> /*  available peripheral interrupt handler's name please refer to the startup */
> /*  file (startup_stm32f10x_xx.s).                                            */
> /******************************************************************************/
> /**
>   * @brief  This function handles macESP8266_USARTx Handler.
>   * @param  None
>   * @retval None
>       */
>       void macESP8266_USART_INT_FUN ( void )
>       	
>       uint8_t ucCh;
>
>       if ( USART_GetITStatus ( macESP8266_USARTx, USART_IT_RXNE ) != RESET )
>       {
>       	ucCh  = USART_ReceiveData( macESP8266_USARTx );
>       	
>       	if ( strEsp8266_Fram_Record .InfBit .FramLength < ( RX_BUF_MAX_LEN - 1 ) )                       //预留1个字节写结束符
>       		strEsp8266_Fram_Record .Data_RX_BUF [ strEsp8266_Fram_Record .InfBit .FramLength ++ ]  = ucCh;
>
>       }
>        	 
>       if ( USART_GetITStatus( macESP8266_USARTx, USART_IT_IDLE ) == SET )                                         //数据帧接收完毕
>       {
>     strEsp8266_Fram_Record .InfBit .FramFinishFlag = 1;
>     	
>     	ucCh = USART_ReceiveData( macESP8266_USARTx );                                                              //由软件序列清除中断标志位(先读USART_SR，然后读USART_DR)
>     
>     	ucTcpClosedFlag = strstr ( strEsp8266_Fram_Record .Data_RX_BUF, "CLOSED\r\n" ) ? 1 : 0;
>
>   }	
>
> }
> /**
>   * @brief  This function handles PPP interrupt request.
>   * @param  None
>   * @retval None
>       */
>       /*void PPP_IRQHandler(void)
>       {
>       }*/
>
> void BLT_USART_IRQHandler(void)
> {
>     bsp_USART_Process();
>
> }
>
> /**
>   * @}
>       */ 
>
>
> /******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/

### main

> #include "stm32f10x.h"
> #include "./usart/bsp_usart.h"
> #include "./usart/bsp_usart_blt.h"
> #include "./SysTick/bsp_SysTick.h"
> #include "./hc05/bsp_hc05.h"
> #include "bsp_esp8266.h"
> #include "test.h"
> #include "bsp_led.h"
> #include <string.h>
> #include <stdlib.h>
>
>
> unsigned int Task_Delay[3]; 
>
>
> BLTDev bltDevList;
>
> 
>
>
> char sendData[1024];
> char linebuff[1024];
>
> int main(void)
> {
> 	 char* redata;
> 		char cStr [ 100 ] = { 0 };
> 	uint16_t len;
> 	static uint8_t hc05_role=1;
> 	unsigned long count;
> 	
> 	char hc05_mode[10]="SLAVE";
> 	char hc05_name[30]="HC05_SLAVE";
> 	char hc05_nameCMD[40];
> 	char str[20];
> 	
> 	  //初始化systick
> 	SysTick_Init();
> 	SysTick->CTRL|=SysTick_CTRL_ENABLE_Msk;
> 	
> 	USART_Config();
> 	
> 	ESP8266_Init (); 
> 	HC05_INFO("**********HC05模块实验************");
> 	
> 	if(HC05_Init() == 0)
> 		HC05_INFO("HC05模块检测正常。");
> 	else
> 	{
> 		HC05_ERROR("HC05模块检测不正常，请检查模块与开发板的连接，然后复位开发板重新测试。");
> 		while(1);
> 	}
>
>
> 	/*复位、恢复默认状态*/
> 	HC05_Send_CMD("AT+RESET\r\n",1);	
> 	delay_ms(800);
> 	
> 	HC05_Send_CMD("AT+ORGL\r\n",1);
> 	delay_ms(200);
>
>
> ​	
> 	/*各种命令测试演示，默认不显示。
> 	 *在bsp_hc05.h文件把HC05_DEBUG_ON 宏设置为1，
> 	 *即可通过串口调试助手接收调试信息*/	
> 	
> 	HC05_Send_CMD("AT+VERSION?\r\n",1);
> 	
> 	HC05_Send_CMD("AT+ADDR?\r\n",1);
> 	
> 	HC05_Send_CMD("AT+UART?\r\n",1);
> 	
> 	HC05_Send_CMD("AT+CMODE?\r\n",1);
> 	
> 	HC05_Send_CMD("AT+STATE?\r\n",1);	
> 	
> 	HC05_Send_CMD("AT+ROLE=1\r\n",1);
> 	
> 	/*初始化SPP规范*/
> 	HC05_Send_CMD("AT+INIT\r\n",1);
> 	HC05_Send_CMD("AT+CLASS=0\r\n",1);
> 	HC05_Send_CMD("AT+INQM=1,9,48\r\n",1);
> 	
> 	/*设置模块名字*/
> 	//sprintf(hc05_nameCMD,"AT+NAME=%s\r\n",hc05_name);
> 	//HC05_Send_CMD(hc05_nameCMD,1);
> 	
> 	HC05_INFO("本模块名字为:%s ,模块已准备就绪。",hc05_name);
> 	
> 	while(1)
> 	{
> 	
> 		//搜索蓝牙模块，并进行连接
> 		if(Task_Delay[2]==0 && !IS_HC05_CONNECTED()) 
> 		{
> 			if(hc05_role == 1)	//主模式 AT+STATE?
> 			{
> 				HC05_INFO("正在扫描蓝牙设备...");
> 				linkHC05();
> 				Task_Delay[2]=3000; //此值每1ms会减1，减到0才可以重新进来这里，所以执行的周期是3s
> 			}
> 		}				
> 		
> 			//连接后每隔一段时间检查接收缓冲区
> 		if(Task_Delay[0]==0 && IS_HC05_CONNECTED())  
> 		{
> 				uint16_t linelen;
> 	
> 				/*获取数据*/
> 				redata = get_rebuff(&len); 
> 				linelen = get_line(linebuff,redata,len);
> 			
> 				/*检查数据是否有更新*/
> 				if(linelen<200 && linelen != 0)
> 				{
> 					 
> 					sprintf ( cStr,redata);
> 		
> 					ESP8266_SendString ( ENABLE, cStr, 0, Single_ID_0 );               //发送数据
> 					
> 					delay_ms ( 100 );
> 						//HC05_INFO("receive:\r\n%s",redata);
> 					/*处理数据后，清空接收蓝牙模块数据的缓冲区*/
> 					clean_rebuff();
> 					
> 				}
> 			Task_Delay[0]=500;//此值每1ms会减1，减到0才可以重新进来这里，所以执行的周期是500ms
> 		}
> 	}
> 	
> 	/*ESP8266_Init ();                                                               //初始化WiFi模块使用的接口和外设
>
>
> ​	
> 	printf ( "\r\n野火 WF-ESP8266 WiFi模块测试例程\r\n" );                          //打印测试例程提示信息
>
> ​	
>   ESP8266_StaTcpClient_UnvarnishTest ();
> 	
> ​	
>   while ( 1 );*/
> 	
> }

这应该是最重要的两个最有坑的两个；整个源代码放到Github上吧，右上角小八爪猫；