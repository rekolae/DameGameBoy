#ifndef MEMORY_BANK_CONTROLLER_H
#define MEMORY_BANK_CONTROLLER_H

#include "rom.hh"
#include "ram.hh"

#include <cstdint>

class MemoryBankController
{
public:
    MemoryBankController(Rom* rom, Ram* ram, uint8_t type);
    ~MemoryBankController();

private:
    Rom* rom_;
    Ram* ram_;
    uint8_t type_;
};

#endif // MEMORY_BANK_CONTROLLER_H
