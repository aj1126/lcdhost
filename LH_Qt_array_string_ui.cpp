#include "LH_Qt_array_string_ui.h"

void LH_Qt_array_string_ui::init(lh_setup_type ui_type, int uiFlags )
{
    if(ui_type == lh_type_string)
        ui_ = new LH_Qt_QString(parent(), QString("%1__ui__").arg(ident()).toUtf8(),"", uiFlags );
    if(ui_type == lh_type_string_filename)
        ui_ = new LH_Qt_QFileInfo(parent(), QString("%1__ui__").arg(ident()).toUtf8(),QFileInfo(), uiFlags );

    Q_ASSERT(ui_ != NULL);

    if( ui_ )
    {
        ui_->setTitle(ident());
        connect(ui_, SIGNAL(changed()), this, SLOT(uiValueChanged()));
    }

    connect(this, SIGNAL(changed()), this, SLOT(arrayValuesChanged()));
    connect(this, SIGNAL(set()), this, SLOT(arrayValuesChanged()));
}

void LH_Qt_array_string_ui::setEditIndex(int index)
{
    uiIndex_ = index;
    arrayValuesChanged();
}

void LH_Qt_array_string_ui::setFlag(int f, bool state)
{
    if(f != LH_FLAG_HIDDEN)
        LH_Qt_array_string::setFlag(f, state);
    ui_->setFlag(f, state);
}

void LH_Qt_array_string_ui::setHelp(const QString& s)
{
    LH_Qt_array_string::setHelp(s);
    ui_->setHelp(s);
}

void LH_Qt_array_string_ui::setTitle(const char *s)
{
    LH_Qt_array_string::setTitle(s);
    ui_->setTitle(s);
}

void LH_Qt_array_string_ui::setTitle( const QString &s )
{
    LH_Qt_array_string::setTitle(s);
    ui_->setTitle(s);
}

void LH_Qt_array_string_ui::arrayValuesChanged()
{
    if( uiIndex_>=0 && uiIndex_ < size() )
    {
        ui_->blockSignals(true);
        ui_->setValue( at(uiIndex_) );
        ui_->blockSignals(false);
    }
}

void LH_Qt_array_string_ui::uiValueChanged()
{
    if( uiIndex_>=0 && uiIndex_<size() )
    {
        setAt( uiIndex_, ui_->value() );
    }
}