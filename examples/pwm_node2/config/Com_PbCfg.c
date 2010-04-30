/* 
* Configuration of module Com (Com_PbCfg.c)
* 
* Created by: 
* Configured for (MCU): MPC551x
* 
* Module editor vendor:  ArcCore
* Module editor version: 2.0.0
* 
* 
* Generated by Arctic Studio (http://arccore.com)
*           on Fri Apr 30 15:56:33 CEST 2010
*/


#include "Com.h"
#include "stdlib.h"
#if defined(USE_PDUR)
#include "PduR.h"
#endif





/*
 * Signal init values.
 */
const uint16 Com_SignalInitValue_SetLedLevelRx = 0;
	

/*
 * Group signal definitions
 */
const ComGroupSignal_type ComGroupSignal[] = {
	{
		.Com_Arc_EOL = 1
	}
};


/* SignalGroup GroupSignals lists. */

/*
 * Signal definitions
 */
const ComSignal_type ComSignal[] = {
	{
		.ComHandleId = SetLedLevelRx,
		.ComFirstTimeoutFactor = 0,
		.ComNotification = NULL,
		.ComTimeoutFactor = 0,
		.ComTimeoutNotification = NULL,
		.ComTransferProperty = TRIGGERED,
		
		
		.ComSignalInitValue = &Com_SignalInitValue_SetLedLevelRx,
		.ComBitPosition = 7,
		.ComBitSize = 16,
		.ComSignalEndianess = BIG_ENDIAN,
		.ComSignalType = UINT16,
		.ComGroupSignal = NULL,
		
	},
	{
		.Com_Arc_EOL = 1
	}
};


/*
 * I-PDU group definitions
 */
const ComIPduGroup_type ComIPduGroup[] = {
	{
		.ComIPduGroupHandleId = RxGroup
	},
	
	{
		.Com_Arc_EOL  = 1
	}
};

/* IPdu signal lists. */
const ComSignal_type *ComIPduSignalRefs_LedCommandRx[] = {
	&ComSignal[ SetLedLevelRx ],		
	NULL,
};

/*
 * I-PDU definitions
 */
const ComIPdu_type ComIPdu[] = {	
    
	{ // LedCommandRx
		.ArcIPduOutgoingId = PDUR_SOURCE_PDU_ID_LedCommandRx,
		.ComIPduCallout = NULL,
		.ComIPduSignalProcessing =  DEFERRED,
		.ComIPduSize =  8,
		.ComIPduDirection = RECEIVE,
		.ComIPduGroupRef = RxGroup,
		
		.ComIPduSignalRef = ComIPduSignalRefs_LedCommandRx,
	},   
	{
		.Com_Arc_EOL = 1
	}
};

const Com_ConfigType ComConfiguration = {
	.ComConfigurationId = 1,
	.ComIPdu = ComIPdu,
	.ComIPduGroup = ComIPduGroup,
	.ComSignal = ComSignal,
	.ComGroupSignal = ComGroupSignal
};


