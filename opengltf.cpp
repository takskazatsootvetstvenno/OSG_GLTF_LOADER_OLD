#include<iostream>
#include<fstream>
#include<vector>
#include <cstdlib>
#include <json.h> 
#include <osgViewer/Viewer>
#include<osgDB/WriteFile>
#include <osgDB/ReadFile>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osg/MatrixTransform>
#include <osg/StateAttribute>
#include <osg/Group>
#include <base64.h>
#include <base64.cpp>
//#include <iostream>
struct scenn
{
	osg::ref_ptr<osg::Group> sc;
	std::vector<int> children;
};
struct nodd
{
	osg::ref_ptr<osg::Group> gr;
	
	std::vector<int> children;
	double matrix[16];
	double translation[3];
	double scale[3];
	int mesh=-1;// только 1 mesh! -1 значит mesh не привязан
	int camera = -1;//-1 значит не привязан
};
struct version_of_file
{
	char* version;
	char* generator;
};
struct cameras
{
	osg::ref_ptr<osg::Camera> cm;

	char* type_of_view; //"perspective"
	double aspectRatio;
	double yfov;
	double zfar;
	double znear;
};
struct meshes
{
	char* name;
	osg::ref_ptr<osg::Geode> mh;
	int NORMAL=-1;
	int POSITION=-1;
	int TEXCOORD_0 = -1;
	int TEXCOORD_1 = -1;

	int indices=-1;
	int mode=4;
	int material=-1;
};
struct accessors
{
	char* type;
	std::vector<int> min;
	std::vector<int> max;

	int count;
	bool normalized=false;

	int componentType;
	int byteOffset=0;
	int bufferView;
};
struct buffers
{
	char* uri;
//	std::vector<unsigned char> byte_file_data;
	char* byte_file_data;
	long int byteLength;
};
struct bufferViews
{
	int buffer;
	int byteOffset;

	int byteLength;
	int byteStride=0;
	int target;
	char* name;
};
struct materials
{
	double baseColorFactor[4];//default 1 1 1 1
	double metallicFactor=1;//default 1
	double emissiveFactor[3];//default 0 0 0
	double roughnessFactor = 1;//default 1
	bool doubleSided=false;//default false

	
	

	int normalTexture_index = -1;
	double normalTexture_scale=1;
	int normalTexture_texCoord=0;

	int baseColorTexture_index = -1;
	int baseColorTexture_texCoord = -1;

	int metallicRoughnessTexture_index = -1;
	int metallicRoughnessTexture_texCoord = -1;

	char* alphaModee = "OPAQUE";
	char* name;
};
struct textures
{
	int sampler=-1;
	int source=-1;
};
struct images{
char* uri;
osg::ref_ptr<osg::Image> image;
//

};
struct samplers
{
	int magFilter;
	int minFilter;
	int wrapS;
	int wrapT;
};
//osg::ref_ptr<osg::Geode> mesh_bank = new osg::Geode;
//osg::ref_ptr<osg::Geode> mesh_bank = new osg::Geode;
using namespace std;
std::vector<samplers> sampler;
samplers my_sampler;

std::vector<images> image;
images my_image;

std::vector<textures> texture;
textures my_texture;
std::vector<buffers> bufs;
buffers my_bufs;

std::vector<bufferViews> bufvs;
bufferViews bfs;

std::vector<accessors> acces;
accessors acc;

std::vector<scenn> scenns;
scenn scenna;
std::vector<nodd> nd;//nodes
nodd ndd;
std::vector<cameras> cam;
cameras my_camera;
version_of_file ver;
std::vector<meshes> mhs;
meshes meh;
std::vector<materials> mater;
materials my_material;
/*osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
// Создать массив для хранения четырех вершин.
osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
geom->setVertexArray(v.get());
v->push_back(osg::Vec3(-1.f, 0.f, -1.f));
v->push_back(osg::Vec3(1.f, 0.f, -1.f));
v->push_back(osg::Vec3(1.f, 0.f, 1.f));
v->push_back(osg::Vec3(-1.f, 0.f, 1.f));
// Создать массив их четырех цветов
osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
geom->setColorArray(c.get());
geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
c->push_back(osg::Vec4(1.f, 0.f, 0.f, 1.f));
c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));
// Создать массив содержащий одну нормаль.
osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
geom->setNormalArray(n.get());
geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
n->push_back(osg::Vec3(0.f, -1.f, 0.f));
// Получить прямоугольник из четырех вершин, из ранее
// подготовленных данных.
geom->addPrimitiveSet(
new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, 4));
// Добавить Geometry (Drawable) в Geode и вернуть Geode.
osg::ref_ptr<osg::Geode> geode = new osg::Geode;

osg::ref_ptr<osg::Geode> geode2 = new osg::Geode;
geode->addDrawable(geom.get());*/
void decoder_samplers(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {

								   for (Json::ArrayIndex i = 0; i < size; i++) {
									   if (was == 0){
										  sampler.push_back(my_sampler);
										   index++;
									   }
									   decoder_samplers(val[i], was, index);

								   }
							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 9;
										if (key == "magFilter")
										{
											//			ver.version = (char*)val[key].asCString();
											sampler[index].magFilter = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "version";
											was = 8;
										}
										if (key == "minFilter")
										{
											//ver.generator = (char*)val[key].asCString();
											sampler[index].minFilter = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "generator";
											was = 7;
										}
										if (key == "wrapS")
										{
											//ver.generator = (char*)val[key].asCString();
											sampler[index].wrapS = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "generator";
											was = 6;
										}
										if (key == "wrapT")
										{
											//ver.generator = (char*)val[key].asCString();
											sampler[index].wrapT = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "generator";
											was = 5;
										}
										decoder_samplers(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		std::exit(0);
	}
}
void decoder_images(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {

								   for (Json::ArrayIndex i = 0; i < size; i++) {
									   if (was == 0){
										   image.push_back(my_image);
										   index++;
									   }
									   decoder_images(val[i], was, index);

								   }
							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 7;
										if (key == "uri")
										{
												image[index].uri = (char*)val[key].asCString();
											//texture[index].sampler = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "version";
											was = 6;
										}
									/*	if (key == "source")
										{
											//ver.generator = (char*)val[key].asCString();
											texture[index].source = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "generator";
											was = 5;
										}*/
										decoder_images(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		std::exit(0);
	}
}
void decoder_textures(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {

								   for (Json::ArrayIndex i = 0; i < size; i++) {
									   if (was == 0){
										   texture.push_back(my_texture);
										   index++;
									   }
									   decoder_textures(val[i], was, index);

								   }
							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 7;
										if (key == "sampler")
										{
								//			ver.version = (char*)val[key].asCString();
											texture[index].sampler = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "version";
											was = 6;
										}
										if (key == "source")
										{
											//ver.generator = (char*)val[key].asCString();
											texture[index].source = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "generator";
											was = 5;
										}
										decoder_textures(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		std::exit(0);
	}
}
void decode_base64_F(char *decode, unsigned int i, char**ptr_to_decoder)//~
{
	std::string decoded = base64_decode(decode);
	char* dec = new char[bufs[i].byteLength];
	for (int j = 0; j < bufs[i].byteLength;j++)
	dec[j] = decoded[j];
	bufs[i].byte_file_data = dec;
}
void decoder_materials(const Json::Value& val, int was = 0, int index = 0){
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {

									   if (was == 0){

										   //   scenna.children.push_back(i);
										   //acces.push_back(acc);
										   //   scenna.children.push_back(i);
										   mater.push_back(my_material);
										   index++;
									   }
									   if (was == 1){//emissiveFactor
										   mater[index].emissiveFactor[i] = val[i].asDouble();
									//	   acces[index].max.push_back(val[i].asLargestInt());
									   }
									  
									   if (was == 4){//baseColorFactor

										   // mater[index].metallicRoughnessTexture_index =
										   mater[index].baseColorFactor[i] = val[i].asDouble();
										   //  acces[index].min.push_back(val[i].asLargestInt());
										 //  was = 13;
									   }
									   
									   decoder_materials(val[i], was, index);


									   //  scenna.sc = new osg::ref_ptr<osg::Group>;
								   }



							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i < keys.size(); i++) {
										const string& key = keys[i];
										if(was==0)was = 11;
										if (key == "name")
										{
											//	mhs[index].NORMAL = val[key].asLargestInt();
											mater[index].name = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "type";
							//				was = 10;
										}
										if (key == "alphaMode")
										{
											//	mhs[index].NORMAL = val[key].asLargestInt();
											mater[index].alphaModee = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "type";
							//				was = 9;
										}
										if (key == "doubleSided")
										{
											mater[index].doubleSided = (char*)val[key].asBool();
											//	acces[index].count = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "count";
								//			was = 8;
										}

										if (key == "roughnessFactor")
										{
											mater[index].roughnessFactor = val[key].asDouble();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "componentType";
								//			was = 7;
										}
										if (key == "metallicFactor")
										{
											mater[index].metallicFactor = val[key].asDouble();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "byteOffset";
								//			was = 6;
										}
										if (key == "normalTexture")//
										{
											//	acces[index].bufferView = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "bufferView";
											was = 5;
										}
										if (key == "baseColorFactor")//
										{
											//mhs[index].material = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "min";
											was = 4;
										}
										if (key == "baseColorTexture")
										{
											//mhs[index].material = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "max";
											was = 3;
										//	decoder_materials(val[key], was, index);
										}
										if (key == "metallicRoughnessTexture")
										{
											//mhs[index].material = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "max";
										//	decoder_materials(val[key], was, index);
											was = 2;
										}
										if (key == "emissiveFactor")
										{
											//mhs[index].material = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "max";
											was = 1;
										}
										if (key == "index")
										{
											if (was == 3)mater[index].baseColorTexture_index = val[key].asLargestInt();
											if (was == 2)mater[index].metallicRoughnessTexture_index = val[key].asLargestInt();
											if (was == 5)mater[index].normalTexture_index = val[key].asLargestInt();
										}
										if (key == "texCoord")
										{
											if (was == 5)mater[index].normalTexture_texCoord = val[key].asLargestInt();
											if (was == 3)mater[index].baseColorTexture_texCoord = val[key].asLargestInt();
											if (was == 2)mater[index].metallicRoughnessTexture_texCoord = val[key].asLargestInt();
										}
										{
											if (key == "scale")
											if(was==5)mater[index].normalTexture_scale = val[key].asLargestInt();
										}
										/*if (was == 2){//metallicRoughnessTexture
											//if (key == "index")
											if (key == "texCoord")
											was = 12;
										}
										if (was == 3){//baseColorTexture
											if (key == "index")
												mater[index].baseColorTexture_index = val[key].asLargestInt();
											if (key == "texCoord")
												mater[index].baseColorTexture_texCoord = val[key].asLargestInt();

											// mater[index].metallicRoughnessTexture_index =
											//  acces[index].min.push_back(val[i].asLargestInt());
											was = 13;
										}*/
										//if (was == 5){//normalTexture
										//	if (key == "index")
												
										//	if (key == "texCoord")
						
											// mater[index].metallicRoughnessTexture_index =

											//  acces[index].min.push_back(val[i].asLargestInt());
										//	was = 15;
										//}
										decoder_materials(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_buffers(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {

									   if (was == 0){
										   bufs.push_back(my_bufs);
										   index++;
									   }
									   decoder_buffers(val[i], was, index);
								   }
							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 8;
										if (key == "uri")
										{
											//	mhs[index].NORMAL = val[key].asLargestInt();
											bufs[index].uri = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											cout << "uri";
											was = 2;
										}
										if (key == "byteLength")
										{
											bufs[index].byteLength = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											cout << "byteLength";
											was = 1;
										}
										decoder_buffers(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_bufferViews(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {

									   if (was == 0){

										   //   scenna.children.push_back(i);
										   bufvs.push_back(bfs);
										   //   scenna.children.push_back(i);
										   index++;
									   }
									   decoder_bufferViews(val[i], was, index);


									   //  scenna.sc = new osg::ref_ptr<osg::Group>;
								   }



							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 8;
										if (key == "name")
										{
											//	mhs[index].NORMAL = val[key].asLargestInt();
											bufvs[index].name = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "name";
											was = 7;
										}
										if (key == "buffer")
										{
											bufvs[index].buffer = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "buffer";
											was = 6;
										}
										if (key == "byteLength")
										{
											bufvs[index].byteLength = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "byteLength";
											was = 5;
										}
										if (key == "byteOffset")
										{
											bufvs[index].byteOffset = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "byteOffset";
											was = 4;
										}
										if (key == "byteStride")
										{
											bufvs[index].byteStride = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "byteStride";
											was = 3;
										}
										if (key == "target")
										{
											bufvs[index].target = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "target";
											was = 2;
										}

										decoder_bufferViews(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_accessors(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {

									   if (was == 0){
											
										   //   scenna.children.push_back(i);
										   acces.push_back(acc);
										   //   scenna.children.push_back(i);
										
										   index++;
									   }
									   if (was == 1){
										   acces[index].max.push_back(val[i].asLargestInt());
									   }
									   if (was == 2){
										   acces[index].min.push_back(val[i].asLargestInt());
									   }
									   decoder_accessors(val[i], was, index);


									   //  scenna.sc = new osg::ref_ptr<osg::Group>;
								   }



							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 8;
										if (key == "type")
										{
											//	mhs[index].NORMAL = val[key].asLargestInt();
											acces[index].type = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "type";
											was = 7;
										}
										if (key == "count")
										{
											acces[index].count = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "count";
											was = 6;
										}

										if (key == "componentType")
										{
											acces[index].componentType = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "componentType";
											was = 5;
										}
										if (key == "byteOffset")
										{
											acces[index].byteOffset = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "byteOffset";
											was = 4;
										}
										if (key == "bufferView")
										{
											acces[index].bufferView = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "bufferView";
											was = 3;
										}
										if (key == "min")
										{
											//mhs[index].material = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "min";
											was = 2;
										}
										if (key == "max")
										{
											//mhs[index].material = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "max";
											was = 1;
										}

										decoder_accessors(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_meshes(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {
									  
									   if (was == 0){
										   osg::ref_ptr<osg::Geode> temp_geode = new osg::Geode;
										   meh.mh = temp_geode.get();
										   //   scenna.children.push_back(i);
										   mhs.push_back(meh);
										    index++;
									   }
										   decoder_meshes(val[i], was, index);
									 
									 
									   //  scenna.sc = new osg::ref_ptr<osg::Group>;
								   }



							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 8;
										if (key == "attributes")//ignore
										{
											was = 9;
										}
										if (key == "name")
										{
										//	mhs[index].NORMAL = val[key].asLargestInt();
											mhs[index].name = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "name";
											was = 8;
										}
										if (key == "TEXCOORD_1")
										{
											mhs[index].TEXCOORD_1 = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "NORMAL";
											was = 7;
										}
										if (key == "TEXCOORD_0")
										{
											mhs[index].TEXCOORD_0 = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "NORMAL";
											was = 6;
										}
										if (key == "NORMAL")
										{
											mhs[index].NORMAL = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "NORMAL";
											was = 5;
										}
										
										if (key == "POSITION")
										{
											mhs[index].POSITION = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "POSITION";
											was = 4;
										}
										if (key == "indices")
										{
											mhs[index].indices = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "indices";
											was = 3;
										}
										if (key == "mode")
										{
											mhs[index].mode = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "mode";
											was = 2;
										}
										if (key == "material")
										{
											mhs[index].material = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "material";
											was = 1;
										}

										decoder_meshes(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_version(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {
									   //  if (was == 0){
									   /*osg::ref_ptr<osg::Camera> temp_camera = new osg::Camera;
									   my_camera.cm = temp_camera.get();
									   //   scenna.children.push_back(i);
									   cam.push_back(my_camera);
									   index++;*/
									   decoder_version(val[i], was, index);
									   //   }
									   // if (was == 1){
									   //ndd.children.push_back(in)
									   //   nd[index].children.push_back(val[i].asLargestInt());
									   //   decoder_cameras(val[i], was, index);
									   // }
									   //  if (was == 2){
									   //ndd.children.push_back(in)
									   //  nd[index].matrix[i] = val[i].asDouble();
									   // decoder_cameras(val[i], was, index);
									   //}
									   //  scenna.sc = new osg::ref_ptr<osg::Group>;
									   //  decoder_cameras(val[i], was, index);
								   }



							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										was = 7;
										if (key == "version")
										{
											ver.version = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "version";
											was = 6;
										}
										if (key == "generator")
										{
											ver.generator= (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "generator";
											was = 5;
										}
										decoder_version(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_cameras(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {
									 //  if (was == 0){
										   osg::ref_ptr<osg::Camera> temp_camera = new osg::Camera;
										   my_camera.cm = temp_camera.get();
										   //   scenna.children.push_back(i);
										   cam.push_back(my_camera);
										   index++;
										   decoder_cameras(val[i], was, index);
									//   }
									  // if (was == 1){
										   //ndd.children.push_back(in)
										//   nd[index].children.push_back(val[i].asLargestInt());
										//   decoder_cameras(val[i], was, index);
									  // }
									 //  if (was == 2){
										   //ndd.children.push_back(in)
										 //  nd[index].matrix[i] = val[i].asDouble();
										  // decoder_cameras(val[i], was, index);
									   //}
									   //  scenna.sc = new osg::ref_ptr<osg::Group>;
									 //  decoder_cameras(val[i], was, index);
								   }



							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										if (key == "znear")
										{
											cam[index].znear = val[key].asDouble();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "znear";
											was = 6;
										}
										if (key == "zfar")
										{
											cam[index].zfar = val[key].asDouble();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout<< "zfar";
											was = 5;
										}
										if (key == "type")
										{
											cam[index].type_of_view = (char*)val[key].asCString();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "type";
											was = 4;
										}

										if (key == "aspectRatio")
										{
											cam[index].aspectRatio = val[key].asDouble();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "aspectRatio";
											was = 2;
										}
										if (key == "yfov")
										{
											cam[index].yfov= val[key].asDouble();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "yfov";
											was = 1;
										}

										decoder_cameras(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_nodes(const Json::Value& val, int was = 0, int index = 0){//nodes - 0; childeren - 1; matrix - 2;mesh - 3
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {
									   if (was == 0){
										   osg::ref_ptr<osg::Group> temp_group = new osg::Group;
										   ndd.gr = temp_group.get();
										   //   scenna.children.push_back(i);
										   nd.push_back(ndd); ndd.children.clear();
										   index++;
										   decoder_nodes(val[i], was, index);
									   }
									   if (was == 1){
										   //ndd.children.push_back(in)
										   nd[index].children.push_back(val[i].asLargestInt());
										   decoder_nodes(val[i], was, index);
									   }
									   if (was == 2){
										   //ndd.children.push_back(in)
										   nd[index].matrix[i] = val[i].asDouble();
										   decoder_nodes(val[i], was, index);
									   }
									   if (was == 3){
										   //ndd.children.push_back(in)
										   nd[index].translation[i] = val[i].asDouble();
										   decoder_nodes(val[i], was, index);
									   }
									   if (was == 4){
										   //ndd.children.push_back(in)
										   nd[index].scale[i] = val[i].asDouble();
										   decoder_nodes(val[i], was, index);
									   }
								   }



							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										if (key == "camera")
										{
											nd[index].camera = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "camera";
											was = 6;
										}
										if (key == "mesh")
										{
											nd[index].mesh = val[key].asLargestInt();
											//	nd[index].mesh.push_back(val[i].asLargestInt());
											//cout << "mesh";
											was = 5;
										}
										if (key == "scale")
										{
											//cout << "matrix";
											was = 4;
										}
										if (key == "translation")
										{
											//cout << "matrix";
											was = 3;
										}
										if (key == "matrix")
										{
											//cout << "matrix";
											was = 2;
										}
										if (key == "children")
										{
											//cout << "children";
											was = 1;
										}

										decoder_nodes(val[key], was, index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder_scenes(const Json::Value& val, int was=0,int index=0){
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i < size; i++) {
									   if (was == 0){
									   osg::ref_ptr<osg::Group> temp_group = new osg::Group;
									   scenna.sc = temp_group.get();
									//   scenna.children.push_back(i);
									   scenns.push_back(scenna); scenna.children.clear();
									  }
									   if (was == 1){
										   scenns[index].children.push_back(val[i].asLargestInt());
									   }
									 //  scenna.sc = new osg::ref_ptr<osg::Group>;
									   decoder_scenes(val[i],was,0);
								   }
							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];

										if (key == "scenes")
										{
											//cout << "scenes";

										}
										if (key == "nodes")
										{
											//cout << "nodes";
											was = 1;
										}
										decoder_scenes(val[key],was,index);

									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
void decoder(const Json::Value& val) {
	switch (val.type()) {
	case Json::nullValue: break;
	case Json::booleanValue: break;
	case Json::intValue:  break;
	case Json::uintValue:  break;
	case Json::realValue:  break;
	case Json::stringValue:   break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0){}
							   else {
								   for (Json::ArrayIndex i = 0; i<size; i++) {
									   decoder( val[i]);
								   }
							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty()){}
								else {
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
										const string& key = keys[i];
										if (key == "scenes")
										{
											cout << "scenes\n";
											decoder_scenes(val[key],0);
										}
										if (key == "nodes")
										{
											cout << "nodes\n";
											decoder_nodes(val[key], 0,-1);
										}
										if (key == "meshes")
										{
											cout << "meshes\n";
											decoder_meshes(val[key], 0, -1);
										}
										if (key == "cameras")
										{
											cout << "cameras\n";
											decoder_cameras(val[key], 0, -1);
										}
										if (key == "asset")
										{
											cout << "asset\n";
											decoder_version(val[key], 0, -1);
										}
										if (key == "accessors")
										{
											cout << "asset\n";
											decoder_accessors(val[key], 0, -1);
										}
										if (key == "bufferViews")
										{
											cout << "bufferViews\n";
											decoder_bufferViews(val[key], 0, -1);
										}
										if (key == "buffers")
										{
											cout << "buffers\n";
											decoder_buffers(val[key], 0, -1);
										}
										if (key == "materials")
										{
											cout << "materials\n";
											decoder_materials(val[key], 0, -1);
										}
										if (key == "textures")
										{
											cout << "textures\n";
											decoder_textures(val[key], 0, -1);
										}
										if (key == "images")
										{
											cout << "images\n";
											decoder_images(val[key], 0, -1);
										}
										if (key == "samplers")
										{
											cout << "samplers\n";
											decoder_samplers(val[key], 0, -1);
										}
									}
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
/*void MyPrint(ostream& ofs, const Json::Value& val, int indent = 0, int what_was = 0, osg::ref_ptr<osg::Group> current_node = NULL) {
	switch (val.type()) {
	case Json::nullValue: ofs << "null"; break;
	case Json::booleanValue: ofs << (val.asBool() ? "true" : "false"); break;
	case Json::intValue: ofs << val.asLargestInt(); break;
	case Json::uintValue: ofs << val.asLargestUInt(); break;
	case Json::realValue: ofs << val.asDouble(); break;
	case Json::stringValue: ofs << '"' << val.asString() << '"'; break;
	case Json::arrayValue: {
							   Json::ArrayIndex size = val.size();
							   if (size == 0)
								   ofs << "[]";
							   else {
								   ofs << "[\n";
								   int newIndent = indent + 4;
								   for (Json::ArrayIndex i = 0; i<size; i++) {
									
									   MyPrint(ofs, val[i], newIndent, what_was, current_node);
									   ofs << (i + 1 == size ? "\n" : ",\n");
								   }
								 //  Indent(ofs, indent);
								   ofs << ']';
							   }
							   break;
	}
	case Json::objectValue: {
								if (val.empty())
									ofs << "{}";
								else {
									ofs << "{\n";
									int newIndent = indent + 4;
									vector<string> keys = val.getMemberNames();
									for (size_t i = 0; i<keys.size(); i++) {
									//	Indent(ofs, newIndent);
										const string& key = keys[i];

										switch (what_was)
										{
										case 1: //было scenes/////////////////////////////////
											cout << val[key].type();
											//	if (Json::arrayValue == val[key].type())
											//		cout << "array ";
											if (Json::arrayValue == val[key].type() && key == "nodes")
											{
												cout << val[key].size();
												for (int i = 0; i < val[key].size(); i++){
													int g = current_node->getNumChildren();
													char buf2[10]; memset(buf2, 0, sizeof(buf2));
													char buf[7]; memset(buf, 0, sizeof(buf));
													buf[0] = 'n'; buf[1] = 'o'; buf[2] = 'd'; buf[3] = 'e';
													current_node->addChild(new osg::Group);
													itoa(i, buf2, 10);
													strcat(buf, buf2);
													current_node->getChild(g)->setName(buf);
												}
												cout << "array with nodes ";

											}
											if (Json::objectValue == val[key].type())
												cout << "object ???";


											break;//////////////////////////////////////////
										case 2: //было nodes////////////////////////////////
											cout << val[key].size();
											if (Json::arrayValue == val[key].type() && key == "mesh")
											{
												cout << val[key].size();
												for (int i = 0; i < val[key].size(); i++)
													current_node->addChild(new osg::Geode);
												cout << "array with nodes ";

											}
											if (Json::intValue == val[key].type() && key == "mesh")
											{
												cout << "init with mesh: " << val[key].asLargestInt();
												int g = mesh_bank->getNumDrawables();

												char buf2[10]; memset(buf2, 0, sizeof(buf2));
												char buf[7]; memset(buf, 0, sizeof(buf));
												buf[0] = 'm'; buf[1] = 'e'; buf[2] = 's'; buf[3] = 'h';
												mesh_bank->addDrawable(new osg::Geometry);
												itoa(val[key].asLargestInt(), buf2, 10);
												strcat(buf, buf2);
												mesh_bank->getDrawable(g)->setName(buf);

											}
											if (Json::objectValue == val[key].type())
												cout << "object ???";

											break;/////////////////////////////////////////
										default:
											break;
										}

										if (key == "scenes")
										{
											cout << "scenes";
											what_was = 1;
										}
										if (key == "nodes")
										{
											cout << "nodes";
											what_was = 2;
										}

										ofs << '"' << key << '"' << " : ";
										MyPrint(ofs, val[key], newIndent, what_was, current_node);
										what_was = 0;
										ofs << (i + 1 == keys.size() ? "\n" : ",\n");
									}
								//	Indent(ofs, indent);
									ofs << '}';
								}
								break;
	}
	default:
		cerr << "Wrong type!" << endl;
		exit(0);
	}
}
*/
void print(osg::ref_ptr<osg::Node> nod, std::string s)
{
	//cout << " asGr: " << nod->asGroup();
	if (nod->asGroup() != NULL && nod->getName() != "geode")
	for (int i = 0; i < nod->asGroup()->getNumChildren(); i++)
	{
		std::cout << s << "Group: " << nod->asGroup()->getChild(i) << "\n";
		s.push_back(' ');
		print(nod->asGroup()->getChild(i), s);
	}
	if (nod->asTransform() != NULL)
	for (int i = 0; i < nod->asTransform()->getNumChildren(); i++)
	{
		std::cout << s << "MatrixTransform: " << nod->asTransform()->getChild(i) << "\n";
		s.push_back('-');
		print(nod->asTransform()->getChild(i), s);
	}
	
	//cout << " asgeode: " << nod->asGeode();
	//if (nod->asGeode() != NULL)
	if (nod->getName() == "geode")
	for (int i = 0; i < nod->asGroup()->getNumChildren(); i++)
	{

		std::cout << s << "Geode: " << nod->asGroup()->getChild(i) << "\n";
		s.push_back(' ');
		//	print(nod->asGeode()->getDrawable(i));
	}

 };
void read_image_files(char* path)
{
	char mypath[100];
	
	for (int i = 0; i < image.size(); i++)
	{
		memset(mypath, 0, sizeof(mypath));
		strcpy(mypath, path);
		for (int i = 99; i > 0; i--)
		{
			if (mypath[i] == '/')break;
			mypath[i] = 0;
		}
	//	osg::ref_ptr<osg::Image> image;
		strcat(mypath, image[i].uri);
		image[i].image = osgDB::readImageFile(mypath);
		if (image[i].image == NULL)
		image[i].image =osgDB::readImageFile(image[i].uri);
		if (image[i].image != NULL)
		{
			cout << "\n-----------------------------------------------------\n";
			cout << "Read images file(s) is succes! File:\n" << mypath << "\nName(path): " << image[i].uri;
			cout << "\n-----------------------------------------------------\n";
		}
		else
		{
			cout << "\n-----------------------------------------------------\n";
			cout << "Something Wrong, can't read! File:\n" << mypath << "\nName(path): " << image[i].uri;
			cout << "\n-----------------------------------------------------\n";
		}
	}

}
void read_bin_files(char* path)
{
	char mypath[100]; 
	memset(mypath, 0, sizeof(mypath));
	strcpy(mypath, path);
	for (int i = 49; i > 0; i--)
	{
		if (mypath[i] == '/')break;
		mypath[i] = 0;
	}


	for (int i = 0; i < bufs.size(); i++)
	{
		if (bufs[i].uri[0] == 'd' &&bufs[i].uri[1] == 'a' && bufs[i].uri[2] == 't'&&bufs[i].uri[3] == 'a')
		{
			///дописать, если данные хранятся в jltf
			char* buffer=new char;//(char*)malloc(bufs[i].byteLength);
			decode_base64_F((bufs[i].uri + 37), i, &buffer);
		}
		else
		{
			strcat(mypath, bufs[i].uri);
			ifstream reader(mypath, std::ios::binary | ios::in);
			if (reader.is_open()){
				

				 char* buffer = (char*)malloc(bufs[i].byteLength);
				
				reader.read((char*)buffer, bufs[i].byteLength);
				bufs[i].byte_file_data = buffer;
				reader.close();

				cout << "\n-----------------------------------------------------\n";
				cout << "Read bin file is succes! File:\n" << mypath <<"\nLength: "<< bufs[i].byteLength;
				cout << "\n-----------------------------------------------------\n";
				return ;
				/*for (int j = 0; j < bufs[i].byteLength; j++)
				{
					reader.read((char *)&temp, sizeof(temp));
					bufs[i].byte_file_data.push_back(temp);
				}*/
			}
			else
			{
				cout << "\n-----------------------------------------------------\n";
				cout << "Something Wrong, can't read! File:\n" << mypath << "\nLength: " << bufs[i].byteLength;
				cout << "\n-----------------------------------------------------\n";
			}
			memset(mypath, 0, sizeof(mypath));
			strcpy(mypath, path);
			for (int i = 29; i > 0; i--){
				if (mypath[i] == '/')break;
				mypath[i] = 0;
			}
		}

		
	}

}
void get_scalar(vector<unsigned int>* v, int position, int size_type = 3)//получение координат
{
	unsigned long int a = 0;//начало
	unsigned long int b = 0;//конец
	int comp_type = 4;
	//int size_type = 3;

	unsigned int stride = 0;
	stride = bufvs[acces[position].bufferView].byteStride;
	a += bufvs[acces[position].bufferView].byteOffset;
	b = bufvs[acces[position].bufferView].byteLength + a;
	a += acces[position].byteOffset;
	/*if (acces[position].type[0] == 'S' && acces[position].type[1] == 'C'&& acces[position].type[2] == 'A'&& acces[position].type[3] == 'L'&& acces[position].type[4] == 'A'&&acces[position].type[5] == 'R')size_type = 1;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '2')size_type = 2;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '3')size_type = 3;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '4')size_type = 4;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '2')size_type = 4;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '3')size_type = 9;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '4')size_type = 16;
	*/
	switch (acces[position].componentType)
	{
	case 5126://FLOAT 4
		comp_type = 4;
		break;
	case 5125://UNSIGNED_INT 4
		comp_type = 4;
		break;
	case 5123://UNSIGNED_SHORT 2
		comp_type = 2;
		break;
	case 5122://SHORT 2
		comp_type = 2;
		break;
	case 5121://UNSIGNED_BYTE 1
		comp_type = 1;
	case 5120://BYTE 1
		comp_type = 1;
		break;
	default:
		cout << "COMP_TYPE? uses 4byte";
		break;
	}
	/*unsigned long int c;
	if (stride == 0)
	{
		c = (b - a) / comp_type;
		stride = size_type*comp_type;
	}
	else
		c = (b - a) / stride;*/
	if (stride == 0)stride = size_type*comp_type;

	char*temp = new char[comp_type];//если stride не задан, значит он сам вектор

	float* objf = new float[size_type];
	unsigned int *objui = new unsigned int[size_type];
	short *objs = new short[size_type];
	unsigned char *objuc = new unsigned char[size_type];
	unsigned short *objus = new unsigned short[size_type];
	char *objc = new char[size_type];
	for (int i = 0; i < acces[position].count*size_type + 1; i++)
	{
		b = a + comp_type*size_type;//a-b  a-b  a-b
		//if (i%comp_type == 0 &&i!=0){


		if (i%size_type == 0 && i != 0){//фигня
			switch (acces[position].componentType)
			{
				//osg::Vec3ui(objui[0], objui[1], objui[2])

			//case 5126:v->push_back(objf[0]); break;
			case 5125:v->push_back(objui[0]); break;
			case 5123:v->push_back(objus[0]); break;
			case 5121:v->push_back(objuc[0]); break;
			case 5120:v->push_back(objc[0]); break;
			default:
				v->push_back(objui[0]);
				break;
			}
			//(*v)->push_back(osg::Vec3f(objf[0], objf[1], objf[2]));
			a += stride;//сдвиг
		}
		for (int j = 0; j < comp_type; j++)
		{
			temp[j] = bufs[bufvs[acces[position].bufferView].buffer].byte_file_data[a + (i%size_type)*comp_type + j];
		}
		if (acces[position].componentType == 5126){
			objf[i%size_type] = ((float*)temp)[0];
		}
		if (acces[position].componentType == 5125)//доделать для остальных типов
			objui[i%size_type] = ((unsigned int*)temp)[0];
		if (acces[position].componentType == 5123)
			objus[i%size_type] = ((unsigned short*)temp)[0];
		if (acces[position].componentType == 5122)
			objs[i%size_type] = ((unsigned short*)temp)[0];
		if (acces[position].componentType == 5121)
			objuc[i%size_type] = ((unsigned char*)temp)[0];
		if (acces[position].componentType == 5123)
			objc[i%size_type] = ((char*)temp)[0];
	}
	delete temp; delete objui; delete objus; delete objs; delete objuc; delete objc;
}
void get_position_vec2(osg::ref_ptr<osg::Vec2Array>* v, int position, int size_type = 3)//получение координат
{
	unsigned long int a = 0;//начало
	unsigned long int b = 0;//конец
	int comp_type = 4;
	//int size_type = 3;

	unsigned int stride = 0;
	stride = bufvs[acces[position].bufferView].byteStride;
	a += bufvs[acces[position].bufferView].byteOffset;
	b = bufvs[acces[position].bufferView].byteLength + a;
	a += acces[position].byteOffset;
	/*if (acces[position].type[0] == 'S' && acces[position].type[1] == 'C'&& acces[position].type[2] == 'A'&& acces[position].type[3] == 'L'&& acces[position].type[4] == 'A'&&acces[position].type[5] == 'R')size_type = 1;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '2')size_type = 2;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '3')size_type = 3;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '4')size_type = 4;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '2')size_type = 4;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '3')size_type = 9;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '4')size_type = 16;
	*/
	switch (acces[position].componentType)
	{
	case 5126://FLOAT 4
		comp_type = 4;
		break;
	case 5125://UNSIGNED_INT 4
		comp_type = 4;
		break;
	case 5123://UNSIGNED_SHORT 2
		comp_type = 2;
		break;
	case 5122://SHORT 2
		comp_type = 2;
		break;
	case 5121://UNSIGNED_BYTE 1
		comp_type = 1;
	case 5120://BYTE 1
		comp_type = 1;
		break;
	default:
		cout << "COMP_TYPE? uses 4byte";
		break;
	}
	unsigned long int c;
	if (stride == 0)stride = size_type*comp_type;

	//	c = ((b - a) / stride)*size_type;

	unsigned char*temp = new unsigned char[comp_type];//если stride не задан, значит он сам вектор

	float* objf = new float[size_type];
	unsigned int *objui = new unsigned int[size_type];
	short *objs = new short[size_type];
	unsigned char *objuc = new unsigned char[size_type];
	unsigned short *objus = new unsigned short[size_type];
	char *objc = new char[size_type];
	for (int i = 0; i < acces[position].count*size_type + 1; i++)
	{
		b = a + comp_type*size_type;//a-b  a-b  a-b
		//if (i%comp_type == 0 &&i!=0){


		if (i%size_type == 0 && i != 0){//фигня
			switch (acces[position].componentType)
			{
				//osg::Vec3ui(objui[0], objui[1], objui[2])
			case 5126:(*v)->push_back(osg::Vec2(objf[0], objf[1])); break;
			case 5125:(*v)->push_back(osg::Vec2(objui[0], objui[1])); break;
			case 5123:(*v)->push_back(osg::Vec2(objus[0], objus[1])); break;
			default:
				(*v)->push_back(osg::Vec2f(objf[0], objf[1]));
				break;
			}
			//(*v)->push_back(osg::Vec3f(objf[0], objf[1], objf[2]));
			a += stride;//сдвиг
		}
		for (int j = 0; j < comp_type; j++)
		{
			temp[j] = bufs[bufvs[acces[position].bufferView].buffer].byte_file_data[a + (i%size_type)*comp_type + j];
		}
		if (acces[position].componentType == 5126){
			objf[i%size_type] = ((float*)temp)[0];
		}
		if (acces[position].componentType == 5125)//доделать для остальных типов
			objui[i%size_type] = ((unsigned int*)temp)[0];
		if (acces[position].componentType == 5123)
			objus[i%size_type] = ((unsigned short*)temp)[0];
		if (acces[position].componentType == 5122)
			objs[i%size_type] = ((unsigned short*)temp)[0];
		if (acces[position].componentType == 5121)
			objuc[i%size_type] = ((unsigned char*)temp)[0];
		if (acces[position].componentType == 5123)
			objc[i%size_type] = ((char*)temp)[0];
	}
}
void get_position_vec3(osg::ref_ptr<osg::Vec3Array>* v,int position,int size_type=3)//получение координат
{
	unsigned long int a=0;//начало
	unsigned long int b=0;//конец
	int comp_type = 4;
	//int size_type = 3;
	
	unsigned int stride = 0;
	stride = bufvs[acces[position].bufferView].byteStride;
	a += bufvs[acces[position].bufferView].byteOffset;
	b = bufvs[acces[position].bufferView].byteLength + a;
	a += acces[position].byteOffset;
	/*if (acces[position].type[0] == 'S' && acces[position].type[1] == 'C'&& acces[position].type[2] == 'A'&& acces[position].type[3] == 'L'&& acces[position].type[4] == 'A'&&acces[position].type[5] == 'R')size_type = 1;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '2')size_type = 2;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '3')size_type = 3;
	if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '4')size_type = 4;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '2')size_type = 4;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '3')size_type = 9;
	if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '4')size_type = 16;
	*/
	switch (acces[position].componentType)
	{
	case 5126://FLOAT 4
		comp_type = 4;
		break;
	case 5125://UNSIGNED_INT 4
		comp_type = 4;
		break;
	case 5123://UNSIGNED_SHORT 2
		comp_type = 2;
		break;
	case 5122://SHORT 2
		comp_type = 2;
		break;
	case 5121://UNSIGNED_BYTE 1
		comp_type = 1;
	case 5120://BYTE 1
		comp_type = 1;
		break;
	default:
		cout << "COMP_TYPE? uses 4byte";
		break;
	}
	unsigned long int c;
	if (stride == 0)stride = size_type*comp_type;

	//	c = ((b - a) / stride)*size_type;

	unsigned char*temp = new unsigned char[comp_type];//если stride не задан, значит он сам вектор

	float* objf = new float[size_type];
	unsigned int *objui = new unsigned int[size_type];
	short *objs = new short[size_type];
	unsigned char *objuc = new unsigned char[size_type];
	unsigned short *objus = new unsigned short[size_type];
	char *objc = new char[size_type];
	for (int i = 0; i < acces[position].count*size_type+1 ; i++)
	{
		b = a + comp_type*size_type;//a-b  a-b  a-b
		//if (i%comp_type == 0 &&i!=0){


		if (i%size_type == 0 && i != 0){//фигня
			switch (acces[position].componentType)
			{
				//osg::Vec3ui(objui[0], objui[1], objui[2])
			case 5126:(*v)->push_back(osg::Vec3(objf[0], objf[1], objf[2]));break;
			case 5125:(*v)->push_back(osg::Vec3(objui[0], objui[1], objui[2])); break;
			case 5123:(*v)->push_back(osg::Vec3(objus[0], objus[1], objus[2])); break;
			default:
				(*v)->push_back(osg::Vec3f(objf[0], objf[1], objf[2]));
				break;
			}
			//(*v)->push_back(osg::Vec3f(objf[0], objf[1], objf[2]));
			a += stride;//сдвиг
		}
		for (int j = 0; j < comp_type; j++)
		{
			temp[j] = bufs[bufvs[acces[position].bufferView].buffer].byte_file_data[a + (i%size_type)*comp_type + j];
		}
			if (acces[position].componentType == 5126){
				objf[i%size_type] =	 ((float*)temp)[0];}
			if (acces[position].componentType == 5125)//доделать для остальных типов
				objui[i%size_type] = ((unsigned int*)temp)[0];
			if (acces[position].componentType == 5123)
				objus[i%size_type] = ((unsigned short*)temp)[0];
			if (acces[position].componentType == 5122)
				objs[i%size_type] = ((unsigned short*)temp)[0];
			if (acces[position].componentType == 5121)
				objuc[i%size_type] = ((unsigned char*)temp)[0];
			if (acces[position].componentType == 5123)
				objc[i%size_type] = ((char*)temp)[0];
	}
}
void get_position_vec4(osg::ref_ptr<osg::Vec4Array>* v, int position, int size_type = 4)//получение координат
{
	unsigned long int a = 0;//начало
	unsigned long int b = 0;//конец
	int comp_type = 4;
	//int size_type = 3;

	unsigned int stride = 0;
	stride = bufvs[acces[position].bufferView].byteStride;
	a += bufvs[acces[position].bufferView].byteOffset;
	b = bufvs[acces[position].bufferView].byteLength + a;
	a += acces[position].byteOffset;
	switch (acces[position].componentType)
	{
	case 5126://FLOAT 4
		comp_type = 4;
		break;
	case 5125://UNSIGNED_INT 4
		comp_type = 4;
		break;
	case 5123://UNSIGNED_SHORT 2
		comp_type = 2;
		break;
	case 5122://SHORT 2
		comp_type = 2;
		break;
	case 5121://UNSIGNED_BYTE 1
		comp_type = 1;
	case 5120://BYTE 1
		comp_type = 1;
		break;
	default:
		cout << "COMP_TYPE? uses 4byte";
		break;
	}
	unsigned long int c;
	if (stride == 0)stride = size_type*comp_type;

	//	c = ((b - a) / stride)*size_type;

	unsigned char*temp = new unsigned char[comp_type];//если stride не задан, значит он сам вектор

	float* objf = new float[size_type];
	unsigned int *objui = new unsigned int[size_type];
	short *objs = new short[size_type];
	unsigned char *objuc = new unsigned char[size_type];
	unsigned short *objus = new unsigned short[size_type];
	char *objc = new char[size_type];
	for (int i = 0; i < acces[position].count*size_type + 1; i++)
	{
		b = a + comp_type*size_type;//a-b  a-b  a-b
		//if (i%comp_type == 0 &&i!=0){


		if (i%size_type == 0 && i != 0){//фигня
			switch (acces[position].componentType)
			{
				//osg::Vec3ui(objui[0], objui[1], objui[2])
			case 5126:(*v)->push_back(osg::Vec4(objf[0], objf[1], objf[2], objf[3])); break;
			case 5125:(*v)->push_back(osg::Vec4(objui[0], objui[1], objui[2], objui[3])); break;
			case 5123:(*v)->push_back(osg::Vec4(objus[0], objus[1], objus[2], objus[3])); break;
			default:
				(*v)->push_back(osg::Vec4f(objf[0], objf[1], objf[2], objf[3]));
				break;
			}
			//(*v)->push_back(osg::Vec3f(objf[0], objf[1], objf[2]));
			a += stride;//сдвиг
		}
		for (int j = 0; j < comp_type; j++)
		{
			temp[j] = bufs[bufvs[acces[position].bufferView].buffer].byte_file_data[a + (i%size_type)*comp_type + j];
		}
		if (acces[position].componentType == 5126){
			objf[i%size_type] = ((float*)temp)[0];
		}
		if (acces[position].componentType == 5125)//доделать для остальных типов
			objui[i%size_type] = ((unsigned int*)temp)[0];
		if (acces[position].componentType == 5123)
			objus[i%size_type] = ((unsigned short*)temp)[0];
		if (acces[position].componentType == 5122)
			objs[i%size_type] = ((unsigned short*)temp)[0];
		if (acces[position].componentType == 5121)
			objuc[i%size_type] = ((unsigned char*)temp)[0];
		if (acces[position].componentType == 5123)
			objc[i%size_type] = ((char*)temp)[0];
	}
}
void add_groups_to_root(osg::ref_ptr<osg::Group>* group)
{
	(*group)->addChild(scenns[0].sc.get());//scenna 0 - начало

	for (int i = 0; i < nd.size(); i++)//nodes
	{
		if (nd[i].scale[0] == 0 && nd[i].scale[1] == 0 && nd[i].scale[2] == 0)
		{
			nd[i].scale[0] = 1; nd[i].scale[1] = 1; nd[i].scale[2] = 1;
		}
		if (nd[i].matrix[0] == 0 && nd[i].matrix[1] == 0 && nd[i].matrix[2] == 0 && nd[i].matrix[3] == 0 && nd[i].matrix[4] == 0 && nd[i].matrix[5] == 0 && nd[i].matrix[6] == 0 && nd[i].matrix[7] == 0 &&
			nd[i].matrix[8] == 0 && nd[i].matrix[9] == 0 && nd[i].matrix[10] == 0 && nd[i].matrix[11] == 0 && nd[i].matrix[12] == 0 && nd[i].matrix[13] == 0 && nd[i].matrix[14] == 0 && nd[i].matrix[15] == 0)
		{
			nd[i].matrix[0] = 1; nd[i].matrix[5] = 1; nd[i].matrix[10] = 1; nd[i].matrix[15] = 1;
		}
		//СДВИГ
		//nd[i].matrix[12] += nd[i].translation[0]; 
		//nd[i].matrix[13] += nd[i].translation[1];
		//nd[i].matrix[14] += nd[i].translation[2];

		if (nd[i].mesh != -1)
		{
			osg::ref_ptr<osg::MatrixTransform> MT = new osg::MatrixTransform;
			//MT->
			osg::Matrix m;
			m.set(nd[i].matrix);
			//m.makeTranslate(nd[i].translation[0], nd[i].translation[1], nd[i].translation[2]);
	//		m.setTrans(nd[i].translation[0], nd[i].translation[1], nd[i].translation[2]);
			//m.makeScale(nd[i].scale[0], nd[i].scale[1], nd[i].scale[2]);
			//m = ;
			MT->setMatrix(m);
			nd[i].gr->addChild(MT.get());
			MT->addChild(mhs[nd[i].mesh].mh.get());//
			//std::cout << "3";
			//nd[i].translation[0];
		}
	//	if (nd[i].children.size() == 0){}
		//roots->addChild(nd[i].gr);
		//else
		//{
			for (int j = 0; j < nd[i].children.size(); j++){
				osg::ref_ptr<osg::MatrixTransform> MT = new osg::MatrixTransform;
				osg::Matrix m1; //osg::Matrix m2;
				m1.set(nd[i].matrix);

			//	for (int v = 0; v < 16; v++)
			//		cout << m1(v / 4, v % 4) << "  " << nd[i].matrix[v]<<endl;
			//	m2.set(nd[nd[i].children[j]].matrix);
			//	osg::Matrix resultMat = m1 * m2;
				MT->setMatrix(m1);
				nd[i].gr->addChild(MT.get());
				MT->addChild(nd[nd[i].children[j]].gr.get());
				//nd[nd[i].children[j]].matrix = resultMat.;///////!!!!//////
			//	for (int v = 0; v < 16; v++)
			//		nd[nd[i].children[j]].matrix[v] = resultMat(v / 4, v % 4);
			//	int mmm[16]
				//resultMat.;
				//nd[nd[i].children[j]].matrix[12] += nd[i].matrix[12];
				//nd[nd[i].children[j]].matrix[13] += nd[i].matrix[13];
				//nd[nd[i].children[j]].matrix[14] += nd[i].matrix[14];
				//for (int g = 0; g < 16;g++)
				//	nd[nd[i].children[j]].matrix[g] += nd[i].matrix[g];
				//nd[i].gr->addChild(nd[nd[i].children[j]].gr.get());
			//	nd[nd[i].children[j]].gr->setName("geode");
	//		}
		}
	}
	for (int i = 0; i < scenns.size(); i++)//scenes
	{
		if (scenns[i].children.size() == 0)
			scenns[i].sc->addChild(nd[0].gr.get());
		else
		{
			for (int j = 0; j < scenns[i].children.size(); j++)
				scenns[i].sc->addChild(nd[scenns[i].children[j]].gr.get());
		}
		//roots->addChild(sz[i].sc.get());
	}
	for (int i = 0; i < mhs.size(); i++)
	{
		osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
		osg::StateSet* state = geom->getOrCreateStateSet();/////
		osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;////
		vector<unsigned int> ii;////
			int size_type = 4;
			int position; position = mhs[i].POSITION;

		//	osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
			if (acces[position].type[0] == 'S' && acces[position].type[1] == 'C'&& acces[position].type[2] == 'A'&& acces[position].type[3] == 'L'&& acces[position].type[4] == 'A'&&acces[position].type[5] == 'R'){
			
			}
			if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '2'){
				size_type = 2;
				osg::ref_ptr<osg::Vec2Array> v = new osg::Vec2Array;
				//	geom->setVertexArray(v.get());
				get_position_vec2(&v, position, size_type);
				//geom->setVertexAttribBinding();
				geom->setVertexArray(v.get());//coord->geom
				cout << "P_R\n";
			}
			if (mhs[i].TEXCOORD_0 != -1)if (acces[mhs[i].TEXCOORD_0].type[0] == 'V'&&acces[mhs[i].TEXCOORD_0].type[1] == 'E'&&acces[mhs[i].TEXCOORD_0].type[2] == 'C' && acces[mhs[i].TEXCOORD_0].type[3] == '2'){
				size_type = 2;
				osg::ref_ptr<osg::Vec2Array> v = new osg::Vec2Array;
				//	geom->setVertexArray(v.get());
				get_position_vec2(&v, mhs[i].TEXCOORD_0, size_type);

				geom->setTexCoordArray(0, v.get());
			//	geom->addPrimitiveSet(sideIndices.get());
				//geom->setVertexAttribBinding();
			//	geom->setVertexArray(v.get());//coord->geom
				cout << "P_R\n";
			}
			if (mhs[i].TEXCOORD_1!=-1)if(acces[mhs[i].TEXCOORD_1].type[0] == 'V'&&acces[mhs[i].TEXCOORD_1].type[1] == 'E'&&acces[mhs[i].TEXCOORD_1].type[2] == 'C' && acces[mhs[i].TEXCOORD_1].type[3] == '2'){
				size_type = 2;
				osg::ref_ptr<osg::Vec2Array> v = new osg::Vec2Array;
				//	geom->setVertexArray(v.get());
				get_position_vec2(&v, mhs[i].TEXCOORD_1, size_type);

				geom->setTexCoordArray(1, v.get());
				//	geom->addPrimitiveSet(sideIndices.get());
				//geom->setVertexAttribBinding();
				//	geom->setVertexArray(v.get());//coord->geom
				cout << "P_R\n";
			}
		if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '3'){
			size_type = 3;
			osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array; 
		//	geom->setVertexArray(v.get());
			get_position_vec3(&v, position,size_type);
			//geom->setVertexAttribBinding();
			geom->setVertexArray(v.get());//coord->geom
			cout << "P_R\n";
		}
		if (acces[position].type[0] == 'V'&&acces[position].type[1] == 'E'&&acces[position].type[2] == 'C' && acces[position].type[3] == '4'){
			size_type = 4;
			osg::ref_ptr<osg::Vec4Array> v = new osg::Vec4Array;
			//	geom->setVertexArray(v.get());
			get_position_vec4(&v, position, size_type);
			//geom->setVertexAttribBinding();
			geom->setVertexArray(v.get());//coord->geom
			cout << "P_R\n";
		}
		
		if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '2')size_type = 4;
		if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '3')size_type = 9;
		if (acces[position].type[0] == 'M'&&acces[position].type[1] == 'A'&&acces[position].type[2] == 'T' && acces[position].type[3] == '4')size_type = 16;
		
		
		//////////////////////////////////////////////////////////////////////NORMAL INPUT
		int normal = -1; normal = mhs[i].NORMAL;
		if (normal != -1){
			if (acces[normal].type[0] == 'S' && acces[normal].type[1] == 'C'&& acces[normal].type[2] == 'A'&& acces[normal].type[3] == 'L'&& acces[normal].type[4] == 'A'&&acces[normal].type[5] == 'R')
				size_type = 1;
			if (acces[normal].type[0] == 'V'&&acces[normal].type[1] == 'E'&&acces[normal].type[2] == 'C' && acces[normal].type[3] == '2')if (acces[normal].type[0] == 'V'&&acces[normal].type[1] == 'E'&&acces[normal].type[2] == 'C' && acces[normal].type[3] == '4'){
				size_type = 2;
				osg::ref_ptr<osg::Vec2Array> n = new osg::Vec2Array;

				get_position_vec2(&n, normal, size_type);
				geom->setNormalArray(n.get());//normal_coord->geom
				geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

				cout << "N_R\n";
			}
			if (acces[normal].type[0] == 'V'&&acces[normal].type[1] == 'E'&&acces[normal].type[2] == 'C' && acces[normal].type[3] == '3'){
				size_type = 3;
				osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;

				get_position_vec3(&n, normal, size_type);
				geom->setNormalArray(n.get());//normal_coord->geom
				geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
				
				cout << "N_R\n";
			}

			if (acces[normal].type[0] == 'V'&&acces[normal].type[1] == 'E'&&acces[normal].type[2] == 'C' && acces[normal].type[3] == '4'){
				size_type = 4;
				osg::ref_ptr<osg::Vec4Array> n = new osg::Vec4Array;

				get_position_vec4(&n, normal, size_type);
				geom->setNormalArray(n.get());//normal_coord->geom
				geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

				cout << "N_R\n";
			}
			if (acces[normal].type[0] == 'M'&&acces[normal].type[1] == 'A'&&acces[normal].type[2] == 'T' && acces[normal].type[3] == '2')size_type = 4;
			if (acces[normal].type[0] == 'M'&&acces[normal].type[1] == 'A'&&acces[normal].type[2] == 'T' && acces[normal].type[3] == '3')size_type = 9;
			if (acces[normal].type[0] == 'M'&&acces[normal].type[1] == 'A'&&acces[normal].type[2] == 'T' && acces[normal].type[3] == '4')size_type = 16;
		}
		//////////////////////////////////////////////////////////////////////INDEX INPUT

		int index=-1; index = mhs[i].indices;
		if (index != -1){
			if (acces[index].type[0] == 'S' && acces[index].type[1] == 'C'&& acces[index].type[2] == 'A'&& acces[index].type[3] == 'L'&& acces[index].type[4] == 'A'&&acces[index].type[5] == 'R')
			{
				size_type = 1;
				//get_position_vec3(&i, position, size_type);
				get_scalar(&ii, index, size_type);//////////СВЯЗАТЬ ИНДЕКСЫ И КООРДИНАТЫ
				//DrawElementsUInt
					//geom->drawe
				cout << "SC_R\n";
			}
			if (acces[index].type[0] == 'V'&&acces[index].type[1] == 'E'&&acces[index].type[2] == 'C' && acces[index].type[3] == '2')size_type = 2;
			if (acces[index].type[0] == 'V'&&acces[index].type[1] == 'E'&&acces[index].type[2] == 'C' && acces[index].type[3] == '3')size_type = 3;
			if (acces[index].type[0] == 'V'&&acces[index].type[1] == 'E'&&acces[index].type[2] == 'C' && acces[index].type[3] == '4')size_type = 4;
			if (acces[index].type[0] == 'M'&&acces[index].type[1] == 'A'&&acces[index].type[2] == 'T' && acces[index].type[3] == '2')size_type = 4;
			if (acces[index].type[0] == 'M'&&acces[index].type[1] == 'A'&&acces[index].type[2] == 'T' && acces[index].type[3] == '3')size_type = 9;
			if (acces[index].type[0] == 'M'&&acces[index].type[1] == 'A'&&acces[index].type[2] == 'T' && acces[index].type[3] == '4')size_type = 16;
		}
		////////////////////////////////////////////////////////////////////MATERIALS INPUT
		int material_choose = -1; material_choose = mhs[i].material;
		if (material_choose != -1)if (mater[material_choose].baseColorFactor[0] != 0 && mater[material_choose].baseColorFactor[1] != 0 && mater[material_choose].baseColorFactor[2] != 0 && mater[material_choose].baseColorFactor[3] != 0){
			osg::ref_ptr<osg::Vec4Array> mat_vec = new osg::Vec4Array;
			geom->setColorArray(mat_vec.get());
			geom->setColorBinding(osg::Geometry::BIND_OVERALL);
			mat_vec->push_back(osg::Vec4(mater[material_choose].baseColorFactor[0], mater[material_choose].baseColorFactor[1], mater[material_choose].baseColorFactor[2], mater[material_choose].baseColorFactor[3]));
		//	c->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.f));
		//	c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
		//	c->push_back(osg::Vec4(1.f, 1.f, 1.f, 1.f));
		}
		/////////////////////////////////////////////////////////////
		if (mhs[i].indices != -1)//если есть индексы
		{
			switch (mhs[i].mode){//choose mode for primit.
			case 0:
			{
					  //geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, acces[mhs[i].POSITION].count)); break;
					  osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_POINTS);
					  for (int j = 0; j < ii.size(); j++)
						  sideIndices->push_back(ii[j]);
					  //	osg::ref_ptr<osg::DrawElementsUInt> sideIndices =new osg::DrawElementsUInt(GL_QUAD_STRIP);
					  //	sideIndices->
					  geom->addPrimitiveSet(sideIndices.get());
					  break;
			}
			case 1:
			{
					  //geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, acces[mhs[i].POSITION].count)); break;
					  osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_LINES);
					  for (int j = 0; j < ii.size(); j++)
						  sideIndices->push_back(ii[j]);
					  //	osg::ref_ptr<osg::DrawElementsUInt> sideIndices =new osg::DrawElementsUInt(GL_QUAD_STRIP);
					  //	sideIndices->
					  geom->addPrimitiveSet(sideIndices.get());
					  break;
			}
			case 2:
			{
					  //geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, acces[mhs[i].POSITION].count)); 
					  osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_LINES);
					  for (int j = 0; j < ii.size(); j++)
						  sideIndices->push_back(ii[j]);
					  //	osg::ref_ptr<osg::DrawElementsUInt> sideIndices =new osg::DrawElementsUInt(GL_QUAD_STRIP);
					  //	sideIndices->
					  geom->addPrimitiveSet(sideIndices.get());
					  break;
			}
			case 3:{
					   //geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, acces[mhs[i].POSITION].count)) break;
					   osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_LINE_STRIP);
					   for (int j = 0; j < ii.size(); j++)
						   sideIndices->push_back(ii[j]);
					   //	osg::ref_ptr<osg::DrawElementsUInt> sideIndices =new osg::DrawElementsUInt(GL_QUAD_STRIP);
					   //	sideIndices->
					   geom->addPrimitiveSet(sideIndices.get());
					   break;
			}
			case 4:{
			//	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, acces[mhs[i].POSITION].count)); 
				osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_TRIANGLES);
				for (int j = 0; j < ii.size(); j++)
					sideIndices->push_back(ii[j]);
				
				
				
			//	state->setMode(GL_LIGHTING, osg::StateAttribute::OFF | osg::StateAttribute::PROTECTED);
			//	state->setRenderingHint(osg::StateSet::USE_RENDERBIN_DETAILS);

				//tex->setUnRefImageDataAfterApply(true);
				//state->setTextureAttributeAndModes(0, tex);
				
				//state->setTextureMode(0);
			//	state->setTextureMode(0, GL_TEXTURE_WRAP_T, osg::StateAttribute::GL_REPEAT);
				// Повторять текстуру по оси s
				//tex->setImage(new osg::Image())
				if (texture.size() != 0)
				{

					tex->setImage(image[texture[i].source].image.get());
					//state->setTextureMode(0, GL_TEXTURE_GEN_S, osg::StateAttribute::ON);
					//	mhs[i].mh->getOrCreateStateSet()->setTextureAttributesAndModes(0, GL_TEXTURE_GEN_Q)

					switch (sampler[texture[i].sampler].wrapS)
					{
					case 10497:
						tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT); break;
					case 33648:
						tex->setWrap(osg::Texture::WRAP_S, osg::Texture::MIRROR);
						break;
					default:
						tex->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT); break;
					}
					switch (sampler[texture[i].sampler].wrapT)
					{
					case 10497:
						tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT); break;
					case 33648:
						tex->setWrap(osg::Texture::WRAP_T, osg::Texture::MIRROR);
						break;
					default:
						tex->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT); break;
					}
				}
					// Повторять текстуру по оси r
					//tex->setWrap(osg::Texture::WRAP_R, osg::Texture::REPEAT);
				if(mater[mhs[i].material].baseColorTexture_index==-1)
					mhs[i].mh->getOrCreateStateSet()->setTextureAttributeAndModes(0, tex.get());
				else
					mhs[i].mh->getOrCreateStateSet()->setTextureAttributeAndModes(mater[mhs[i].material].baseColorTexture_index, tex.get());
				
				//	osg::ref_ptr<osg::DrawElementsUInt> sideIndices =new osg::DrawElementsUInt(GL_QUAD_STRIP);
				//	sideIndices->
				//osg::ref_ptr<osg::Texture2D> tex = new osg::Texture2D;
				//osg::StateSet* state = mhs[i].mh.get();
				geom->addPrimitiveSet(sideIndices.get());
				break;
			}
			case 5:
			{
			//		  geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, acces[mhs[i].POSITION].count)); break;
					  osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_TRIANGLE_STRIP);
					//  geom->add
					 
						  geom->addPrimitiveSet(new osg::DrawArrays(GL_QUADS, 0, 4));
					  for (int j = 0; j < ii.size(); j++)
						  sideIndices->push_back(ii[j]);
					  //	osg::ref_ptr<osg::DrawElementsUInt> sideIndices =new osg::DrawElementsUInt(GL_QUAD_STRIP);
					  //	sideIndices->
					  geom->addPrimitiveSet(sideIndices.get());
					  break;
			}
			case 6:
			{
					  //geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN, 0, acces[mhs[i].POSITION].count)); break
					  osg::ref_ptr<osg::DrawElementsUInt> sideIndices = new osg::DrawElementsUInt(GL_TRIANGLE_FAN);
					  for (int j = 0; j < ii.size(); j++)
						  sideIndices->push_back(ii[j]);
					  //	osg::ref_ptr<osg::DrawElementsUInt> sideIndices =new osg::DrawElementsUInt(GL_QUAD_STRIP);
					  //	sideIndices->
					  geom->addPrimitiveSet(sideIndices.get());
					  break;
			}
			default:cout << "??? mode????"; break;
			}
		}
		else//если нет индексации
		{
			switch (mhs[i].mode){//choose mode for primit.
			case 0:geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, acces[mhs[i].POSITION].count)); break;
			case 1:geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, acces[mhs[i].POSITION].count)); break;
			case 2:geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP, 0, acces[mhs[i].POSITION].count)); break;
			case 3:geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_STRIP, 0, acces[mhs[i].POSITION].count)); break;
			case 4: geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLES, 0, acces[mhs[i].POSITION].count)); break;
			case 5:geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP, 0, acces[mhs[i].POSITION].count)); break;
			case 6:geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_FAN, 0, acces[mhs[i].POSITION].count)); break;
			default:cout << "??? mode????"; break;
			}
		}
	//	geom->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINES,0, acces[mhs[i].POSITION].count));
		// Добавить Geometry (Drawable) в Geode и вернуть Geode.
		//osg::ref_ptr<osg::Geode> geode = new osg::Geode;
		
		mhs[i].mh->addDrawable(geom.get());
	//	scenns[0].sc->addChild(mhs[i].mh);
		//acces[mhs[i].POSITION];
	}
}
osg::Group* open_gltf(char* path)
{
	osg::ref_ptr<osg::Group> group = new osg::Group;
	group->setName("group");
	ifstream ifs(path);
	Json::Value val;
	ifs >> val;
//	MyPrint(cout, val, 0, 0, group);
	decoder(val);
	read_bin_files(path);
	read_image_files(path);
	add_groups_to_root(&group);
	std::cout << '\n'; std::cout << '\n';
	std::string cc = "";
//	group->addChild(new osg::Geode);
	//print(group.get(), cc);

	std::cout << '\n';
	/*for (int i = 0; i < group->getNumChildren(); i++)
	{
		string s = group->getChild(i)->getName();
		if (s[0] == 'n' && s[1] == 'o' &&s[2] == 'd'&&s[3] == 'e')
		{
			int g = 0;
			group->getChild(0)->asGroup()->addChild(mesh_bank);
			//	group->getChild(0)->asGeode()->addDrawable(mesh_bank->getDrawable(g));
			cout << "node";
			g++;
		}


	}*/
	return group.release();

}
