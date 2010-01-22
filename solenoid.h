/*
 * solenoid.h
 *	Handles all i/o for the LT9822E solid state relay
 *
 *  Created on: 2010-01-21
 *  Author: John Hughes <jondo2010@gmail.com>
 */

#ifndef SOLENOID_H_
#define SOLENOID_H_

#define SOL_CLUTCH_A	0x01
#define SOL_CLUTCH_B	0x02
#define SOL_DOWNSHIFT	0x04
#define SOL_UPSHIFT		0x08
#define SOL_STARTER		0x10

void
solenoid_init_output_driver (void);

void
solenoid_init_clutch_pwm (void);

void
solenoid_update_output_driver (void);

void
solenoid_set_clutch_a_duty (uint8_t d);

void
solenoid_set_clutch_b_duty (uint8_t d);

#endif /* SOLENOID_H_ */
