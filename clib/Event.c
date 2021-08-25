#include "Event.h"

void disable_irq();
void enable_irq();

/****************************************************************************************
 * @brief   Set an Event to a signaled state.
 *
 * @param   ev The Event
 *
 * @return  Returns the previous state of the Event.
 ****************************************************************************************/
bool set_event(pevent ev)
{
    disable_irq();
    bool retval = ev->state;
    ev->state = true;
    enable_irq();
    return retval;
}

/****************************************************************************************
 * @brief   Set an Event to a non-signaled state.
 *
 * @param   ev The Event
 *
 * @return  Returns the previous state of the Event.
 ****************************************************************************************/
bool reset_event(pevent ev)
{
    disable_irq();
    bool retval = ev->state;
    ev->state = false;
    enable_irq();
    return retval;
}

/****************************************************************************************
 * @brief   Set an Event to a non-signaled state.
 *
 * @param   ev The Event
 *
 * @retval  None
 ****************************************************************************************/
void clear_event(pevent ev)
{
    ev->state = false;
}

/****************************************************************************************
 * @brief   Check if an event is signaled.
 *
 * @param   ev The Event
 *
 * @return  Returns the state of the Event. If the Event was initialized
 *          as an auto reset Event, then the Event state will be set to 
 *          non-signaled after this function.
 ****************************************************************************************/
bool is_event_set(pevent ev)
{
    disable_irq();
    bool retval = ev->state;
    if  (ev->auto_reset) {
        ev->state = false;
    }
    enable_irq();
    return retval;
}

void disable_irq()
{

}
void enable_irq()
{

}