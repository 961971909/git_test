/*! @file
********************************************************************************
<PRE>
模块名       : 调度器内核函数
文件名       : SCH.c
相关文件     :
文件实现功能 : 任务调度
作者         : <l、>
版本         : 1.0
--------------------------------------------------------------------------------
备注         : 电流表
--------------------------------------------------------------------------------
修改记录 :
日 期        版本   修改人         修改内容
2017/03/22   1.0    <l、>           创建
</PRE>
********************************************************************************

  * 版权所有(c) YYYY, <xxx>, 保留所有权利

*******************************************************************************/

/* Includes ------------------------------------------------------------------*/
#include "Include.h"

/*----------------------------------------------------------------------------*/

sTask SCH_tasks_G[SCH_MAX_TASKS];   //任务调度器数组

void SCH_Init_T(void)
{
	u8 i;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;

	for (i = 0; i < SCH_MAX_TASKS; i++)
    {
        SCH_Delete_Task(i);				//删除不必要的任务
    }
	TIM_DeInit(TIM3);
	TIM_TimeBaseStructure.TIM_Period = 3999;       //定时器值
	TIM_TimeBaseStructure.TIM_Prescaler = 11;       //时钟分频数 定时1ms
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;    //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
}

void Modebus_Init_T(void)
{
	TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;

	TIM_DeInit(TIM2);
	TIM_TimeBaseStructure.TIM_Period = 11999;       //定时器值
	TIM_TimeBaseStructure.TIM_Prescaler = 11;       //时钟分频数 定时2ms
	TIM_TimeBaseStructure.TIM_ClockDivision = 0;    //
	TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

	TIM_Cmd(TIM2, ENABLE);
    TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);
    
}

void SCH_Start(void)
{
	/* TIM enable counter */
	TIM_Cmd(TIM3, ENABLE);

	/* TIM IT enable */
	TIM_ITConfig(TIM3, TIM_IT_Update, ENABLE);
}

u16 g_IWDGCount = 0; //喂狗计数
void SIGNAL_IRQHandler(void)
{
    u8 Index;
	if (TIM_GetITStatus(TIM3, TIM_IT_Update) != RESET)
	{
		for ( Index = 0;  Index < SCH_MAX_TASKS;  Index++ )
		{
			if (SCH_tasks_G[Index].pTask)
			{
				if (SCH_tasks_G[Index].Delay == 0)
				{
					SCH_tasks_G[Index].RunMe += 1;

					if (SCH_tasks_G[Index].Period)
					{
						SCH_tasks_G[Index].Delay = SCH_tasks_G[Index].Period;
					}
				}
				else
				{
					SCH_tasks_G[Index].Delay -= 1;
				}
			}
		}

		TIM_ClearITPendingBit(TIM3, TIM_IT_Update );
		g_IWDGCount++;
		if (g_IWDGCount>=120)
		{
			//IWDG_ReloadCounter(); //手动喂狗
			g_IWDGCount = 0;
		}
	}
}

void Modbus_IRQHandler(void)
{
    vMSRS232_RxProtocol();
    TIM_ClearFlag(TIM2,TIM_FLAG_Update);
}

void SCH_RUN_Tasks(void)  //任务执行
 {
   u8 Index;

   for (Index = 0; Index < SCH_MAX_TASKS; Index++)
   {
      if (SCH_tasks_G[Index].RunMe > 0)
      {
         (*SCH_tasks_G[Index].pTask)();

         SCH_tasks_G[Index].RunMe -= 1;

         if (SCH_tasks_G[Index].Period == 0)
         {
            SCH_Delete_Task(Index);
         }
      }
   }
}

u8 SCH_Add_Task(void (*pFunction)(void),  //增??
                    u16 DELAY,
                    u16 PERIOD)
{
   u8 Index = 0;

   while ((SCH_tasks_G[Index].pTask != 0) && (Index < SCH_MAX_TASKS))
   {
      Index++;
   }

   if (Index == SCH_MAX_TASKS)
   {
      return SCH_MAX_TASKS;
    }

   SCH_tasks_G[Index].pTask  = pFunction;
   SCH_tasks_G[Index].Delay  = DELAY;
   SCH_tasks_G[Index].Period = PERIOD;
   SCH_tasks_G[Index].RunMe  = 0;

   return Index;
}

u8 SCH_Delete_Task( u8 TASK_INDEX)        //删除
{
   SCH_tasks_G[TASK_INDEX].pTask   = 0x0000;
   SCH_tasks_G[TASK_INDEX].Delay   = 0;
   SCH_tasks_G[TASK_INDEX].Period  = 0;
   SCH_tasks_G[TASK_INDEX].RunMe   = 0;

   return 0;
}

