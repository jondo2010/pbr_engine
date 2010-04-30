/*
 * engine_param_iface.c
 *
 *  Created on: 2010-04-25
 *      Author: john
 */

#include <avr/io.h>
#include <libeeprom/eeprom.h>
#include <libpbr/param.h>

#include "engine_param_iface.h"

static engine_param_struct_t params;

void
engine_param_iface_init (void)
{
	eeprom_read_many (0x0000, (uint8_t *)&params, sizeof(engine_param_struct_t));
}

void
engine_param_iface_store_param_struct (void)
{
	eeprom_write_many (0x0000, (uint8_t *)&params, sizeof(engine_param_struct_t));
}

const engine_param_struct_t *
engine_param_iface_get_param_struct (void)
{
	return &params;
}

uint8_t
engine_param_iface_get_param
(
	engine_param_t	p,
	uint8_t			data[8]
)
{
	switch (p) {
		case param_engine_otstart_enabled:
			*(uint16_t *)data = params.otstart_enabled;
			break;
		case param_engine_otstart_timeout:
			*(uint16_t *)data = params.otstart_timeout;
			break;
		case param_engine_idle_rpm:
			*(uint16_t *)data = params.idle_rpm;
			break;
		default:
			break;
	}
	return engine_param_defs[p].size;
}

uint8_t
engine_param_iface_set_param
(
	engine_param_t	p,
	uint8_t			data[8]
)
{
	switch (p)
	{
		case param_engine_otstart_enabled:
			if (*(uint8_t *)data > 0)
			{
				params.otstart_enabled = 1;
			}
			else
			{
				params.otstart_enabled = 0;
			}
			break;
		case param_engine_otstart_timeout:
			if (*(uint16_t *)data > OTSTART_MAX_TIME)
			{
				params.otstart_timeout = OTSTART_MAX_TIME;
			}
			else if (*(uint16_t *)data < OTSTART_MIN_TIME)
			{
				params.otstart_timeout = OTSTART_MIN_TIME;
			}
			else
			{
				params.otstart_timeout = *(uint16_t *)data;
			}
			break;
		case param_engine_idle_rpm:
			if (*(uint16_t *)data > IDLE_MAX)
			{
				params.idle_rpm  = IDLE_MAX;
			}
			else if (*(uint16_t *)data < IDLE_MIN)
			{
				params.idle_rpm  = IDLE_MIN;
			}
			else
			{
				params.idle_rpm = *(uint16_t *)data;
			}
			break;
		default:
			break;
	}
	return 1;
}
