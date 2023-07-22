#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgGA/StateSetManipulator>

#include <osgUtil/Optimizer>
#include <osgUtil/SmoothingVisitor>

// ���ɶ��㷨����ʾ��

// ����һ���ı��νڵ�
osg::ref_ptr<osg::Geometry> createQuad()
{
	// ����һ��Ҷ�ڵ����
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// ����һ�����������
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	// �����������飬ע�ⶥ������˳��Ϊ��ʱ���
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	// �������
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));

	// ���ö�������
	geom->setVertexArray(v.get());

	// ������������
	osg::ref_ptr<osg::Vec2Array> vt = new osg::Vec2Array();
	// �������
	vt->push_back(osg::Vec2(0.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 0.0f));
	vt->push_back(osg::Vec2(1.0f, 1.0f));
	vt->push_back(osg::Vec2(0.0f, 1.0f));

	// ������������
	geom->setTexCoordArray(0, vt.get());

	// ������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	// �������
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0f));
	
	// ������ɫ����
	geom->setColorArray(vc.get());
	// ������ɫ�İ󶨷�ʽΪ�������
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	// ���ͼԪ����ͼ��ԪΪ�ı���
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	return geom.get();
}

int main()
{
	// ���� Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();
	// �л�����ģʽ������Ƚ�ģ��
	viewer->addEventHandler(new osgGA::StateSetManipulator(viewer->getCamera()->getOrCreateStateSet()));

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ����һ�����������ע�⣬�����岢û��ָ������
	// �������ע���������ɶ��㷨�ߵĴ��룬�Ϳ��Կ������յĲ��
	osg::ref_ptr<osg::Geometry> geometry = createQuad();

	// ���ɶ��㷨��
	osgUtil::SmoothingVisitor::smooth(*(geometry.get()));

	// ��ӵ�Ҷ�ڵ�
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->addDrawable(geometry.get());

	// ��ӵ�������
	root->addChild(geode.get());

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