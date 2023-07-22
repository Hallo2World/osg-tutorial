
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

	// ��������任�ڵ�1
	osg::ref_ptr<osg::MatrixTransform> mt1 = new osg::MatrixTransform();
	// ����һ������
	osg::Matrix m;
	// ��X����ƽ��10����λ
	m.makeTranslate(osg::Vec3(10.0f, 0.f, 0.f));
	// ��X����ת45��
	m.makeRotate(45.0f, 1.0, 0.0f, 0.0f);
	// ���þ���
	mt1->setMatrix(m);
	// ����ӽڵ�
	mt1->addChild(node.get());

	// ��������任�ڵ�2
	osg::ref_ptr<osg::MatrixTransform> mt2 = new osg::MatrixTransform();
	// ����һ������
	osg::Matrix t;
	// ��X�Ḻ������ƽ��10����λ
	t.makeTranslate(osg::Vec3(-10.0f, 0.0f, 0.0f));
	// ���þ���
	mt2->setMatrix(t);
	// ����ӽڵ�
	mt2->addChild(node.get());

	// ��ӵ�����
	root->addChild(mt1.get());
	root->addChild(mt2.get());

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