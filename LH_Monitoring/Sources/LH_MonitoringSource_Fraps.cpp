#include "LH_MonitoringSource_Fraps.h"
#include "LH_MonitoringTypes_Fraps.h"

LH_MonitoringSource_Fraps::LH_MonitoringSource_Fraps(LH_QtObject *parent): LH_MonitoringSource(parent, "Fraps")
{
    fps_ = (SensorDefinition){ "fps", (minmax){ NA_, NA_ }, NA_ };
}

FRAPS_SHARED_DATA *(WINAPI *FrapsSharedData) ();
bool LH_MonitoringSource_Fraps::doUpdate()
{
#ifndef Q_OS_WIN32
    return false;
#else
    HMODULE frapsDLL;
    FRAPS_SHARED_DATA *fsd;
    frapsDLL = GetModuleHandleA("FRAPS32.DLL");
    bool resultVal = false;

    setDataAvailable(frapsDLL != NULL);
    if(!dataAvailable()) // Not running
        pingFraps();
    else {
        FrapsSharedData = (FRAPS_SHARED_DATA *(WINAPI *)()) GetProcAddress(frapsDLL, "FrapsSharedData");

        if (!FrapsSharedData)
        {
            qWarning() << "This version of Fraps is incompatible with LCDHost: Fraps 1.9C or later is required!";
        } else {
            fsd = FrapsSharedData();
            updateValue("Current FPS","","",(int)fsd->currentFPS, fps_);
            updateValue("Game Name","","",fsd->gameName);
            //updateValue("Total Frames","","",(int)fsd->totalFrames);
            //updateValue("Time of Last Frame","","",(int)fsd->timeOfLastFrame);
            resultVal = true;
        }
    }
    return resultVal;
#endif
}

void LH_MonitoringSource_Fraps::pingFraps()
{
#ifndef Q_OS_WIN32
    return;
#else
    if( FindWindowA( "#32770", NULL ) != (HWND)NULL )
    {
        HWND hWndLH = FindWindowA( "QWidget" , "LCDHost" );
        if ( hWndLH != 0 )
        {
            HINSTANCE instance = (HINSTANCE)GetWindowLong(hWndLH, GWL_HINSTANCE);

            HWND hWnd = CreateWindowA("QWidget", "LCDHost",
                                       WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                                       (HWND) NULL,(HMENU) NULL, instance, (LPVOID) NULL);
            DestroyWindow( hWnd );
        }
    }
#endif
}

