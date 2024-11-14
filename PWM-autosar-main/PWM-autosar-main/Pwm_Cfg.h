#ifndef __PWM_CFG_H__
#define __PWM_CFG_H__
#include <stdint.h>
#define STD_ON 1
#define STD_OFF 0
#define PwmDevErrorDetect STD_ON
#define PwmDutycycleUpdatedEndperiod STD_ON
#define PwmIndex 0
#define PwmLowPowerStatesSupport STD_ON
#define PwmNotificationSupported STD_ON
#define PwmPowerStateAsynchTransitionMode STD_ON
#define PwmDutycycleDefaultMax 0x8000
#define PwmDutycycleDefaultMin 0x00
typedef uint8_t PwmIdleState ;
#define PWM_HIGH ((PwmIdleState)0xff)
#define PWM_LOW ((PwmIdleState)0x00)
#define PwmNotification STD_ON
/*typedef uint8_t PwmPolarity;
#define PWM_HIGH ((PwmPolarity)0xff)
#define PWM_LOW  ((PwmPolarity)0x00)*/
#define PwmDeInitApi STD_ON
#define PwmGetOutputState STD_ON
#define PwmSetDutyCycle STD_ON
#define PwmSetOutputToIdle STD_ON
#define PwmSetPeriodAndDuty STD_ON
#define PwmVersionInfoApi STD_ON
#endif
