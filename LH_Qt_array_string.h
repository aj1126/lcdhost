#ifndef LH_QT_ARRAY_STRING_H
#define LH_QT_ARRAY_STRING_H

#include <QString>
#include <QStringList>
#include "LH_Qt_array.h"

class LH_Qt_array_string : public LH_Qt_array
{
    QStringList list_;

public:
    LH_Qt_array_string( LH_QtObject *parent, const char *ident, const QStringList& value = QStringList(), int flags = 0 )
        : LH_Qt_array( parent, ident, flags, lh_type_array_string )
    {
        copy( value );
    }

    void setup_change()
    {
        if( item_.data.b.p )
            list_ = QString::fromUtf8( (const char*) item_.data.b.p ).split(QChar(0));
        else
            list_.clear();
        LH_QtSetupItem::setup_change();
    }

    void resize(int size, const QString& defaultValue = QString() )
    {
        if( list_.size() != size )
        {
            while( list_.size() > size ) list_.removeLast();
            while( list_.size() < size ) list_.append(defaultValue);
            setArray(list_.join(QChar(0)).toUtf8());
            refreshData();
        }
    }

    int size() const
    {
        return list_.size();
    }

    QString at( int index, const QString& defaultValue = QString() ) const
    {
        if( index < 0 || index >= list_.size() ) return defaultValue;
        return list_.at(index);
    }

    void setAt( int index, const QString& value )
    {
        Q_ASSERT( index >= 0 );
        Q_ASSERT( index < list_.size() );
        if( index >= 0 && index < list_.size() )
        {
            list_[index] = value;
            setArray(list_.join(QChar(0)).toUtf8());
            refreshData();
            emit set();
        }
    }

    void copy( const QStringList& other )
    {
        list_ = other;
        setArray(list_.join(QChar(0)).toUtf8());
        refreshData();
    }

    QStringList& list()
    {
        return list_;
    }

    qint64 intMin() const { return 0; }
    qint64 intMax() const { return 0; }
    qint64 intAt(int index) const { return list_.at(index).toInt(); }
    double doubleMin() const { return 0.0; }
    double doubleMax() const { return 0.0; }
    double doubleAt(int index) const { return list_.at(index).toDouble(); }
    QString stringAt(int index) const { return at(index); }
};

#endif // LH_QT_ARRAY_STRING_H
