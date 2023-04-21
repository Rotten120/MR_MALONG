#include <iostream>
#include <cmath>
#include <vector>

struct point {
    double x;
    double y;
    double z;
};

double getDistance3d(point A, point B) {
    double TermX = pow(A.x - B.x, 2);
    double TermY = pow(A.y - B.y, 2);
    double TermZ = pow(A.z - B.z, 2);
    double Distance = sqrt(TermX + TermY + TermZ);

    return Distance;
}

int main() {
    std::vector <point> Red = {
        {2, 5, 3},
        {3, 4, 2},
        {1, 1, 4},
        {5, 8, 1},
        {3, 9, 4}
    };

    std::vector <point> Blue = {
        {6, 6, 6},
        {5, 3, 8},
        {7, 2, 7},
        {8, 9, 7},
        {8, 5, 9}
    };

    for(int i = 0; i < Red.size(); i++) {
        std::cout << "point " << i << "\n";
        for(int n = 0; n < Blue.size(); n++)
            std::cout << getDistance3d(Red[i], Blue[n]) << "\n";
        std::cout << "\n\n";
    }

    return 0;
}