#pragma once

#include "cocos2d.h"

#include <QMouseEvent>
#include <QWidget>

typedef void(*KEY_PTRFUN)(QKeyEvent *event);

class CCQGLWidget;

NS_CC_BEGIN

class CCQGLView : public GLViewImpl
{
public:
    CCQGLView();
    virtual ~CCQGLView();

    /* override functions */
	virtual bool isOpenGLReady() override;
	virtual void end() override;
	virtual void swapBuffers() override;
	virtual void setFrameSize(float width, float height) override;
	virtual void setIMEKeyboardState(bool bOpen) override;
    virtual void setViewName(const char* pszViewName);

    /* Qt functions */
    void mouseMove(QMouseEvent *event);
    void mousePress(QMouseEvent *event);
    void mouseRelease(QMouseEvent *event);
	void wheel(QWheelEvent *event);
    QWidget * getGLWidget();

	void resize(); // auto adjust frame size according to current window size
	void updateWindowSize();
	void setBgColor(Color4B &color);

	/* get the shared main open gl window */
	static CCQGLView* getInstance();

private:
	virtual bool Create();

    bool			_isInit;
    float			_screenScaleFactor;
	float			_lastWindowHeight;
	Color4F			_bgColor;
    CCQGLWidget*	_window;
};

NS_CC_END

