
#include <bits/stdc++.h>
using namespace std;

typedef vector<double> Vec;
typedef vector<Vec> Mat;

const int MAXIT = 1000;
const double TOL = 1e-5;

double infNorm(const Vec &v) {
    double m = 0.0;
    for (double x : v) m = max(m, fabs(x));
    return m;
}

Vec vecSub(const Vec &a, const Vec &b) {
    Vec r(a.size());
    for (size_t i = 0; i < a.size(); i++) r[i] = a[i] - b[i];
    return r;
}

void printVec(const Vec &v, int prec = 6) {
    cout << "(";
    for (size_t i = 0; i < v.size(); i++) {
        cout << fixed << setprecision(prec) << v[i];
        if (i + 1 < v.size()) cout << ", ";
    }
    cout << ")";
}

struct Result {
    Vec x;
    int iterations;
    bool converged;
};

Result jacobi(const Mat &A, const Vec &b, Vec x0, double tol = TOL, int maxIter = MAXIT) {
    int n = A.size();
    Vec x = x0, xNew(n);
    bool converged = false;
    int k = 0;

    for (k = 1; k <= maxIter; k++) {
        for (int i = 0; i < n; i++) {
            double s = b[i];
            for (int j = 0; j < n; j++)
                if (j != i) s -= A[i][j] * x[j];
            xNew[i] = s / A[i][i];
        }
        double err = infNorm(vecSub(xNew, x));
        x = xNew;
        if (err < tol) { converged = true; break; }
    }
    return {x, k, converged};
}

Result gaussSeidel(const Mat &A, const Vec &b, Vec x0, double tol = TOL, int maxIter = MAXIT) {
    int n = A.size();
    Vec x = x0, xOld(n);
    bool converged = false;
    int k = 0;

    for (k = 1; k <= maxIter; k++) {
        xOld = x;
        for (int i = 0; i < n; i++) {
            double s = b[i];
            for (int j = 0; j < n; j++)
                if (j != i) s -= A[i][j] * x[j];
            x[i] = s / A[i][i];
        }
        double err = infNorm(vecSub(x, xOld));
        if (err < tol) { converged = true; break; }
    }
    return {x, k, converged};
}

Result sor(const Mat &A, const Vec &b, Vec x0, double omega, double tol = TOL, int maxIter = MAXIT) {
    int n = A.size();
    Vec x = x0, xOld(n);
    bool converged = false;
    int k = 0;

    for (k = 1; k <= maxIter; k++) {
        xOld = x;
        for (int i = 0; i < n; i++) {
            double s = b[i];
            for (int j = 0; j < n; j++)
                if (j != i) s -= A[i][j] * x[j];
            double gs = s / A[i][i];
            x[i] = (1.0 - omega) * xOld[i] + omega * gs;
        }
        double err = infNorm(vecSub(x, xOld));
        if (err < tol) { converged = true; break; }
    }
    return {x, k, converged};
}

void printJacobiMatrix(const Mat &A) {
    int n = A.size();
    cout << "Gauss-Jacobi iteration matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "  [ ";
        for (int j = 0; j < n; j++) {
            double val = (i == j) ? 0.0 : -A[i][j] / A[i][i];
            cout << fixed << setprecision(4) << setw(9) << val << " ";
        }
        cout << "]\n";
    }
    cout << "\n";
}


void printGaussSeidelMatrix(const Mat &A) {
    int n = A.size();
    Mat DL(n, Vec(n, 0.0)), U(n, Vec(n, 0.0));
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            if (j <= i) DL[i][j] = A[i][j];
            else        U[i][j]  = -A[i][j];
        }

    Mat H(n, Vec(n, 0.0));
    for (int col = 0; col < n; col++) {
        Vec rhs(n);
        for (int i = 0; i < n; i++) rhs[i] = U[i][col];
        Vec sol(n, 0.0);
        for (int i = 0; i < n; i++) {
            double s = rhs[i];
            for (int j = 0; j < i; j++) s -= DL[i][j] * sol[j];
            sol[i] = s / DL[i][i];
        }
        for (int i = 0; i < n; i++) H[i][col] = sol[i];
    }

    cout << "Gauss-Seidel iteration matrix:\n";
    for (int i = 0; i < n; i++) {
        cout << "  [ ";
        for (int j = 0; j < n; j++)
            cout << fixed << setprecision(4) << setw(9) << H[i][j] << " ";
        cout << "]\n";
    }
    cout << "\n";
}

int main() {
    cout << fixed << setprecision(6);

    Mat A = {
        { 4,  1, -1,  1,  0},
        { 1,  5,  2,  0,  1},
        {-1,  2,  5,  1,  1},
        { 1,  0,  1,  4,  2},
        { 0,  1,  1,  2,  5}
    };
    Vec b = {9.5, -4, -0.5, 10.5, -4.5};
    Vec x0(5, 0.0);


    printJacobiMatrix(A);
    Result rj = jacobi(A, b, x0);

    printGaussSeidelMatrix(A);
    Result rgs = gaussSeidel(A, b, x0);

    Vec eig = {-0.7605, 0.7294, -0.2445, -0.0824, 0.3579};
    double rhoJ = 0.0;
    for (double e : eig) rhoJ = max(rhoJ, fabs(e));
    double omegaOpt = 2.0 / (1.0 + sqrt(1.0 - rhoJ * rhoJ));
    cout << "rho(H_J) =  " << setprecision(4) << rhoJ
         << "  ->  omega_opt = " << setprecision(6) << omegaOpt << "\n\n";

    Result rsor = sor(A, b, x0, omegaOpt);

    struct Row { string name; int iters; Vec x; };
    vector<Row> rows = {
        {"Jacobi", rj.iterations, rj.x},
        {"Gauss-Seidel", rgs.iterations, rgs.x},
        {"SOR (w_opt)", rsor.iterations, rsor.x}
    };
    sort(rows.begin(), rows.end(), [](const Row &a, const Row &b) { return a.iters < b.iters; });

    cout << left << setw(6) << "Rank" << setw(16) << "Method" << setw(12) << "Iterations" << "Solution vector\n";
    cout << string(90, '-') << "\n";
    for (size_t i = 0; i < rows.size(); i++) {
        cout << left << setw(6) << (i + 1) << setw(16) << rows[i].name << setw(12) << rows[i].iters;
        printVec(rows[i].x);
        cout << "\n";
    }

    return 0;
}

