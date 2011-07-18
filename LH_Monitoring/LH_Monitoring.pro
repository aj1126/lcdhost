TARGET = LH_Monitoring
TEMPLATE = lib
DEFINES += LH_Monitoring_LIBRARY
QT += xml

include(../Plugins.pri)
include(../cf/cf.pri)

HEADERS += \
    LH_QtPlugin_Monitoring.h \
    ../LH_QtPlugin.h \
    ../LH_QtSetupItem.h \
    ../LH_QtObject.h \
    ../LH_Graph/LH_Graph.h \
    ../LH_Text/LH_Text.h \
    ../LH_Bar/LH_Bar.h \
    ../LH_Dial/LH_Dial.h \
    ../LH_QtInstance.h \
    ../lh_plugin.h \
    LH_QImage/LH_QImage.h \
#    LH_AidaWriter.h \
    LH_RivaWriter.h \
    Sources/LH_SpeedFanTypes.h \
    Sources/LH_SpeedFanData.h \
    Sources/LH_RivaTunerTypes.h \
    Sources/LH_RivaTunerData.h \
    Sources/LH_MonitoringData.h \
    Sources/LH_LogitechData.h \
    Sources/LH_GPUZTypes.h \
    Sources/LH_GPUZData.h \
    Sources/LH_FrapsTypes.h \
    Sources/LH_FrapsData.h \
    Sources/LH_CoreTempTypes.h \
    Sources/LH_CoreTempData.h \
    Sources/LH_ATITrayToolsTypes.h \
    Sources/LH_ATITrayToolsData.h \
    Sources/LH_Aida64Types.h \
    Sources/LH_Aida64Data.h \
    Sources/LH_AfterburnerTypes.h \
    Sources/LH_AfterburnerData.h \
    Sources/LH_MonitoringUI.h \
    Objects/LH_MonitoringText.h \
    Objects/LH_MonitoringImage.h \
    Objects/LH_MonitoringGraph.h \
    Objects/LH_MonitoringDial.h \
    Objects/LH_MonitoringBar.h

SOURCES += \
    LH_QtPlugin_Monitoring.cpp \
    ../LH_QtPlugin.cpp \
    ../LH_QtSetupItem.cpp \
    ../LH_QtObject.cpp \
    ../LH_Graph/LH_Graph.cpp \
    ../LH_Text/LH_Text.cpp \
    ../LH_Bar/LH_Bar.cpp \
    ../LH_Dial/LH_Dial.cpp \
    ../LH_QtInstance.cpp \
    LH_QImage/logo_blob.c \
    LH_QImage/LH_QImage.cpp \
 #   LH_AidaWriter.cpp \
    LH_RivaWriter.cpp \
    Sources/LH_SpeedFanData.cpp \
    Sources/LH_RivaTunerData.cpp \
    Sources/LH_MonitoringData.cpp \
    Sources/LH_LogitechData.cpp \
    Sources/LH_GPUZData.cpp \
    Sources/LH_FrapsData.cpp \
    Sources/LH_CoreTempData.cpp \
    Sources/LH_ATITrayToolsData.cpp \
    Sources/LH_Aida64Data.cpp \
    Sources/LH_AfterburnerData.cpp \
    Sources/LH_MonitoringUI.cpp \
    Objects/LH_MonitoringText.cpp \
    Objects/LH_MonitoringImage.cpp \
    Objects/LH_MonitoringGraph.cpp \
    Objects/LH_MonitoringDial.cpp \
    Objects/LH_MonitoringBar.cpp

RESOURCES +=
