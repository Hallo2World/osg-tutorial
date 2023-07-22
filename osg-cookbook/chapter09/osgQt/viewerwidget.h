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

class ViewerWidget : public QWidget
{
public:
    explicit ViewerWidget(osg::Camera* camera, osg::Node* scene);

protected:
    void paintEvent(QPaintEvent *event) override
    {
        _viewer.frame();
    }
private:
    osgViewer::Viewer _viewer;
    QTimer _timer;
};

#endif // VIEWER_WIDGET_H
