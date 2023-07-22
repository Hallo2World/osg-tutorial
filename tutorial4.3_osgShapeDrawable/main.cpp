#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// 预定义几何体示例

// 绘制多个预定义的几何体
osg::ref_ptr<osg::Node> createShape()
{
	// 创建一个叶节点对象
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// 设置半径和高度
	float radius = 0.8f;
	float height = 1.0f;

	// 创建精细度对象，精细度越高，细化就越多
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();
	// 设置精细度为0.5f
	hints->setDetailRatio(0.5f);

	// 添加一个球体，第一个参数是预定义几何体对象，第二个是精细度，默认为0
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints.get()));

	// 添加一个正方体
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), 2*radius), hints.get()));

	// 添加一个圆锥
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints.get()));

	// 添加一个圆锥体
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), radius, height), hints.get()));

	// 添加一个太空舱
	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height), hints.get()));

	return geode.get();
}

int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 添加到场景数据
	root->addChild(createShape());

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