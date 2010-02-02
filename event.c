/*
 * event.c
 *
 *  Created on: 2010-02-01
 *      Author: john
 */

typedef enum event_type_t
{
}
event_type_t;

typedef struct event_t
{
	uint16_t time;
	event_type_t type;
	event_t *next;
}
event_t;

static event_t *queue;

void
event_queue_push
(
	event_t *e
)
{
	if (!queue)
	{
		queue = e;
	}
	else
	{
		event_t *cur = queue;

		while (e->time > cur->time && cur->next)
		{
			cur = cur->next;
		}

		if (cur->next)
		{
			e->next = cur;

			if (cur==queue) /// Insert at the beginning of the list
			{
				queue = e;
			}
		}
		else /// Insert at the end of the list
		{
			e->next = null;
			cur->next = e;
		}

	}
}

event_t *
event_queue_pop_head (void)
{
	event_t *e = queue;

	if (!e)
		return 0;		/* Empty List */

	if (e->next)
	{

	}
}
