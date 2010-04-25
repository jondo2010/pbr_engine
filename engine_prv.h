/*
 * engine_prv.h
 *
 *  Created on: 2010-01-24
 *      Author: john
 */

#ifndef ENGINE_PRV_H_
#define ENGINE_PRV_H_

#define SOL_CLUTCH_A	0x01
#define SOL_CLUTCH_B	0x02
#define SOL_DOWNSHIFT	0x04
#define SOL_UPSHIFT		0x08
#define SOL_STARTER		0x10

#define IO_LAUNCH_CTL	_BV (PC0)
#define IO_SHIFTCUT		_BV (PC1)
#define	ECU_LOG			_BV (PC2)
#define TRAC_W/D		_BV (PC3)
#define TRAG_TGL		_BV	(PC4)

#define PWM_DUTY_SCALE 2.05

void
engine_adc_callback (const uint8_t d);

void
engine_init_output_driver (void);

void
engine_init_clutch_pwm (void);

void
engine_update_output_driver (void);

void
engine_set_clutch_a_duty (const uint8_t d);

void
engine_set_clutch_b_duty (const uint8_t d);

#endif /* ENGINE_PRV_H_ */
