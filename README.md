CocosQtPort
===========
<br>
This is porting code, which port cocos2d-x3.3 to QT5.3.<br>
It is useful for coding a game editor.<br>
<br>
How to use?<br>
1. copy CocoQtPort directory to your Classes folder. <br>
2. change AppDelegate to inherit form cocos2d::CCQApplication. add a member, like:<br>
```
class  AppDelegate : private cocos2d::CCQApplication
{
public:
	AppDelegate(int argc, char *argv[]) : cocos2d::CCQApplication(argc, argv) {};
	virtual ~AppDelegate();
......
protected:
	CCGEditor _mainWindow;  // CCGEditor is the MainWindow class which you created in QT.
}
```
<br>
3. modify AppDelegate::applicationDidFinishLaunching(), use CCQGLView to create glview. like:<br>
```
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
```
<br>
4. Modify your QT MainWindow class (here is CCGEditor):<br>
CCGEditor.h<br>
```
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
```
<br>
CCGEditor.cpp<br>
```
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
```
<br>
5. modify the main function in this way:<br>
```
int main(int argc, char *argv[])
{
	AppDelegate app(argc, argv);
	return cocos2d::CCQApplication::getInstance()->run();
}
```
<br>
6. do not forget the header files_(:зゝ∠)_<br>
<br>
See my blog for detail:<br>
http://www.cnblogs.com/marisa/p/4141862.html
