TRISCOPIC = LH_Cursor LH_DataViewer LH_Graph LH_Dial LH_Weather LH_TS3
win32: TRISCOPIC += LH_Monitoring LH_NowPlaying

include($$PWD/ConditionalFormatting/ConditionalFormatting.pri)
include($$PWD/json/json.pri)