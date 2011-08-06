/**
  \file     LH_CursorRectangle.h
  \author   Andy Bridges <triscopic@codeleap.co.uk>
  \author   Johan Lindh <johan@linkdata.se>
  \legalese Copyright (c) 2010,2011 Andy Bridges & Johan Lindh
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

 **/

#ifndef LH_CURSORRECTANGLE_H
#define LH_CURSORRECTANGLE_H

#include "../LH_Decor/LH_Rectangle.h"
#include "../LH_Qt_bool.h"
#include "../LH_Qt_QSlider.h"
#include "../LH_Qt_QColor.h"
#include "../LH_Qt_QString.h"
#include "../LH_Qt_QFileInfo.h"

#include "LH_CursorData.h"

#include <QHash>

class LH_CursorRectangle : public LH_Rectangle
{
    Q_OBJECT

    bool updateState();

protected:
    LH_Qt_QString *setup_coordinate_;
    LH_Qt_QStringList *setup_cursor_state_;

    LH_Qt_bool *setup_layout_trigger_;
    LH_Qt_QFileInfo *setup_layout_;

public:
    const char *userInit();

    int polling() ;

    static lh_class *classInfo();

public slots:
    void changeLayoutTrigger();
};

#endif // LH_CURSORRECTANGLE_H
