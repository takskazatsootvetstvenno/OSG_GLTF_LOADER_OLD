#include <osgViewer/Viewer>
#include<osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osg/Geode>
#include <osg/Group>
#include <iostream>
#include <fstream> // подключаем библиотеку
//#include <osg::ref_ptr>
//#include <D:\OpenGl\OpenSceneGraph-3.6.3-VC2017-64-Debug\bin\osgPlugins-3.6.3\osgdb_freetyped.dll>
//#pragma comment (lib, "zlibd.lib")
#include <osg/Geode>
#include <osg/Geometry>
osg::Group* open_gltf(char*);
int main()
{
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> groop = new osg::Group;
	osg::ref_ptr<osg::Group> gr = new osg::Group;
	//gr = open_gltf("D:/temp/test_gltf/gearboxassy/GearboxAssy.gltf");
	gr = open_gltf("D:/temp/test_gltf/tri.gltf");
	//gr = open_gltf("C:/Users/Denis/Downloads/Malice_GLTF_222/export.gltf");
	viewer.setSceneData(gr);
	//std::cout << "    " << std::endl << gr->getNumChildren();

	return viewer.run();
}
