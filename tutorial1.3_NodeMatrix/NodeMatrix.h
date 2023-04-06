#pragma once
#include <osg/MatrixTransform>

class NodeMatrix :
	public osg::MatrixTransform
{
public:
	NodeMatrix();

	~NodeMatrix();
	/**
	* \brief 设置当前模型转动方式
	*/
	void rotating(const osg::Vec3d& pivot, const osg::Vec3d& axis, float angularVelocity);

	/**
	* \brief 旋转模型
	*/
	void toRotate(const osg::Matrix &matrix);

	/**
	* \brief 旋转模型
	*/
	void toRotate(double angle, const osg::Vec3f &axis);

	/**
	* \brief 缩放模型
	*/
	void toScale(const osg::Matrix &matrix);

	/**
	* \brief 缩放模型
	*/
	void toScale(double sx, double sy, double sz);

	/**
	* \brief 将模型移动到指定位置
	*/
	void toPosition(osg::Vec3d pos);

	/**
	* \brief 限制模型大小
	*/
	void adapt(osg::BoundingSphere sphere);

	/**
	* \brief 添加子节点
	*/
	void addChild2(osg::Node *node);

private:
	osg::ref_ptr<osg::MatrixTransform>	_matrix;
	osg::BoundingSphere				    _sphere;	// 模型包围盒
};

