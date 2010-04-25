/*
 * engine_param_iface.c
 *
 *  Created on: 2010-04-25
 *      Author: john
 */

#include <avr/io.h>
#include <libeeprom/eeprom.h>

#include "engine_param_iface.h"

static engine_param_struct_t param_struct;

void
engine_param_iface_init (void)
{
	eeprom_read_many (0x0000, (uint8_t *)&param_struct, sizeof(engine_param_struct_t));
}

void
engine_param_iface_store_param_struct (void)
{
	eeprom_write_many (0x0000, (uint8_t *)&param_struct, sizeof(engine_param_struct_t));
}

const engine_param_struct_t *
engine_param_iface_get_param_struct (void)
{
	return &param_struct;
}

void
engine_param_iface_set_otstart_on (uint8_t on);

void
engine_param_iface_set_otstart_timeout	(uint16_t t);

void
engine_param_iface_set_idle_rpm (uint16_t rpm);
