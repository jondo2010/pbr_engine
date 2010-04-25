/*
 * engine_param_iface.h
 *
 *  Created on: 2010-04-25
 *      Author: john
 */

#ifndef ENGINE_PARAM_IFACE_H_
#define ENGINE_PARAM_IFACE_H_

#include <avr/io.h>

#define OTSTART_MIN_TIME	1000	/* 1 second */
#define OTSTART_MAX_TIME	20000	/* 20 seconds */
#define IDLE_MIN			0
#define IDLE_MAX			10000

typedef struct engine_param_struct_t
{
	uint16_t	otstart_timeout;
	uint16_t	idle_rpm;
}
engine_param_struct_t;

/**
 * Initialize the engine parameter interface, restore from EEPROM
 */
void
engine_param_iface_init (void);

/**
 * Store the parameters to EEPROM
 */
void
engine_param_iface_store_param_struct (void);

/**
 * Return a pointer to the parameter struct
 */
const engine_param_struct_t *
engine_param_iface_get_param_struct (void);

/**
 * Set one-touch start on or off
 */
void
engine_param_iface_set_otstart_on (uint8_t on);

/**
 * Set the timeout for one-touch start
 */
void
engine_param_iface_set_otstart_timeout	(uint16_t t);

/**
 * Set the threshold RPM for engine-running detection
 */
void
engine_param_iface_set_idle_rpm (uint16_t rpm);

#endif /* ENGINE_PARAM_IFACE_H_ */