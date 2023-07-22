
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

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 创建节点
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	// 创建位置变换节点1
	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform();
	// 设置位置
	pat1->setPosition(osg::Vec3(-10.0f, 0.0f,   0.0f));
	// 设置缩放，在X、Y、Z方向都缩小一倍
	pat1->setScale(osg::Vec3(0.5f, 0.5f, 0.5f));
	// 添加子节点
	pat1->addChild(node.get());

	// 创建位置变换节点2
	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 = new osg::PositionAttitudeTransform();
	pat2->setPosition(osg::Vec3(10.0f, 0.0f,   0.0f));
	pat2->addChild(node.get());

	// 添加到场景
	root->addChild(pat1.get());
	root->addChild(pat2.get());

	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	// 设置场景数据
	viewer->setSceneData(root.get());

	//这里是单屏幕显示
	viewer->setUpViewOnSingleScreen(0);

	viewer->realize();

	viewer->run();

	return 0;
}