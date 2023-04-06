#include "NodeMatrix.h"
#include <osg/AnimationPath>

NodeMatrix::NodeMatrix()
{
	_matrix = new osg::MatrixTransform;
	addChild(_matrix);
}

NodeMatrix::~NodeMatrix()
{
}

void NodeMatrix::rotating(const osg::Vec3d& pivot, const osg::Vec3d& axis, float angularVelocity)
{
	setUpdateCallback(new osg::AnimationPathCallback(pivot, axis, angularVelocity));
}

void NodeMatrix::toRotate(const osg::Matrix &matrix)
{
	_matrix->setMatrix(matrix);
}

void NodeMatrix::toRotate(double angle, const osg::Vec3f &axis)
{
	_matrix->setMatrix(osg::Matrix::rotate(angle, axis));
}

void NodeMatrix::toScale(const osg::Matrix &matrix)
{
	_matrix->setMatrix(matrix);
}

void NodeMatrix::toScale(double sx, double sy, double sz)
{
	_matrix->setMatrix(osg::Matrix::scale(sx, sy, sz));
}

void NodeMatrix::toPosition(osg::Vec3d pos)
{
	osg::Vec3d cps;	// 模型中心点位置
	cps.set(-_sphere.center().x(), -_sphere.center().y(), -_sphere.center().z());
	_matrix->setMatrix(osg::Matrix::translate(cps) * osg::Matrix::translate(pos));
}

void NodeMatrix::adapt(osg::BoundingSphere sphere)
{
	float ratio = sphere.radius() / _sphere.radius();
	_matrix->setMatrix(osg::Matrix::scale(ratio, ratio, ratio));
}

void NodeMatrix::addChild2(osg::Node *node)
{
	_matrix->addChild(node);
	_sphere = node->getBound();
	osg::notify(osg::NOTICE) << _sphere.center().x() << "  " << _sphere.center().y() << "  " << _sphere.center().z() << std::endl;
}