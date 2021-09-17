// SPDX-License-Identifier: GPL-2.0+
/*
 * Setup code for SAM9X60.
 *
 * Copyright (C) 2019 Microchip Technology Inc. and its subsidiaries
 *
 * Author: Claudiu Beznea <claudiu.beznea@microchip.com>
 */

#include <linux/of.h>
#include <linux/of_platform.h>

#include <asm/io.h>
#include <asm/mach/arch.h>
#include <asm/system_misc.h>

#include "generic.h"

#include "at91sam9_smc.h" 

static void flash_setup( void )
{
	struct	at91_smc * smc = (struct at91_smc * )ATMEL_BASE_SMC;

	/* Configure SMC CS3 for NAND/SmartMedia */
	writel(AT91_SMC_SETUP_NWE(10), &smc->cs[3].setup);		// 4

	writel(AT91_SMC_PULSE_NWE(15) | AT91_SMC_PULSE_NCS_WR(25) |			// 10 20
	       AT91_SMC_PULSE_NRD(15) | AT91_SMC_PULSE_NCS_RD(25),
	       &smc->cs[3].pulse);

	writel(AT91_SMC_CYCLE_NWE(30) | AT91_SMC_CYCLE_NRD(30),		// 20 20
	       &smc->cs[3].cycle);

	writel(AT91_SMC_MODE_RM_NRD | AT91_SMC_MODE_WM_NWE |
	       AT91_SMC_MODE_DBW_8 |
	       AT91_SMC_MODE_TDF | AT91_SMC_MODE_TDF_CYCLE(20),		// 15
	       &smc->cs[3].mode);
}

static void __init sam9x60_init(void)
{
	of_platform_default_populate(NULL, NULL, NULL);

	sam9x60_pm_init();

	flash_setup( );
}

static const char *const sam9x60_dt_board_compat[] __initconst = {
	"microchip,sam9x60",
	NULL
};

DT_MACHINE_START(sam9x60_dt, "Microchip SAM9X60")
	/* Maintainer: Microchip */
	.init_machine	= sam9x60_init,
	.dt_compat	= sam9x60_dt_board_compat,
MACHINE_END
