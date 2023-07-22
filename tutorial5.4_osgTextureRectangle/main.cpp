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

// TextureRectangle 纹理映射示例

// 创建一个四边形
osg::ref_ptr<osg::Geode> createNode()
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();

	// 设置顶点
	osg::ref_ptr<osg::Vec3Array> vec = new osg::Vec3Array();
	vec->push_back(osg::Vec3(-10.0f, 0.0f, -10.f));
	vec->push_back(osg::Vec3(-10.0f, 0.0f, 10.f));
	vec->push_back(osg::Vec3(10.0f, 0.0f, 10.f));
	vec->push_back(osg::Vec3(10.0f, 0.0f, -10.f));

	geom->setVertexArray(vec.get());

	// 设置纹理坐标
	osg::ref_ptr<osg::Vec2Array> tex = new osg::Vec2Array();
	tex->push_back(osg::Vec2f(0.0f, 0.0f));
	tex->push_back(osg::Vec2f(1.0f, 0.0f));
	tex->push_back(osg::Vec2f(1.0f, 1.0f));
	tex->push_back(osg::Vec2f(0.0f, 1.0f));

	geom->setTexCoordArray(0, tex.get());


	// 设置法线
	osg::ref_ptr<osg::Vec3Array> nc = new osg::Vec3Array();
	nc->push_back(osg::Vec3f(0.0f, -1.0f, 0.0f));

	geom->setNormalArray(nc.get());
	geom->setNormalBinding(osg::Geometry::BIND_PER_PRIMITIVE_SET);

	// 添加图元
	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));

	// 绘制
	geode->addDrawable(geom.get());

	return geode.get();
}

// 创建二维纹理状态对象
osg::ref_ptr<osg::StateSet> createTexture2DState(osg::ref_ptr<osg::Image> image)
{
	// 创建状态集对象
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

	// 创建二维纹理对象
	osg::ref_ptr<osg::TextureRectangle> texture = new osg::TextureRectangle();
	texture->setDataVariance(osg::Object::DYNAMIC);
	// 设置贴图
	texture->setImage(image.get());

	// 设置纹理矩阵，并设置为根据矩阵纹理（TextureRectangle）的大小自动缩放
	// 从而允许应用一个矩阵纹理到一个纹理坐标不在0~1上
	osg::ref_ptr<osg::TexMat> texmat = new osg::TexMat();
	texmat->setScaleByTextureRectangleSize(true);

	// 启动纹理及纹理矩阵
	stateset->setTextureAttributeAndModes(0, texmat.get(), osg::StateAttribute::ON);
	stateset->setTextureAttributeAndModes(0, texture.get(), osg::StateAttribute::ON);

	// 关闭光照
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	return stateset.get();
}


int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 读取贴图文件
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/primitives.gif");

	osg::ref_ptr<osg::Node> node = createNode();

	// 创建状态集对象
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
	stateset = createTexture2DState(image.get());

	// 使用二维纹理
	node->setStateSet(stateset.get());

	root->addChild(node.get());

	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(root.get());

	// 设置场景数据
	viewer->setSceneData(root.get());

	//这里是单屏幕显示
	viewer->setUpViewOnSingleScreen(0);

	// 初始化并创建窗口
	viewer->realize();

	// 开始渲染
	viewer->run();

	return 0;
}