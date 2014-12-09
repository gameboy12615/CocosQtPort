CocosQtPort
===========

This is porting code, which prot cocos2d-x3.3 to QT5.3.
It is useful for coding a game editor.

How to use?
1. copy CocoQtPort directory to your Classes folder. 
2. change AppDelegate to inherit form cocos2d::CCQApplication. add a member, like:
class  AppDelegate : private cocos2d::CCQApplication
{
public:
	AppDelegate(int argc, char *argv[]) : cocos2d::CCQApplication(argc, argv) {};
    virtual ~AppDelegate();
......
protected:
	CCGEditor _mainWindow;  // CCGEditor is the MainWindow class which you created in QT.
}

3. modify AppDelegate::applicationDidFinishLaunching(), use CCQGLView to create glview. like:
bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
	auto glview = CCQGLView::getInstance();
	glview->setBgColor(Color4B(50, 50, 50, 255));

	director->setOpenGLView(glview);
	_mainWindow.setGLView(glview->getGLWidget());
	_mainWindow.show();
......
}

4. Modify your QT MainWindow class (here is CCGEditor):
CCGEditor.h
class CCGEditor : public QMainWindow
{
	Q_OBJECT

public:
	CCGEditor(QWidget *parent = 0);
	~CCGEditor() {}

	void setGLView(QWidget *glWidget);

protected:
	void closeEvent(QCloseEvent *);

private:
	Ui::CCGEditorClass ui;
	AppDelegate *_appDelegate;
	QWidget *_glWidget;
};

CCGEditor.cpp
CCGEditor::CCGEditor(QWidget *parent)
	: QMainWindow(parent),
	_appDelegate(NULL),
	_glWidget(NULL)
{
	ui.setupUi(this);
}

void CCGEditor::closeEvent(QCloseEvent *)
{
	cocos2d::Director::getInstance()->end();
	qApp->quit();
}

void CCGEditor::setGLView(QWidget *glWidget)
{
	_glWidget = glWidget;

	if (_glWidget)
	{
		ui.SceneWidget->setWidget(_glWidget);
		setCentralWidget(ui.SceneWidget);
	}
}

5. modify the main function in this way:
int main(int argc, char *argv[])
{
	AppDelegate app(argc, argv);
	return cocos2d::CCQApplication::getInstance()->run();
}

6. do not forget the header files_(:зゝ∠)_
