# a dummy library with the system library dependencies
fips_begin_lib(sokol)
    fips_files(sokol.cpp)
    if (FIPS_LINUX)
        fips_libs(X11 Xi Xcursor GL m dl asound)
    endif()
fips_end_lib()
