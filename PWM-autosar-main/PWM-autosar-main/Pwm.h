#ifndef __PWM_H__
#define __PWM_H__
#include "Pwm_Cfg.h"
#include "Std_Types.h"
#include <stdint.h>
/*************************************************************************************************************/
//Service           :SWS_Pwm_00106
//Name              :Pwm_PeriodType
//Type              :uint
//Description       :Numeric identifier of a PWM channel.
typedef uint32_t Pwm_ChannelType;
/*************************************************************************************************************/
//Service           :SWS_Pwm_00107
//Name              :Pwm_ChannelType
//Type              :uint
//Description       :Definition of the period of a PWM channel.
typedef uint32_t Pwm_PeriodType;
/*************************************************************************************************************/
//Service           :SWS_Pwm_00107
//Name              :Pwm_ChannelType
//Type              :uint
//Description       :Definition of the period of a PWM channel.
typedef uint8_t Pwm_OutputStateType;
#define PWM_HIGH                   ((Pwm_OutputStateType)0x01)
#define PWM_LOW                    ((Pwm_OutputStateType)0x00))
/*************************************************************************************************************/
//Service           :SWS_Pwm_00107
//Name              :Pwm_ChannelType
//Type              :uint
//Description       :Definition of the period of a PWM channel.
typedef uint8_t Pwm_EdgeNotificationType;
#define PWM_RISING_EDGE            ((Pwm_EdgeNotificationType)0x01)
#define PWM_FALLING_EDGE           ((Pwm_EdgeNotificationType)0x00)
#define PWM_BOTH_EDGES             ((Pwm_EdgeNotificationType)0x02)
/*************************************************************************************************************/
//Service           :SWS_Pwm_00107
//Name              :Pwm_ChannelType
//Type              :uint
//Description       :Definition of the period of a PWM channel.
typedef uint8_t Pwm_ChannelClassType;
#define PWM_VARIABLE_PERIOD         ((Pwm_ChannelClassType)0x01)
#define PWM_FIXED_PERIOD            ((Pwm_ChannelClassType)0x02)
#define PWM_FIXED_PERIOD_SHIFTED    ((Pwm_ChannelClassType)0x03)
/*************************************************************************************************************/
//Service           :SWS_Pwm_00106
//Name              :Pwm_ChannelType
//Type              :uint
//Description       :Definition of the period of a PWM channel.
typedef int PwmPolarity;
#define PWM_HIGH ((PwmPolarity)0x01);
#define PWM_LOW ((PwmPolarity)0x00);
typedef struct{
   int index;
   uint32_t PwmChannelId;
   Pwm_OutputStateType StateType ;
   int PwmNotification=NULL;
   int PwmPeriodDefault;
   PwmPolarity Polarity;
   int PwmSetPeriodAndDuty;
   Pwm_ChannelClassType ChannelClassType;
   uint64_t PwmDutycycleDefault;
   int PwmPowerState;
}Pwm_ConfigType;
/*************************************************************************************************************/
//Service           :SWS_Pwm_00107
//Name              :Pwm_ChannelType
//Type              :uint
//Description       :Definition of the period of a PWM channel.
typedef uint8_t Pwm_PowerStateRequestResultType;
#define PWM_SERVICE_ACCEPTED       ((Pwm_PowerStateRequestResultType)0x01)
#define PWM_NOT_INIT               ((Pwm_PowerStateRequestResultType)0x00)
#define PWM_SEQUENCE_ERROR         ((Pwm_PowerStateRequestResultType)0x02)
#define PWM_HW_FAILURE             ((Pwm_PowerStateRequestResultType)0x03)
#define PWM_POWER_STATE_NOT_SUPP   ((Pwm_PowerStateRequestResultType)0x04)
#define PWM_TRANS_NOT_POSSIBLE     ((Pwm_PowerStateRequestResultType)0x05)
/*************************************************************************************************************/
//Service           :SWS_Pwm_00107
//Name              :Pwm_ChannelType
//Type              :uint
//Description       :Definition of the period of a PWM channel.
typedef uint8_t Pwm_PowerStateType;
#define PWM_FULL_POWER             ((Pwm_PowerStateType)0xff)
#define POWER                      ((Pwm_PowerStateType)0x01)
/*************************************************************************************************************/
typedef uint8_t PWM_IDLE_STATE;
#define PWM_HIGH                  ((PWM_IDLE_STATE)0xff)
#define PWM_LOW                   ((PWM_IDLE_STATE)0x00)
/*************************************************************************************************************/
typedef uint8_t  McuClockReferencePoin;
typedef struct{
    Pwm_ChannelClassType Pwm_Channel;
    uint8_t PWM_DUTYCYLE_DEFAULT;
    PWM_IDLE_STATE PWM_IDLE;
    uint8_t Pwm_Notification;
    uint8_t PWM_PERIOD_DEFAULT;
    McuClockReferencePoint PwmMcuClockReferencePoint;
    PwmPolarity Polarity;
}PwmChannel;
#endif
