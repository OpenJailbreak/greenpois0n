# -------------------------------------------------
# Project created by QtCreator 2010-09-15T19:37:30
# -------------------------------------------------
TARGET = PoisonJB
TEMPLATE = app
SOURCES += main.cpp \
    poisonmain.cpp
LIBS += libpois0n.a \
    -lusb-1.0 \
    -lcurl \
    -lz
HEADERS += poisonmain.h
FORMS += poisonmain.ui
RESOURCES += resources.qrc
