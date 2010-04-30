/* 
* Configuration of module Os (Os_Cfg.c)
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

	

#include <stdlib.h>
#include <stdint.h>
#include "Platform_Types.h"
#include "Os.h"				// includes Os_Cfg.h
#include "os_config_macros.h"
#include "kernel.h"
#include "kernel_offset.h"
#include "alist_i.h"
#include "Mcu.h"

extern void dec_exception( void );

// Set the os tick frequency
OsTickType OsTickFreq = 1000;


// ###############################    DEBUG OUTPUT     #############################
uint32 os_dbg_mask = D_RESOURCE |D_SCHTBL |D_EVENT |D_TASK |D_ALARM;
 


// #################################    COUNTERS     ###############################
GEN_COUNTER_HEAD {
	GEN_COUNTER(	COUNTER_ID_OsTick,
					"OsTick",
					COUNTER_TYPE_HARD,
					COUNTER_UNIT_NANO,
					0xffff,
					1,
					1,
					0),
};

CounterType Os_Arc_OsTickCounter = COUNTER_ID_OsTick;

// ##################################    ALARMS     ################################
GEN_ALARM_AUTOSTART(ALARM_ID_ComAlarm, ALARM_AUTOSTART_ABSOLUTE, 5, 20, OSDEFAULTAPPMODE );
	
GEN_ALARM_AUTOSTART(ALARM_ID_ReadSwAlarm, ALARM_AUTOSTART_ABSOLUTE, 10, 30, OSDEFAULTAPPMODE );
	

GEN_ALARM_HEAD {
	GEN_ALARM(	ALARM_ID_ComAlarm,
				"ComAlarm",
				COUNTER_ID_OsTick,
				GEN_ALARM_AUTOSTART_NAME(ALARM_ID_ComAlarm),
				ALARM_ACTION_ACTIVATETASK,
				TASK_ID_ComTask,
				NULL,
				NULL ),
	GEN_ALARM(	ALARM_ID_ReadSwAlarm,
				"ReadSwAlarm",
				COUNTER_ID_OsTick,
				GEN_ALARM_AUTOSTART_NAME(ALARM_ID_ReadSwAlarm),
				ALARM_ACTION_ACTIVATETASK,
				TASK_ID_ReadSwitches,
				NULL,
				NULL ),
};

// ################################    RESOURCES     ###############################
GEN_RESOURCE_HEAD {
	GEN_RESOURCE(	
		RES_SCHEDULER,
		RESOURCE_TYPE_STANDARD,
		0
	),
};

// ##############################    STACKS (TASKS)     ############################
DECLARE_STACK(OsIdle,OS_OSIDLE_STACK_SIZE);
DECLARE_STACK(ComTask,2048);
DECLARE_STACK(ReadSwitches,2048);
DECLARE_STACK(StartupTask,2048);

// ##################################    TASKS     #################################
GEN_TASK_HEAD {
	GEN_ETASK(	OsIdle,
				0,
				FULL,
				TRUE,
				NULL,
				0 
	),
	GEN_BTASK(
		ComTask,
		10,
		FULL,
		FALSE,
		NULL,
		0,
		1
	),
				
	GEN_BTASK(
		ReadSwitches,
		5,
		FULL,
		FALSE,
		NULL,
		0,
		1
	),
				
	GEN_BTASK(
		StartupTask,
		20,
		FULL,
		TRUE,
		NULL,
		0,
		1
	),
				
};

// ##################################    HOOKS     #################################
GEN_HOOKS( 
	StartupHook, 
	NULL, 
	ShutdownHook, 
	ErrorHook,
	PreTaskHook, 
	PostTaskHook 
);

// ##################################    ISRS     ##################################


// ############################    SCHEDULE TABLES     #############################

// Table heads
GEN_SCHTBL_HEAD {
};

GEN_PCB_LIST()

uint8_t os_interrupt_stack[OS_INTERRUPT_STACK_SIZE] __attribute__ ((aligned (0x10)));

GEN_IRQ_VECTOR_TABLE_HEAD {};
GEN_IRQ_ISR_TYPE_TABLE_HEAD {};
GEN_IRQ_PRIORITY_TABLE_HEAD {};

#include "os_config_funcs.h"
