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

	// 设置颜色
	shape->setColor(osg::Vec4(0.5, 0.5, 0.5, 0.5));

	// 设置精度
	hints->setDetailRatio(0.5);

	// 设置材质
	material->setAmbient(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));		// 设置环境光
	material->setDiffuse(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));		// 设置漫射光照
	material->setSpecular(osg::Material::FRONT_AND_BACK, osg::Vec4(1.0, 1.0, 1.0, 1.0));    // 设置镜面光照
	material->setShininess(osg::Material::FRONT_AND_BACK, 60.0);

	// 设置纹理
	osg::Image* image = osgDB::readImageFile("C:/penSceneGraph-Data/Images/lz.rgb");
	if (image) {
		texture2D->setImage(image);
	}

	// 应用材质
	geode->getOrCreateStateSet()->setAttributeAndModes(material, osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);
	geode->getOrCreateStateSet()->setMode(GL_DEPTH_TEST, osg::StateAttribute::ON);	// 启动深度测试

	// 应用纹理
	geode->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture2D, osg::StateAttribute::ON);

	geode->addDrawable(shape);
	return geode;
}

osg::ref_ptr<osg::Geode> CreateSimple()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> coords = new osg::Vec3Array;	// 申请顶点对象
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;	// 申请颜色对象
	osg::ref_ptr<osg::Vec3Array> norms = new osg::Vec3Array;	// 申请法向量
	osg::ref_ptr<osg::LineWidth> width = new osg::LineWidth;	// 申请线宽对象

	geode->addDrawable(geom);

	// 打开透明度
	geode->getOrCreateStateSet()->setMode(GL_BLEND, osg::StateAttribute::ON);

	// 设置线宽
	width->setWidth(100.0);
	geode->getOrCreateStateSet()->setAttributeAndModes(width, osg::StateAttribute::ON);

	// 设置顶点
	geom->setVertexArray(coords);
	//geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::Mode::LINE_LOOP, 0, 4));	// 设置顶点关联方式
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::Mode::QUADS, 0, 4));	// 设置顶点关联方式

	// 设定顶点颜色
	geom->setColorArray(colors);
	geom->setColorBinding(osg::Geometry::AttributeBinding::BIND_PER_VERTEX);

	// 设置法线
	geom->setNormalArray(norms);
	geom->setNormalBinding(osg::Geometry::AttributeBinding::BIND_OVERALL);

	// 设置顶点
	coords->push_back(osg::Vec3(-5.0, 0.0, -5.0));
	coords->push_back(osg::Vec3(5.0, 0.0, -5.0));
	coords->push_back(osg::Vec3(5.0, 0.0, 5.0));
	coords->push_back(osg::Vec3(-5.0, 0.0, 5.0));

	// 设置颜色
	colors->push_back(osg::Vec4(1.0, 0.0, 0.0, 0.5));
	colors->push_back(osg::Vec4(0.0, 1.0, 0.0, 0.5));
	colors->push_back(osg::Vec4(0.0, 0.0, 1.0, 0.5));
	colors->push_back(osg::Vec4(1.0, 1.0, 0.0, 0.5));

	// 设置法向量
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