cmake_minimum_required(VERSION 3.4.1)

# 设置输出so目标目录
#set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/libs/${ANDROID_ABI})

# 设置库名及打包的cpp
file(GLOB source_files "src/main/cpp/*.cpp")
add_library(demo
            SHARED
            ${source_files})
add_definitions(-DLIBCXX_HAS_MUSL_LIBC=ON)
add_definitions(-D_LIBCPP_PROVIDES_DEFAULT_RUNE_TABLE)
# 设置头文件目录
include_directories(
                    src/main/cpp/
                    src/main/cpp/include
                    src/main/cpp/include/jsoncpp
                    src/main/cpp/include/curl
                    )

# 添加引用库所在逻辑, STATIC:代表.a库， SHARED:代表.so库
add_library(curl STATIC IMPORTED)
set_target_properties(curl
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/libs/armeabi/libcurl.a)

add_library(jsoncpp STATIC IMPORTED)
set_target_properties(jsoncpp
                      PROPERTIES IMPORTED_LOCATION
                      ${CMAKE_SOURCE_DIR}/libs/armeabi/libjsoncpp.a)

# 查找ndk需要的库文件
find_library( log-lib
              log )


# 确保 zlib 库存在并链接
find_library(ZLIB_LIB NAMES z PATHS ${CMAKE_SOURCE_DIR}/libs/${ANDROID_ABI})
if(ZLIB_LIB)
    message(STATUS "Found zlib library: ${ZLIB_LIB}")
else()
    message(FATAL_ERROR "Could not find zlib library")
endif()


# 目标文件与库文件链接
target_link_libraries( # Specifies the target library. 需要链接库
                        demo
                       # Links the target library to the log library
                       # included in the NDK. 引入文件
                       jsoncpp
                       curl
                       ${log-lib} )

