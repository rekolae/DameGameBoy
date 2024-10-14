#ifndef RAM_HH
#define RAM_HH

#include <cstdint>
#include <vector>

class Ram
{
public:
    const static unsigned int RAM_BANK_SIZE          = 0x1000; // 4 KiB - inside the device
    const static unsigned int RAM_EXTERNAL_BANK_SIZE = 0x2000; // 8 KiB - inside the cartridge

    Ram(unsigned int bank_count, unsigned int size = RAM_BANK_SIZE);

private:
    using ram_bank = std::vector<uint8_t>;

    std::vector<ram_bank> ram_data_;
};

#endif // RAM_HH
