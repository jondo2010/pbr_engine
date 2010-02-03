/*
 * event_handler.h
 *
 *  Created on: 2010-02-01
 *  Author: John Hughes <jondo2010@gmail.com>
 */

#ifndef EVENT_HANDLER_H_
#define EVENT_HANDLER_H_

/**
 * States for the event handler to be in
 */

typedef enum event_handler_state_t
{
	free,
	shifting_up,
	shifting_down,
	finding_neutral
}
event_handler_state_t;

/**
 * Event type definitions for upshift events
 */

typedef enum upshift_event_type_t
{
	shiftcut_high,
	shiftcut_low,
	upshift_high,
	upshift_low
}
upshift_event_type_t;

typedef enum downshift_event_type_t
{
	downshift_release,
	clutch_disengaged,
	downshift_low
}
downshift_event_type_t;

typedef enum downshift_state_t
{
	shifting,
	waiting_for_shift,
	waiting_for_revmatch
}
downshift_state_t;

void
event_handler_upshift
(
	upshift_event_type_t event_type
);

void
event_handler_downshift
(
	downshift_event_type_t event_type
);

#endif /* EVENT_HANDLER_H_ */
