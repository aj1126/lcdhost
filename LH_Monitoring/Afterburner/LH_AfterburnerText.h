#ifndef LH_AFTERBURNERTEXT_H
#define LH_AFTERBURNERTEXT_H

#include "LH_AfterburnerData.h"
#include "../_Templates/LH_MonitoringText.h"

class LH_AfterburnerText : public LH_MonitoringText
{
    Q_OBJECT
public:
    LH_AfterburnerText();
    static lh_class *classInfo();
};

#endif // LH_AFTERBURNERTEXT_H
