#include <osgViewer/Viewer>
#include <osgViewer/ViewerEventHandlers>

#include <osg/Node>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Image>
#include <osg/TexGen>
#include <osg/Texture2D>
#include <osg/TexEnv>
#include <osg/StateSet>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// 多重纹理映射示例

int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");

	// 读取贴图
	osg::ref_ptr<osg::Image> image = osgDB::readImageFile("Images/primitives.gif");

	if (image.get()) {
		// 创建二维纹理
		osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
		texture->setImage(image.get());

		// 设置自动生成坐标
		osg::ref_ptr<osg::TexGen> texgen = new osg::TexGen();
		texgen->setMode(osg::TexGen::SPHERE_MAP);

		// 设置纹理环境，模式为BLEND
		osg::ref_ptr<osg::TexEnv> texenv = new osg::TexEnv();
		texenv->setMode(osg::TexEnv::BLEND);
		// 设置BLEND操作的颜色
		texenv->setColor(osg::Vec4(0.6f, 0.6f, 0.6f, 0.0f));

		// 启动单元1自动生成纹理坐标，并使用纹理
		osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();
		stateset->setTextureAttributeAndModes(1, texture.get(), osg::StateAttribute::ON);
		stateset->setTextureAttributeAndModes(1, texgen.get(), osg::StateAttribute::ON);

		// 设置纹理环境
		stateset->setTextureAttribute(1, texenv.get());

		// 设置纹理状态
		node->setStateSet(stateset.get());
	}
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