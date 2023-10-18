AT_SDK=/opt/at-solutionpackage/cxSDK
AT_SDK_EX=$(AT_SDK)/../examples/cxSDK/cpp/src
ARCH=linux_amd64


CXXFLAGS:=-Wl,-rpath,$(AT_SDK)/lib/$(ARCH) -ggdb3 -std=c++17 -fuse-ld=gold -lcx3dLib  -lcxBaseLib -lcxCamLib -I$(AT_SDK)/include -L$(AT_SDK)/lib/$(ARCH)
default:
	g++ $(CXXFLAGS) trsf.cpp -o trsf
run:
	LD_LIBRARY_PATH=$(AT_SDK)/lib/$(ARCH) ./grab_point_cloud
