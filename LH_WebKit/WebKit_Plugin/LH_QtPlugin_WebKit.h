/**
  \author   Johan Lindh <johan@linkdata.se>
  \legalese Copyright (c) 2009-2010 Johan Lindh

  All rights reserved.

  Redistribution and use in source and binary forms, with or without
  modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright
      notice, this list of conditions and the following disclaimer in the
      documentation and/or other materials provided with the distribution.

    * Neither the name of Link Data Stockholm nor the names of its
      contributors may be used to endorse or promote products derived from
      this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.


  */

#ifndef LH_QTPLUGIN_WEBKIT_H
#define LH_QTPLUGIN_WEBKIT_H

#include <QProcess>
#include <QTime>
#include "../../LH_QtPlugin.h"

class LH_QtPlugin_WebKit : public LH_QtPlugin
{
    QTime last_start_;

public:
    LH_QtPlugin_WebKit() : LH_QtPlugin() {}

    const char * lh_name(void) { return "WebKit"; }
    const char * lh_shortdesc(void) { return "Allows HTML and JavaScript."; }
    const char * lh_author(void) { return "Johan \"SirReal\" Lindh"; }
    const char * lh_homepage(void) { return "<a href=\"http://www.linkdata.se/software/lcdhost\">Link Data Stockholm</a>"; }
    const char * lh_longdesc(void)
    {
        return "<a href=\"http://webkit.org\">WebKit</a> integration. Add URL's or HTML instances, complete with JavaScript.";
    }
    const char *lh_load();
    void lh_unload();

    const lh_buildinfo * lh_version( int amaj, int amin )
    {
        static lh_buildinfo buildinfo = LH_STD_BUILDINFO;
        Q_UNUSED( amaj );
        Q_UNUSED( amin );
        Q_ASSERT( amaj == LH_API_MAJOR );
        Q_ASSERT( amin >= LH_API_MINOR );
        return &buildinfo;
    }

    bool startServer();
    bool sendQuit();
};

#endif // LH_QTPLUGIN_WEBKIT_H
