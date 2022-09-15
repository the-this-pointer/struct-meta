include(ExternalProject)

ExternalProject_Add(
        log-library
        PREFIX "vendor/log-library"
        SOURCE_DIR "${CMAKE_SOURCE_DIR}/vendor/log-library"
        GIT_REPOSITORY "https://github.com/the-this-pointer/log-library.git"
        GIT_TAG 2d1780e34f7e622c5cd0ba3cf13bc91565f98a21
        -DWITH_LITERALS=OFF
        TIMEOUT 10
        CMAKE_ARGS
        CONFIGURE_COMMAND ""
        BUILD_COMMAND ""
        INSTALL_COMMAND ""
        UPDATE_COMMAND ""
)

# Prepare log-library (log-library is a header-only library)
ExternalProject_Get_Property(log-library source_dir)
set(LOGLIB_INCLUDE_DIR ${source_dir})