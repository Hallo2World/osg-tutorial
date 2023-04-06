#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>
#include "NodeMatrix.h"

#include <string>

int main()
{
	std::string str;
	int c = 0;
	str += c;
	str += c;
	str += 97;
	str += 98;

	int n = str.size();


	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;
	osg::ref_ptr<NodeMatrix> nm = new NodeMatrix;
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("glider.osg");

	nm->addChild2(osgDB::readNodeFile("TrCow.osg"));
	//nm->rotating(osg::Vec3d(0.0, 0.0, 0.0), osg::Z_AXIS, 1.0);
	//nm->toRotate(1, osg::Y_AXIS);
	nm->toPosition(osg::Vec3d(0.0, 0.0, 0.0));
	nm->adapt(node->getBound());

	group->addChild(node);
	group->addChild(nm);

	viewer->setSceneData(group);
	 
	return viewer->run();
}