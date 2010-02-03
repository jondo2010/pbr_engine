/*
 * event_handler.c - Actually implements sequencer state logic.
 * Event handlers are called from the main() loop when their
 * events become current, or sometimes from other ISRs.
 *
 * Created on: 2010-02-01
 * Author: John Hughes <jondo2010@gmail.com>
 */

#include "event_handler.h"
#include "engine.h"

static event_handler_state_t handler_state;

void
event_handler_upshift
(
	upshift_event_type_t event_type
)
{
	if (handler_state == free)
	{
		handler_state = shifting_up;
		engine_set_shiftcut_state (1);

		// schedule "power shift cut low" for t+t_shift_cut
		// schedule "up shift high" t+t_settle_up
	}
	else if (handler_state == shifting_up)
	{
		if (event_type == shiftcut_low)
		{
			engine_set_shiftcut_state (0);
			// if t_shift_cut > t_shift
			handler_state = free;
		}
		else if (event_type == upshift_high)
		{
			engine_set_upshift_state (1);
			//		schedule "up shift low" t+t_shift <- Done with feedback from gear position.
		}
		else if (event_type == upshift_low)
		{
			engine_set_upshift_state (0);
			// if t_shift > t_shift_cut
			handler_state = free;
		}
	}
}

void
event_handler_downshift
(
	downshift_event_type_t event_type
)
{
	static downshift_state_t downshift_state;

	if (handler_state == free)
	{
		handler_state = shifting_down;
		downshift_state = shifting;
		// set clutch position disengaged
	}
	else if (handler_state == shifting_down)
	{
		if (event_type == clutch_disengaged)
		{
			engine_set_downshift_state (1);
			// schedule "down shift low" t+t_shift <- Done with feedback from gear position.
		}
		else if (event_type == downshift_low)
		{
			engine_set_downshift_state (0);
			if (downshift_state == shifting)
			{
				downshift_state = waiting_for_revmatch;		/* 1 */
			}
			else
			{
				// set clutch position engaged
			}
		}
		else if (event_type == downshift_release)
		{
			if (downshift_state == shifting)
			{
				downshift_state = waiting_for_shift;		/* 2 */
			}
			else
			{
				// set clutch position engaged
			}
		}
	}
}

//
//	1.	The shift has completed, waiting for driver to release
//		paddle before re-engaging the clutch.
//
//	2.	Driver has released paddle, waiting for shift to complete
//		before re-engaging the clutch.
//

void
event_handler_neutral_find
(
	downshift_event_type_t event_type
)
{
	if (handler_state == free)
	{
		handler_state = finding_neutral;
		// set clutch position disengaged
	}
	else if (handler_state == finding_neutral)
	{
		if (event_type == clutch_disengaged)
		{
			engine_set_downshift_state (1);
			// schedule "down shift low" t+t_shift <- Done with feedback from gear position.
		}
	}
}
