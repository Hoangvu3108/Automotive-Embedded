#ifndef __STD_TYPES_H__
#define __STD_TYPES_H__
#include "Compiler.h"
#include "Platform_Types.h"
#include <stdint.h>
typedef uint8_t Std_ReturnType;
int E_OK=1;
int E_NOT_OK=0;
typedef struct{
uint16_t vendorID;
uint16_t moduleID;
uint8_t instanceID;
uint8_t sw_major_version;
uint8_t sw_minor_version;
uint8_t sw_patch_version;
} Std_VersionInfoType;
#endif
