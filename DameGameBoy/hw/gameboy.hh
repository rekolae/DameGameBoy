#ifndef GAMEBOY_HH
#define GAMEBOY_HH

#include "hw/cpu.hh"
#include "hw/cartridge.hh"
#include "hw/ram.hh"
#include "hw/rom.hh"

#include <QObject>

class GameBoy : public QObject
{
    Q_OBJECT

public:
    explicit GameBoy(QObject *parent = nullptr);
    ~GameBoy();

    bool load_cartridge(const std::string &path);


signals:


private:
    Cpu* cpu_;

    Cartridge* cartridge_;

    Ram* wram_;
    Ram* vram_;
    Ram* oam_;
    Ram* io_;
    Ram* hram_;

    void init_ram();
    void init_cpu();
};

#endif // GAMEBOY_HH
