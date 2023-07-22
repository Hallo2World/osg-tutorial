#ifndef VIEWER_WIDGET_H
#define VIEWER_WIDGET_H

#include <QWidget>

#include <QtCore/QtCore>
#include <QtGui/QtGui>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/Viewer>
#include <osgQt/GraphicsWindowQt>

osg::Camera* createCamera(int x, int y, int w, int h);

class RenderThread : public QThread
{
public:
    RenderThread() : QThread(), _viewerPtr(nullptr) {}

    ~RenderThread() override
    {
        if (_viewerPtr) {
            _viewerPtr->setDone(true);
        }
        wait();
    }
protected:
    void run() override
    {
        if (_viewerPtr) {
            _viewerPtr->run();
        }
    }
public:
    osgViewer::Viewer *_viewerPtr = nullptr;
};

class ViewerWidget : public QWidget
{
public:
    explicit ViewerWidget(osg::Camera* camera, osg::Node* scene);

private:
    osgViewer::Viewer _viewer;
    RenderThread _thread;
};

#endif // VIEWER_WIDGET_H
