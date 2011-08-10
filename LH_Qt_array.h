#ifndef LH_QT_ARRAY_H
#define LH_QT_ARRAY_H

#include "LH_QtSetupItem.h"

class LH_Qt_array : public LH_QtSetupItem
{
public:
    LH_Qt_array( LH_QtObject *parent, const char *ident, int size = 0, int flags = 0, lh_setup_type subtype = lh_type_array_qint64 )
        : LH_QtSetupItem( parent, ident, subtype, flags )
    {
        resize( size );
        memset( data_array_.data(), 0, data_array_.size()  );
    }

    void resize( int size )
    {
        Q_ASSERT( item_.type & lh_type_array );
        if( item_.type == lh_type_array_qint64 ) size *= sizeof(qint64);
        else if( item_.type == lh_type_array_double ) size *= sizeof(double);
        if( size > 0 )
        {
            data_array_.resize( size );
            item_.data.b.p = data_array_.data();
            item_.data.b.n = data_array_.size();
        }
        else
        {
            data_array_.clear();
            item_.data.b.p = 0;
            item_.data.b.n = 0;
        }
    }

    int size() const
    {
        if( item_.type == lh_type_array_qint64 )
        {
            Q_ASSERT( !(item_.data.b.n % sizeof(qint64)) );
            return item_.data.b.n / sizeof(qint64);
        }
        if( item_.type == lh_type_array_double )
        {
            Q_ASSERT( !(item_.data.b.n % sizeof(double)) );
            return item_.data.b.n / sizeof(double);
        }
        return 0;
    }

    qint64 intMin() const
    {
        if( item_.type == lh_type_array_qint64 ) return item_.param.i.min;
        if( item_.type == lh_type_array_double ) return item_.param.d.min;
        return 0;
    }

    qint64 intMax() const
    {
        if( item_.type == lh_type_array_qint64 ) return item_.param.i.max;
        if( item_.type == lh_type_array_double ) return item_.param.d.max;
        return 0;
    }

    qint64 intAt(int index) const
    {
        Q_ASSERT( index >= 0 );
        Q_ASSERT( index < size() );
        if( item_.type == lh_type_array_qint64 ) return ((qint64*)item_.data.b.p)[index];
        if( item_.type == lh_type_array_double ) return ((double*)item_.data.b.p)[index];
        return 0;
    }

    double doubleMin() const
    {
        if( item_.type == lh_type_array_qint64 ) return item_.param.i.min;
        if( item_.type == lh_type_array_double ) return item_.param.d.min;
        return 0;
    }

    double doubleMax() const
    {
        if( item_.type == lh_type_array_qint64 ) return item_.param.i.max;
        if( item_.type == lh_type_array_double ) return item_.param.d.max;
        return 0;
    }

    double doubleAt(int index) const
    {
        Q_ASSERT( index >= 0 );
        Q_ASSERT( index < size() );
        if( item_.type == lh_type_array_qint64 ) return ((qint64*)item_.data.b.p)[index];
        if( item_.type == lh_type_array_double ) return ((double*)item_.data.b.p)[index];
        return 0;
    }
};

#endif // LH_QT_ARRAY_H
