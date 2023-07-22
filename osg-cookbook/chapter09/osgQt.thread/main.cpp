#include "viewerwidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    osg::Camera* camera = createCamera(50, 50, 640, 480);
    osg::Node* scene = osgDB::readNodeFile("cow.osg");

    ViewerWidget *widget = new ViewerWidget(camera, scene);
    widget->setGeometry(100, 100, 800, 600);
    widget->show();

    return a.exec();
}
