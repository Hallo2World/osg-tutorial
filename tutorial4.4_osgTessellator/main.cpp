#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Geometry>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>
#include <osgUtil/DelaunayTriangulator>
#include "Text.h"

// Delaunay（狄洛尼） 三角网绘制示例
int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	// 方便查看在多边形之间切换，以查看三角网
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 创建顶点数组
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array();

	// 计算顶点数组的大小
	unsigned int n = sizeof(vertex/sizeof(float[3]));

	// 添加顶点数据
	for (unsigned int i = 0; i < n; i++)
	{
		coords->push_back(osg::Vec3(vertex[i][0], vertex[i][1], vertex[i][2]));
	}

	// 创建Delaunay三角对象
	osg::ref_ptr<osgUtil::DelaunayTriangulator> dt = new osgUtil::DelaunayTriangulator(coords.get());

	// 生成三角网
	dt->triangulate();

	// 创建几何体
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	// 设置顶点数组
	geometry->setVertexArray(coords.get());

	// 加入到绘图基元
	geometry->addPrimitiveSet(dt->getTriangles());

	// 添加到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geometry.get());
	root->addChild(geode.get());

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