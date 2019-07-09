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
osg::Group* open_gltf(char*,int,char*);
int main(int argc, char *argv[])//ПЕРВЫЙ аргумент - путь, ВТОРОЙ - Режим (DEBUG -на экране отладочная инфа)
{
	//std::cout << argc;
	//std::cout << std::endl << argv[0] << std::endl << argv[1] << std::endl << argv[2] << std::endl << argv[3];
	osgViewer::Viewer viewer;
	osg::ref_ptr<osg::Group> groop = new osg::Group;
	osg::ref_ptr<osg::Group> gr = new osg::Group;
	//gr = open_gltf("D:/temp/test_gltf/gearboxassy/GearboxAssy.gltf");
	//gr = open_gltf("D:/temp/test_gltf/boxtextured/BoxTextured.gltf");
	//gr = open_gltf("D:/temp/test_gltf/engi/2CylinderEngine.gltf");
	//gr = open_gltf("D:/SDK/osg-src/OpenSceneGraph-Data-3.0.0/steampunk_underwater_explorer/scene.gltf");
	//gr = open_gltf("D:/temp/test_gltf/boxtextured/BoxTextured.gltf");
	//gr = open_gltf("C:/Users/Denis/Downloads/Malice_GLTF_222/export.gltf");
	//gr = open_gltf("D:/temp/test_gltf/Malice_GLTF_222/export.gltf");
	//gr = open_gltf("D:/SDK/osg-src/OpenSceneGraph-Data-3.0.0/Bridge_Enterprise_GLTF_20/export.gltf");
	char* temp_pointer;
	
	if (argv[1] != NULL)temp_pointer = argv[1];
	else
	{
		temp_pointer = "D:/temp/test_gltf/Malice_GLTF_222/export.gltf";//ЭТОТ ФАЙЛ БУДЕТ ПЫТАТЬСЯ ГРУЗИТЬ ПО УМОЛЧАНИЮ
	}
		gr = open_gltf(temp_pointer, argc, argv[2]);
		
	
	viewer.setSceneData(gr);
	viewer.setUpViewInWindow(100, 100, 800, 600, 0);
	//std::cout << "    " << std::endl << gr->getNumChildren();

	return viewer.run();
}
