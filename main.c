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

#include "engine.h"

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
	DDRG |= _BV (PE2);

	engine_init ();
	engine_set_clutch_position (50);

	sei ();

	//DDRF &= ~_BV (PF0);

	//adc_init (0);
	//adc_set_conversion_callback (&callback);
	//adc_enable ();

//	can_init (baud_1000);

//	mob_config_t mob1;
//	mob1.id = 0xab;
//	mob1.id_type = standard;
//	mob1.mode = transmit;

//	uint8_t data[] = "TESTING";

//	can_config_mob (0, &mob1);

	for (;;)
	{
		//can_load_data (0, data, 7);
		//can_ready_to_send (0);
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
