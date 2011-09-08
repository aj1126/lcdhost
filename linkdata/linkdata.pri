#
# linkdata.pri
#
# This defines the commonly used values, paths and actions
# for LCDHost plugins. It also supports the qmake CONFIG
# values 'hidapi' and 'libusb', which will pull in those
# libraries, respectively.
#
# Johan Lindh <johan@linkdata.se> is the sole maintainer of this
# file and all the files in this directory and subdirectories.
# Do *NOT* commit here unless you have his explicit approval to do so.
#
# If you find a bug or need a feature or change, submit an issue
# at "http://code.google.com/p/lcdhost/issues/list" and label it
# "linkdata", carefully describing the issue and how to reproduce it.
#

isEmpty(TARGET): error("TARGET must be set")
isEmpty(TEMPLATE): error("TEMPLATE must be set")

LH_LINKDATA_DIR = $$PWD
LH_PLUGINS_DIR = $$LH_LINKDATA_DIR/..
LH_ROOT_DIR = $$LH_PLUGINS_DIR/..

# Default destination directories depending on platform and debug/release
CONFIG(debug, debug|release):RELDEB = Debug
else:RELDEB = Release
win32 {
    LCDHOST_PLUGINS = $$LH_ROOT_DIR/$$RELDEB/plugins
    LCDHOST_BINARIES = $$LH_ROOT_DIR/$$RELDEB
}
macx {
    LCDHOST_PLUGINS = $$LH_ROOT_DIR/$$RELDEB/LCDHost.app/Contents/PlugIns
    LCDHOST_BINARIES = $$LH_ROOT_DIR/$$RELDEB/LCDHost.app/Contents/MacOS
}
unix:!macx {
    LCDHOST_PLUGINS = $$LH_ROOT_DIR/$$RELDEB/plugins
    LCDHOST_BINARIES = $$LH_ROOT_DIR/$$RELDEB
}

# The core files always go in
INCLUDEPATH += $$LH_LINKDATA_DIR
HEADERS += $$LH_LINKDATA_DIR/lh_plugin.h
SOURCES += $$LH_LINKDATA_DIR/lh_plugin.c

# Qt support files
LH_QT_SUPPORT_DIR = $$LH_LINKDATA_DIR/QtSupport

LH_QT_SUPPORT_HEADERS = \
    $$LH_QT_SUPPORT_DIR/LH_QVariant.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_array.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_array_double.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_array_int.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_array_string.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_bool.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_double.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_html.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_InputState.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_InputValue.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_int.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QColor.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QFileInfo.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QFont.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QImage.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QProgressBar.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QSlider.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QString.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QStringList.h \
    $$LH_QT_SUPPORT_DIR/LH_Qt_QTextEdit.h \
    $$LH_QT_SUPPORT_DIR/LH_QtBuffer.h \
    $$LH_QT_SUPPORT_DIR/LH_QtCPU.h \
    $$LH_QT_SUPPORT_DIR/LH_QtInputDevice.h \
    $$LH_QT_SUPPORT_DIR/LH_QtInstance.h \
    $$LH_QT_SUPPORT_DIR/LH_QtLayoutClass.h \
    $$LH_QT_SUPPORT_DIR/LH_QtMemory.h \
    $$LH_QT_SUPPORT_DIR/LH_QtNetwork.h \
    $$LH_QT_SUPPORT_DIR/LH_QtObject.h \
    $$LH_QT_SUPPORT_DIR/LH_QtOutputDevice.h \
    $$LH_QT_SUPPORT_DIR/LH_QtPlugin.h \
    $$LH_QT_SUPPORT_DIR/LH_QtSetupItem.h \
    $$LH_QT_SUPPORT_DIR/LH_QtVariant.h

LH_QT_SUPPORT_SOURCES = \
    $$LH_QT_SUPPORT_DIR/LH_QVariant.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtBuffer.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtCPU.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtInputDevice.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtInstance.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtLayoutClass.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtMemory.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtNetwork.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtObject.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtOutputDevice.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtPlugin.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtSetupItem.cpp \
    $$LH_QT_SUPPORT_DIR/LH_QtVariant.cpp

contains( QT, core ) {
    INCLUDEPATH += $$LH_QT_SUPPORT_DIR
    contains( TEMPLATE, lib ) {
        HEADERS += $$LH_QT_SUPPORT_HEADERS
        SOURCES += $$LH_QT_SUPPORT_SOURCES
    } else {
        HEADERS += $$LH_QT_SUPPORT_DIR/LH_QVariant.h
        SOURCES += $$LH_QT_SUPPORT_DIR/LH_QVariant.cpp
    }
}

contains( TEMPLATE, lib ): DESTDIR = $$LCDHOST_PLUGINS
contains( TEMPLATE, app ): DESTDIR = $$LCDHOST_BINARIES

# Changeset and revision defines from mercurial
CHANGESET_REVISION = $$system(hg log -l 1 --template {node}/{rev} $$_PRO_FILE_PWD_)
!isEmpty(CHANGESET_REVISION) {
    CHANGESET = $$section(CHANGESET_REVISION,"/",0,0)
    REVISION = $$section(CHANGESET_REVISION,"/",1,1)
    isEmpty( REVISION ): REVISION = 0
    DEFINES += CHANGESET=\"\\\"$$CHANGESET\\\"\"
    DEFINES += REVISION=$$REVISION
} else {
    message("can't get revision data for" $$_PRO_FILE_PWD_)
}

# Check for hidapi in CONFIG
hidapi {
    # We don't want warnings from 3rd party C code
    QMAKE_CFLAGS_WARN_ON = -w

    LH_HIDAPI_DIR = $$LH_LINKDATA_DIR/hidapi
    INCLUDEPATH += $$LH_HIDAPI_DIR
    HEADERS += $$LH_HIDAPI_DIR/hidapi.h

    win32 {
            SOURCES += $$LH_HIDAPI_DIR/win/hid.cpp
            LIBS += -lsetupapi
    }

    macx {
            SOURCES += $$LH_HIDAPI_DIR/osx/hid.c
            LIBS += -framework CoreFoundation -framework IOKit
    }

    unix:!macx {
            SOURCES += $$LH_HIDAPI_DIR/lin/hid.c
            LIBS += -ludev
    }
}

# Check for libusb in CONFIG
libusb {
    # We don't want warnings from 3rd party C code
    QMAKE_CFLAGS_WARN_ON = -w

    LH_LIBUSB_DIR = $$LH_LINKDATA_DIR/libusb
    INCLUDEPATH += $$LH_LIBUSB_DIR
    HEADERS += $$LH_LIBUSB_DIR/libusb.h
    SOURCES += $$LH_LIBUSB_DIR/core.c $$LH_LIBUSB_DIR/descriptor.c $$LH_LIBUSB_DIR/io.c $$LH_LIBUSB_DIR/sync.c

    win32 {
            DEFINES += OS_WINDOWS
            SOURCES += \
                $$LH_LIBUSB_DIR/os/windows_usb.c \
                $$LH_LIBUSB_DIR/os/threads_windows.c \
                $$LH_LIBUSB_DIR/os/poll_windows.c
            LIBS += -lole32 -lsetupapi -lcfgmgr32
    }

    macx {
            DEFINES += OS_DARWIN THREADS_POSIX HAVE_SYS_TIME_H HAVE_POLL_H
            SOURCES += $$LH_LIBUSB_DIR/os/darwin_usb.c
            LIBS += -framework CoreFoundation -framework IOKit
    }

    unix:!macx {
            DEFINES += OS_LINUX THREADS_POSIX HAVE_SYS_TIME_H HAVE_POLL_H
            SOURCES += $$LH_LIBUSB_DIR/os/linux_usbfs.c
    }
}

# Sign plugins
#
# Define SIGNATURE_PRIVATE_FILE to point to the file 
# containing the private key data (store it outside the 
# repository to be on the safe side) and 
# SIGNATURE_PUBLIC_URL to the URL where the public key
# can be downloaded by users.
#
# Both the private key file and the public key file can
# be generated by SignPlugin, just start it without
# parameters and you'll get a dialog.
#
# If you use the '-o' switch to SignPlugin, it will
# operate in 'offline' mode, and won't check that the
# public key is actually at that URL or that it matches
# the private key data. I don't recommend this until
# you're sure everything is in place and checks out.
#
# Note that this does nothing at all if the
# target being built is not a library or
# SIGNATURE_PRIVATE_FILE isn't set.
#
contains( TEMPLATE, lib ) {
    isEmpty(SIGNATURE_PRIVATE_FILE):exists($$LH_ROOT_DIR/lcdhost-private.pem) {
            SIGNATURE_SWITCHES = -o
            SIGNATURE_PRIVATE_FILE = $$LH_ROOT_DIR/lcdhost-private.pem
            SIGNATURE_PUBLIC_URL = http://www.linkdata.se/downloads/software/lcdhost/lcdhost-public.pem
    }

    isEmpty(SIGNATURE_PRIVATE_FILE):exists($$LH_ROOT_DIR/triscopic-private.pem) {
            SIGNATURE_SWITCHES =
            SIGNATURE_PRIVATE_FILE = $$LH_ROOT_DIR/triscopic-private.pem
            SIGNATURE_PUBLIC_URL = http://www.codeleap.co.uk/lcdhost/public-key
    }

    !isEmpty(SIGNATURE_PRIVATE_FILE) {
        exists($$SIGNATURE_PRIVATE_FILE) {
            QMAKE_POST_LINK = \
                $$LCDHOST_BINARIES/SignPlugin -c $$SIGNATURE_SWITCHES \
                $$SIGNATURE_PRIVATE_FILE \
                $$SIGNATURE_PUBLIC_URL \
                $$DESTDIR/$$TARGET
        } else {
            error("private key file" $$SIGNATURE_PRIVATE_FILE "not found")
        }
    }
}