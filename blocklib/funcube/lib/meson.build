funcube_sources += []
funcube_deps += [gnuradio_gr_dep, volk_dep, fmt_dep, spdlog_dep, pmtf_dep, python3_embed_dep, json_dep, hidapi_dep, gnuradio_block_dep, gnuradio_audio_dep]

block_cpp_args = ['-DHAVE_CPU']

# if IMPLEMENT_CUDA
#     block_cpp_args += '-DHAVE_CUDA'

#     gnuradio_blocklib_funcube_cu = library('gnuradio-blocklib-funcube-cu', 
#         funcube_cu_sources, 
#         include_directories : incdir, 
#         install : true, 
#         dependencies : [cuda_dep])

#     gnuradio_blocklib_funcube_cu_dep = declare_dependency(include_directories : incdir,
#                         link_with : gnuradio_blocklib_funcube_cu,
#                         dependencies : cuda_dep)

#     funcube_deps += [gnuradio_blocklib_funcube_cu_dep, cuda_dep]

# endif

incdir = include_directories(['../include/gnuradio/funcube','../include'])
gnuradio_blocklib_funcube_lib = library('gnuradio-blocklib-funcube', 
    funcube_sources, 
    include_directories : incdir, 
    install : true,
    link_language: 'cpp',
    dependencies : funcube_deps,
    cpp_args : block_cpp_args)

gnuradio_blocklib_funcube_dep = declare_dependency(include_directories : incdir,
					   link_with : gnuradio_blocklib_funcube_lib,
                       dependencies : funcube_deps)

pkg = import('pkgconfig')
libs = [gnuradio_blocklib_funcube_lib]     # the library/libraries users need to link against
h = ['.'] # subdirectories of ${prefix}/${includedir} to add to header path
pkg.generate(libraries : libs,
             subdirs : h,
             version : meson.project_version(),
             name : 'libgnuradio-blocklib-funcube',
             filebase : 'gnuradio-blocklib-funcube',
             description : 'GNU Radio funcube component')
