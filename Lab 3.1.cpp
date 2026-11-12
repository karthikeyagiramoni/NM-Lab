#include <bits/stdc++.h>
using namespace std;

const int N = 3;

double round4(double x) {
    if (x == 0.0) return 0.0;
    int sign = (x < 0) ? -1 : 1;
    x = fabs(x);
    int exponent = (int)floor(log10(x));
    double factor = pow(10.0, 3 - exponent);
    double rounded = round(x * factor) / factor;
    return sign * rounded;
}
double rmul(double a, double b) { return round4(a * b); }
double rdiv(double a, double b) { return round4(a / b); }
double radd(double a, double b) { return round4(a + b); }
double rsub(double a, double b) { return round4(a - b); }

void printAug(vector<vector<double>>& A, vector<double>& b,const string& title) {
    cout << "\n" << title << ":\n";
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++)
            cout << setw(10) << round4(A[i][j]) << " ";

        cout << " | " << setw(10) << round4(b[i]) << "\n";
    }
}

vector<double> backSubstitute(vector<vector<double>> A, vector<double> b,
                               vector<int> colOrder, bool& success) {
    vector<double> x(N, 0.0);
    success = true;
    for (int i = N - 1; i >= 0; i--) {
        if (fabs(A[i][i]) < 1e-12) { success = false; return x; }
        double sum = b[i];
        for (int j = i + 1; j < N; j++)
            sum =(sum- (A[i][j]* x[j]));
        x[i] = (sum/ A[i][i]);
    }
    vector<double> xFinal(N);
    for (int i = 0; i < N; i++) xFinal[colOrder[i]] = x[i];
    return xFinal;
}

/*No Pivoting*/
vector<double> gaussNoPivot(vector<vector<double>> A, vector<double> b, bool& success,
                             vector<double>& initialPivots) {
    vector<int> colOrder = {0, 1, 2};
    for (int k = 0; k < N - 1; k++) {
        initialPivots.push_back(A[k][k]);
        if (fabs(A[k][k]) < 1e-12) { success = false; return vector<double>(N, 0); }
        for (int i = k + 1; i < N; i++) {
            double m =(A[i][k]/ A[k][k]);
            for (int j = k; j < N; j++)
                A[i][j] =(A[i][j]-(m* A[k][j]));
            b[i] =(b[i]-(m* b[k]));
        }
    }
    initialPivots.push_back(A[N - 1][N - 1]);
    printAug(A, b, "  Upper-triangular form (No Pivoting)");
    return backSubstitute(A, b, colOrder, success);
}

/*Partial Pivoting*/
vector<double> gaussPartialPivot(vector<vector<double>> A, vector<double> b, bool& success,
                                  vector<double>& initialPivots) {
    vector<int> colOrder = {0, 1, 2};
    for (int k = 0; k < N - 1; k++) {
        int piv = k;
        double maxVal = fabs(A[k][k]);
        for (int i = k + 1; i < N; i++)
            if (fabs(A[i][k]) > maxVal) { maxVal = fabs(A[i][k]); piv = i; }
        if (piv != k) { swap(A[k], A[piv]); swap(b[k], b[piv]); }
        initialPivots.push_back(A[k][k]);
        if (fabs(A[k][k]) < 1e-12) { success = false; return vector<double>(N, 0); }
        for (int i = k + 1; i < N; i++) {
            double m = rdiv(A[i][k], A[k][k]);
            for (int j = k; j < N; j++)
                A[i][j] = rsub(A[i][j], rmul(m, A[k][j]));
            b[i] = rsub(b[i], rmul(m, b[k]));
        }
    }
    initialPivots.push_back(A[N - 1][N - 1]);
    printAug(A, b, "  Upper-triangular form (Partial Pivoting)");
    return backSubstitute(A, b, colOrder, success);
}

/*Complete Pivoting*/
vector<double> gaussCompletePivot(vector<vector<double>> A, vector<double> b, bool& success,
                                   vector<double>& initialPivots) {
    vector<int> colOrder = {0, 1, 2};
    for (int k = 0; k < N - 1; k++) {
        int pivRow = k, pivCol = k;
        double maxVal = fabs(A[k][k]);
        for (int i = k; i < N; i++)
            for (int j = k; j < N; j++)
                if (fabs(A[i][j]) > maxVal) { maxVal = fabs(A[i][j]); pivRow = i; pivCol = j; }
        if (pivRow != k) { swap(A[k], A[pivRow]); swap(b[k], b[pivRow]); }
        if (pivCol != k) {
            for (int i = 0; i < N; i++) swap(A[i][k], A[i][pivCol]);
            swap(colOrder[k], colOrder[pivCol]);
        }
        initialPivots.push_back(A[k][k]);
        if (fabs(A[k][k]) < 1e-12) { success = false; return vector<double>(N, 0); }
        for (int i = k + 1; i < N; i++) {
            double m = rdiv(A[i][k], A[k][k]);
            for (int j = k; j < N; j++)
                A[i][j] = rsub(A[i][j], rmul(m, A[k][j]));
            b[i] = rsub(b[i], rmul(m, b[k]));
        }
    }
    initialPivots.push_back(A[N - 1][N - 1]);
    printAug(A, b, "  Upper-triangular form (Complete Pivoting)");
    return backSubstitute(A, b, colOrder, success);
}



vector<vector<double>> inverse3x3(vector<vector<double>> A, bool& success) {
    double a = A[0][0], b = A[0][1], c = A[0][2];
    double d = A[1][0], e = A[1][1], f = A[1][2];
    double g = A[2][0], h = A[2][1], i = A[2][2];

    double C11 = rsub(rmul(e, i), rmul(f, h));
    double C12 = -rsub(rmul(d, i), rmul(f, g));
    double C13 = rsub(rmul(d, h), rmul(e, g));
    double C21 = -rsub(rmul(b, i), rmul(c, h));
    double C22 = rsub(rmul(a, i), rmul(c, g));
    double C23 = -rsub(rmul(a, h), rmul(b, g));
    double C31 = rsub(rmul(b, f), rmul(c, e));
    double C32 = -rsub(rmul(a, f), rmul(c, d));
    double C33 = rsub(rmul(a, e), rmul(b, d));

    double det = radd(radd(rmul(a, C11), rmul(b, C12)), rmul(c, C13));
    if (fabs(det) < 1e-12) { success = false; return {}; }
    success = true;

    vector<vector<double>> invA(N, vector<double>(N));
    invA[0][0] = rdiv(C11, det); invA[0][1] = rdiv(C21, det); invA[0][2] = rdiv(C31, det);
    invA[1][0] = rdiv(C12, det); invA[1][1] = rdiv(C22, det); invA[1][2] = rdiv(C32, det);
    invA[2][0] = rdiv(C13, det); invA[2][1] = rdiv(C23, det); invA[2][2] = rdiv(C33, det);
    return invA;
}

void printSolution(const string& label, bool success,vector<double>& x, vector<double>& pivots) {
    cout << "\nInitial pivot sequence: ";
    for (double p : pivots)
        cout << round4(p) << " ";

    cout << "\nStatus: "
         << (success ? "Successful" : "Failed") << "\n";

    if (success) {
        cout << "Solution vector:\n";
        cout << "x1 = " << round4(x[0]) << "\n";
        cout << "x2 = " << round4(x[1]) << "\n";
        cout << "x3 = " << round4(x[2]) << "\n";
    }
}

int main() {
    cout << fixed << setprecision(4);

    vector<vector<double>> A = {
        {0.0001, 1.0000, 1.0000},
        {1.0000, 1.0000, 2.0000},
        {2.0000, 1.0000, 1.0000}
    };
    vector<double> b = {2.0001, 4.0000, 4.0000};

    cout << "\n (b) Gaussian Elimination WITHOUT pivoting\n";
    bool succ1 = true;
    vector<double> piv1;
    vector<double> x1 = gaussNoPivot(A, b, succ1, piv1);
    printSolution("No Pivoting", succ1, x1, piv1);

    cout << "\n (c) Gaussian Elimination WITH partial pivoting\n";
    bool succ2 = true;
    vector<double> piv2;
    vector<double> x2 = gaussPartialPivot(A, b, succ2, piv2);
    printSolution("Partial Pivoting", succ2, x2, piv2);
    
    cout << "\n (d) Gaussian Elimination WITH complete pivoting\n";
    bool succ3 = true;
    vector<double> piv3;
    vector<double> x3 = gaussCompletePivot(A, b, succ3, piv3);
    printSolution("Complete Pivoting", succ3, x3, piv3);

    cout << "\n Summary Table\n";
    cout << left << setw(20) << "Strategy" << setw(14) << "InitialPivot"
         << setw(30) << "Solution Vector" << "Status\n";
    cout << left << setw(20) << "No Pivoting" << setw(14) << piv1[0]
         << "[" << x1[0] << ", " << x1[1] << ", " << x1[2] << "]  "
         << (succ1 ? "Successful" : "Failed") << "\n";
    cout << left << setw(20) << "Partial Pivoting" << setw(14) << piv2[0]
         << "[" << x2[0] << ", " << x2[1] << ", " << x2[2] << "]  "
         << (succ2 ? "Successful" : "Failed") << "\n";
    cout << left << setw(20) << "Complete Pivoting" << setw(14) << piv3[0]
         << "[" << x3[0] << ", " << x3[1] << ", " << x3[2] << "]  "
         << (succ3 ? "Successful" : "Failed") << "\n";

    
    return 0;
}

