#include "rom.hh"

#include <iostream>
#include <ios>
#include <stdexcept>

Rom::Rom(std::ifstream& rom_stream)
{
    rom_bank bank(ROM_BANK_SIZE);

    while(rom_stream.read(reinterpret_cast<char*>(bank.data()), ROM_BANK_SIZE)) {
        rom_data_.push_back(bank);
    }

    rom_stream.close();

    bank_count_ = rom_data_.size();
}

uint8_t Rom::read(uint16_t addr, uint8_t bank)
{
    if (addr > ROM_BANK_SIZE) {
        throw std::out_of_range("Invalid address");
    }

    else if (bank > bank_count_) {
        throw std::out_of_range("Invalid ROM bank");
    }

    return rom_data_[bank][addr];
}
