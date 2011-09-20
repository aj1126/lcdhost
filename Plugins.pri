#
# Plugins.pri
#
# This plugin include file sets things up the way
# I want them when I build LCDHost. It may or may
# not work for you.
#
# In particular, the automated signing using
# QMAKE_POST_LINK need to use your own keys
# and URL's if you want to use it.
#

CONFIG(debug, debug|release):RELDEB = Debug
else:RELDEB = Release

CHANGESET_REVISION = $$system(hg log -l 1 --template {node}/{rev} $$PWD/$$TARGET)
CHANGESET = $$section(CHANGESET_REVISION,"/",0,0)
REVISION = $$section(CHANGESET_REVISION,"/",1,1)
isEmpty( REVISION ): REVISION = 0
DEFINES += CHANGESET=\"\\\"$$CHANGESET\\\"\"
DEFINES += REVISION=$$REVISION

win32 {
    LCDHOST_PLUGINS = $$PWD/../$$RELDEB/plugins
    LCDHOST_BINARIES = $$PWD/../$$RELDEB
}

macx {
    LCDHOST_PLUGINS = $$PWD/../$$RELDEB/LCDHost.app/Contents/PlugIns
    LCDHOST_BINARIES = $$PWD/../$$RELDEB/LCDHost.app/Contents/MacOS
}

unix:!macx {
    LCDHOST_PLUGINS = $$PWD/../$$RELDEB/plugins
    LCDHOST_BINARIES = $$PWD/../$$RELDEB
}

DESTDIR = $$LCDHOST_PLUGINS

QTSUPPORT = $$PWD/QtSupport

INCLUDEPATH += \
    $$PWD \
    $$QTSUPPORT

PLUGIN_SOURCES = \
    $$PWD/lh_plugin.c \
    $$QTSUPPORT/LH_QtObject.cpp \
    $$QTSUPPORT/LH_QtPlugin.cpp \
    $$QTSUPPORT/LH_QtInstance.cpp \
    $$QTSUPPORT/LH_QtSetupItem.cpp

PLUGIN_HEADERS += \
    $$PWD/lh_plugin.h \
    $$QTSUPPORT/LH_QtObject.h \
    $$QTSUPPORT/LH_QtPlugin.h \
    $$QTSUPPORT/LH_QtInstance.h \
    $$QTSUPPORT/LH_QtSetupItem.h

systemstats {
    PLUGIN_HEADERS += \
        $$QTSUPPORT/LH_QtCPU.h  \
        $$QTSUPPORT/LH_QtNetwork.h

    PLUGIN_SOURCES += \
        $$QTSUPPORT/LH_QtCPU.cpp \
        $$QTSUPPORT/LH_QtNetwork.cpp
}

device {
    PLUGIN_HEADERS += \
        $$QTSUPPORT/LH_QtDevice.h

    PLUGIN_SOURCES += \
        $$QTSUPPORT/LH_QtDevice.cpp
}

cf {
    include(codeleap/ConditionalFormatting/ConditionalFormatting.pri)
}

translator {
    include(codeleap/GoogleTranslator/GoogleTranslator.pri)
}

contains( TEMPLATE, lib ) {
    exists($$PWD/../lcdhost-private.pem) {
        QMAKE_POST_LINK = \
            $$LCDHOST_BINARIES/SignPlugin -c -o \
            $$PWD/../lcdhost-private.pem \
            http://www.linkdata.se/downloads/software/lcdhost/lcdhost-public.pem \
            $$DESTDIR/$$TARGET
    }
    exists($$PWD/../triscopic-private.pem) {
        QMAKE_POST_LINK = \
            $$LCDHOST_BINARIES/SignPlugin -c -o \
            $$PWD/../triscopic-private.pem \
            http://www.codeleap.co.uk/lcdhost/public-key \
            $$DESTDIR/$$TARGET
    }
}

