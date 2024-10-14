#include "ram.hh"

#include <iostream>

Ram::Ram(unsigned int bank_count, unsigned int size)
{
    // Reserve space for N amount of RAM banks each 4 KiB in size
    ram_data_.reserve(bank_count);
    for (unsigned int i = 0; i < bank_count; i++) {
        ram_data_.push_back(ram_bank(size, 0));
    }
}
