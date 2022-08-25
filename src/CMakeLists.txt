file(GLOB_RECURSE StructMeta_SRC_FILES ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

if(BUILD_SHARED_LIBS)
    add_library(structMeta_shared SHARED ${StructMeta_SRC_FILES})
    add_dependencies(structMeta_shared rapidjson)

    target_include_directories(structMeta_shared
            PUBLIC
            $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
            $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
            )

    if(WIN32)
        target_compile_definitions(structMeta_shared
                PRIVATE
                WIN32_LEAN_AND_MEAN
                )
    endif()
endif()

add_library(structMeta_static STATIC ${StructMeta_SRC_FILES})
add_dependencies(structMeta_static rapidjson)

target_include_directories(structMeta_static
        PUBLIC
        $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/inc>
        $<INSTALL_INTERFACE:$<INSTALL_PREFIX>/${CMAKE_INSTALL_INCLUDEDIR}>
        )

if(WIN32)
    target_compile_definitions(structMeta_static
            PRIVATE
            WIN32_LEAN_AND_MEAN
            )
endif()
