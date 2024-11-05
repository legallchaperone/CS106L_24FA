#include <iostream>
#include <cmath>
#include <utility>

std::pair<bool, std::pair<double, double>> solveQuadratic(double a, double b, double c){
    double delta = b*b-4*a*c;
    std::pair<bool, std::pair<double, double>> Solution;
    if (delta >= 0){
        bool solvable = true;
        double root1 = ((-b + sqrt(delta)) / (2 * a));
        double root2 = ((-b - sqrt(delta)) / (2 * a));
        std::pair<double,double> solutions = {root1, root2};
        Solution.first = solvable;
        Solution.second = solutions;
        return Solution;
    }
    Solution.first = false;
    return Solution;
}

int main() {
    double a, b ,c;
    std::cout << "Enter coefficients a, b, and c: ";
    std::cin >> a >> b >> c;

    auto result = solveQuadratic(a,b,c);
    if (result.first){
        std::cout<< "The First Root is:" << result.second.first << std::endl;
        std::cout<< "The Second Root is:"<< result.second.second << std::endl;
    }
    else {
        std::cout << "No real roots." << std::endl;
    }
    return 0;
}