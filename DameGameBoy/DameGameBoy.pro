QT += quick

SOURCES += \
        hw/cartridge.cpp \
        hw/cpu.cpp \
        hw/gameboy.cpp \
        hw/memory_bank_controller.cpp \
        hw/ram.cpp \
        hw/rom.cpp \
        main.cpp

resources.files = ui/main.qml
resources.prefix = /$${TARGET}
RESOURCES += resources

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Additional import path used to resolve QML modules just for Qt Quick Designer
QML_DESIGNER_IMPORT_PATH =

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    hw/cartridge.hh \
    hw/cpu.hh \
    hw/gameboy.hh \
    hw/memory_bank_controller.hh \
    hw/ram.hh \
    hw/rom.hh
