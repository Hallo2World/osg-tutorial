#include "viewerwidget.h"
#include <QVBoxLayout>

osg::Camera* createCamera(int x, int y, int w, int h)
{
    osg::DisplaySettings* ds = osg::DisplaySettings::instance().get();

    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;
    traits->windowDecoration = false;
    traits->x = x;
    traits->y = y;
    traits->width = w;
    traits->height = h;
    traits->doubleBuffer = true;

    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setGraphicsContext(new osgQt::GraphicsWindowQt(traits.get()));
    camera->setClearColor(osg::Vec4(0.2f, 0.2f, 0.6f, 1.0f));
    camera->setViewport(new osg::Viewport(0, 0 , traits->width, traits->height));
    camera->setProjectionMatrixAsPerspective(30.0, static_cast<double>(traits->width) / static_cast<double>(traits->height), 1.0, 10000.0);

    return camera.release();
}

ViewerWidget::ViewerWidget(osg::Camera* camera, osg::Node* scene)
{
    _viewer.setCamera(camera);
    _viewer.setSceneData(scene);
    _viewer.addEventHandler(new osgViewer::StatsHandler);
    _viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    _viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);

    if (osgQt::GraphicsWindowQt* gw = dynamic_cast<osgQt::GraphicsWindowQt*>(camera->getGraphicsContext())) {
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(dynamic_cast<QWidget*>(gw->getGLWidget()));
        setLayout(layout);
    }

    connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
    _timer.start(40);
}

