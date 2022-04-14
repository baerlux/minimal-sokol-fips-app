#
# project: minimal-sokol-fips-app
#
cmake_minimum_required(VERSION 3.2)
set(CMAKE_CXX_STANDARD 20)
project(minimal-sokol-fips-app)

# include the fips main cmake file
get_filename_component(FIPS_ROOT_DIR "../fips" ABSOLUTE)
include("${FIPS_ROOT_DIR}/cmake/fips.cmake")

fips_setup()
    set(sokol_backend SOKOL_GLCORE33)
    set(slang "glsl330")

    fips_include_directories(libs)
    fips_add_subdirectory(libs)

    fips_include_directories(src)
    fips_add_subdirectory(src)
fips_finish()
