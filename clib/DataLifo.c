#include "DataLifo.h"
#include "../util.h"
#include <stdio.h>

void disable_irq();
void enable_irq();

/**
 * @brief  Initialize the LIFO structure
 *
 * @param  p_lifo     Pointer to the LIFO
 * @param  start_addr Start address of the reserved buffer
 * @param  lifo_len   The lifo stack size
 * 
 * @retval None
 */
void lifo_init(data_lifo *p_lifo, void *start_addr, int lifo_len)
{
    disable_irq();
    p_lifo->data       = start_addr;
    p_lifo->size       = lifo_len;
    p_lifo->top_index  = -1;

    p_lifo->initialized = 1;
    enable_irq();
}

/**
 * @brief   Stack is full when top is equal to the last index (overflow condition)
 *
 * @param   p_lifo Pointer to the LIFO
 */
int is_lifo_full(data_lifo *p_lifo) 
{
    return p_lifo->top_index == p_lifo->size - 1;
}

/**
 *  @brief  Empty when top is -1 (end of flow condition)
 *  
 *  @param  p_lifo Pointer to the LIFO
 */
int is_lifo_empty(data_lifo *p_lifo)
{
    return p_lifo->top_index == -1;
}

/**
 *  @brief  Get available size in buffer for write operation
 *  
 *  @param  p_lifo Pointer to the LIFO
 */
int lifo_get_free(data_lifo *p_lifo)
{
    return p_lifo->size - p_lifo->top_index - 1;
}

/**
* @brief Write data to the stack.
*
* @param p_lifo Pointer to the LIFO
* @param data   Pointer to data to write into buffer
* @param btw    Number of bytes to write
*
* @retval None
*/
void lifo_write(data_lifo *p_lifo, const void* data, size_t btw) 
{
    /* Check if no overflow happen */
    if(is_lifo_full(p_lifo)) {
        return;
    }

    /* Check that the stack can hold the buffer */
    if (btw > lifo_get_free(p_lifo)) {
        return;
    }

    disable_irq();

   /* Reverses the bytes for endianes control */
    REVERSE_BYTE_ARRAY( data, btw, 0 ); 

    /* Copy to the stack */
    memcpy(&p_lifo->data[++p_lifo->top_index], data, btw);

    /* Increase the pointer */
    p_lifo->top_index += btw;

    enable_irq();
}

/**
* @brief read data to the stack.
*
* @param p_lifo Pointer to the LIFO
* @param data   Pointer to data to read into buffer
* @param btw    Number of bytes to read
*
* @retval None
*/
void lifo_read(data_lifo *p_lifo, void* data, size_t btw) 
{
    /* Check if no end of flow happen */
    if(is_lifo_empty(p_lifo)) {
        return;
    }

    /* Check that the stack can hold the buffer */
    if (btw > lifo_get_free(p_lifo)) {
        return;
    }

    disable_irq();

    /* Force reverse the buffer */
    REVERSE_BYTE_ARRAY( &p_lifo->data[p_lifo->top_index - btw], btw, 1 ); 

    /* Copy the reversed buffer to the stack */
    memcpy(data, &p_lifo->data[p_lifo->top_index - btw], btw);

    /* Restore the buffer */
    REVERSE_BYTE_ARRAY( &p_lifo->data[p_lifo->top_index - btw], btw, 1 );

    /* Reverses the bytes for endianes control */
    REVERSE_BYTE_ARRAY( data, btw, 0 ); 

    /* Decrease index iterator */
    p_lifo->top_index -= (btw + 1);

    enable_irq();
}

/**
* @brief To get the top element 
*
* @param p_lifo Pointer to the LIFO
*/
int lifo_pop(data_lifo *p_lifo) 
{
    /* Check if no end of flow happen */
    if(is_lifo_empty(p_lifo)) {
        return -1;
    }

    return p_lifo->data[p_lifo->top_index--];
}

/**
* @brief To get the top element 
*
* @param p_lifo Pointer to the LIFO
*/
int lifo_peek(data_lifo *p_lifo) 
{
    /* Check if no end of flow happen */
    if(is_lifo_empty(p_lifo)) {
        return -1;
    }

    return p_lifo->data[p_lifo->top_index];
}

int lifo_free(data_lifo *p_lifo) 
{
    disable_irq();
    memset(p_lifo, 0, sizeof(data_lifo));
    p_lifo->top_index    = -1;
    p_lifo->initialized  = 0;
    enable_irq();
}

void disable_irq()
{

}
void enable_irq()
{

}