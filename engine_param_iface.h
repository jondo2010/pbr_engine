/*
 * engine_param_iface.h
 *
 *  Created on: 2010-04-25
 *      Author: john
 */

#ifndef ENGINE_PARAM_IFACE_H_
#define ENGINE_PARAM_IFACE_H_

#include <avr/io.h>
#include <libpbr/param.h>

#define ENGINE_MODULE_ID	0x01
#define ENGINE_NUM_PARAMS	3

#define OTSTART_MIN_TIME	1000	/* 1 second */
#define OTSTART_MAX_TIME	20000	/* 20 seconds */
#define OTSTART_GRAN		100
#define IDLE_MIN			0
#define IDLE_MAX			10000
#define IDLE_GRAN			100

typedef enum engine_param_t
{
	param_engine_otstart_enabled	= 0x00,		/* One-touch start */
	param_engine_otstart_timeout	= 0x01,		/* Timeout in ms */
	param_engine_idle_rpm			= 0x02
}
engine_param_t;

typedef struct engine_param_struct_t
{
	uint8_t		otstart_enabled;
	uint16_t	otstart_timeout;
	uint16_t	idle_rpm;
}
engine_param_struct_t;

const static module_param_t engine_param_defs[] =
{
	{"ENG OTSTRT ON",		2},
	{"ENG OTSTRT TIME",	2},
	{"ENG IDLE RPM",		2}
};

/**
 * Initialise the engine parameter interface, restore from EEPROM
 */
void
engine_param_iface_init (void);

/**
 * Store the parameters to EEPROM
 */
void
engine_param_iface_store_param_struct (void);

uint8_t
engine_param_iface_get_param
(
	engine_param_t	p,
	uint8_t			data[8]
);

uint8_t
engine_param_iface_set_param
(
	engine_param_t	p,
	uint8_t			data[8]
);

#endif /* ENGINE_PARAM_IFACE_H_ */
