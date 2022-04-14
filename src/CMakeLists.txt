# select the 3D backend for sokol_gfx.h and sokol_app.h
add_definitions(-D${sokol_backend})

# test app definition
fips_begin_app(sapp windowed)
    fips_files(main.cc)
    sokol_shader(simple.glsl ${slang})
    fips_deps(sokol)
fips_end_app()
fips_begin_app(sapp-ui windowed)
    fips_files(main.cc)
    sokol_shader(simple.glsl ${slang})
    fips_deps(sokol dbgui)
fips_end_app()
target_compile_definitions(sapp-ui PRIVATE USE_DBG_UI)