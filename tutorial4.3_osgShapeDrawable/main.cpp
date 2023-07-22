#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/ShapeDrawable>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// Ԥ���弸����ʾ��

// ���ƶ��Ԥ����ļ�����
osg::ref_ptr<osg::Node> createShape()
{
	// ����һ��Ҷ�ڵ����
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// ���ð뾶�͸߶�
	float radius = 0.8f;
	float height = 1.0f;

	// ������ϸ�ȶ��󣬾�ϸ��Խ�ߣ�ϸ����Խ��
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints();
	// ���þ�ϸ��Ϊ0.5f
	hints->setDetailRatio(0.5f);

	// ���һ�����壬��һ��������Ԥ���弸������󣬵ڶ����Ǿ�ϸ�ȣ�Ĭ��Ϊ0
	geode->addDrawable(new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), radius), hints.get()));

	// ���һ��������
	geode->addDrawable(new osg::ShapeDrawable(new osg::Box(osg::Vec3(2.0f, 0.0f, 0.0f), 2*radius), hints.get()));

	// ���һ��Բ׶
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cone(osg::Vec3(4.0f, 0.0f, 0.0f), radius, height), hints.get()));

	// ���һ��Բ׶��
	geode->addDrawable(new osg::ShapeDrawable(new osg::Cylinder(osg::Vec3(6.0f, 0.0f, 0.0f), radius, height), hints.get()));

	// ���һ��̫�ղ�
	geode->addDrawable(new osg::ShapeDrawable(new osg::Capsule(osg::Vec3(8.0f, 0.0f, 0.0f), radius, height), hints.get()));

	return geode.get();
}

int main()
{
	// ���� Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ��ӵ���������
	root->addChild(createShape());

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