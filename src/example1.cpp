// First example: Only use the basic ARPACK functionality
// https://github.com/yixuan/arpack-eigen
#include <RcppEigen.h>
#include <SymEigs.h>

RcppExport SEXP example1()
{
    BEGIN_RCPP

    // We are going to calculate the eigenvalues of M
    Eigen::MatrixXd A = Eigen::MatrixXd::Random(100, 100);
    Eigen::MatrixXd M = A + A.transpose();

    // Construct matrix operation object using the wrapper class DenseGenMatProd
    DenseGenMatProd<double> op(M);

    // Construct eigen solver object, requesting the largest three eigenvalues
    SymEigsSolver< double, LARGEST_ALGE, DenseGenMatProd<double> > eigs(&op, 3, 10);

    // Initialize and compute
    eigs.init();
    int nconv = eigs.compute();

    // Retrieve results
    Eigen::VectorXd evalues;
    if(nconv > 0)
        evalues = eigs.eigenvalues();

    Rcpp::Rcout << "Eigenvalues found:\n" << evalues << std::endl;

    return R_NilValue;

    END_RCPP
}
