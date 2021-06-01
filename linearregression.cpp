#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

using namespace std;

int main() {
    ifstream file("dat.txt");
    
    if(!file) {
        cerr << "Could not open file" << endl;
        exit(1);
    }
    
    vector<pair<double, double>> data;
    
    double token_x, token_y;
    
    while(file >> token_x >> token_y) {
        data.emplace_back(token_x, token_y);
    }
    
    double x_bar = 0, y_bar = 0;
    
    for(const pair<double, double>& point : data) {
        x_bar += point.first;
        y_bar += point.second;
    }
    
    x_bar /= data.size();
    y_bar /= data.size();
    
    cout << "n = " << data.size() << endl << "X Bar = " << x_bar << endl << "Y Bar = " << y_bar << endl;
    
    double sxx = 0, syy = 0, sxy = 0;
    
    for(const pair<double, double>& point : data) {
        sxx += pow((point.first - x_bar), 2);
        syy += pow((point.second - y_bar), 2);
        sxy += (point.first - x_bar) * (point.second - y_bar);
    }
    
    cout << "Sxx = " << sxx << endl << "Syy = " << syy << endl << "Sxy = " << sxy << endl;
    
    double b1 = sxy / sxx;
    double b0 = y_bar - (x_bar * b1);
    
    cout << "b1 = " << b1 << endl << "b0 = " << b0 << endl;
    
    double variance = 0;
    
    for(const pair<double, double>& point : data) {
        variance += pow(((b0 + (b1 * point.first)) - point.second), 2);
    }
    
    variance /= data.size() - 2;
    
    cout << "Sample Variance = " << variance << endl;
    
    double sse = syy - (b1 * sxy);
    double r2 = 1 - (sse / syy);
    
    cout << "SSE = " << sse << endl << "R^2 = " << r2 << endl;

    return 0;
}
