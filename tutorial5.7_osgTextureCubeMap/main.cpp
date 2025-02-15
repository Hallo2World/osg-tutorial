#include <osgViewer/Viewer>

#include <osg/Vec3>
#include <osg/Vec4>
#include <osg/Quat>
#include <osg/Matrix>
#include <osg/ShapeDrawable>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Transform>
#include <osg/Material>
#include <osg/NodeCallback>
#include <osg/Depth>
#include <osg/CullFace>
#include <osg/TexMat>
#include <osg/TexGen>
#include <osg/TexEnv>
#include <osg/TextureCubeMap>

#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

#include <iostream>

// 立方体纹理示例

// 读取立方图
osg::ref_ptr<osg::TextureCubeMap> readCubeMap()
{
	osg::ref_ptr<osg::TextureCubeMap> cubemap = new osg::TextureCubeMap();

	osg::ref_ptr<osg::Image> imagePosX = osgDB::readImageFile("right.jpg");
	osg::ref_ptr<osg::Image> imageNegX = osgDB::readImageFile("left.jpg");
	osg::ref_ptr<osg::Image> imagePosY = osgDB::readImageFile("front.jpg");
	osg::ref_ptr<osg::Image> imageNegY = osgDB::readImageFile("back.jpg");
	osg::ref_ptr<osg::Image> imagePosZ = osgDB::readImageFile("up.jpg");
	osg::ref_ptr<osg::Image> imageNegZ = osgDB::readImageFile("down.jpg");

	if (imagePosX.get() && imageNegX.get() && imagePosY.get() && imageNegY.get() && imagePosZ.get() && imageNegZ.get()) {
		// 设置立方体图的6个面的贴图
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_X, imagePosX.get());
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_X, imageNegX.get());
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_Y, imagePosY.get());
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Y, imageNegY.get());
		cubemap->setImage(osg::TextureCubeMap::POSITIVE_Z, imagePosZ.get());
		cubemap->setImage(osg::TextureCubeMap::NEGATIVE_Z, imageNegZ.get());

		// 设置纹理环绕模式
		cubemap->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP_TO_EDGE);
		cubemap->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP_TO_EDGE);
		cubemap->setWrap(osg::Texture::WRAP_R, osg::Texture::CLAMP_TO_EDGE);

		// 设置滤波：线形和mipmap
		cubemap->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
		cubemap->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	}
	return cubemap.get();
}


// 更新立方体图纹理
struct TexMatCallback : public osg::NodeCallback
{
	// 纹理矩阵
	osg::TexMat& _texMat;
public:
	TexMatCallback(osg::TexMat& tm) :
		_texMat(tm) {
		//
	}

	virtual void operator()(osg::Node* node, osg::NodeVisitor* nv) {
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv) {
			// 得到模型视图矩阵并设置旋转角度
			const osg::Matrix& MV = *(cv->getModelViewMatrix());
			const osg::Matrix R = osg::Matrix::rotate(osg::DegreesToRadians(112.0f), 0.0f, 0.0f, 1.0f) * osg::Matrix::rotate(osg::DegreesToRadians(90.0f), 1.0f, 0.0f, 0.0f);
			osg::Quat q = MV.getRotate();
			const osg::Matrix C = osg::Matrix::rotate(q.inverse());

			// 设置纹理矩阵
			_texMat.setMatrix(C*R);
		}
		traverse(node, nv);
	}
};

// 一个变换类，使天空盒绕视点旋转
class MoveEarthSkyWithEyePointTransform : public osg::Transform
{
public:
	// 局部矩阵计算成世界矩阵
	virtual bool computeLocalToWorldMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
	{
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv)
		{
			osg::Vec3 eyePointLocal = cv->getEyeLocal();
			matrix.preMult(osg::Matrix::translate(eyePointLocal));
		}
		return true;
	}

	// 世界矩阵计算成局部矩阵
	virtual bool computeWorldToLocalMatrix(osg::Matrix& matrix, osg::NodeVisitor* nv) const
	{
		osgUtil::CullVisitor* cv = dynamic_cast<osgUtil::CullVisitor*>(nv);
		if (cv)
		{
			osg::Vec3 eyePointLocal = cv->getEyeLocal();
			matrix.postMult(osg::Matrix::translate(eyePointLocal));
		}
		return true;
	}

};

// 创建天空盒
osg::ref_ptr<osg::Node> createSkyBox()
{
	osg::ref_ptr<osg::StateSet> stateset = new osg::StateSet();

	// 设置纹理映射方式，指定为替代方式，即纹理中的颜色替代原来的颜色
	osg::ref_ptr<osg::TexEnv> te = new osg::TexEnv;
	te->setMode(osg::TexEnv::REPLACE);
	stateset->setTextureAttributeAndModes(0, te.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	// 自动生成纹理坐标，反射方式为（REFLECTION_MAP）
	/*
		NORMAL_MAP 标准模式—立方图纹理
		REFLECTION_MAP 反射模式—球体纹理
		SPHERE_MAP 球体模型—球体纹理
	*/
	osg::ref_ptr<osg::TexGen> tg = new osg::TexGen();
	tg->setMode(osg::TexGen::NORMAL_MAP);
	stateset->setTextureAttributeAndModes(0, tg.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	// 设置纹理矩阵
	osg::ref_ptr<osg::TexMat> tm = new osg::TexMat;
	stateset->setTextureAttribute(0, tm.get());

	// 设置立方图纹理
	osg::ref_ptr<osg::TextureCubeMap> skymap = readCubeMap();
	stateset->setTextureAttributeAndModes(0, skymap.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	stateset->setMode(GL_CULL_FACE, osg::StateAttribute::OFF);

	// 将深度设为远平面
	osg::ref_ptr<osg::Depth> depth = new osg::Depth();
	depth->setFunction(osg::Depth::ALWAYS);
	depth->setRange(1.0f, 1.0); // 远平面
	stateset->setAttributeAndModes(depth, osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE);

	// 设置渲染顺序为-1，先渲染
	stateset->setRenderBinDetails(-1, "RenderBin");

	osg::ref_ptr<osg::Drawable> drawable = new osg::ShapeDrawable(new osg::Sphere(osg::Vec3(0.0f, 0.0f, 0.0f), 1));

	// 把球体加入到叶节点
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	geode->setCullingActive(false);
	geode->setStateSet(stateset.get());
	geode->addDrawable(drawable.get());

	// 设置变换
	osg::ref_ptr<osg::Transform> transform = new MoveEarthSkyWithEyePointTransform();
	transform->setCullingActive(false);
	transform->addChild(geode.get());

	osg::ref_ptr<osg::ClearNode> clearNode = new osg::ClearNode();
	clearNode->setCullCallback(new TexMatCallback(*tm));
	clearNode->addChild(transform.get());

	return clearNode.get();


}


int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> root = new osg::Group();

	// 加入天空盒
	root->addChild(createSkyBox());

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