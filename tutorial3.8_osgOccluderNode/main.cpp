
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/OccluderNode>
#include <osg/StateSet>
#include <osg/ConvexPlanarOccluder>
#include <osg/BoundingBox>
#include <osg/BoundingSphere>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgSim/Impostor>

#include <osgUtil/Optimizer>

#include <string>

using std::string;


// 创建遮挡节点
osg::ref_ptr<osg::Node> createOccluder(
	const osg::Vec3& v1,
	const osg::Vec3& v2,
	const osg::Vec3& v3,
	const osg::Vec3& v4) {
	// 创建遮挡节点对象
	osg::ref_ptr<osg::OccluderNode> occluderNode = new osg::OccluderNode();
	// 创建遮挡平面
	osg::ref_ptr<osg::ConvexPlanarOccluder> cpo = new osg::ConvexPlanarOccluder;

	// 关联遮挡板平面
	occluderNode->setOccluder(cpo.get());
	occluderNode->setName("occluder");

	// 初始化一个遮挡平面
	osg::ConvexPlanarPolygon& occluder = cpo->getOccluder();
	occluder.add(v1);
	occluder.add(v2);
	occluder.add(v3);
	occluder.add(v4);

	// 为遮挡面画一个四边形
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array(occluder.getVertexList().begin(),
		occluder.getVertexList().end());

	geom->setVertexArray(coords);

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array(1);
	(*colors)[0].set(1.0f, 1.0f, 1.0f, 0.5f);

	geom->setColorArray(colors.get());

	geom->setColorBinding(osg::Geometry::BIND_OVERALL);
	
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	geode->addDrawable(geom.get());

	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

	// 关闭光照
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	// 使用混合，保证Alpha纹理正确
	stateset->setMode(GL_BLEND, osg::StateAttribute::ON);

	// 设置透明渲染元
	stateset->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);

	geom->setStateSet(stateset.get());


	// 添加四边形作为遮挡节点，遮挡节点本不具备遮挡能力
	occluderNode->addChild(geode.get());

	return occluderNode.get();
}

// 创建绕模型的遮挡场景
osg::ref_ptr<osg::Group> createOccludesAroundModel(osg::ref_ptr<osg::Node> model)
{
	// 创建场景组节点
	osg::ref_ptr<osg::Group> scene = new osg::Group();
	scene->setName("OccluderScene");

	// 添加子节点
	scene->addChild(model.get());
	model->setName("cow.osg");

	// 计算模型的包围盒
	const osg::BoundingSphere bs = model->getBound();

	// 根据包围盒创建前后左右4个遮挡面
	osg::BoundingBox bb;
	bb.expandBy(bs);

	// 前遮挡面
	scene->addChild(createOccluder(bb.corner(0), bb.corner(1), bb.corner(5), bb.corner(4)));

	// 右遮挡面
	scene->addChild(createOccluder(bb.corner(1), bb.corner(3), bb.corner(7), bb.corner(5)));

	// 左遮挡面
	scene->addChild(createOccluder(bb.corner(2), bb.corner(0), bb.corner(4), bb.corner(6)));

	// 后遮挡面
	scene->addChild(createOccluder(bb.corner(3), bb.corner(2), bb.corner(6), bb.corner(7)));

	return scene.get();
}

int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 创建一个节点，读取牛模型
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	// 添加遮挡场景
	root->addChild(createOccludesAroundModel(node.get()));
	
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