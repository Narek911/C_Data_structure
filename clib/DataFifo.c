#include <DataFifo.h>
#include "PSP.h"

/**
 * @brief   Set the FIFO to the empty state
 *
 * @param   pFifo Pointer to the FIFO
 */
void FifoInit(DataFifo *pFifo, void *startAddr, int fifoLen, int entryLen)
{
    pFifo->readIdx     = 0;
    pFifo->writeIdx    = 0;
    pFifo->data        = startAddr;
    pFifo->fifoLength  = fifoLen;
    pFifo->entryLength = entryLen;
    pFifo->numEntries  = 0;

    pFifo->initialized = 1;
}

bool FifoReserveEntry(DataFifo *pFifo, void *ppEntry)
{
    bool retval = false;
    const unsigned char* d = ppEntry;

    if(!pFifo->initialized) {
        return retval;
    }

  //  PSPDisableIRQ();
    int writeIdx = pFifo->writeIdx;
    int readIdx  = pFifo->readIdx;
    int entryLen = pFifo->entryLength;
    int fifoLen  = pFifo->fifoLength;

    int full = (writeIdx == readIdx-1) ||
            (writeIdx == fifoLen - 1 && readIdx == 0);

    if (!full) {
        pFifo->data[entryLen * writeIdx++] = *d;
        if (writeIdx == fifoLen) {
            writeIdx = 0;
        }
        pFifo->writeIdx = writeIdx;
        pFifo->numEntries++;
        retval = true;
    }
  //  PSPEnableIRQ();

    return retval;
}

/**
 * @brief   Append an item to the FIFO
 *
 * @param   pFifo  Pointer to the FIFO
 * @param   ppEntry Pointer to reserved FIFO Entry
 *
 * @return  int  -1 if the operation failed (FIFO full)
 */
bool FifoReserveEntry(DataFifo *pFifo, void **ppEntry)
{
    bool retval = false;

    if(!pFifo->initialized) {
        return retval;
    }

    PSPDisableIRQ();
    int writeIdx = pFifo->writeIdx;
    int readIdx  = pFifo->readIdx;
    int entryLen = pFifo->entryLength;
    int fifoLen  = pFifo->fifoLength;

    int full = (writeIdx == readIdx-1) ||
            (writeIdx == fifoLen - 1 && readIdx == 0);

    if (!full) {
        *ppEntry = &pFifo->data[entryLen * writeIdx++];
        if (writeIdx == fifoLen) {
            writeIdx = 0;
        }
        pFifo->writeIdx = writeIdx;
        pFifo->numEntries++;
        retval = true;
    }
    PSPEnableIRQ();

    return retval;
}

/**
 * @brief   Get the pointer to oldest entry in the FIFO.
 *
 * @param   pFifo Pointer to the FIFO
 * @param   ppEntry Pointer to the oldest entry in the FIFO
 *
 * @return  true if entry was returned or false if FIFO empty.
 */
bool FifoGetEntry(DataFifo *pFifo, void **ppEntry)
{
    bool retval = false;

    if(!pFifo->initialized) {
        return retval;
    }

    PSPDisableIRQ();
    int readIdx  = pFifo->readIdx;
    int entryLen = pFifo->entryLength;

    if (readIdx != pFifo->writeIdx) {
        retval = true;
        *ppEntry = &pFifo->data[entryLen * readIdx];
    }
    PSPEnableIRQ();

    return retval;
}

/**
 * @brief   Pop an entry from the given FIFO.
 *
 * @param   pFifo Pointer to the FIFO
 *
 * @return  true if entry was popped or false if FIFO empty.
 */
bool FifoPopEntry(DataFifo *pFifo)
{
    bool retval = false;
    
    if(!pFifo->initialized) {
        return retval;
    }

    PSPDisableIRQ();
    int readIdx = pFifo->readIdx;

    if (readIdx != pFifo->writeIdx) {
        readIdx++;
        if (readIdx == pFifo->fifoLength) {
            readIdx = 0;
        }
        pFifo->readIdx = readIdx;
        pFifo->numEntries--;
        retval = true;
    }
    PSPEnableIRQ();

    return retval;
}

/**
 * @brief   Get number of entries in the FIFO
 *
 * @param   pFifo Pointer to the FIFO
 *
 * @return  Number of entries in the FIFO
 */
int FifoGetNumEntries(DataFifo *pFifo)
{
    return pFifo->numEntries;
}

/**
 * @brief   Reset the given FIFO.
 *
 * @param   pFifo Pointer to the FIFO
 */
void FifoReset(DataFifo *pFifo)
{
    PSPDisableIRQ();
    pFifo->readIdx     = 0;
    pFifo->writeIdx    = 0;
    pFifo->numEntries  = 0;
    PSPEnableIRQ();
}
