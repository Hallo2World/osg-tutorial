#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/ViewerEventHandlers>
#include <osg/Geode>
#include <osg/Geometry>
#include <osg/ShapeDrawable>
#include <osg/Material>
#include <osg/Image>
#include <osg/Texture2D>
#include <osg/LineWidth>

osg::ref_ptr<osg::Geode> CreateBox()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::TessellationHints> hints = new osg::TessellationHints;
	osg::ref_ptr<osg::ShapeDrawable> shape = new osg::ShapeDrawable(new osg::Box(osg::Vec3(0.0, 0.0, 0.0), 1.0, 10.0, 10.0), hints.get());
	osg::ref_ptr<osg::Material> material = new osg::Material;
	osg::ref_ptr<osg::Texture2D> texture2D = new osg::Texture2D;

	// ������ɫ
	shape->setColor(osg::Vec4(0.5, 0.5, 0.5, 0.5));

	// ���þ���
	hints->setDetailRatio(0.5);

	// ���ò���
	material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));		// ���û�����
	material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));		// �����������
	material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));    // ���þ������
	material->setShininess(osg::Material::FRONT_AND_BACK, 60.0);

	// ��������
	osg::Image* image = osgDB::readImageFile("C:/penSceneGraph-Data/Images/lz.rgb");
	if (image) {
		texture2D->setImage(image);
	}

	// Ӧ�ò���
	geode->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);	// ������Ȳ���

	// Ӧ������
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture2D, osg::StateAttribute::ON);

	geode->addDrawable(shape);
	return geode;
}

osg::ref_ptr<osg::Geode> CreateSimple()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;	// ���붥�����
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;	// ������ɫ����
	osg::ref_ptr<osg::Vec3Array> norms = new osg::Vec3Array;	// ���뷨����
	osg::ref_ptr<osg::LineWidth> width = new osg::LineWidth;	// �����߿����

	geode->addDrawable(geom);

	// ��͸����
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

	// �����߿�
	width->setWidth(100.0);
	geode->getOrCreateStateSet()->setAttributeAndModes(width, osg::StateAttribute::ON);

	// ���ö���
	geom->setVertexArray(coords);
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::Mode::LINE_LOOP, 0, 4));	// ���ö��������ʽ
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::Mode::QUADS, 0, 4));	// ���ö��������ʽ

	// �趨������ɫ
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);

	// ���÷���
	geom->setNormalArray(norms);
	geom->setNormalBinding(osg::Geometry::AttributeBinding::BIND_OVERALL);

	// ���ö���
	coords->push_back(osg::Vec3(-5.0, 0.0, -5.0));
	coords->push_back(osg::Vec3(5.0, 0.0, -5.0));
	coords->push_back(osg::Vec3(5.0, 0.0, 5.0));
	coords->push_back(osg::Vec3(-5.0, 0.0, 5.0));

	// ������ɫ
	colors->push_back(osg::Vec4(1.0, 0.0, 0.0, 0.5));
	colors->push_back(osg::Vec4(0.0, 1.0, 0.0, 0.5));
	colors->push_back(osg::Vec4(0.0, 0.0, 1.0, 0.5));
	colors->push_back(osg::Vec4(1.0, 1.0, 0.0, 0.5));

	// ���÷�����
	norms->push_back(osg::Vec3(0.0, -1.0, 0.0));

	return geode;
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;

	osg::ref_ptr<osg::Group> group = new osg::Group;

	
	group->addChild(CreateBox());
	group->addChild(osgDB::readNodeFile("glider.osg"));
	group->addChild(CreateSimple());

	//viewer->setSceneData(CreateBox());
	//viewer->setSceneData(CreateSimple());
	viewer->setSceneData(group);

	return viewer->run();
}