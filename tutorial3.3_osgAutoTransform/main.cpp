
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


// �����Զ��任�ڵ�
osg::ref_ptr<osg::Node> createAutoTransform(osg::Vec3 position, float size, string& label,
	osg::AutoTransform::AutoRotateMode autoMode, osgText::Text::AxisAlignment axisAlignment)
{
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();

	// ����
	string font("fonts/cour.ttf");

	// ���� Text ����
	osg::ref_ptr<osgText::Text> text = new osgText::Text();
	geode->addDrawable(text.get());

	// ��������
	text->setFont(font);
	// ��������ֱ���
	text->setFontResolution(128.0f, 128.0f);
	// ���������С
	text->setCharacterSize(size);
	// ���ö��뷽ʽ
	text->setAlignment(osgText::Text::CENTER_CENTER);
	// ���÷���
	text->setAxisAlignment(axisAlignment);
	// ��������
	text->setText(label);

	// �رչ���
	geode->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

	// �����Զ��任�ڵ�
	osg::ref_ptr<osg::AutoTransform> at = new osg::AutoTransform();
	// ����ӽڵ�
	at->addChild(geode.get());

	// ���ñ任��ʽ
	at->setAutoRotateMode(autoMode);
	// ������Ļ��С�����Žڵ㣬Ĭ��Ϊfalse������trueʱ���ڵ��޷�����
	at->setAutoScaleToScreen(false);
	// �������ŵ�������С����
	at->setMinimumScale(0.0f);
	at->setMaximumScale(5.0f);
	// ����λ��
	at->setPosition(position);

	return at.get();
}


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	string text("Fly to Sky");

	// ���ROTATE_TO_SCREEN ģʽ�任�ڵ�
	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f), 
		60.0f, 
		text, 
		osg::AutoTransform::ROTATE_TO_SCREEN, 
		osgText::Text::XY_PLANE));

	// ���NO_ROTATION ģʽ�任�ڵ�
	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f),
		60.0f,
		text,
		osg::AutoTransform::NO_ROTATION,
		osgText::Text::YZ_PLANE));

	// ���ROTATE_TO_CAMERA ģʽ�任�ڵ�
	root->addChild(createAutoTransform(osg::Vec3(0.0f, 0.0f, 0.0f),
		60.0f,
		text,
		osg::AutoTransform::ROTATE_TO_CAMERA,
		osgText::Text::XY_PLANE));

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