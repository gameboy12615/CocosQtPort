#include "CCQApplication.h"
#include "CCQGLView.h"

#include <QTimer>

NS_CC_BEGIN

/* sharedApplication pointer */
CCQApplication * CCQApplication::sm_pSharedApplication = nullptr;

CCQApplication::CCQApplication(int argc, char *argv[])
    : QApplication(argc, argv)
    , _timer(nullptr)
{
    _qAnimationInterval = 1.0f / 60.0f * 1000.0f;
    CC_ASSERT(! sm_pSharedApplication);
    sm_pSharedApplication = this;
}

CCQApplication::~CCQApplication()
{
    CC_ASSERT(this == sm_pSharedApplication);
    sm_pSharedApplication = nullptr;
}

int CCQApplication::run()
{
    /* Initialize instance and cocos2d */
    if (! applicationDidFinishLaunching())
    {
        return 0;
    }

    _timer = new QTimer(this);
    connect(_timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));
    _timer->start(_qAnimationInterval);

    return cocos2d::CCQApplication::getInstance()->exec();
}

void CCQApplication::setAnimationInterval(double interval)
{
    _qAnimationInterval = interval * 1000.0f;
    if (_timer)
    {
        _timer->start(_qAnimationInterval);
    }
}

/* static member function */
CCQApplication* CCQApplication::getInstance()
{
    CC_ASSERT(sm_pSharedApplication);
    return sm_pSharedApplication;
}

void CCQApplication::timerUpdate()
{
	Director::getInstance()->mainLoop();
	CCQGLView::getInstance()->updateWindowSize();
}

NS_CC_END

