
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

	// �����ڵ�
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	// ����λ�ñ任�ڵ�1
	osg::ref_ptr<osg::PositionAttitudeTransform> pat1 = new osg::PositionAttitudeTransform();
	// ����λ��
	pat1->setPosition(osg::Vec3(-10.0f, 0.0f,   0.0f));
	// �������ţ���X��Y��Z������Сһ��
	pat1->setScale(osg::Vec3(0.5f, 0.5f, 0.5f));
	// ����ӽڵ�
	pat1->addChild(node.get());

	// ����λ�ñ任�ڵ�2
	osg::ref_ptr<osg::PositionAttitudeTransform> pat2 = new osg::PositionAttitudeTransform();
	pat2->setPosition(osg::Vec3(10.0f, 0.0f,   0.0f));
	pat2->addChild(node.get());

	// ��ӵ�����
	root->addChild(pat1.get());
	root->addChild(pat2.get());

	// �Ż���������
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	// ���ó�������
	viewer->setSceneData(root.get());

	//�����ǵ���Ļ��ʾ
	viewer->setUpViewOnSingleScreen(0);

	viewer->realize();

	viewer->run();

	return 0;
}