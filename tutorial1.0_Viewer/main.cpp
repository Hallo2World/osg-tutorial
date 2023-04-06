#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/ViewerEventHandlers>


// 自定义事件处理器
class CustomEventHandler : public osgGA::GUIEventHandler
{
public:
	virtual void getUsage(osg::ApplicationUsage& usage) const override{
		usage.addKeyboardMouseBinding("h", "Jiliguala");
	}

	// 如果返回true后面添加事件处理无法得到处理
	virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&) { return false; }
};

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Node> node = new osg::Node;

	// 读取模型
	node = osgDB::readFile<osg::Node>("glider.osg");

	// 添加帮助事件
	viewer->addEventHandler(new osgViewer::HelpHandler);

	// 添加屏幕帧率参数事件处理器
	viewer->addEventHandler(new osgViewer::StatsHandler);

	// 添加自定义事件处理器
	viewer->addEventHandler(new CustomEventHandler);

	// 添加窗口大小事件处理器
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);

	// 添加屏幕捕获事件处理器
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);

	viewer->setSceneData(node);
	
	return viewer->run();
}