from setuptools import Extension, setup
from Cython.Build import cythonize

setup(
        ext_modules = cythonize([Extension("trace_cython", ["trace_cython.pyx"],
                                           libraries=["seistrace"]),
                                 Extension("segy_cython", ["segy_cython.pyx"],
                                           libraries=["seissegy"])],
                                compiler_directives={"language_level" : "3"})
        )
