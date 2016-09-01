aux_source_directory(. DIR_LIB_SRC)
include_directories(../include/)
add_library(hello SHARED ${DIR_LIB_SRC})
