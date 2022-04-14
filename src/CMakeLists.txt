# select the 3D backend for sokol_gfx.h and sokol_app.h
add_definitions(-D${sokol_backend})

# test app definition
fips_begin_app(sapp windowed)
    fips_files(main.cpp)
    fips_deps(sokol)
fips_end_app()