/* 
* Configuration of module PduR (PduR_PbCfg.h)
* 
* Created by: 
* Configured for (MCU): MPC551x
* 
* Module editor vendor:  ArcCore
* Module editor version: 2.0.1
* 
* 
* Generated by Arctic Studio (http://arccore.com)
*           on Fri Apr 30 15:56:33 CEST 2010
*/


#if (PDUR_SW_MAJOR_VERSION != 1) 
#error "PduR: Configuration file version differs from BSW version."
#endif


#if defined(USE_DCM)
#include "Dcm.h"
#endif
#if defined(USE_COM)
#include "Com.h"
#endif
#if defined(USE_CANIF)
#include "CanIf.h"
#endif
#if defined(USE_CANTP)
#include "CanTp.h"
#endif

extern PduR_PBConfigType PduR_Config;

//  PduR Polite Defines.

#define PDUR_SOURCE_PDU_ID_LedCommandRx CANIF_PDU_ID_LedCommandRx
#define PDUR_DEST_PDU_ID_LedCommandRx COM_PDU_ID_LedCommandRx
