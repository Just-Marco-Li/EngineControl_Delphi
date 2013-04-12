//=============================================================================
// include files
//=============================================================================
#include "hal_os.h"
#include "HLS.h"
#include "hal_diag.h"

extern void Update_DiagStatus_10ms(void);

//=============================================================================
// HAL_OS_1ms_Task
//=============================================================================
  void  HAL_OS_1ms_Task(void) 
 {
     HLS_Task_1ms();
 }

//=============================================================================
// HAL_OS_1ms_Task
//=============================================================================
  void  HAL_OS_5ms_Task(void) 
 {
     HLS_Task_5ms();
 }
//=============================================================================
//  HAL_OS_10ms_Task
//=============================================================================
uint16_t OS_10ms_Cnt;
void  HAL_OS_10ms_Task(void) 
 {
     OS_10ms_Cnt++;
     HLS_Task_10ms();
   if(OS_10ms_Cnt ==5)
   {
        HLS_Task_50ms();
      OS_10ms_Cnt = 0;
   }
   
   if(OS_10ms_Cnt&1)
   {
    HLS_Task_20ms();
   }
   Update_DiagStatus_10ms();
 }

//=============================================================================
//  HAL_OS_100ms_Task
//=============================================================================
uint16_t OS_100ms_Cnt;
  void  HAL_OS_100ms_Task(void)
{

   OS_100ms_Cnt++;
   HLS_Task_100ms();
   if(OS_100ms_Cnt ==10)
   {
        HLS_Task_1000ms();
      OS_100ms_Cnt = 0;
   }
   
   if(!(OS_100ms_Cnt&&0x01))
   {
    HLS_Task_200ms();
   }

}

//=============================================================================
//  App_Init_Task
//=============================================================================
  void HAL_OS_Init_Task(void)
  {
    HLS_ini();
  }


//=============================================================================
//  HAL_OS_SYN_Task
//=============================================================================
 void HAL_OS_SYN_Task(void)
 {
     HLS_syn();
 }




