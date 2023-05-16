from cffi import FFI
from pathlib import Path
ffibuilder = FFI()

sgypath = Path("/home/andalevor/Programming/SeisSegy")
trcpath = Path("/home/andalevor/Programming/SeisTrace")

with open("libsheader.h") as h_f:
    ffibuilder.cdef(h_f.read())

ffibuilder.set_source("_cffi",
                      '#include "SeisISegy.h"',
                      libraries=["seissegy", "seistrace"],
                      library_dirs=[(sgypath / "release/src").as_posix(),
                                    (trcpath / "release/src").as_posix()],
                      extra_link_args=["-Wl,-rpath,."])

ffibuilder.compile()
