import imp
import os
import re
import getopt
import sys
import subprocess

from KratosMultiphysics import KratosLoader


def Usage():
    ''' Prints the usage of the script '''

    lines = [
        'Usage:',
        '\t python kratos_run_tests [-l level] [-v vervosity] [-a app1:[app2:...]]',  # noqa
        'Options',
        '\t -h, --help: Shows this command',
        '\t -l, --level: Minimum level of detail of the tests: \'all\'(Default) \'(small)\' \'(nightly)\'',  # noqa
        '\t -a, --applications: List of applications to run separated by \':\'. All compiled applications will be run by default',  # noqa
        '\t -v, --verbose: Vervosty level: 0, 1 (Default), 2'
    ]

    for l in lines:
        print(l)


def GetModulePath(module):
    ''' Returns the location of a module using its absolute path

    Return
    ------
    string
        The absolute path of the module

    '''

    return imp.find_module(module)[1]


def GetAvailableApplication():
    ''' Return the list of applications available in KratosMultiphysics

    Return a list of compiled applications available in the KratosMultiphysics
    module.

    Return
    ------
    list of string
        List of the names of the applications

    '''
    kratosPath = GetModulePath('KratosMultiphysics')

    apps = [
        f.split('.')[0] for f in os.listdir(kratosPath)
        if re.match(r'.*Application\.py$', f)
    ]

    return apps


def RunTestSuit(application, path, level, verbose):
    ''' Calls the script that will run the tests.

    Input
    -----
    application: string
        Name of the application that will be tested.

    path: string
        Absoulte path with the location of the application.

    level: string
        minimum level of the test that will be run if possible.

    verbose: int
        detail of the ouptut. The grater the verbosity level, the greate the
        detail will be.

    '''

    subprocess.call([
        'python',
        path+'/tests/'+'test_'+application+'.py',
        '-v '+str(verbose),
        '-l '+level
    ])


def main():

    verbose_values = ['0', '1', '2']
    level_values = ['all', 'small', 'nightly']

    # Set default values
    applications = GetAvailableApplication() + ['KratosCore']
    verbosity = 1
    level = 'all'

    # Parse Commandline
    try:
        opts, args = getopt.getopt(
            sys.argv[1:],
            'ha:v:l:', [
                'help',
                'applications=',
                'verbose=',
                'level='
            ])
    except getopt.GetoptError as err:
        print(str(err))
        Usage()
        sys.exit(2)

    for o, a in opts:
        if o in ('-v', '--verbose'):
            if a in verbose_values:
                verbosity = a
            else:
                print('Error: {} is not a valid verbose level.'.format(a))
                Usage()
                sys.exit()
        elif o in ('-h', '--help'):
            Usage()
            sys.exit()
        elif o in ('-l', '--level'):
            if a in level_values:
                level = a
            else:
                print('Error: {} is not a valid level.'.format(a))
                Usage()
                sys.exit()
        elif o in ('-a', '--applications'):
            try:
                parsedApps = a.split(':')
            except:
                print('Error: Cannot parse applications.')
                Usage()
                sys.exit()

            for a in parsedApps:
                if a not in applications:
                    print('Error: {} does not exists'.format(a))
                    sys.exit()

            applications = parsedApps
        else:
            assert False, 'unhandled option'

    # Run the tests for KratosCore
    if 'KratosCore' in applications:
        RunTestSuit(
            'KratosCore',
            GetModulePath('KratosMultiphysics'),
            level,
            verbosity
        )

    # Run the tests for the rest of the Applications
    for application in applications:
        RunTestSuit(
            application,
            KratosLoader.kratos_applications+'/'+application,
            level,
            verbosity
        )

if __name__ == "__main__":
    main()