cmake_minimum_required(VERSION 3.27)

set(PROJECT_NAME JifInjector)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WIN32_EXECUTABLE ON)

project(
    ${PROJECT_NAME}
    VERSION 1.0.0
    LANGUAGES CXX
)

add_executable(
    ${PROJECT_NAME}
)

set(CMAKE_EXE_LINKER_FLAGS
    "${CMAKE_EXE_LINKER_FLAGS} /ENTRY:wWinMainCRTStartup"
)

if(MSVC)
    target_compile_options(
        ${PROJECT_NAME}
        PRIVATE
        /W4
    )
endif()

target_include_directories(
    ${PROJECT_NAME}
    PRIVATE
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(
    ${PROJECT_NAME}
    PRIVATE
    d3d11.lib
)

add_subdirectory(external)
add_subdirectory(src)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    $<TARGET_FILE:${PROJECT_NAME}>
    ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}.exe
)

if(NOT DEFINED APP_PACKAGE)
    set(APP_PACKAGE false)
endif()

if (APP_PACKAGE)
    include(InstallRequiredSystemLibraries)

    install(TARGETS ${PROJECT_NAME}
        DESTINATION bin
    )

    install(
        DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/assets/"
        DESTINATION "bin/assets"
    )

    set(CPACK_PACKAGE_NAME ${PROJECT_NAME})
    set(CPACK_PACKAGE_VERSION "1.0.0")
    set(CPACK_PACKAGE_VENDOR "JifInjector")
    set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A cpp mono injector")
    set(CPACK_PACKAGE_EXECUTABLES ${PROJECT_NAME} ${PROJECT_NAME})
    set(CPACK_SOURCE_PACKAGE_FILE_NAME ${PROJECT_NAME}-${CPACK_PACKAGE_VERSION})
    set(CPACK_PACKAGE_INSTALL_DIRECTORY ${PROJECT_NAME})
    set(CPACK_CREATE_DESKTOP_LINKS ${PROJECT_NAME})

    set(CPACK_GENERATOR NSIS)
    set(CPACK_NSIS_PACKAGE_NAME "JifInjector")
    set(CPACK_RESOURCE_FILE_LICENSE "${CMAKE_CURRENT_SOURCE_DIR}/LICENSE")

    list(APPEND CPACK_SOURCE_IGNORE_FILES "/\.github/")
    list(APPEND CPACK_SOURCE_IGNORE_FILES "/\.git/")
    list(APPEND CPACK_SOURCE_IGNORE_FILES "/build/")
    list(APPEND CPACK_SOURCE_IGNORE_FILES "/dllTest/")
    list(APPEND CPACK_SOURCE_IGNORE_FILES "/external/")
    list(APPEND CPACK_SOURCE_IGNORE_FILES "/scripts/")

    include(CPack)
endif()
