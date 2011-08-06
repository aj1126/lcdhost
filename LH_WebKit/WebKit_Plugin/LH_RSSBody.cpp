#include "LH_RSSBody.h"
#include <QDebug>

LH_PLUGIN_CLASS(LH_RSSBody)

lh_class *LH_RSSBody::classInfo()
{
    static lh_class classInfo =
    {
        sizeof(lh_class),
        "Dynamic",
        "DynamicRSSFeedBody",
        "RSS feed (Body)",
        -1, -1,
        
        
    };
    return &classInfo;
}

const char *LH_RSSBody::userInit()
{
    if( const char *err = LH_WebKit::userInit() ) return err;

    rss_ = new LH_RSSInterface(this);
    connect( rss_, SIGNAL(changed()), this, SLOT(setRssItem()) );
    connect( rss_, SIGNAL(begin()), this, SLOT(beginFetch()) );

    setup_template_->setHelp(
                QString(setup_template_->help()).append(
                             "<br><b>\\title</b> : RSS item title "
                             "<br><b>\\author</b> : RSS item author "
                             "<br><b>\\link</b> : RSS item link url "
                             "<br><b>\\pubDate</b> : RSS item published date "
                             "<br><b>\\thumbnail_url</b> : RSS item thumbnail url "
                             "<br><b>\\thumbnail_height</b> : RSS item thumbnail height "
                             "<br><b>\\thumbnail_width</b> : RSS item thumbnail width "
                    ));
    setRssItem();
    return 0;
}

int LH_RSSBody::notify(int code,void* param)
{
    return rss_->notify(code,param) | LH_WebKit::notify(code,param);
}

void LH_RSSBody::setRssItem()
{
    sendRequest( QUrl::fromLocalFile( layoutPath() + "/" ), rss_->item().description );
}

QHash<QString, QString> LH_RSSBody::getTokens()
{
    QHash<QString, QString> tokens = LH_WebKit::getTokens();

    tokens.insert( "title",            rss_->item().title );
    tokens.insert( "author",           rss_->item().author );
    tokens.insert( "link",             rss_->item().link );
    tokens.insert( "pubDate",          rss_->item().pubDate );
    tokens.insert( "thumbnail_url",    rss_->item().thumbnail.url );
    tokens.insert( "thumbnail_height", QString::number(rss_->item().thumbnail.height) );
    tokens.insert( "thumbnail_width",  QString::number(rss_->item().thumbnail.width) );
    return tokens;
}

void LH_RSSBody::beginFetch()
{
    //setText("Loading RSS feed");
}
