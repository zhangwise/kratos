#include "includes/matrix_market_interface.h"
#include "includes/ublas_interface.h"

#include "viennacl/compressed_matrix.hpp"
#include "viennacl/linalg/cg.hpp"

#if defined(_WIN64) || defined(_WIN32) || defined(WIN64)
#include <windows.h>
typedef  __int64 int64_t;
#endif

int64_t Timer()
{
#if defined(_WIN64) || defined(_WIN32)
    LARGE_INTEGER frequency;
    LARGE_INTEGER start;
    LARGE_INTEGER end;

    //  Get the frequency
    QueryPerformanceFrequency(&frequency);

    //  Start timer
    QueryPerformanceCounter(&start);

    return ( start.QuadPart)* (( 1000 *1000 *1000) / long double( frequency.QuadPart ));



#else
    struct timespec tp;

    clock_gettime(CLOCK_MONOTONIC, &tp);

    return (unsigned long long) tp.tv_sec * (1000ULL * 1000ULL * 1000ULL) + (unsigned long long) tp.tv_nsec;
#endif
}

int main(int argc, char *argv[])
{
    int64_t T0, T1;

    if (argc < 3)
    {
        std::cout << "Not enough command line parameters." << std::endl;
        return -1;
    }

    Kratos::CompressedMatrix A;
    Kratos::Vector B;

    std::cout << "Reading matrix and vector from file..." << std::endl;

    Kratos::ReadMatrixMarketMatrix(argv[1], A);
    Kratos::ReadMatrixMarketVector(argv[2], B);

    if (A.size1() != A.size2() || A.size1() != B.size())
    {
        std::cout << "Inconsistent matrix / vector sizes." << std::endl;
        return -1;
    }

    cl_uint Size = A.size1();

    std::cout << "Copying data..." << std::endl;

    viennacl::compressed_matrix <double> VA;
    viennacl::vector <double> VB(Size);

    viennacl::copy(A, VA);
    viennacl::copy(B, VB);

    std::cout << "Solving..." << std::endl;

    viennacl::linalg::cg_tag VCLSolver(1.00e-10, 1000);

    T0 = Timer();

    viennacl::linalg::solve(VA, VB, VCLSolver);

    T1 = Timer() - T0;

    std::cout << "Iterations: " << VCLSolver.iters() << ", error: " << VCLSolver.error() << std::endl;

    std::cout << "Solution took " << double(T1) / 1000000000 << "s." << std::endl;

    return 0;
}
