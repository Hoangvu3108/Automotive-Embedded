#include "Pwm.h"
#include "Pwm_MemMap.h"
PwmChannel PwmChannelcofig[]=
{
    {
        PWM_VARIABLE_PERIOD,
        0x800,
        PWM_HIGH,
        NULL,
        100,
        PWM_HIGH,
        100,
    }

};
