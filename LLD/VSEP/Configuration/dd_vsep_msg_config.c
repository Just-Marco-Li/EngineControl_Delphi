//=============================================================================
//
//       COPYRIGHT, 2003, Delphi Technologies, Inc. All Rights reserved
//
//       Delphi Confidential
//
// ============================================================================
// %name:            dd_vsep_config.c %
//
// created_by:       fz3pdz
//
// date_created:     Tue Mar 22 12:40:49 2005
//
// %derived_by:      nz45s2 %
//
// %date_modified:   Mon Mar  7 18:18:29 2011 %
//
// %version:         15.1.2.1.1.3.2 %
//
// ============================================================================
//
// SPECIFICATION REVISION:
//
// ============================================================================
// REUSE:
// DO NOT MODIFY THIS FILE. It contains no configurable parameters.
// none
//
//=============================================================================

//=============================================================================
// Include the spi port
//=============================================================================
#include "dd_vsep.h"
#include "dd_vsep_discrete.h"
#include "dd_vsep_est_select.h"
#include "dd_vsep_soh.h"
#include "dd_vsep_pwm.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_vr.h"
#include "dd_vsep_deps.h"
#include "io_config_vsep.h"
#include "dd_vsep_discrete_interface.h"
#include "io_config_spi.h"
#include "dd_vsep_fault.h"
#include "dd_vsep_led.h"
#include "dd_vsep_init_config.h"

#define DISCRETE_OUT_VSEP_CSS 0x00

const VSEP_Fault_Channel_Data_T VSEP_Fault_Logging[VSEP_CHANNEL_PCH_30_FLT_LVL_7+1] =
{
    {MTSA_CONFIG_VSEP_PCH_01,      MTSA_CONFIG_VSEP_PCH_01,      VSEP_FAULT_IO_KIND_OUTPUT_COMPARE ,  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_01),1)))}, // PCH1
    {MTSA_CONFIG_VSEP_PCH_02,      MTSA_CONFIG_VSEP_PCH_02,      VSEP_FAULT_IO_KIND_OUTPUT_COMPARE  ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_02),1)))      }, // PCH2
    {MTSA_CONFIG_VSEP_PCH_03,      MTSA_CONFIG_VSEP_PCH_03,      VSEP_FAULT_IO_KIND_OUTPUT_COMPARE   ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_03),1)))     }, // PCH3
    {MTSA_CONFIG_VSEP_PCH_04,      MTSA_CONFIG_VSEP_PCH_04,      VSEP_FAULT_IO_KIND_OUTPUT_COMPARE 	  ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_04),1)))     }, // PCH4
    {MTSA_CONFIG_VSEP_PCH_05,      MTSA_CONFIG_VSEP_PCH_05,      VSEP_FAULT_IO_KIND_DISCRETE,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_05),1)))		 	}, // PCH5
    {MTSA_CONFIG_VSEP_PCH_06,      MTSA_CONFIG_VSEP_PCH_06,      VSEP_FAULT_IO_KIND_DISCRETE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_06),1)))			}, // PCH6
    {MTSA_CONFIG_VSEP_PCH_07,      MTSA_CONFIG_VSEP_PCH_07,      VSEP_FAULT_IO_KIND_DISCRETE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_07),1)))			}, // PCH7
    {MTSA_CONFIG_VSEP_PCH_08,      MTSA_CONFIG_VSEP_PCH_08,      VSEP_FAULT_IO_KIND_DISCRETE  ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_08),1)))    			}, // PCH8
    {MTSA_CONFIG_VSEP_PCH_09,      MTSA_CONFIG_VSEP_PCH_09,      VSEP_FAULT_IO_KIND_OUTPUT_COMPARE  ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_09),1)))     }, // PCH9
    {MTSA_CONFIG_VSEP_PCH_10,      MTSA_CONFIG_VSEP_PCH_10,    VSEP_FAULT_IO_KIND_OUTPUT_COMPARE  ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_10),1)))      }, // PCH10
    {MTSA_CONFIG_VSEP_PCH_11,      MTSA_CONFIG_VSEP_PCH_11,    VSEP_FAULT_IO_KIND_OUTPUT_COMPARE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_11),1)))        }, // PCH11
    {MTSA_CONFIG_VSEP_PCH_12,      MTSA_CONFIG_VSEP_PCH_12,    VSEP_FAULT_IO_KIND_OUTPUT_COMPARE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_12),1)))      }, // PCH12
    {MTSA_CONFIG_VSEP_PCH_13,      MTSA_CONFIG_VSEP_PCH_13,    VSEP_FAULT_IO_KIND_DISCRETE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_13),1))) 	              }, // PCH13
    {MTSA_CONFIG_VSEP_PCH_14,   	   MTSA_CONFIG_VSEP_PCH_14,   VSEP_FAULT_IO_KIND_DISCRETE   ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_14),1)))           		 	}, // PCH14
    {MTSA_CONFIG_VSEP_PCH_15,      MTSA_CONFIG_VSEP_PCH_15,   	VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION  ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_15),1)))      }, // PCH15
    {MTSA_CONFIG_VSEP_PCH_16,      MTSA_CONFIG_VSEP_PCH_16,      	VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION	,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_16),1)))	}, // PCH16
    {MTSA_CONFIG_VSEP_PCH_17, 	  MTSA_CONFIG_VSEP_PCH_17,   	VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION	,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_17),1)))		}, // PCH17
    {MTSA_CONFIG_VSEP_PCH_18,      MTSA_CONFIG_VSEP_PCH_18,   	VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_18),1)))		}, // PCH18
    {MTSA_CONFIG_VSEP_PCH_19,      MTSA_CONFIG_VSEP_PCH_19,        VSEP_FAULT_IO_KIND_DISCRETE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_19),1)))		}, // PCH19
    {MTSA_CONFIG_VSEP_PCH_20,      MTSA_CONFIG_VSEP_PCH_20,     	VSEP_FAULT_IO_KIND_DISCRETE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_20),1)))		}, // PCH20
    //{MTSA_CONFIG_VSEP_PCH_19, 	 DISCRETE_OUT_VIS_OUTPUT1,				VSEP_FAULT_IO_DUMMY_PIN ,DISCRETE_OUT_VIS_OUTPUT1_DiagMask		}, // PCH19
    //{MTSA_CONFIG_VSEP_PCH_20, 	 DISCRETE_OUT_VIS_OUTPUT2,				VSEP_FAULT_IO_DUMMY_PIN ,DISCRETE_OUT_VIS_OUTPUT2_DiagMask		}, // PCH20
    {MTSA_CONFIG_VSEP_PCH_21,      MTSA_CONFIG_VSEP_PCH_21,       	VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_21),1)))		}, // PCH21  
    {MTSA_CONFIG_VSEP_PCH_22,      MTSA_CONFIG_VSEP_PCH_22,      	VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_22),1)))		}, // PCH22
    //{MTSA_CONFIG_VSEP_PCH_23,   DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE, VSEP_FAULT_IO_KIND_IGNORE_PIN_STATE ,DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_DiagMask						}, // PCH23
    //{MTSA_CONFIG_VSEP_PCH_23,		  DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE, VSEP_FAULT_IO_KIND_DISCRETE ,DISCRETE_OUT_TURBO_COMPR_RECIRC_VALVE_DiagMask					   }, // PCH23
    {MTSA_CONFIG_VSEP_PCH_23,	  MTSA_CONFIG_VSEP_PCH_23,  VSEP_FAULT_IO_KIND_DISCRETE,	((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_23),1)))	   }, // PCH23
    //{MTSA_CONFIG_VSEP_PCH_24,	PULSE_OUT_TURBO_WG_PWM, 		   VSEP_FAULT_IO_KIND_IGNORE_PIN_STATE ,PULSE_OUT_TURBO_WG_PWM_DiagMask 	   }, // PCH24
    //{MTSA_CONFIG_VSEP_PCH_24,	   PULSE_OUT_TURBO_WG_PWM,			   VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION ,PULSE_OUT_TURBO_WG_PWM_DiagMask	   }, // PCH24
    //{MTSA_CONFIG_VSEP_PCH_24,  PULSE_OUT_SS_STARTER_RELAY_PWM,	VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION,	PULSE_OUT_SS_STARTER_RELAY_PWM_DiagMask 	   }, // PCH24
    {MTSA_CONFIG_VSEP_PCH_24,	 MTSA_CONFIG_VSEP_PCH_24,  VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION,  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_24),1)))	   }, // PCH24
    {MTSA_CONFIG_VSEP_PCH_25,     MTSA_CONFIG_VSEP_PCH_25, 		   VSEP_FAULT_IO_KIND_DISCRETE ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_25),1))) 						   }, // PCH25
    //{MTSA_CONFIG_VSEP_PCH_26,	   DISCRETE_OUT_SES_LAMP,				   VSEP_FAULT_IO_KIND_DISCRETE	,DISCRETE_OUT_SES_LAMP_DiagMask 						   }, // PCH26
    {MTSA_CONFIG_VSEP_PCH_26,	 MTSA_CONFIG_VSEP_PCH_26,  VSEP_FAULT_IO_KIND_DISCRETE,  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_26),1)))							   }, // PCH26
    {MTSA_CONFIG_VSEP_PCH_27,	 MTSA_CONFIG_VSEP_PCH_27,		   VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION  ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_27),1))) 	   }, // PCH27
    //{MTSA_CONFIG_VSEP_PCH_28,	   PULSE_OUT_AIR_PUMP_SPEED,		   VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION  ,PULSE_OUT_AIR_PUMP_SPEED_DiagMask		   }, // PCH28
    {MTSA_CONFIG_VSEP_PCH_28,	MTSA_CONFIG_VSEP_PCH_28,  VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION,  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_28),1)))		   }, // PCH28
    {MTSA_CONFIG_VSEP_PCH_29,	MTSA_CONFIG_VSEP_PCH_29 ,		   VSEP_FAULT_IO_KIND_PULSE_WIDTH_MODULATION ,((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_29),1)))				}, // PCH29
    //{MTSA_CONFIG_VSEP_PCH_30,	   DISCRETE_OUT_CRUISE_ACTIVE_LAMP,    VSEP_FAULT_IO_KIND_DISCRETE	,DISCRETE_OUT_CRUISE_ACTIVE_LAMP_DiagMask							   }  // PCH30
    {MTSA_CONFIG_VSEP_PCH_30,	MTSA_CONFIG_VSEP_PCH_30,  VSEP_FAULT_IO_KIND_DISCRETE,  ((Mask32(VSEP_Get_Channel(MTSA_CONFIG_VSEP_PCH_30),1)))							   }  // PCH30
};


//=============================================================================
// VSEP EST Fault Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_EST_FAULT_MESSAGE_DEFINITION =
{
    VSEP_EST_Fault_Rxd,
    VSEP_EST_Fault_Txd,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_EST_FAULT_RXD_MESSAGE_MAX,
    VSEP_EST_FAULT_TXD_MESSAGE_MAX,      
};

static SPI_Message_Control_Block_T VSEP_EST_FAULT_CB;


//=============================================================================
// VSEP Fault Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_FAULT_MESSAGE_DEFINITION =
{
    VSEP_Fault_Rxd,
    (void *)VSEP_FAULT_TXD,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_FAULT_RXD_MESSAGE_MAX,
    VSEP_FAULT_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_FAULT_CB;

//=============================================================================
// VSEP INIT Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_INIT_MESSAGE_DEFINITION =
{
    NULL,//
    &VSEP_INIT_TXD_INITIAL,
    DISCRETE_OUT_VSEP_CSS,
    0,
    VSEP_INIT_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_INIT_CB;

//=============================================================================
// VSEP PCH Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_PCH_MESSAGE_DEFINITION =
{
    &VSEP_PCH_Rxd,
    &VSEP_PCH_Txd,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_PCH_RXD_MESSAGE_MAX,
    VSEP_PCH_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_PCH_CB;

//=============================================================================
// VSEP PWM Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_PWM_MESSAGE_DEFINITION[ VSEP_PWM_CHANNEL_MAX ] =
{
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_1 ],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_2 ],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_3 ],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_4 ],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_5 ],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_6 ],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_7 ],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    },
    {
        VSEP_PWM_Rxd,
        &VSEP_PWM_Txd[ VSEP_PWM_CHANNEL_8],
        DISCRETE_OUT_VSEP_CSS,
        VSEP_PWM_RXD_MESSAGE_MAX,
        VSEP_PWM_TXD_MESSAGE_MAX
    }
};

static SPI_Message_Control_Block_T VSEP_PWM_CB[ VSEP_PWM_CHANNEL_MAX ];

//=============================================================================
// VSEP SOH Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_SOH_MESSAGE_DEFINITION =
{
    &VSEP_SOH_Rxd,
    &VSEP_SOH_Txd,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_SOH_RXD_MESSAGE_MAX,
    VSEP_SOH_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_SOH_CB;

//=============================================================================
// VSEP SOH Status Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_SOH_STATUS_MESSAGE_DEFINITION =
{
    &VSEP_SOH_Status_Rxd,
    (void *)&VSEP_SOH_STATUS_TXD,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_SOH_STATUS_RXD_MESSAGE_MAX,
    VSEP_SOH_STATUS_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_SOH_STATUS_CB;

//=============================================================================
// VSEP LEDMODE Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_LEDMODE_MESSAGE_DEFINITION =
{
    NULL,
    &VSEP_LEDMODE_Txd,
    DISCRETE_OUT_VSEP_CSS,
    0,
    VSEP_LEDMODE_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_LEDMODE_CB;

//=============================================================================
// VSEP VR Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_VR_MESSAGE_DEFINITION =
{
    &VSEP_VR_Rxd,
    &VSEP_VR_Txd,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_VR_RXD_MESSAGE_MAX,
    VSEP_VR_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_VR_CB;

//=============================================================================
// VSEP DEPS Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_DEPS_MESSAGE_DEFINITION =
{
    &VSEP_DEPS_Rxd,
    &VSEP_DEPS_Txd,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_DEPS_RXD_MESSAGE_MAX,
    VSEP_DEPS_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_DEPS_CB;

//=============================================================================
// VSEP EST Select Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_EST_SELECT_MESSAGE_DEFINITION =
{
    &VSEP_EST_Select_Rxd,
    &VSEP_EST_Select_Txd,
    DISCRETE_OUT_VSEP_CSS,
    VSEP_EST_SELECT_RXD_MESSAGE_MAX,
    VSEP_EST_SELECT_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_EST_SELECT_CB;

//=============================================================================
// VSEP MPIO MODE Message Definition
//=============================================================================
const SPI_Message_Definition_T VSEP_MPIO_MODE_MESSAGE_DEFINITION =
{
    NULL,
    &VSEP_MPIO_MODE_Txd,
    DISCRETE_OUT_VSEP_CSS,
    0,
    VSEP_MPIO_MODE_TXD_MESSAGE_MAX
};

static SPI_Message_Control_Block_T VSEP_MPIO_MODE_CB;

//=============================================================================
// VSEP Message
//=============================================================================
const SPI_Message_T VSEP_MESSAGE[VSEP_MESSAGE_MAX+7] =
{
    { &VSEP_INIT_MESSAGE_DEFINITION                   , &VSEP_INIT_CB                    },  //VSEP_MESSAGE_INIT
    { &VSEP_VR_MESSAGE_DEFINITION                     , &VSEP_VR_CB                      },  //VSEP_MESSAGE_VR
    { &VSEP_DEPS_MESSAGE_DEFINITION                   , &VSEP_DEPS_CB                    },  //VSEP_MESSAGE_DEPS
    { &VSEP_LEDMODE_MESSAGE_DEFINITION                , &VSEP_LEDMODE_CB                 },  //VSEP_MESSAGE_LEMODE
    { &VSEP_PCH_MESSAGE_DEFINITION                    , &VSEP_PCH_CB                     },  //VSEP_MESSAGE_PCH_MPIO
    { &VSEP_EST_SELECT_MESSAGE_DEFINITION             , &VSEP_EST_SELECT_CB              },  //VSEP_MESSAGE_EST_SELECT
    { &VSEP_EST_FAULT_MESSAGE_DEFINITION              , &VSEP_EST_FAULT_CB               },  //VSEP_MESSAGE_EST_FAULT
    { &VSEP_SOH_MESSAGE_DEFINITION                    , &VSEP_SOH_CB                     },  //VSEP_MESSAGE_SOH
    { &VSEP_SOH_STATUS_MESSAGE_DEFINITION             , &VSEP_SOH_STATUS_CB              },  //VSEP_MESSAGE_SOH_STATUS
    { &VSEP_FAULT_MESSAGE_DEFINITION                  , &VSEP_FAULT_CB                   },  //VSEP_MESSAGE_FAULT
    { &VSEP_MPIO_MODE_MESSAGE_DEFINITION              , &VSEP_MPIO_MODE_CB               },   //VSEP_MESSAGE_MPIO_MODE
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_1], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_1] },  //VSEP_MESSAGE_PWM_1
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_2], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_2] },  //VSEP_MESSAGE_PWM_2
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_3], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_3] },  //VSEP_MESSAGE_PWM_3
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_4], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_4] },  //VSEP_MESSAGE_PWM_4
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_5], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_5] },  //VSEP_MESSAGE_PWM_5
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_6], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_6] },  //VSEP_MESSAGE_PWM_6
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_7], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_7] },  //VSEP_MESSAGE_PWM_7
    { &VSEP_PWM_MESSAGE_DEFINITION[VSEP_PWM_CHANNEL_8], &VSEP_PWM_CB[VSEP_PWM_CHANNEL_8] }   //VSEP_MESSAGE_PWM_8
};


/* return true if channel fault counter reach threshold */
bool VSEP_Is_Channel_Fault_Threshold_Reach(VSEP_Channel_T channel)
{
    return ((VSEP_Fault_Counter[channel] >= KsVSEP_Diagnostic_Counter_Thd) ? true : false);
}

/*===========================================================================*\
 * Revision Log                                                              *
 *===========================================================================*
 *                                                                           *
 * Rev. SCR        Date     By  Description                                  *
 * ==== ========== ======== === ============================================ *
 * 1.0  n/a        08/02/14 WSQ Created the initial version  for MT22p1 based on MT80       * 
 * 15.1.2.1.1.3.1 110128 nz45s2 mt20u2#809 RSM_CTC_0375_add auto start-stop function in MT22.1_Rev0_20101229
 * 15.1.2.1.1.3.2 20110222 nz45s2 mt20u2#828 RSM_CTC_0340_Support Lin type battery Sensor in MT22p1p1 Stop-Start SW_Rev3_20110114
\*===========================================================================*/