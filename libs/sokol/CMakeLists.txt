# a dummy library with the system library dependencies
fips_begin_lib(sokol)
    fips_files(sokol.cpp)
    fips_libs(X11 Xi Xcursor GL m dl asound)
fips_end_lib()