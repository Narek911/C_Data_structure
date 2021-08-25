#ifndef __DATALIFO_H__
#define __DATALIFO_H__

#include <stdbool.h>
#include <stddef.h>
#include <string.h>

//! Character FIFO, typically used to buffer UART data.
typedef struct {
    int  initialized;    //!< LIFO initialized flag
    int  top_index;      //!< LIFO top index 
    int  size;           //!< LIFO length
    unsigned char *data; //!< LIFO data bytes
} data_lifo;

void lifo_init(data_lifo *pLifo, void *start_addr, int lifo_len);
int is_lifo_full(data_lifo *p_lifo);
int is_lifo_empty(data_lifo *p_lifo);
int lifo_get_free(data_lifo *p_lifo);
void lifo_write(data_lifo *p_lifo, const void* data, size_t btw);
void lifo_read(data_lifo *p_lifo, void* data, size_t btw);
int lifo_pop(data_lifo *p_lifo);
int lifo_peek(data_lifo *p_lifo);
int lifo_free(data_lifo *p_lifo);

#endif  /* __DATALIFO_H__ */