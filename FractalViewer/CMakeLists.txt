set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(PROJECT_NAME "FractalViewer")

add_executable(${PROJECT_NAME})

# get_target_property(IMGUI_SOURCE_DIR imgui SOURCE_DIR)
# get_target_property(IMGUI_SFML_SOURCE_DIR imgui-sfml SOURCE_DIR)

target_sources(
	${PROJECT_NAME}
	PRIVATE
        main.cpp
        application.cpp
        fractal_renderer.cpp
        ${IMGUI_SFML_SOURCE_DIR}/imgui-SFML.cpp
        ${IMGUI_SOURCE_DIR}/imgui.cpp
        ${IMGUI_SOURCE_DIR}/imgui_demo.cpp
        ${IMGUI_SOURCE_DIR}/imgui_draw.cpp
        ${IMGUI_SOURCE_DIR}/imgui_widgets.cpp
)

# OpenGL
#find_package(OpenGL REQUIRED)

target_link_libraries(${PROJECT_NAME} PUBLIC FractalCore sfml-window sfml-graphics sfml-audio sfml-network sfml-system sfml-main opengl32)
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_SFML_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${IMGUI_SOURCE_DIR})
target_include_directories(${PROJECT_NAME} PUBLIC ${SFML_INCLUDE_DIR})

message(${SFML_BINARY_DIR}/lib/$<CONFIG>)
# Custom post build command to copy shared libs
add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD # Add post build to app project
    COMMAND ${CMAKE_COMMAND} -E copy_directory  # executes "cmake - E copy_if_different..."
        ${SFML_BINARY_DIR}/lib/$<CONFIG> # In file
        $<TARGET_FILE_DIR:${PROJECT_NAME}>) # Directory of the app binary file

# Add install logic
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)