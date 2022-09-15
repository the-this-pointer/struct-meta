include(ExternalProject)

ExternalProject_Add(
        rapidjson
        PREFIX "vendor/rapidjson"
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/rapidjson"
        GIT_REPOSITORY "https://github.com/Tencent/rapidjson.git"
        GIT_TAG 06d58b9e848c650114556a23294d0b6440078c61
        TIMEOUT 10
        CMAKE_ARGS
        -DRAPIDJSON_BUILD_TESTS=OFF
        -DRAPIDJSON_BUILD_DOC=OFF
        -DRAPIDJSON_BUILD_EXAMPLES=OFF
        -DRAPIDJSON_HAS_STDSTRING=ON
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
)

# Prepare RapidJSON (RapidJSON is a header-only library)
ExternalProject_Get_Property(rapidjson source_dir)
set(RAPIDJSON_INCLUDE_DIR ${source_dir}/include)