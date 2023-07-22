
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
#include <osg/AutoTransform>
#include <osgText/Text>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <string>

using std::string;


// 创建自动变换节点
osg::ref_ptr<osg::Node> createAutoTransform(osg::Vec3 position, float size, string& label,
	osg::AutoTransform::AutoRotateMode autoMode, osgText::Text::AxisAlignment axisAlignment)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// 字体
	string font("fonts/cour.ttf");

	// 创建 Text 对象
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	geode->addDrawable(text.get());

	// 设置字体
	text->setFont(font);
	// 设置字体分辨率
	text->setFontResolution(128.0f, 128.0f);
	// 设置字体大小
	text->setCharacterSize(size);
	// 设置对齐方式
	text->setAlignment(osgText::Text::CENTER_CENTER);
	// 设置方向
	text->setAxisAlignment(axisAlignment);
	// 设置文字
	text->setText(label);

	// 关闭光照
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	// 创建自动变换节点
	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform();
	// 添加子节点
	at->addChild(geode.get());

	// 设置变换方式
	at->setAutoRotateMode(autoMode);
	// 根据屏幕大小来缩放节点，默认为false，设置true时，节点无法缩放
	at->setAutoScaleToScreen(false);
	// 设置缩放的最大和最小比例
	at->setMinimumScale(0.0f);
	at->setMaximumScale(5.0f);
	// 设置位置
	at->setPosition(position);

	return at.get();
}


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	string text("Fly to Sky");

	// 添加ROTATE_TO_SCREEN 模式变换节点
	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f), 
		60.0f, 
		text, 
		osg::AutoTransform::ROTATE_TO_SCREEN, 
		osgText::Text::XY_PLANE));

	// 添加NO_ROTATION 模式变换节点
	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f),
		60.0f,
		text,
		osg::AutoTransform::NO_ROTATION,
		osgText::Text::YZ_PLANE));

	// 添加ROTATE_TO_CAMERA 模式变换节点
	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f),
		60.0f,
		text,
		osg::AutoTransform::ROTATE_TO_CAMERA,
		osgText::Text::XY_PLANE));

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