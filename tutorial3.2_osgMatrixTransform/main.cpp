
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

	// 创建矩阵变换节点1
	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform();
	// 创建一个矩阵
	osg::Matrix m;
	// 在X方向平移10个单位
	m.makeTranslate(osg::Vec3(10.0f, 0.f, 0.f));
	// 绕X轴旋转45°
	m.makeRotate(45.0f, 1.0, 0.0f, 0.0f);
	// 设置矩阵
	mt1->setMatrix(m);
	// 添加子节点
	mt1->addChild(node.get());

	// 创建矩阵变换节点2
	osg::ref_ptr<osg::MatrixTransform> mt2 = new osg::MatrixTransform();
	// 创建一个矩阵
	osg::Matrix t;
	// 在X轴负方向上平移10个单位
	t.makeTranslate(osg::Vec3(-10.0f, 0.0f, 0.0f));
	// 设置矩阵
	mt2->setMatrix(t);
	// 添加子节点
	mt2->addChild(node.get());

	// 添加到场景
	root->addChild(mt1.get());
	root->addChild(mt2.get());

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