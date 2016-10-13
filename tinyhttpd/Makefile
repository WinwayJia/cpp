.PHONY: all test clean deps tags

VER=release # debug

CXX=g++
CXXFLAGS=-std=c++11 -Wliteral-suffix
ifeq ($(VER), debug)
CXXFLAGS += -g 
else
CXXFLAGS += -O3 -s
endif

LDFLAGS += -lpthread -lpqxx -lpq

DEPS_INCLUDE_PATH=-I deps/json-cpp/include/ -I deps/http-parser/ -I deps/libpqxx-4.0/include
DEPS_LIB_PATH=deps/json-cpp/output/lib/libjson_libmt.a deps/http-parser/libhttp_parser.a 
SRC_INCLUDE_PATH=-I src
OUTPUT_INCLUDE_PATH=-I output/include
OUTPUT_LIB_PATH=output/lib/libsimpleserver.a

objects := $(patsubst %.cpp,%.o,$(wildcard src/*.cpp))


all: deps libsimpleserver.a
	mkdir -p output/include output/lib output/bin
	cp src/*.h output/include/
	mv libsimpleserver.a output/lib/

tags:
	ctags -R /usr/include src deps

deps:
	make -C deps/http-parser package
	make -C deps/json-cpp

libsimpleserver.a: $(objects) 
	ar -rcs libsimpleserver.a src/*.o

test: http_server_test http_parser_test
	
%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) $(DEPS_INCLUDE_PATH) $(SRC_INCLUDE_PATH) $< -o $@

http_server_test: test/http_server_test.cpp
	$(CXX) $(CXXFLAGS) $(DEPS_INCLUDE_PATH) $(OUTPUT_INCLUDE_PATH) $< $(OUTPUT_LIB_PATH) $(DEPS_LIB_PATH) $(LDFLAGS) -o output/bin/$@
	
http_parser_test: test/http_parser_test.cpp
	$(CXX) $(CXXFLAGS) $(DEPS_INCLUDE_PATH) $(OUTPUT_INCLUDE_PATH) $< $(OUTPUT_LIB_PATH) $(DEPS_LIB_PATH) $(LDFLAGS) -o output/bin/$@

clean:
	rm -rf src/*.o
	rm -rf output/*

