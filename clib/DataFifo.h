#ifndef __DATAFIFO_H__
#define __DATAFIFO_H__

#include <stdbool.h>

//! Character FIFO, typically used to buffer UART data.
typedef struct {
    int  initialized;    //!< FIFO initialized flag
    int  readIdx;        //!< Index of next byte to read from FIFO
    int  writeIdx;       //!< Index of next byte to write to FIFO
    int  entryLength;    //!< Single entry length
    int  fifoLength;     //!< FIFO length
    int  numEntries;     //!< Number of FIFO entries
    unsigned char *data; //!< FIFO data bytes
} DataFifo;

void FifoInit(DataFifo *pFifo, void *startAddr, int fifoLen, int entryLen);
bool FifoReserveEntry(DataFifo *pFifo, void **ppEntry);
bool FifoGetEntry(DataFifo *pFifo, void **ppEntry);
bool FifoPopEntry(DataFifo *pFifo);
int  FifoGetNumEntries(DataFifo *pFifo);
void FifoReset(DataFifo *pFifo);

#endif  /* __DATAFIFO_H__ */
