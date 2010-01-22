/*
 * solenoid.c
 *	Handles all i/o for the LT9822E solid state relay
 *
 *  Created on: 2010-01-21
 *  Author: John Hughes <jondo2010@gmail.com>
 */

#include <avr/io.h>
#include <avr/interrupt.h>

#include <spi.h>

#include "solenoid.h"

static uint8_t clutch_a_duty = 0;
static uint8_t clutch_b_duty = 0;

static uint8_t pwm_state = 0;
static uint8_t driver_state = 0xff;

#define SOL_DUTY_SCALE 2.05

/**
 * Timer 0 interrupt service routine. Handles accurate generation
 * of PWM signals for the clutch solenoids.
 */

ISR(TIMER2_COMP_vect)
{
	switch (pwm_state)
	{
	case 0:

		if (clutch_a_duty==clutch_b_duty)
		{
			/// Turn both A and B off
			driver_state |= SOL_CLUTCH_A | SOL_CLUTCH_B;
			OCR2A = SOL_DUTY_SCALE * (100 - clutch_a_duty);
			pwm_state = 2;
		}
		else if (clutch_a_duty>clutch_b_duty)
		{
			/// Turn off B
			driver_state |= SOL_CLUTCH_B;
			OCR2A = SOL_DUTY_SCALE * (clutch_a_duty-clutch_b_duty);
			pwm_state = 1;
		}
		else
		{
			/// Turn off A
			driver_state |= SOL_CLUTCH_A;
			OCR2A = SOL_DUTY_SCALE * (clutch_b_duty-clutch_a_duty);
			pwm_state = 1;
		}
		break;

	case 1:
		if (clutch_a_duty>clutch_b_duty)
		{
			/// Turn off A
			driver_state |= SOL_CLUTCH_A;
			OCR2A = SOL_DUTY_SCALE * (100 - clutch_a_duty);
		}
		else
		{
			/// Turn off B
			driver_state |= SOL_CLUTCH_B;
			OCR2A = SOL_DUTY_SCALE * (100 - clutch_b_duty);
		}
		pwm_state = 2;
		break;

	case 2:

		/// Turn both PWMs on if duty > 0
		if (clutch_a_duty>0)
			driver_state &= ~SOL_CLUTCH_A;

		if (clutch_b_duty>0)
			driver_state &= ~SOL_CLUTCH_B;

		if (clutch_a_duty>clutch_b_duty)
			OCR2A = SOL_DUTY_SCALE * clutch_b_duty;
		else
			OCR2A = SOL_DUTY_SCALE * clutch_a_duty;

		pwm_state = 0;
		break;
	}

	solenoid_update_output_driver ();
}

/**
 * Initialize the SPI driver for the LT9822E, and the ADC chip.
 * The LT9822E samples data on the trailing edge of SCK, so is set
 * to use SPI_MODE_1
 */

void
solenoid_init_output_driver (void)
{
	spi_slave_desc_t desc;

	spi_init (1);

	/**
	 * Line documentation:
	 * PB0 Solenoid driver CS line
	 * PB4 DAC FS
	 * PB5 DAC CS line
	 */

	DDRB |= _BV (PB0) | _BV (PB4) | _BV (PB5);

	desc.port = &PORTB;
	desc.select_delay = 1;
	desc.deselect_delay = 1;
	desc.spi_mode = SPI_MODE_1;

	desc.pin = PB0;
	spi_setup_slave (0, &desc);

	//desc.pin = PB4;
	//spi_setup_slave (1, &desc);

	//desc.pin = PB5;
	//spi_setup_slave (2, &desc);

	solenoid_update_output_driver ();
}

/**
 * Initialize Timer2 using the 32.768 kHz external clock to provide interrupts
 * for the PWM generator. For now the PWM frequency is set to just under 20Hz.
 */

void
solenoid_init_clutch_pwm (void)
{
	/// Initialize timer0 for generating the PWM
	ASSR = _BV (AS2);					/// External 32.768kHz crystal source
	TCCR2A |= _BV (WGM21) | _BV (CS21);	/// CTC mode, Prescale the system clock by 8
	TIMSK2 = _BV (OCIE2A);				/// Interrupt on compare match
}

/**
 * Update the value stored in the output latch of the LT9228E
 */

void
solenoid_update_output_driver (void)
{
	spi_slave_select (0);
	spi_putch (driver_state);
	spi_slave_deselect (0);
}

/**
 * Set the duty cycle % for Clutch A from  0 to 100
 */

void
solenoid_set_clutch_a_duty (uint8_t d)
{
	clutch_a_duty = d;
}

/**
 * Set the duty cycle % for Clutch B from  0 to 100
 */

void
solenoid_set_clutch_b_duty (uint8_t d)
{
	clutch_b_duty = d;
}
