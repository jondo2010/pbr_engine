/*
 * engine.h
 *	Handles all i/o for the LT9822E solid state relay
 *
 *  Created on: 2010-01-21
 *  Author: John Hughes <jondo2010@gmail.com>
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include <avr/io.h>

/**
 * Initialize the engine module
 */

void
engine_init (void);

void
engine_set_clutch_position (uint8_t p);

void
engine_set_upshift_state (uint8_t state);

void
engine_set_downshift_state (uint8_t state);

void
engine_set_shiftcut_state (uint8_t state);


#endif /* ENGINE_H_ */
