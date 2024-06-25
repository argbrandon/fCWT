#!/usr/bin/env python

"""
setup.py file for SWIG
"""

from setuptools import Extension, setup, find_packages
import numpy


# Obtain the numpy include directory.  This logic works across numpy versions.
try:
    numpy_include = numpy.get_include()
except AttributeError:
    numpy_include = numpy.get_numpy_include()

libraries = ['fftw3f']
comp_args = ["/arch:AVX", "/O2", "/openmp"]
link_args = []
files2 = [
    "omp.h",
    "fftw3.h",
    "fftw3f.dll",
    "fftw3f.lib",
    "libfftw3fmac.a",
    "libfftw3f_ompmac.a",
    "libfftw3fl.so",
    "libfftw3f_ompl.so",
    "libomp.a",
]
files = ["fcwt.h", "fcwt.cpp"]

files = files + files2


libraries = ['fftw3f', 'fftw3f_omp']
comp_args = ["-mavx", "-O3"]
link_args = ["-lomp"]


setup(
    ext_modules=[
        Extension(
            'fcwt._fcwt',
            sources=['src/fcwt/fcwt.cpp', 'src/fcwt/fcwt_wrap.cxx'],
            library_dirs=[
                'src/fcwt',
                'src',
                '/usr/lib/x86_64-linux-gnu',
                '/usr/lib/llvm-10/lib',
            ],
            include_dirs=['src/fcwt', 'src', numpy_include],
            libraries=libraries,
            extra_compile_args=comp_args,
            extra_link_args=link_args,
        )
    ],
    packages=find_packages(where='src'),
    package_dir={'fcwt': 'src/fcwt'},
    package_data={'fcwt': files},
)

# swig -c++ -python fcwt-swig.i
