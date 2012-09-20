/*
* Configuration of module: EcuM (EcuM_Callout_Stubs.c)
*
* Created by:              
* Copyright:               
*
* Configured for (MCU):    MPC5567
*
* Module vendor:           ArcCore
* Generator version:       2.0.2
*
* Generated by Arctic Studio (http://arccore.com) 
*/


#include "EcuM.h"
#include "EcuM_Generated_Types.h"
#include "Det.h"
#if defined(USE_DEM)
#include "Dem.h"
#endif
#if defined(USE_MCU)
#include "Mcu.h"
#endif
#if defined(USE_GPT)
#include "Gpt.h"
#endif
#if defined(USE_CAN)
#include "Can.h"
#endif
#if defined(USE_CANIF)
#include "CanIf.h"
#endif
#if defined(USE_PDUR)
#include "PduR.h"
#endif
#if defined(USE_COM)
#include "Com.h"
#endif
#if defined(USE_CANTP)
#include "CanTp.h"
#endif
#if defined(USE_J1939TP)
#include "J1939Tp.h"
#endif
#if defined(USE_DCM)
#include "Dcm.h"
#endif
#if defined(USE_PWM)
#include "Pwm.h"
#endif
#if defined(USE_IOHWAB)
#include "IoHwAb.h"
#endif
#if defined(USE_FLS)
#include "Fls.h"
#endif
#if defined(USE_EEP)
#include "Eep.h"
#endif
#if defined(USE_FEE)
#include "Fee.h"
#endif
#if defined(USE_EA)
#include "Ea.h"
#endif
#if defined(USE_NVM)
#include "NvM.h"
#endif
#if defined(USE_COMM)
#include "ComM.h"
#endif
#if defined(USE_NM)
#include "Nm.h"
#endif
#if defined(USE_CANNM)
#include "CanNm.h"
#endif
#if defined(USE_CANSM)
#include "CanSM.h"
#endif
#if defined(USE_UDPNM)
#include "UdpNm.h"
#endif
#if defined(USE_LINSM)
#include "LinSM.h"
#endif
#if defined(USE_SPI)
#include "Spi.h"
#endif
#if defined(USE_WDG)
#include "Wdg.h"
#endif
#if defined(USE_WDGM)
#include "WdgM.h"
#endif

#define VALIDATE_STATE(_state) \
	do { \
		EcuM_StateType ecuMState;  \
		EcuM_GetState(&ecuMState); \
		assert(ecuMState == (_state) ); \
	} while(0)


void EcuM_AL_DriverInitZero(void)
{
	Det_Init();/** @req EcuM2783 */
    Det_Start();/** @req EcuM2634 */
}

extern EcuM_ConfigType EcuMConfig;

EcuM_ConfigType* EcuM_DeterminePbConfiguration(void)
{
	return &EcuMConfig;
}

void EcuM_AL_DriverInitOne(const EcuM_ConfigType *ConfigPtr)
{
	(void)ConfigPtr;
  //lint --e{715}       PC-Lint (715) - ConfigPtr usage depends on configuration of modules

#if defined(USE_MCU)
	Mcu_Init(ConfigPtr->McuConfig);

	/* Set up default clock (Mcu_InitClock requires initRun==1) */
	/* Ignoring return value */
	(void) Mcu_InitClock( ConfigPtr->McuConfig->McuDefaultClockSettings );

	// Wait for PLL to sync.
	while (Mcu_GetPllStatus() != MCU_PLL_LOCKED)
	{
	  ;
	}
#endif

#if defined(USE_DEM)
	// Preinitialize DEM
	Dem_PreInit();
#endif

#if defined(USE_PORT)
	// Setup Port
	Port_Init(ConfigPtr->PortConfig);
#endif


#if defined(USE_GPT)
	// Setup the GPT
	Gpt_Init(ConfigPtr->GptConfig);
#endif

	// Setup watchdog
#if defined(USE_WDG)
	Wdg_Init(ConfigPtr->WdgConfig);
#endif
#if defined(USE_WDGM)
	WdgM_Init(ConfigPtr->WdgMConfig);
#endif

#if defined(USE_DMA)
	// Setup DMA
	Dma_Init(ConfigPtr->DmaConfig);
#endif

#if defined(USE_ADC)
	// Setup ADC
	Adc_Init(ConfigPtr->AdcConfig);
#endif

	// Setup ICU
	// TODO

	// Setup PWM
#if defined(USE_PWM)
	// Setup PWM
	Pwm_Init(ConfigPtr->PwmConfig);
#endif
}

void EcuM_AL_DriverInitTwo(const EcuM_ConfigType* ConfigPtr)
{
	(void)ConfigPtr;
  //lint --e{715}       PC-Lint (715) - ConfigPtr usage depends on configuration of modules

#if defined(USE_SPI)
	// Setup SPI
	Spi_Init(ConfigPtr->SpiConfig);
#endif

#if defined(USE_EEP)
	// Setup EEP
	Eep_Init(ConfigPtr->EepConfig);
#endif

#if defined(USE_FLS)
	// Setup Flash
	Fls_Init(ConfigPtr->FlashConfig);
#endif

#if defined(USE_FEE)
	// Setup FEE
	Fee_Init();
#endif

#if defined(USE_EA)
	// Setup EA
	Ea_Init();
#endif

#if defined(USE_NVM)
	// Setup NVRAM Manager and start the read all job
	NvM_Init();
	NvM_ReadAll();
#endif

	// Setup CAN tranceiver
	// TODO

#if defined(USE_CAN)
	// Setup Can driver
	Can_Init(ConfigPtr->CanConfig);
#endif

#if defined(USE_CANIF)
	// Setup CanIf
	CanIf_Init(ConfigPtr->CanIfConfig);
#endif

#if defined(USE_CANTP)
	// Setup CAN TP
	CanTp_Init();
#endif

#if defined(USE_CANSM)
        CanSM_Init(ConfigPtr->CanSMConfig);
#endif

#if defined(USE_J1939TP)
	// Setup J1939Tp
	J1939Tp_Init(ConfigPtr->J1939TpConfig);
#endif


	// Setup LIN
	// TODO

#if defined(USE_PDUR)
	// Setup PDU Router
	PduR_Init(ConfigPtr->PduRConfig);
#endif

#if defined(USE_CANNM)
        // Setup Can Network Manager
        CanNm_Init(ConfigPtr->CanNmConfig);
#endif

#if defined(USE_UDPNM)
        // Setup Udp Network Manager
        UdpNm_Init(ConfigPtr->UdpNmConfig);
#endif

#if defined(USE_NM)
        // Setup Network Management Interface
        Nm_Init(ConfigPtr->NmConfig);
#endif

#if defined(USE_COM)
	// Setup COM layer
	Com_Init(ConfigPtr->ComConfig);
#endif

#if defined(USE_DCM)
	// Setup DCM
	Dcm_Init();
#endif

#if defined(USE_IOHWAB)
	// Setup IO hardware abstraction layer
	IoHwAb_Init();
#endif

}

void EcuM_AL_DriverInitThree(const EcuM_ConfigType* ConfigPtr)
{
	(void)ConfigPtr;
  //lint --e{715}       PC-Lint (715) - ConfigPtr usage depends on configuration of modules

#if defined(USE_DEM)
	// Setup DEM
	Dem_Init();
#endif

#if defined(USE_COMM)
        // Setup Communication Manager
        ComM_Init(ConfigPtr->ComMConfig);
#endif
}

void EcuM_OnEnterRun(void)
{

}

void EcuM_OnExitRun(void)
{

}

void EcuM_OnExitPostRun(void)
{

}

void EcuM_OnPrepShutdown(void)
{

}

void EcuM_OnGoSleep(void)
{

}

void EcuM_OnGoOffOne(void)
{

}

void EcuM_OnGoOffTwo(void)
{

}

void EcuM_AL_SwitchOff(void)
{

}

void EcuM_CheckWakeup(EcuM_WakeupSourceType source) {
}

void EcuM_EnableWakeupSources( EcuM_WakeupSourceType source ) {
}

void EcuM_DisableWakeupSources(EcuM_WakeupSourceType wakeupSource) {
}


/**
 *
 *
 *
 * @param wakeupSource
 */
void EcuM_StartWakeupSources(EcuM_WakeupSourceType wakeupSource) {
	VALIDATE_STATE( ECUM_STATE_WAKEUP_VALIDATION );

}

void EcuM_CheckValidation(EcuM_WakeupSourceType wakeupSource) {

	VALIDATE_STATE( ECUM_STATE_WAKEUP_VALIDATION);

	(void) wakeupSource;
}

/**
 * Restart drivers..
 */
void EcuM_AL_DriverRestart( void ) {

	VALIDATE_STATE( ECUM_STATE_WAKEUP_VALIDATION );

}


/**
 *
 * @param wact
 * @return
 */
EcuM_WakeupReactionType EcuM_OnWakeupReaction( EcuM_WakeupReactionType wact ) {

	VALIDATE_STATE( ECUM_STATE_WAKEUP_REACTION );

	return wact;
}

/**
 * Generate RAM hash.
 * We are in ECUM_STATE_SLEEP here.
 *
 */
void EcuM_GenerateRamHash( void ) {
	VALIDATE_STATE( ECUM_STATE_SLEEP );
}

/**
 * Check RAM hash.
 * We are still in ECUM_STATE_SLEEP here.
 *
 * @return
 */
uint8 EcuM_CheckRamHash( void ) {
	VALIDATE_STATE( ECUM_STATE_SLEEP );

	return 0;
}


