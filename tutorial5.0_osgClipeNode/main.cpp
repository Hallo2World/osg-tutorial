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

// ��Ⱦ״̬ʾ��

osg::ref_ptr<osg::Node> createClipNode(osg::ref_ptr<osg::Node> subgraph)
{
	osg::ref_ptr<osg::Group> root = new osg::Group();
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	
	// ��������Ի��ƣ�����ͷ��涼����
	osg::ref_ptr<osg::PolygonMode> polymode = new osg::PolygonMode();
	polymode->setMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::LINE);

	// ���ö�������λ���ģʽ����ָ��״̬���Լ̳�����ΪOVERRIDE
	stateset->setAttributeAndModes(polymode, osg::StateAttribute::OVERRIDE | osg::StateAttribute::ON);

	// ��������Ի��ƽڵ�
	osg::ref_ptr<osg::Group> wireframe_subgrap = new osg::Group();
	// ������Ⱦ״̬
	wireframe_subgrap->setStateSet(stateset.get());
	wireframe_subgrap->addChild(subgraph.get());

	root->addChild(wireframe_subgrap.get());

	osg::ref_ptr<osg::MatrixTransform> transform = new osg::MatrixTransform;
	// ���»ص���ʵ�ֶ�̬�ü�
	osg::ref_ptr<osg::NodeCallback> nc = new osg::AnimationPathCallback(subgraph->getBound().center(), osg::Vec3(0.0f, 0.0f, 1.0f), osg::inDegrees(45.0f));
	transform->setUpdateCallback(nc.get());

	// �����ü��ڵ�
	osg::ref_ptr<osg::ClipNode> clipnode = new osg::ClipNode();
	osg::BoundingSphere bs = subgraph->getBound();
	bs.radius() *= 0.4f;

	// ���òü���İ�Χ��
	osg::BoundingBox bb;
	bb.expandBy(bs);

	// ����ǰ��ָ���İ�Χ�д���6���ü�ƽ��
	clipnode->createClipBox(bb);
	// ���ü�ѡ
	clipnode->setCullingActive(false);

	transform->addChild(clipnode.get());
	root->addChild(transform.get());

	// ����δ���ü��Ľڵ�
	osg::ref_ptr<osg::Group> clippedNode = new osg::Group();
	clippedNode->setStateSet(clipnode->getStateSet());
	clippedNode->addChild(subgraph.get());
	
	root->addChild(clippedNode.get());

	return root.get();
}

int main()
{
	// ���� Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Node> root = new osg::Node();

	// ����ģ��
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cessna.osg");

	root = createClipNode(node.get());

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	// ���ó�������
	viewer->setSceneData(root.get());

	//�����ǵ���Ļ��ʾ
	viewer->setUpViewOnSingleScreen(0);

	// ��ʼ������������
	viewer->realize();

	// ��ʼ��Ⱦ
	viewer->run();

	return 0;
}