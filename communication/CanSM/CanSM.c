/* -------------------------------- Arctic Core ------------------------------
 * Arctic Core - the open source AUTOSAR platform http://arccore.com
 *
 * Copyright (C) 2009  ArcCore AB <contact@arccore.com>
 *
 * This source code is free software; you can redistribute it and/or modify it
 * under the terms of the GNU General Public License version 2 as published by the
 * Free Software Foundation; See <http://www.gnu.org/licenses/old-licenses/gpl-2.0.txt>.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
 * or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License
 * for more details.
 * -------------------------------- Arctic Core ------------------------------*/

//lint -emacro(904,CANSM_VALIDATE_INIT,CANSM_VALIDATE_NETWORK,CANSM_VALIDATE_POINTER,CANSM_VALIDATE_MODE) //904 PC-Lint exception to MISRA 14.7 (validate macros).

/* Globally fulfilled requirements */
/** @req CANSM069 */
/** @req CANSM077 */
/** @req CANSM076 */
/** @req CANSM078 */
/** @req CANSM079 */
/** @req CANSM237 */
/** @req CANSM156.bswbuilder */

#include "ComStack_Types.h"
#include "CanSM.h"              /**< @req CANSM013 */
#include "Com.h"                /**< @req CANSM172 */
#include "ComM.h"               /**< @req CANSM174 */
#include "ComM_BusSm.h"         /**< @req CANSM191 */
#include "Det.h"                /**< @req CANSM015 */
#if defined(USE_DEM)
#include "Dem.h"                /**< @req CANSM014 */
#endif
#include "CanIf.h"              /**< @req CANSM017 */
#include "CanSM_Internal.h"

static CanSM_Internal_NetworkType CanSM_InternalNetworks[CANSM_NETWORK_COUNT];

static CanSM_InternalType CanSM_Internal = {
		.InitStatus = CANSM_STATUS_UNINIT,
		.Networks = CanSM_InternalNetworks,
};

static const CanSM_ConfigType* CanSM_Config;

/** @req CANSM217.exceptTranceiver */
void CanSM_Init( const CanSM_ConfigType* ConfigPtr ) {
	CANSM_VALIDATE_POINTER(ConfigPtr, CANSM_SERVICEID_INIT);  /**< @req CANSM179 */

	CanSM_Config = ConfigPtr;
	Std_ReturnType status = E_OK;
	Std_ReturnType totalStatus = E_OK;

	for (uint8 i = 0; i < CANSM_NETWORK_COUNT; ++i) {
		status = CanSM_Internal_RequestComMode(i, COMM_NO_COMMUNICATION);  /**< @req CANSM211 */
		if (status > totalStatus) {
			totalStatus = status;
		}
	}

	if (totalStatus == E_OK) {
		CanSM_Internal.InitStatus = CANSM_STATUS_INIT;
	} else {
		// TODO report error?
	}
}


/** @req CANSM181  @req CANSM183  @req CANSM182.partially  @req CANSM184 */
Std_ReturnType CanSM_RequestComMode( NetworkHandleType NetworkHandle, ComM_ModeType ComM_Mode ) {
	CANSM_VALIDATE_INIT(CANSM_SERVICEID_REQUESTCOMMODE, E_NOT_OK);
	CANSM_VALIDATE_NETWORK(NetworkHandle, CANSM_SERVICEID_REQUESTCOMMODE, E_NOT_OK);
	CANSM_VALIDATE_MODE(ComM_Mode, CANSM_SERVICEID_REQUESTCOMMODE, E_NOT_OK);

	return CanSM_Internal_RequestComMode(NetworkHandle, ComM_Mode);
}

/** @req CANSM032.partially  @req CANSM212  @req CANSM219.exceptTranceiver  @req CANSM218.exceptTranceiver
 *  @req CANSM231  @req CANSM232 */
Std_ReturnType CanSM_Internal_RequestComMode( NetworkHandleType NetworkHandle, ComM_ModeType ComM_Mode ) {
	CanSM_Internal_NetworkType* NetworkInternal = &CanSM_Internal.Networks[NetworkHandle];
	NetworkInternal->RequestedMode = ComM_Mode;

	Std_ReturnType overallStatus = E_OK;
	Std_ReturnType status;
	status = CanSM_Internal_RequestCanIfMode(NetworkHandle, ComM_Mode);      /**< @req CANSM240 */
	if (status > overallStatus){
		overallStatus = status;
	}
	status = CanSM_Internal_RequestComGroupMode(NetworkHandle, ComM_Mode);   /**< @req CANSM241 */
	if (status > overallStatus) {
		overallStatus = status;
	}

	if (overallStatus == E_OK) {
		NetworkInternal->CurrentMode = ComM_Mode;
		ComM_BusSM_ModeIndication(NetworkHandle, ComM_Mode);                 /**< @req CANSM089 */
	}

	return overallStatus;
}

/** @req CANSM039  @req CANSM044 */
Std_ReturnType CanSM_Internal_RequestCanIfMode( NetworkHandleType NetworkHandle, ComM_ModeType ComM_Mode ) {
	const CanSM_NetworkType* Network = &CanSM_Config->Networks[NetworkHandle];
	CanIf_ControllerModeType CanIf_Mode = CANIF_CS_STARTED;
	Std_ReturnType totalStatus = E_OK;

	switch (ComM_Mode) {
		case COMM_NO_COMMUNICATION:
/* CAN wake-up capability is not implemented so we cannot set
 * controllers into sleep because then we would be unable to
 * wake except on internal requests.
 */
#if 0
			CanIf_Mode = CANIF_CS_SLEEP;
#endif
			CanIf_Mode = CANIF_CS_STARTED;
			break;
		case COMM_FULL_COMMUNICATION:
			CanIf_Mode = CANIF_CS_STARTED;
			break;
		default:
			totalStatus = E_NOT_OK;
			break;
	}

	if (totalStatus == E_OK) {
		for (uint8 i = 0; i < Network->ControllerCount; ++i) {
			const CanSM_ControllerType* Controller = &Network->Controllers[i];
			Std_ReturnType status =
					CanIf_SetControllerMode(Controller->CanIfControllerId, CanIf_Mode);
			if (status > totalStatus) {
				totalStatus = status;
			}
		}
	}
	return totalStatus;
}

/** @req CANSM173 */
Std_ReturnType CanSM_Internal_RequestComGroupMode( NetworkHandleType NetworkHandle, ComM_ModeType ComM_Mode ) {
	const CanSM_NetworkType* Network = &CanSM_Config->Networks[NetworkHandle];
	Std_ReturnType status = E_OK;

	switch (ComM_Mode) {
		case COMM_NO_COMMUNICATION:
			Com_IpduGroupStop(Network->ComRxPduGroupId);
			Com_IpduGroupStop(Network->ComTxPduGroupId);
			break;
		case COMM_SILENT_COMMUNICATION:
			Com_IpduGroupStart(Network->ComRxPduGroupId, FALSE);
			Com_IpduGroupStop(Network->ComTxPduGroupId);
			break;
		case COMM_FULL_COMMUNICATION:
			Com_IpduGroupStart(Network->ComRxPduGroupId, FALSE);
			Com_IpduGroupStart(Network->ComTxPduGroupId, FALSE);
			break;
		default:
			status = E_NOT_OK;
			break;
	}
	return status;
}

/** @req CANSM090  @req CANSM185  @req CANSM187  @req CANSM186  @req CANSM188 */
Std_ReturnType CanSM_GetCurrentComMode( NetworkHandleType NetworkHandle, ComM_ModeType* ComM_ModePtr ) {
	CANSM_VALIDATE_INIT(CANSM_SERVICEID_GETCURRENTCOMMODE, E_NOT_OK);
	CANSM_VALIDATE_NETWORK(NetworkHandle, CANSM_SERVICEID_GETCURRENTCOMMODE, E_NOT_OK);

	ComM_ModeType ComM_Mode = COMM_FULL_COMMUNICATION;

	const CanSM_NetworkType* Network = &CanSM_Config->Networks[NetworkHandle];
	Std_ReturnType totalStatus = E_OK;
	for (uint8 i = 0; i < Network->ControllerCount; ++i) {
		const CanSM_ControllerType* Controller = &Network->Controllers[i];
		CanIf_ControllerModeType CanIf_Mode;
		Std_ReturnType status =
				CanIf_GetControllerMode(Controller->CanIfControllerId, &CanIf_Mode);
		if (status > totalStatus) {
			totalStatus = status;
		}

		if (CanIf_Mode != CANIF_CS_STARTED) {
			ComM_Mode = COMM_NO_COMMUNICATION;
		}
	}

	*ComM_ModePtr = ComM_Mode;
	return totalStatus;
}


void CanSM_MainFunction() {
	CANSM_VALIDATE_INIT(CANSM_SERVICEID_MAINFUNCTION);
}
