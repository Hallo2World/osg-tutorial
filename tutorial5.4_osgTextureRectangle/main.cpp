#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Image>
#include <osg/TexGen>
#include <osg/Texture1D>
#include <osg/TexEnv>
#include <osg/StateSet>
#include <osg/TextureRectangle>
#include <osg/TexMat>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// TextureRectangle ����ӳ��ʾ��

// ����һ���ı���
osg::ref_ptr<osg::Geode> createNode()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	// ���ö���
	osg::ref_ptr<osg::Vec3Array> vec = new osg::Vec3Array();
	vec->push_back(osg::Vec3(-10.0f, 0.0f, -10.f));
	vec->push_back(osg::Vec3(-10.0f, 0.0f, 10.f));
	vec->push_back(osg::Vec3(10.0f, 0.0f, 10.f));
	vec->push_back(osg::Vec3(10.0f, 0.0f, -10.f));

	geom->setVertexArray(vec.get());

	// ������������
	osg::ref_ptr<osg::Vec2Array> tex = new osg::Vec2Array();
	tex->push_back(osg::Vec2f(0.0f, 0.0f));
	tex->push_back(osg::Vec2f(1.0f, 0.0f));
	tex->push_back(osg::Vec2f(1.0f, 1.0f));
	tex->push_back(osg::Vec2f(0.0f, 1.0f));

	geom->setTexCoordArray(0, tex.get());


	// ���÷���
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	nc->push_back(osg::Vec3f(0.0f, -1.0f, 0.0f));

	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

	// ���ͼԪ
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	// ����
	geode->addDrawable(geom.get());

	return geode.get();
}

// ������ά����״̬����
osg::ref_ptr<osg::StateSet> createTexture2DState(osg::ref_ptr<osg::Image> image)
{
	// ����״̬������
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

	// ������ά�������
	osg::ref_ptr<osg::TextureRectangle> texture = new osg::TextureRectangle();
	texture->setDataVariance(osg::Object::DYNAMIC);
	// ������ͼ
	texture->setImage(image.get());

	// ����������󣬲�����Ϊ���ݾ�������TextureRectangle���Ĵ�С�Զ�����
	// �Ӷ�����Ӧ��һ����������һ���������겻��0~1��
	osg::ref_ptr<osg::TexMat> texmat = new osg::TexMat();
	texmat->setScaleByTextureRectangleSize(true);

	// ���������������
	stateset->setTextureAttributeAndModes(0, texmat.get(), osg::StateAttribute::ON);
	stateset->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);

	// �رչ���
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	return stateset.get();
}


int main()
{
	// ���� Viewer���󣬳��������
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ��ȡ��ͼ�ļ�
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/primitives.gif");

	osg::ref_ptr<osg::Node> node = createNode();

	// ����״̬������
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	stateset = createTexture2DState(image.get());

	// ʹ�ö�ά����
	node->setStateSet(stateset.get());

	root->addChild(node.get());

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