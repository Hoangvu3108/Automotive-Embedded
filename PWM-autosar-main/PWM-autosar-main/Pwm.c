#include "Pwm.h"
#include "Pwm_MemMap.h"
#include "Det.h"
#include "Dem.h"
#include "SchM_Pwm.h"
#ifdef PWM0 ((volatile int) 0x40028000)
  #define PWMENABLE (*((volatile uinsigned int*)(PWM0+0x008)))
  #define PWM0EN ((PWMENABLE)0X1)
  #define PWM1EN ((PWMENABLE)0X2)
  #define PWM2EN ((PWMENABLE)0X4)
  #define PWM3EN ((PWMENABLE)0X10)
  #define PWM4EN ((PWMENABLE)0X20)
  #define PWM5EN ((PWMENABLE)0X40)
  #define PWM6EN ((PWMENABLE)0X80)
  #define PWM7EN ((PWMENABLE)0X100)
#endif // PWM0
#ifdef PWM1 ((volatile int) 0x40029000)
  #define PWMENABLE (*((volatile uinsigned int*)(PWM1+0x008)))
  #define PWM0EN ((PWMENABLE)0X1)
  #define PWM1EN ((PWMENABLE)0X2)
  #define PWM2EN ((PWMENABLE)0X4)
  #define PWM3EN ((PWMENABLE)0X10)
  #define PWM4EN ((PWMENABLE)0X20)
  #define PWM5EN ((PWMENABLE)0X40)
  #define PWM6EN ((PWMENABLE)0X80)
  #define PWM7EN ((PWMENABLE)0X100)
#endif // PWM1
#define E_OK 0x01
#define E_NOT_OK 0X00
#define
#if(PwmNotificationSupported==STD_ON)
void Pwm_EnableNotification(Pwm_ChannelType ChannelNumber,Pwm_EdgeNotificationType Notification){
    __enable_irq();
    __disable_irq();

}
#endif
#if(PwmNotificationSupported==STD_ON)
void Pwm_DisableNotification(Pwm_ChannelType ChannelNumber)
    __enable_irq();
    __disable_irq();

}
#endif
#if(PwmGetOutputState==STD_ON)
Pwm_OutputStateType Pwm_GetOutputState(Pwm_ChannelType ChannelNumber){
   int state;
   __enable_irq();
   __disable_irq();
   if(ChannelNumber==1)
    state=PWM_HIGH;
   else
    state=PWM_LOW;
   return state;
}
#endif
Std_ReturnType Pwm_SetPowerState(Pwm_PowerStateRequestResultType* Result){
    int state;
    if((*Result).PWM_SERVICE_ACCEPTED)
        state=E_OK;
    else
        state=E_NOT_OK;
    return state;
}
