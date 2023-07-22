#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ClipNode>
#include <osg/PolygonMode>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/AnimationPath>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// 渲染状态示例

osg::ref_ptr<osg::Node> createClipNode(osg::ref_ptr<osg::Node> subgraph)
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	
	// 多边形线性绘制，正面和反面都绘制
	osg::ref_ptr<osg::PolygonMode> polymode = new osg::PolygonMode();
	polymode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

	// 启用多边形线形绘制模式，并指定状态属性继承属性为OVERRIDE
	stateset->setAttributeAndModes(polymode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

	// 多边形线性绘制节点
	osg::ref_ptr<osg::Group> wireframe_subgrap = new osg::Group();
	// 设置渲染状态
	wireframe_subgrap->setStateSet(stateset.get());
	wireframe_subgrap->addChild(subgraph.get());

	root->addChild(wireframe_subgrap.get());

	osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
	// 更新回调，实现动态裁剪
	osg::ref_ptr<osg::NodeCallback> nc = new osg::AnimationPathCallback(subgraph->getBound().center(), osg::Vec3(0.0f, 0.0f, 1.0f), osg::inDegrees(45.0f));
	transform->setUpdateCallback(nc.get());

	// 创建裁剪节点
	osg::ref_ptr<osg::ClipNode> clipnode = new osg::ClipNode();
	osg::BoundingSphere bs = subgraph->getBound();
	bs.radius() *= 0.4f;

	// 设置裁剪点的包围盒
	osg::BoundingBox bb;
	bb.expandBy(bs);

	// 根据前面指定的包围盒创建6个裁剪平面
	clipnode->createClipBox(bb);
	// 禁用拣选
	clipnode->setCullingActive(false);

	transform->addChild(clipnode.get());
	root->addChild(transform.get());

	// 创建未被裁剪的节点
	osg::ref_ptr<osg::Group> clippedNode = new osg::Group();
	clippedNode->setStateSet(clipnode->getStateSet());
	clippedNode->addChild(subgraph.get());
	
	root->addChild(clippedNode.get());

	return root.get();
}

int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Node> root = new osg::Node();

	// 加载模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cessna.osg");

	root = createClipNode(node.get());

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