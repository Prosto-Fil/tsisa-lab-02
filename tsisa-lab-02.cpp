#include <iostream>
#include <cmath>
#include <vector>
#include <string>
#include <iomanip>

using std::cout;
using std::endl;

double f(const double x) {
    return (-sqrt(x) * sin(x));
}

double f_new(const double x) {
    return (f(x) * sin(5 * x));
}

const std::vector<double> P = { 0.9, 0.91, 0.92, 0.93, 0.94, 0.95, 0.96, 0.97, 0.98, 0.99 };

const std::vector<double> q = { 0.005, 0.01, 0.015, 0.02, 0.025, 0.03, 0.035, 0.04, 0.045, 0.05, 0.055, 0.06, 0.065, 0.07, 0.075, 0.08, 0.085, 0.09, 0.095, 0.1 };

const double a = 0.0;

const double b = 3.0;

double random(double min, double max) {
    return (double)(rand()) / RAND_MAX * (max - min) + min;
}

std::vector<std::vector<int>> n_p_q(const std::vector<double>& P, const std::vector<double>& q) {
    std::vector<std::vector<int>> table;
    for (size_t i = 0; i < q.size(); i++) {
        std::vector<int> string;
        for (size_t j = 0; j < P.size(); j++) {
            string.push_back(int(log(1 - P[j]) / log(1 - q[i]) * 100) / 100);
        }
        table.push_back(string);
    }
    return table;
}

void Print_n_p_q(const std::vector<std::vector<int>>& table) {
    cout << std::string(68, '-') << endl;
    cout << "|q\\\P   ";
    for (size_t i = 0; i < P.size(); i++) {
        cout << "|" << std::setw(5) << std::left << P[i];
    }
    cout << '|' << endl;
    cout << std::string(68, '-') << endl;
    for (size_t i = 0; i < table.size(); i++) {
        cout << "|";
        cout << std::setw(6) << std::left << q[i];
        for (size_t j = 0; j < table[i].size(); j++) {
            cout << '|' << std::setw(5) << std::left << table[i][j];
        }
        cout << '|' << endl;
    }
    cout << std::string(68, '-') << endl;
}

void Print(const std::vector<std::vector<double>>& table) {
    cout << std::string(118, '-') << endl;
    cout << "|q\\\P   ";
    for (size_t i = 0; i < P.size(); i++) {
        cout << "|" << std::setw(10) << std::left << P[i];
    }
    cout << '|' << endl;
    cout << std::string(118, '-') << endl;
    for (size_t i = 0; i < table.size(); i++) {
        cout << "|";
        cout << std::setw(6) << std::left << q[i];
        for (size_t j = 0; j < table[i].size(); j++) {
            cout << '|' << std::setw(10) << std::left << table[i][j];
        }
        cout << '|' << endl;
    }
    cout << std::string(118, '-') << endl;
}

std::vector<std::vector<double>> random_search(const std::vector<std::vector<int>>& all_n, const int choice) {
    std::vector<std::vector<double>> table;
    for (size_t i = 0; i < q.size(); i++) {
        std::vector<double> string;
        for (size_t j = 0; j < P.size(); j++) {
            double min = 9223372036854775807.0;
            for (size_t k = 0; k < all_n[i][j]; k++) {
                double elem;
                if (choice == 0) {
                    elem = f(random(a, b));
                }
                else if (choice == 1) {
                    elem = f_new(random(a, b));
                }
                else {
                    throw std::logic_error("Invalid choice");
                }
                if (elem < min) {
                    min = elem;
                }
            }
            string.push_back(min);
        }
        table.push_back(string);
    }
    return table;
}

int main() {
    Print_n_p_q(n_p_q(P, q));
    cout << endl;

    Print(random_search(n_p_q(P, q), 0));
    cout << endl;

    Print(random_search(n_p_q(P, q), 1));
    cout << endl;

    return 0;
}
