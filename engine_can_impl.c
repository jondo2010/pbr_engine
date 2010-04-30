/*
 * engine_can_impl.c
 *
 *  Created on: 2010-04-25
 *      Author: john
 */

#include <avr/io.h>
#include <libcan/can.h>
#include <libpbr/dta_can_impl.h>
#include <libpbr/module_params_can_impl.h>

#include "engine_can_impl.h"
#include "engine_param_iface.h"

void
engine_can_impl_init (void)
{
	can_init (can_baud_1000);

	module_params_can_impl_init (0, ENGINE_MODULE_ID, engine_param_iface_get_param, engine_param_iface_set_param, ENGINE_NUM_PARAMS);
	dta_can_impl_init (1);
}
