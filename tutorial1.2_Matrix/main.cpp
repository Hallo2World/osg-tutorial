#include <osgViewer/Viewer>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/ViewerEventHandlers>
#include <osg/MatrixTransform>
#include <osg/AnimationPath>
#include <osg/PositionAttitudeTransform>

//Output A node
void ExportANode()
{
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("cow.osg");
	osg::ref_ptr<osg::MatrixTransform> matrix = new osg::MatrixTransform;

	matrix->addChild(node);
	matrix->setMatrix(osg::Matrix::translate(50.0, 0.0, 0.0));

	osgDB::ReaderWriter::WriteResult result = osgDB::Registry::instance()->writeNode(*matrix, "TrCow.osg", osgDB::Registry::instance()->getOptions());
	if (result.success())
	{
		osg::notify(osg::NOTICE) << "Write node succesffully" << std::endl;
	}
}

// Matrix Operation
osg::ref_ptr<osg::Node> MatrixOperation()
{
	osg::ref_ptr<osg::Group> group = new osg::Group;
	osg::ref_ptr<osg::MatrixTransform> matrix = new osg::MatrixTransform;	// ->osg::Transform->osg::Group::->os::Node
	osg::ref_ptr<osg::MatrixTransform> matrix2 = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform> matrix3 = new osg::MatrixTransform;
	osg::ref_ptr<osg::MatrixTransform> matrix4 = new osg::MatrixTransform;
	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("glider.osg");

	matrix2->addChild(node);
	matrix2->setMatrix(osg::Matrix::translate(5.0, 0.0, 0.0));	// 移动
	matrix->setUpdateCallback(new osg::AnimationPathCallback(osg::Vec3(4.0, 0.0, 0.0), osg::Z_AXIS, 1.0));	// 动画，按Z轴旋转
	matrix->addChild(matrix2);

	matrix4->addChild(node);
	matrix4->setMatrix(osg::Matrix::translate(-5.0, 0.0, 0.0));	// 移动
	matrix3->setUpdateCallback(new osg::AnimationPathCallback(osg::Vec3(-4.0, 0.0, 0.0), osg::Z_AXIS, 2.0));	// 动画，按Z轴旋转
	matrix3->addChild(matrix4);
	

	group->addChild(node);
	group->addChild(matrix);
	group->addChild(matrix3);

	return group;
}

int main()
{
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer;	// Create Viewer
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform;

	//viewer->setSceneData(MatrixOperation());

	//ExportANode();
	osg::ref_ptr<osg::Group> group = new osg::Group; 
	group->addChild(osgDB::readNodeFile("cow.osg"));
	pat->addChild(osgDB::readNodeFile("TrCow.osg"));
	pat->setPosition(osg::Vec3d(-50.0, 0, 0));

	group->addChild(pat);
	viewer->setSceneData(group);
	 
	return viewer->run();
}