from __future__ import unicode_literals, print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7
import sys
kratos_benchmarking_path = '../../../../benchmarking'
sys.path.append(kratos_benchmarking_path)
import benchmarking

benchmarking.BuildReferenceData("cantilever3dstatic_superlu_benchmarking.py", "cantilever3dstatic.txt")
