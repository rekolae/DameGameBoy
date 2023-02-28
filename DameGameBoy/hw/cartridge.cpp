#include "cartridge.hh"

#include <iostream>
#include <stdexcept>

#define MBC_INFO_ADDR 0x147
#define RAM_INFO_ADDR 0x149
#define CGB_INFO_ADDR 0x143
#define TITLE_INFO_ADDR 0x134


Cartridge::Cartridge(std::ifstream& rom_stream)
{
    std::cout << std::endl;
    std::cout << "Initializing ROM cartridge" << std::endl;
    std::cout << " > Initializing ROM" << std::endl;
    init_rom(rom_stream);

    std::cout << " > Initializing RAM" << std::endl;
    init_ram();

    std::cout << " > Initializing MBC" << std::endl;
    init_mbc();

    std::cout << " > Checking misc info" << std::endl;
    check_misc();

    std::cout << "Initialization complete!" << std::endl;
}

Cartridge::~Cartridge()
{
    delete mbc_;
    delete external_ram_;
    delete rom_;
}

void Cartridge::init_rom(std::ifstream& rom_stream)
{
    rom_ = new Rom(rom_stream);
}

void Cartridge::init_ram()
{
    uint8_t ram_info = rom_->read(RAM_INFO_ADDR);

    switch(ram_info) {
    case 0x00:
        // No RAM on cartridge
        external_ram_ = nullptr;
        break;
    case 0x02:
        // 1 bank of 8KiB => 8KiB total
        external_ram_ = new Ram(1, Ram::RAM_EXTERNAL_BANK_SIZE);
        break;
    case 0x03:
        // 4 bank of 8KiB => 32KiB total
        external_ram_ = new Ram(4, Ram::RAM_EXTERNAL_BANK_SIZE);
        break;
    case 0x04:
        // 16 bank of 8KiB => 128KiB total
        external_ram_ = new Ram(16, Ram::RAM_EXTERNAL_BANK_SIZE);
        break;
    case 0x05:
        // 8 bank of 8KiB => 64KiB total
        external_ram_ = new Ram(8, Ram::RAM_EXTERNAL_BANK_SIZE);
        break;
    default:
        throw std::runtime_error("Unknown cartridge RAM size");
    }
}

void Cartridge::init_mbc()
{
    uint8_t mbc_info = rom_->read(MBC_INFO_ADDR);

    switch (mbc_info) {
    case 0x00:
        // ROM only => no MBC
        break;

    case 0x01:
        // MBC1, no RAM
        mbc_ = new MemoryBankController(rom_, nullptr, 1);
        break;

    case 0x02:
        // MBC1 with RAM
        mbc_ = new MemoryBankController(rom_, external_ram_, 1);
        break;

    case 0x03:
        // MBC1 with RAM and battery
        mbc_ = new MemoryBankController(rom_, external_ram_, 1);
        battery_ = true;
        break;

    case 0x05:
        // MBC2, no battery
        mbc_ = new MemoryBankController(rom_, nullptr, 2);
        break;

    case 0x06:
        // MBC2 with battery
        mbc_ = new MemoryBankController(rom_, nullptr, 2);
        battery_ = true;
        break;

    case 0x0F:
        // MBC3 with timer and battery
        mbc_ = new MemoryBankController(rom_, nullptr, 3);
        battery_ = true;
        break;

    case 0x10:
        // MBC3 with timer, RAM and battery
        mbc_ = new MemoryBankController(rom_, external_ram_, 3);
        battery_ = true;
        break;

    case 0x11:
        // MBC3, nothing else
        mbc_ = new MemoryBankController(rom_, nullptr, 3);
        break;

    case 0x12:
        // MBC3 with RAM
        mbc_ = new MemoryBankController(rom_, external_ram_, 3);
        break;

    case 0x13:
        // MBC3 with RAM and battery
        mbc_ = new MemoryBankController(rom_, external_ram_, 3);
        battery_ = true;
        break;

    case 0x19:
        // MBC5, nothing else
        mbc_ = new MemoryBankController(rom_, nullptr, 5);
        break;

    case 0x1A:
        // MBC5 with RAM
        mbc_ = new MemoryBankController(rom_, external_ram_, 5);
        break;

    case 0x1B:
        // MBC5 with RAM and battery
        mbc_ = new MemoryBankController(rom_, external_ram_, 5);
        battery_ = true;
        break;

    case 0x1C:
        // MBC5 with rumble (not supported)
        mbc_ = new MemoryBankController(rom_, nullptr, 5);
        break;

    case 0x1D:
        // MBC5 with RAM and rumble (not supported)
        mbc_ = new MemoryBankController(rom_, external_ram_, 5);
        break;

    case 0x1E:
        // MBC5 with RAM, battery and rumble (not supported)
        mbc_ = new MemoryBankController(rom_, external_ram_, 5);
        battery_ = true;
        break;

    default:
        throw std::runtime_error ("Unimplemented memory bank controller");
    }
}

void Cartridge::check_misc()
{
    // Check if CGB cartridge was inserted, we need to only look at the MSB
    uint8_t info = rom_->read(CGB_INFO_ADDR);
    cgb_ = info & 0x80;

    uint8_t max_char_count = 16;
    if (cgb_) {
        max_char_count = 15;
    }

    // Read the title
    for (uint8_t i = 0; i < max_char_count; i++) {
        title_ += rom_->read(TITLE_INFO_ADDR + i);
    }
}


