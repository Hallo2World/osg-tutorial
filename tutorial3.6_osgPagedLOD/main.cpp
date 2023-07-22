
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

// �������� PagedLOD ����
osg::ref_ptr<osg::Group> createPagedLOD()
{
	// ���� PagedLOD ����
	osg::ref_ptr<osg::PagedLOD> page = new osg::PagedLOD();

	// ��������λ��
	page->setCenter(osg::Vec3(0.0f, 0.0f, 0.0f));

	// ��ӽڵ㣬���� 0 �������� cow.osg
	page->setFileName(0, "cow.osg");
	// ���ÿ��ӱ仯��ΧΪ 0.0f ~ 50.f
	page->setRange(0, 0.0f, 50.0f);

	// ��ӽڵ㣬���� 1 ��������Ϊ glider.osg
	page->setFileName(1, "glider.osg");
	// ���ÿ��ӱ仯��ΧΪ 50.0f ~ 100.f
	page->setRange(1, 50.0f, 100.0f);

	// ��ӽڵ㣬���� 2 ��������Ϊ cessna.osg
	page->setFileName(2, "cessna.osg");
	// ���ÿ��ӱ仯��ΧΪ 100.0f ~ 200.f
	page->setRange(2, 100.0f, 200.0f);

	return page.get();
}


int main()
{
	// ���� Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ��������任�ڵ�
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	// ����ӽڵ�
	mt->addChild(createPagedLOD());
	// ��ת�����������ʵĽǶ�
	osg::Matrix m;
	m.makeRotate(60.0f, 0.0f, 0.0f, 1.0f);
	// ���þ���
	mt->setMatrix(m);

	// ���PagedLOD ����
	root->addChild(mt.get());

	// д��PagedLOD
	osgDB::writeNodeFile(*root, "page.osg");

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