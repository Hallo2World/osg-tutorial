#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/PositionAttitudeTransform>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>
#include <osgUtil/Simplifier>

// 简化几何体

int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	// 切换网格模式，方便比较模型
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 设置样本比率，样本比率越大，简化越少	
	// 样本比率越小，简化越多
	float smapleRatio = 0.3f;
	// 设置点的最大误差
	float maxError = 4.0f;

	// 创建简化对象
	osgUtil::Simplifier simplifier(smapleRatio, maxError);

	// 读取牛的模型
	osg::ref_ptr<osg::Node> node1 = osgDB::readNodeFile("cow.osg");

	// 深拷贝牛的模型到node2节点
	osg::ref_ptr<osg::Node> node2 = (osg::Node*)(node1->clone(osg::CopyOp::DEEP_COPY_ALL));

	// 创建一个位置变换节点
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();

	// 设置位置
	pat->setPosition(osg::Vec3(10.0f, 0.0f, 0.0f));

	// 添加子节点
	pat->addChild(node2.get());
	// 简化处理
	pat->accept(simplifier);

	// 添加到场景
	root->addChild(node1.get());
	root->addChild(pat.get());

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