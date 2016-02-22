REM @ECHO OFF

REM Identification for arguments
REM basename               = %1
REM Project directory      = %2
REM Problem Type directory = %3
 
REM OutputFile: "%2\%1.info"
REM ErrorFile: "%2\%1.err"


del "%2\%1.info"
del "%2\%1.err"

move "%2\%1.dat" "%2\%1.mdpa"
move "%2\%1-1.dat" "%2\ProjectParameters.py"
copy "%3\\..\\..\\python_scripts\\main_script.py" "%2\\"


"C:\\KratosMultiphysics\\runkratos.exe" "%2\\main_script.py" > "%2\%1.info" 2> "%2\%1.err"