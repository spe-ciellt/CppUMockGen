if( WIN32 )
    set( LIBCLANG_PATHS "C:/Program Files/LLVM" )
    if( MSVC )
        set( LIBCLANG_LIBNAME "libclang" )
    else()
        set( LIBCLANG_LIBNAME "libclang.dll" )
    endif()
else()
    set( LIBCLANG_PATHS "/usr/lib/llvm-6.0" )
    set( LIBCLANG_LIBNAME "clang" )
endif()

find_path( LibClang_INC_DIR clang-c/Index.h PATHS ${LIBCLANG_PATHS} )

find_library( LibClang_LIB_PATH NAMES ${LIBCLANG_LIBNAME} PATHS ${LIBCLANG_PATHS} )

# Should use `llvm-config --includedir`
set( LibClang_INC_DIR "/usr/lib/llvm-6.0/include" )

set( LibClang_LIB_PATH "/usr/lib/llvm-6.0/lib/libclang.so" )

include( FindPackageHandleStandardArgs )
find_package_handle_standard_args( LibClang DEFAULT_MSG LibClang_INC_DIR LibClang_LIB_PATH )

mark_as_advanced( LibClang_INC_DIR LibClang_LIB_PATH )

set( LibClang_INCLUDE_DIRS ${LibClang_INC_DIR} )
get_filename_component( LibClang_LIBRARIES ${LibClang_LIB_PATH} NAME )
get_filename_component( LibClang_LIBRARY_DIRS ${LibClang_LIB_PATH} DIRECTORY )
