#include <QGuiApplication>
#include <QQmlApplicationEngine>

#include <iostream>
#include <QString>

#include "config.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);

    QQmlApplicationEngine engine;
    QObject::connect(
        &engine,
        &QQmlApplicationEngine::objectCreationFailed,
        &app,
        []() { QCoreApplication::exit(-1); },
        Qt::QueuedConnection);
    engine.loadFromModule("DameGameBoy", "Main");

    std::cout << "Project version: " << VERSION << std::endl;

    return app.exec();
}
