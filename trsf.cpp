#include "AT/cx/c3d/Calib.h"
#include<iostream>
using std::cout, std::cerr, std::endl;

int main(int argc, char** argv){
	if(argc!=4){
		cerr<<"Usage: "<<argv[0]<<" XML x0 z0"<<endl;
		exit(-1);
	}
	auto calib=AT::cx::c3d::Calib::createShared();
	calib->load(argv[1]);
	cerr<<"Loaded: "<<argv[1]<<endl;
	AT::cx::Point3d p1(atof(argv[2]),0,atof(argv[3]));
	cerr<<"Original point: "<<p1.x<<", "<<p1.y<<", "<<p1.z<<endl;
	AT::cx::Point3d p2=calib->sensor2world(p1);
	cerr<<"Transformed point: "<<p2.x<<", "<<p2.y<<", "<<p2.z<<endl;
}

