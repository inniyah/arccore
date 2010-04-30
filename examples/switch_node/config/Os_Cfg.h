/* 
* Configuration of module Os (Os_Cfg.h)
* 
* Created by: ArcCore AB
* Configured for (MCU): MPC551x
* 
* Module editor vendor:  ArcCore
* Module editor version: 2.0.7
* 
* Copyright ArcCore AB 2010
* Generated by Arctic Studio (http://arccore.com)
*           on Fri Apr 30 15:54:06 CEST 2010
*/


#if (OS_SW_MAJOR_VERSION != 2) 
#error "Os: Configuration file version differs from BSW version."
#endif


#ifndef OS_CFG_H_
#define OS_CFG_H_


// Alarm Id's
#define ALARM_ID_ComAlarm	0
#define ALARM_ID_ReadSwAlarm	1

// Counter Id's
#define COUNTER_ID_OsTick	0

// Counter macros
#define OSMAXALLOWEDVALUE_OsTick 65535


// Event masks

// Isr Id's

// Resource Id's

// Linked resource id's

// Resource masks

// Task Id's
#define TASK_ID_OsIdle	0
#define TASK_ID_ComTask	1
#define TASK_ID_ReadSwitches	2
#define TASK_ID_StartupTask	3

// Task entry points
void OsIdle( void );
void ComTask( void );
void ReadSwitches( void );
void StartupTask( void );

// Schedule table id's

// Stack size
#define OS_INTERRUPT_STACK_SIZE	2048
#define OS_OSIDLE_STACK_SIZE 512

#define OS_ALARM_CNT			2 
#define OS_TASK_CNT				4
#define OS_SCHTBL_CNT			0
#define OS_COUNTER_CNT			1
#define OS_EVENTS_CNT			0
#define OS_ISRS_CNT				0
#define OS_RESOURCE_CNT			0
#define OS_LINKED_RESOURCE_CNT	0

#define CFG_OS_DEBUG				STD_ON

#define OS_SC1 						STD_ON     
#define OS_STACK_MONITORING			STD_ON
#define OS_STATUS_EXTENDED			STD_ON
#define OS_USE_GET_SERVICE_ID		STD_ON
#define OS_USE_PARAMETER_ACCESS		STD_ON
#define OS_RES_SCHEDULER			STD_ON

#endif /*OS_CFG_H_*/
