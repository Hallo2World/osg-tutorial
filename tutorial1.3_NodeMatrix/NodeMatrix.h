#pragma once
#include <osg/MatrixTransform>

class NodeMatrix :
	public osg::MatrixTransform
{
public:
	NodeMatrix();

	~NodeMatrix();
	/**
	* \brief ���õ�ǰģ��ת����ʽ
	*/
	void rotating(const osg::Vec3d& pivot, const osg::Vec3d& axis, float angularVelocity);

	/**
	* \brief ��תģ��
	*/
	void toRotate(const osg::Matrix &matrix);

	/**
	* \brief ��תģ��
	*/
	void toRotate(double angle, const osg::Vec3f &axis);

	/**
	* \brief ����ģ��
	*/
	void toScale(const osg::Matrix &matrix);

	/**
	* \brief ����ģ��
	*/
	void toScale(double sx, double sy, double sz);

	/**
	* \brief ��ģ���ƶ���ָ��λ��
	*/
	void toPosition(osg::Vec3d pos);

	/**
	* \brief ����ģ�ʹ�С
	*/
	void adapt(osg::BoundingSphere sphere);

	/**
	* \brief ����ӽڵ�
	*/
	void addChild2(osg::Node *node);

private:
	osg::ref_ptr<osg::MatrixTransform>	_matrix;
	osg::BoundingSphere				    _sphere;	// ģ�Ͱ�Χ��
};

