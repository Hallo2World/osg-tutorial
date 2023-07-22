#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// �����󶨼��������ʾ��

// ����һ���ı��νڵ�
osg::ref_ptr<osg::Node> createQuad()
{
	// ����һ��Ҷ�ڵ����
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// ����һ�����������
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	// ������������
	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array();
	// �������
	v->push_back(osg::Vec3(0.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 0.0f));
	v->push_back(osg::Vec3(1.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, 0.0f, 1.0f));
	v->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	// ���ö�������
	geom->setVertexArray(v.get());

	// �����ı��ζ����������飬ָ����ͼ��ԪΪ�ı��Σ�ע�����˳��
	osg::ref_ptr<osg::DrawElementsUInt> quad = new osg::DrawElementsUInt(osg::PrimitiveSet::QUADS, 0);
	// �������
	quad->push_back(0);
	quad->push_back(1);
	quad->push_back(2);
	quad->push_back(3);

	// ��ӵ�������
	geom->addPrimitiveSet(quad.get());

	// ���������ζ����������飬ָ����ͼΪ��ԪΪ�����Σ�ע�����˳��
	osg::ref_ptr<osg::DrawElementsUInt> triangle = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	// �������
	triangle->push_back(4);
	triangle->push_back(0);
	triangle->push_back(3);
	
	// ��ӵ�������
	geom->addPrimitiveSet(triangle.get());

	// ������ɫ����
	osg::ref_ptr<osg::Vec4Array> vc = new osg::Vec4Array();
	// �������
	vc->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0));
	vc->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0));
	vc->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0));
	vc->push_back(osg::Vec4(1.0f, 1.0f, 0.0f, 1.0));

	// ������ɫ��������
	osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4>* colorIndex =
		new osg::TemplateIndexArray<unsigned int, osg::Array::UIntArrayType, 4, 4>();
	// ������ݣ�ע���������˳���붥��һһ��Ӧ
	colorIndex->push_back(0);
	colorIndex->push_back(1);
	colorIndex->push_back(2);
	colorIndex->push_back(3);
	colorIndex->push_back(2);

	// ������ɫ����
	geom->setColorArray(vc.get());
	// ������ɫ��������
	//geom->setColorIndices(colorIndex);		// Not Support now
	// ������ɫ�İ󶨷�ʽΪ��������
	geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);


	// ������������
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	// ��ӷ���
	nc->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));

	// ���÷�������
	geom->setNormalArray(nc.get());
	// ���÷��ߵİ󶨷�ʽΪȫ������
	geom->setNormalBinding(osg::Geometry::BIND_OVERALL);

	// ��ӵ�Ҷ�ڵ�
	geode->addDrawable(geom.get());

	return geode.get();
}

int main()
{
	// ���� Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ��ӵ���������
	root->addChild(createQuad());	

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