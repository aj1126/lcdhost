/**
  \file     LH_QtPlugin_LCoreReboot.cpp
  \author   Andy Bridges <triscopic@codeleap.co.uk>
  \legalese
    This module is based on original work by Johan Lindh.

    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in
    all copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
    THE SOFTWARE.

  */

#include "LH_QtPlugin_LCoreReboot.h"

#ifdef Q_WS_WIN
#include <windows.h>
#include <winbase.h>
#include <Psapi.h>
#endif

#include <QDebug>
#include <QtCore/QLibrary>
#include <QProcess>
#include <QFileInfo>

LH_PLUGIN(LH_QtPlugin_LCoreReboot) =
    "<?xml version=\"1.0\"?>"
    "<lcdhostplugin>"
      "<id>LCoreReboot</id>"
      "<rev>" STRINGIZE(REVISION) "</rev>"
      "<api>" STRINGIZE(LH_API_MAJOR) "." STRINGIZE(LH_API_MINOR) "</api>"
      "<ver>" STRINGIZE(VERSION) "\nr" STRINGIZE(REVISION) "</ver>"
      "<versionurl>http://www.linkdata.se/lcdhost/version.php?arch=$ARCH</versionurl>"
      "<author>Andy \"Triscopic\" Bridges</author>"
      "<homepageurl><a href=\"http://www.codeleap.co.uk\">CodeLeap</a></homepageurl>"
      "<logourl></logourl>"
      "<shortdesc>"
      "Reboots the Logitech Gaming Software"
      "</shortdesc>"
      "<longdesc>"
        "<p>Reboots the Logitech Gaming Software</p>"
    "</longdesc>"
    "</lcdhostplugin>";

#ifdef Q_WS_WIN
static inline QString GetFullProcessImageName(HANDLE h)
{
    TCHAR szProcessFile[MAX_PATH];
    DWORD nSize = sizeof(szProcessFile)/sizeof(TCHAR);

    // Resolve required symbols from the kernel32.dll
    typedef BOOL (WINAPI *QueryFullProcessImageNameWProtoType)(HANDLE, DWORD, LPWSTR, PDWORD);

    static QueryFullProcessImageNameWProtoType queryFullProcessImageNameW = 0;
    if (!queryFullProcessImageNameW) {
        QLibrary kernel32Lib(QLatin1String("kernel32.dll"), 0);
        if (kernel32Lib.isLoaded() || kernel32Lib.load())
            queryFullProcessImageNameW = (QueryFullProcessImageNameWProtoType)kernel32Lib.resolve("QueryFullProcessImageNameW");
    }
    if (!queryFullProcessImageNameW)
        return "";
    // Read out process
    if ((*queryFullProcessImageNameW)(h, (DWORD)0, szProcessFile, &nSize))
        return QString::fromWCharArray(szProcessFile);
    else
        return "";
}
#endif

const char *LH_QtPlugin_LCoreReboot::userInit()
{
    if( const char *err = LH_QtPlugin::userInit() ) return err;

#ifndef Q_WS_WIN
    return "Not supported on this OS";
#else
    // make sure either LCDMon.exe or LCORE.EXE is running on Windows
    if( !FindWindowA( "Logitech LCD Monitor Window", "LCDMon" ) &&
        !FindWindowA( "QWidget", "LCore" ) )
        return "Logitech drivers are not loaded";

    setup_reboot_ = new LH_Qt_QString(this, "Reboot", "Reboot Logitech Gaming Software", LH_FLAG_NOSAVE | LH_FLAG_NOSINK | LH_FLAG_NOSOURCE | LH_FLAG_HIDETITLE, lh_type_string_button);
    connect(setup_reboot_, SIGNAL(changed()), this, SLOT(rebootLCore()));
#endif
    return 0;
}

void LH_QtPlugin_LCoreReboot::rebootLCore()
{  
#ifdef Q_WS_WIN
    HWND hWnd = FindWindowA( NULL, "LCore" );
    if(hWnd)
    {
        UINT uExitCode = 0;

        DWORD dwProcessId;
        GetWindowThreadProcessId( hWnd, &dwProcessId );
        HANDLE hProcess = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ | PROCESS_TERMINATE, false, dwProcessId);
        if (hProcess != NULL)
        {
            QFileInfo LCore(GetFullProcessImageName(hProcess));
            if(LCore.exists())
            {
                QString filename = LCore.absoluteFilePath();
                if(TerminateProcess(hProcess, uExitCode))
                {
                    qDebug() << "Killed LCore";

                    long result = (long)ShellExecute(0, 0, reinterpret_cast<const WCHAR*>(filename.utf16()), reinterpret_cast<const WCHAR*>(QString("/minimized").utf16()), 0, SW_NORMAL);
                    if(result > 32)
                        qDebug() << "Restarted LCore";
                    else
                        qDebug() << "Unable to restart LCore (Code: " << result << ")";
                }
                else
                    qDebug() << "Unable to kill LCore";

                CloseHandle(hProcess);
            }
        }
    }
#endif
}
