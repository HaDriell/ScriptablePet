file(GLOB_RECURSE SOURCES "${ScriptablePet_SOURCE_DIR}/src/*.cpp")


add_executable(ScriptablePet ${SOURCES})
target_include_directories(ScriptablePet PUBLIC "${ScriptablePet_SOURCE_DIR}/src")
target_compile_features(ScriptablePet PUBLIC cxx_std_17)
target_link_libraries(ScriptablePet PRIVATE imgui glfw glad)