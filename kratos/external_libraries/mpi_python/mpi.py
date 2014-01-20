from __future__ import unicode_literals, print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7
import sys
if sys.platform == 'linux2':
    import DLFCN as dl
    flags = sys.getdlopenflags()
    sys.setdlopenflags(dl.RTLD_NOW | dl.RTLD_GLOBAL)
    import mpipython
    sys.setdlopenflags(flags)
else:
    import mpipython

#__all__ = ['mpi']

mpi = mpipython.GetMPIInterface()
