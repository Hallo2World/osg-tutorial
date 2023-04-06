#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/ViewerEventHandlers>


// �Զ����¼�������
class CustomEventHandler : public osgGA::GUIEventHandler
{
public:
	virtual void getUsage(osg::ApplicationUsage& usage) const override{
		usage.addKeyboardMouseBinding("h", "Jiliguala");
	}

	// �������true��������¼������޷��õ�����
	virtual bool handle(const osgGA::GUIEventAdapter&, osgGA::GUIActionAdapter&) { return false; }
};

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<osg::Node> node = new osg::Node;

	// ��ȡģ��
	node = osgDB::readFile<osg::Node>("glider.osg");

	// ��Ӱ����¼�
	viewer->addEventHandler(new osgViewer::HelpHandler);

	// �����Ļ֡�ʲ����¼�������
	viewer->addEventHandler(new osgViewer::StatsHandler);

	// ����Զ����¼�������
	viewer->addEventHandler(new CustomEventHandler);

	// ��Ӵ��ڴ�С�¼�������
	viewer->addEventHandler(new osgViewer::WindowSizeHandler);

	// �����Ļ�����¼�������
	viewer->addEventHandler(new osgViewer::ScreenCaptureHandler);

	viewer->setSceneData(node);
	
	return viewer->run();
}