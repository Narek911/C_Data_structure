#ifndef __EVENT_H__
#define __EVENT_H__

#include <stdint.h>
#include <stdbool.h>

/* Type for system event signals */
typedef struct
{
    bool  state;
    bool  auto_reset;
} event, *pevent;

bool set_event(pevent ev);
bool reset_event(pevent ev);
void clear_event(pevent ev);
bool is_event_set(pevent ev);

#define DEFINE_EVENT( name, auto_reset, state )      \
    static event s_##name = { state, auto_reset };   \
    pevent name = & s_##name;

#endif /* __EVENT_H__ */
