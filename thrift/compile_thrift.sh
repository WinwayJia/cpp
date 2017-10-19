# thrift complile
thrift -gen cpp first.thrift
mv gen-cpp/first.h .
mv gen-cpp/first.cpp .
mv gen-cpp/first_types.h .
mv gen-cpp/first_types.cpp .
#mv gen-cpp/first_server.skeleton.cpp ./first_server.cpp

