set(SOURCE_DIRECTORY .)

aux_source_directory(${SOURCE_DIRECTORY} DIR_LIB_SRCS)

add_library(MathFunctions ${DIR_LIB_SRCS})

#指定库的安装路径
install (TARGETS MathFunctions DESTINATION bin)
install (FILES MathFunctions.h DESTINATION include)
