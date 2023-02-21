#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <iostream>
#include <vector>


int main(int argc, char *argv[])
{
    bool enable_gui = true;
    std::vector<std::string> args(argv, argv+argc);
    for (const std::string &arg : args) {
        if (arg == "--no-gui") {
            enable_gui = false;
            break;
        }
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
        engine.load(url);

        return app.exec();
    } else {
        std::cout << "GUI disabled" << std::endl;
        return 0;
    }
}
