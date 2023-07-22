
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


int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// ����һ���ڵ㣬��ȡţģ��
	osg::ref_ptr<osg::Node> node1 = new osg::Node();
	node1 = osgDB::readNodeFile("cow.osg");

	// ����һ���ڵ㣬��ȡ�����ģ��
	osg::ref_ptr<osg::Node> node2 = osgDB::readNodeFile("glider.osg");
	
	// ����һ�����ؽڵ㣬ֻ��Ⱦ�����������Ⱦţ
	osg::ref_ptr<osg::Switch> swtich = new osg::Switch();
	// ���ţ��ģ�ͣ�������Ⱦ��Ĭ��Ϊtrue
	swtich->addChild(node1.get(), false);
	// ��ӻ������ģ�ͣ�״̬Ϊ��Ⱦ
	swtich->addChild(node2.get(), true);

	root->addChild(swtich.get());

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