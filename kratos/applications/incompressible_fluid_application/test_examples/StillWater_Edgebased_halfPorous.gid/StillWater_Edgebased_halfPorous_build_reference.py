from __future__ import unicode_literals, print_function, absolute_import, division #makes KratosMultiphysics backward compatible with python 2.6 and 2.7
import sys
kratos_benchmarking_path = '../../../../benchmarking'
sys.path.append(kratos_benchmarking_path)
import benchmarking

print("Building reference data for StillWater_Edgebased_halfPorous.py...")
benchmarking.BuildReferenceData(
    "StillWater_Edgebased_halfPorous_script.py",
    "StillWater_Edgebased_halfPorous_ref.txt")
