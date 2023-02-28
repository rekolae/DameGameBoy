#include "hw/gameboy.hh"

#include <iostream>
#include <fstream>
#include <ios>


GameBoy::GameBoy(QObject *parent) : QObject{parent}
{
    std::cout << "Initializing DameGameBoy" << std::endl;
    std::cout << " > Initializing device RAM" << std::endl;
    init_ram();

    std::cout << " > Initializing" << std::endl;
    init_cpu();

    std::cout << "Initialization complete!" << std::endl;
}

 GameBoy::~GameBoy()
{
    delete cpu_;
    delete cartridge_;
    delete wram_;
    delete vram_;
    delete oam_;
    delete io_;
    delete hram_;
}

bool GameBoy::load_cartridge(const std::string &path)
{
    std::ifstream rom_stream(path, std::ios::binary);
    if (!rom_stream.good()) {
        return false;
    }

    cartridge_ = new Cartridge(rom_stream);

    return true;
}

void GameBoy::init_ram()
{
    // DMG has  8KiB of working RAM (2 banks * 4KiB) and  8KiB of video RAM (1 bank  * 8KiB)
    // CGB has 32KiB of working RAM (8 banks * 4KiB) and 16KiB of video RAM (2 banks * 8KiB)
    // Allocate the full memory amount on startup, but handle accessed memory amount based
    // on if the emulator is running in original or color mode
    wram_ = new Ram(8, Ram::RAM_BANK_SIZE);
    vram_ = new Ram(2, Ram::RAM_BANK_SIZE);

    // Smaller memory regions that don't use a full bank of RAM
    oam_ =  new Ram(1, 0xA0);
    io_ =   new Ram(1, 0x80);
    hram_ = new Ram(1, 0x7F);
}

void GameBoy::init_cpu()
{
    cpu_ = new Cpu();
}
