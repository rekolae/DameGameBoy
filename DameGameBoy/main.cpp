#include "hw/gameboy.hh"

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>

#include <iostream>
#include <vector>

#define VERSION "0.0.0"

int main(int argc, char *argv[])
{
    bool enable_gui = true;
    std::string rom_path = "";

    if (argc > 1) {
        enable_gui = false;
        rom_path = argv[1];
    }

    if (enable_gui) {
        QGuiApplication app(argc, argv);

        QQmlApplicationEngine engine;
        const QUrl url(u"qrc:/DameGameBoy/main.qml"_qs);
        QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                         &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
        engine.rootContext()->setContextProperty("app_version", QString(VERSION));
        engine.load(url);

        return app.exec();
    }

    else {
        std::cout << std::endl << "GUI disabled" << std::endl;
        std::cout << "ROM path: " << rom_path << std::endl << std::endl;
        GameBoy damegameboy = GameBoy();

        if (!damegameboy.load_cartridge(rom_path)) {
            std::cout << "Rom read failed!" << std::endl;
        }

        return 0;
    }
}
