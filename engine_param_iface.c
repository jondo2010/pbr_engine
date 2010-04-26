/*
 * engine_param_iface.c
 *
 *  Created on: 2010-04-25
 *      Author: john
 */

#include <avr/io.h>
#include <libeeprom/eeprom.h>

#include "engine_param_iface.h"

#define OTSTART_MIN_TIME	1000	/* 1 second */
#define OTSTART_MAX_TIME	20000	/* 20 seconds */
#define IDLE_MIN			0
#define IDLE_MAX			10000

static engine_param_struct_t params;
const static engine_param_limits_struct_t param_limits =
{
	OTSTART_MIN_TIME,
	OTSTART_MAX_TIME,
	IDLE_MIN,
	IDLE_MAX
};

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

const engine_param_limits_struct_t *
engine_param_iface_get_param_limits_struct (void)
{
	return &param_limits;
}

void
engine_param_iface_set_otstart_on (uint8_t on);

void
engine_param_iface_set_otstart_timeout	(uint16_t t);

void
engine_param_iface_set_idle_rpm (uint16_t rpm);
