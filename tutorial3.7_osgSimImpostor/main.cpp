
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgSim/Impostor>

#include <osgUtil/Optimizer>

#include <string>

using std::string;


int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 创建一个节点，读取牛模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	// 创建一个替代节点
	osg::ref_ptr<osgSim::Impostor> impostor = new osgSim::Impostor();
	// 设置 50.f 以后开始使用贴图
	impostor->setImpostorThreshold(50.f);
	// 设置模型的显示范围 0~1000 内
	impostor->addChild(node.get(), 0, 10000.0f);

	// 添加到场景
	root->addChild(impostor.get());
	
	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	// 设置场景数据
	viewer->setSceneData(root.get());

	//这里是单屏幕显示
	viewer->setUpViewOnSingleScreen(0);

	// 初始化并创建窗口
	viewer->realize();

	// 开始渲染
	viewer->run();

	return 0;
}