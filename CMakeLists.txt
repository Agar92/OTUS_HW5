cmake_minimum_required(VERSION 3.15)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")
set(PROJECT_VERSION 0.0.${PATCH_VERSION})

project(MVC LANGUAGES CXX VERSION ${PROJECT_VERSION})

configure_file(version.h.in version.h @ONLY)

add_executable(${PROJECT_NAME} main.cpp)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR})

set_target_properties(${PROJECT_NAME}
                      PROPERTIES
                      	CXX_STANDARD 17
                      	CXX_STANDARD_REQUIRED ON
)

target_compile_options(${PROJECT_NAME}
                       PRIVATE
        					-g
)

set(CMAKE_INSTALL_PREFIX "./includeeeee/")

install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
file(GLOB headers "*.h")
message("headers=${headers}")
install(FILES ${headers} DESTINATION include)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT agar10@yandex.ru)

include(CPack)
