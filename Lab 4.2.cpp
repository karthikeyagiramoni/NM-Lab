
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
    return {x, converged ? k : k, converged};
}

int main() {
    cout << fixed << setprecision(6);

    Mat A = {
        {13,  0,  1,  3, -1,  1,  1,  3},
        {-2,-11,  3, -1, -1,  1,  0, -1},
        { 2,  1,-12,  0,  2,  2, -2,  0},
        { 1, -3,  0,-15,  2,  1,  0, -3},
        {-3, -1, -1,  3,-16,  0,  0,  3},
        { 2,  2,  3,  2, -1, 16,  3,  0},
        {-3, -1,  1, -1,  3,  1,-18,  3},
        {-2,  0, -3,  0,  2, -2, -2,-15}
    };
    Vec b = {31, 21.5, -2, -35.5, 20.5, 47.5, -7, -4};
    vector<double> x0(8);
    cout<<"\nEnter the Intial Approximation:\n";
    for(int i=0;i<8;i++)
    {
    	cin>>x0[i];
	}


    Result r05 = sor(A, b, x0, 0.5);
    Result r15 = sor(A, b, x0, 1.5);

    double rhoJ = 0.3343;
    double omegaOpt = 2.0 / (1.0 + sqrt(1.0 - rhoJ * rhoJ));
    cout << "rho(H_J) = " << rhoJ
         << "  ->  omega_opt = "
         << setprecision(6) << omegaOpt << "\n\n";

    Result ropt = sor(A, b, x0, omegaOpt);

    cout << left << setw(20) << "Method" << setw(12) << "Iterations" << "Solution vector\n";
    cout << string(95, '-') << "\n";
    cout << left << setw(20) << "SOR (w=0.5)" << setw(12) << r05.iterations;  printVec(r05.x);  cout << "\n";
    cout << left << setw(20) << "SOR (w=1.5)" << setw(12) << r15.iterations;  printVec(r15.x);  cout << "\n";
    cout << left << setw(20) << ("SOR (w_opt=" + to_string(omegaOpt).substr(0, 6) + ")")
         << setw(12) << ropt.iterations; printVec(ropt.x); cout << "\n";

    return 0;
}

