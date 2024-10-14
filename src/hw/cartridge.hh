#ifndef CARTRIDGE_HH
#define CARTRIDGE_HH

#include "hw/memory_bank_controller.hh"
#include "hw/ram.hh"
#include "hw/rom.hh"

#include <fstream>

class Cartridge
{
public:
    Cartridge(std::ifstream& rom_stream);
    ~Cartridge();

private:
    MemoryBankController* mbc_;
    Ram* external_ram_;
    Rom* rom_;

    bool cgb_;
    bool battery_;
    std::string title_;

    void init_rom(std::ifstream& rom_stream);
    void init_ram();
    void init_mbc();
    void check_misc();
};

#endif // CARTRIDGE_HH
