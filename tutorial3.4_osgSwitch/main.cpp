
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/Billboard>
#include <osg/Texture2D>
#include <osg/Image>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>
#include <osg/AutoTransform>
#include <osgText/Text>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <string>

using std::string;


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 创建一个节点，读取牛模型
	osg::ref_ptr<osg::Node> node1 = new osg::Node();
	node1 = osgDB::readNodeFile("cow.osg");

	// 创建一个节点，读取滑翔机模型
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");
	
	// 创建一个开关节点，只渲染滑翔机而不渲染牛
	osg::ref_ptr<osg::Switch> swtich = new osg::Switch();
	// 添加牛的模型，但不渲染，默认为true
	swtich->addChild(node1.get(), false);
	// 添加滑翔机的模型，状态为渲染
	swtich->addChild(node2.get(), true);

	root->addChild(swtich.get());

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