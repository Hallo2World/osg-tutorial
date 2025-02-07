
#include <osgViewer/Viewer>

#include <osg/Node>
#include <osg/Geometry>
#include <osg/Image>
#include <osg/Geode>
#include <osg/Group>
#include <osg/Notify>
#include <osg/Texture>
#include <osg/StateSet>
#include <osg/StateAttribute>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>

#include <osgDB/Registry>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>

#include <osgUtil/Optimizer>

// 自定义 Copy类，用于输出拷贝信息
class GraphCopyOp : public osg::CopyOp
{
protected:
	// 节点映射表，用来保存 child 和拷贝，分别作为原象和象
	mutable std::map<const osg::Node*, osg::Node*> _nodeCopyMap;
public:
	inline GraphCopyOp(CopyFlags flags = SHALLOW_COPY) : osg::CopyOp(flags)
	{
		_nodeCopyMap.clear();
	}

	// 节点的 copy
	virtual osg::Node* operator()(const osg::Node* node) const
	{
		// 判断是否为深拷贝
		if (node && _flags & DEEP_COPY_NODES)
		{
				// 判断节点的父节点是否为多个，如果只要一个，直接深拷贝
			if (node->getNumParents() > 1)
			{
				// 判断是否已经拷贝
				if (_nodeCopyMap.find(node) != _nodeCopyMap.end())
				{
					std::cout << "Copy of node" << node << " " << node->getName() << "," << _nodeCopyMap[node] << ", will be reused" << std::endl;
					// 直接返回拷贝对象的地址
					return (osg::Node*)(_nodeCopyMap[node]);
				}
				else
				{
					// 进行拷贝并在映射表中保存拷贝对象
					osg::Node* newNode = dynamic_cast<osg::Node*>(node->clone(*this));
					_nodeCopyMap[node] = newNode;
					return newNode;
				}
			}
			else
			{
				// 直接拷贝
				return dynamic_cast<osg::Node*>(node->clone(*this));
			}
		}
		else
		{
			// 直接返回地址
			return const_cast<osg::Node*>(node);
		}
	}
};

int main()
{
	// 创建 Viewer对象，场景浏览器
	osg::ref_ptr<osgViewer::Viewer> viewer = new osgViewer::Viewer();

	osg::ref_ptr<osg::Group> rootnode = new osg::Group();

	osg::ref_ptr<osg::Node> node = osgDB::readNodeFile("glider.osg");

	// 子节点pat,共享node
	osg::ref_ptr<osg::PositionAttitudeTransform> pat = new osg::PositionAttitudeTransform();
	pat->setPosition(osg::Vec3(5.0f, 0.0f, 0.0f));
	pat->addChild(node.get());

	// 子节点mt，共享node
	osg::ref_ptr<osg::MatrixTransform> mt = new osg::MatrixTransform();
	osg::Matrix m;
	m.makeScale(2.0f, 2.0f, 2.0f);
	mt->setMatrix(m);
	mt->addChild(node.get());

	// 添加子节点
	rootnode->addChild(pat.get());
	rootnode->addChild(mt.get());

	// 优化场景数据
	osgUtil::Optimizer optimizer;
	optimizer.optimize(rootnode.get());

	// 一个多父节点和一个子节点场景的默认深拷贝
	osg::ref_ptr<osg::Node> deepCopy = dynamic_cast<osg::Node*>(rootnode->clone(osg::CopyOp::DEEP_COPY_ALL));
	std::cout << "完成一个多父节点和一个子节点场景的默认深拷贝" << std::endl << std::endl;
	osgDB::writeNodeFile(*(deepCopy.get()), "deepCopy.osg");

	// 一个多父节点和一个子节点场景的浅拷贝
	osg::ref_ptr<osg::Node> myShallowCopy = dynamic_cast<osg::Node*>(rootnode->clone(GraphCopyOp(osg::CopyOp::SHALLOW_COPY)));
	std::cout << "完成一个多父节点和一个子节点场景的浅拷贝" << std::endl << std::endl;
	osgDB::writeNodeFile(*(myShallowCopy.get()), "myShallowCopy.osg");

	// 一个多父节点和一个子节点场景的深拷贝
	osg::ref_ptr<osg::Node> myDeepCopy = dynamic_cast<osg::Node*>(rootnode->clone(GraphCopyOp(osg::CopyOp::DEEP_COPY_ALL)));
	std::cout << "完成一个多父节点和一个子节点场景的深拷贝" << std::endl << std::endl;
	osgDB::writeNodeFile(*(myDeepCopy.get()), "myDeepCopy.osg");
		
	// 设置场景数据
	viewer->setSceneData(rootnode.get());

	//这里是单屏幕显示
	viewer->setUpViewOnSingleScreen(0);

	// 初始化并创建窗口
	viewer->realize();

	// 开始渲染
	viewer->run();

	return 0;
}