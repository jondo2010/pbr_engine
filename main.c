/*
 * main.c
 *	Engine/Transmission Module
 *
 *  Created on: 2010-01-14
 *  Author: John Hughes <jondo2010@gmail.com>
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#include <spi.h>
#include <adc.h>

#include "solenoid.h"

static uint8_t delay = 50;

void callback (uint8_t d)
{
	delay = d;
}

#define DAC_FAST_MODE	0x4000
#define DAC_POWER_DOWN	0x2000

uint16_t
get_dac_word
(
	uint8_t value
)
{
	return DAC_FAST_MODE | (value << 4);
}

int
main (void)
{
	DDRG = _BV (PE2);

	solenoid_init_output_driver ();
	solenoid_init_clutch_pwm ();

	solenoid_set_clutch_a_duty (50);
	solenoid_set_clutch_b_duty (25);

	sei ();

	//DDRF &= ~_BV (PF0);

	//adc_init (0);
	//adc_set_conversion_callback (&callback);
	//adc_enable ();

	uint8_t cnt = 0;
	uint16_t value = 0;

	for (;;)
	{
/*
		value = get_dac_word (cnt);

		spi_slave_select (2);
		spi_slave_select (1);

		spi_putch ((uint8_t)(value >> 8));
		spi_putch ((uint8_t)value );

		spi_slave_deselect (1);
		spi_slave_deselect (2);

		_delay_ms(5);

		cnt++;
*/

		_delay_ms (50);
		PORTG ^= _BV (PG2);
	}

	return 0;
}
