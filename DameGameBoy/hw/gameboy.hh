#ifndef GAMEBOY_HH
#define GAMEBOY_HH

#include <QObject>

class GameBoy : public QObject
{
    Q_OBJECT

public:
    explicit GameBoy(QObject *parent = nullptr);

signals:

};

#endif // GAMEBOY_HH
