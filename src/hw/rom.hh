#ifndef ROM_HH
#define ROM_HH

#include <cstdint>
#include <fstream>
#include <vector>

class Rom
{
    const unsigned int ROM_BANK_SIZE = 0x4000;

public:
    Rom(std::ifstream& rom_stream);

    uint8_t read(uint16_t addr, uint8_t bank = 0);

private:
    using rom_bank = std::vector<uint8_t>;

    std::vector<rom_bank> rom_data_;
    uint8_t bank_count_;
};

#endif // ROM_HH
