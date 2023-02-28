#include "memory_bank_controller.hh"


MemoryBankController::MemoryBankController(Rom *rom, Ram *ram, uint8_t type) : rom_{rom}, ram_{ram}, type_{type}
{
    if (type_ == 2) {
        ram_ = new Ram(1, 512);
    }
}

MemoryBankController::~MemoryBankController()
{
    if (type_ == 2) {
        delete ram_;
    }
}
