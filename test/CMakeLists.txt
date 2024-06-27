file(
        GLOB_RECURSE SRC_FILES CONFIGURE_DEPENDS
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp
)

add_executable(
	Test_Math_in_Compile_Time 
	${SRC_FILES}
)

target_include_directories(
	Test_Math_in_Compile_Time PUBLIC ${CMAKE_SOURCE_DIR}/include
)

target_compile_features(
	Test_Math_in_Compile_Time PRIVATE cxx_std_17
)