
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PagedLOD>
#include <osg/PositionAttitudeTransform>
#include <osg/MatrixTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <string>

using std::string;

// 创建三级 PagedLOD 场景
osg::ref_ptr<osg::Group> createPagedLOD()
{
	// 创建 PagedLOD 对象
	osg::ref_ptr<osg::PagedLOD> page = new osg::PagedLOD();

	// 设置中心位置
	page->setCenter(osg::Vec3(0.0f, 0.0f, 0.0f));

	// 添加节点，设置 0 级的内容 cow.osg
	page->setFileName(0, "cow.osg");
	// 设置可视变化范围为 0.0f ~ 50.f
	page->setRange(0, 0.0f, 50.0f);

	// 添加节点，设置 1 级的内容为 glider.osg
	page->setFileName(1, "glider.osg");
	// 设置可视变化范围为 50.0f ~ 100.f
	page->setRange(1, 50.0f, 100.0f);

	// 添加节点，设置 2 级的内容为 cessna.osg
	page->setFileName(2, "cessna.osg");
	// 设置可视变化范围为 100.0f ~ 200.f
	page->setRange(2, 100.0f, 200.0f);

	return page.get();
}


int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 创建矩阵变换节点
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	// 添加子节点
	mt->addChild(createPagedLOD());
	// 旋转，调整到合适的角度
	osg::Matrix m;
	m.makeRotate(60.0f, 0.0f, 0.0f, 1.0f);
	// 设置矩阵
	mt->setMatrix(m);

	// 添加PagedLOD 场景
	root->addChild(mt.get());

	// 写入PagedLOD
	osgDB::writeNodeFile(*root, "page.osg");

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