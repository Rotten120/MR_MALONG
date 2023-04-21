#include <iostream>
#include <vector>
#include <fraction.h>
#include <cmath>

class points {
    double a;
    double b;
    double c;

    public:
        points();
        points (const double, const double, const double);
        
        double total() const;
        double diff() const;
        points getConstantMultiply(const double) const;
        void print(const int);

        points operator + (const points) const;
        points operator - (const points) const;
        points operator * (const points) const;
        points operator / (const points) const;
};

struct hyperPlane { 
    points constant;
    double omegaBase;
};

hyperPlane trainSVM(points Base, points Ref) {
    points omega = Base - Ref;
    Base = Base * omega;
    Ref = Ref * omega;

    double multiplier = 2 / (Base.total() - Ref.total());

    hyperPlane Plane;
    Plane.omegaBase = 1 - multiplier * Base.total();
    Plane.constant = omega.getConstantMultiply(multiplier);
    return Plane;
}

int main() {
    //CHANGE THE VALUES HERE :))))))))
    points Base(6, 6, 6);
    points Ref(3, 4, 2);
    hyperPlane Plane = trainSVM(Base, Ref);

    std::cout << "g(x) = ";

    for(int i = 0; i < 3; i++) {
        Plane.constant.print(i);
        std::cout << "x" << i+1 << " + ";
    }

    std::cout << Fraction(Plane.omegaBase).printFraction() << "\n";
}

points::points() {
    a = 0;
    b = 0;
    c = 0;
}

points::points(const double A, const double B, const double C) {
    a = A;
    b = B;
    c = C;
}

double points::total() const {
    return a + b + c;
}

double points::diff() const {
    return a - b - c;
}

points points::getConstantMultiply(double constant) const {
    points Product = {
        a * constant,
        b * constant,
        c * constant
    };
    return Product;
}

void points::print(const int value) {
    Fraction printValue;
    switch(value) {
        case 0: printValue = Fraction(a); break;
        case 1: printValue = Fraction(b); break;
        case 2: printValue = Fraction(c); break;
        default: break;
    }
    std::cout << printValue.printFraction();
    return;
}

points points::operator + (const points Point) const {
    points total;
    total = {
        a + Point.a,
        b + Point.b,
        c + Point.c,
    };
    return total;
}

points points::operator - (const points Point) const {
    points diff;
    diff = {
        a - Point.a,
        b - Point.b,
        c - Point.c,
    };
    return diff;
}

points points::operator * (const points Point) const {
    points pro;
    pro = {
        a * Point.a,
        b * Point.b,
        c * Point.c,
    };
    return pro;
}

points points::operator / (const points Point) const {
    points quo;
    quo = {
        a / Point.a,
        b / Point.b,
        c / Point.c,
    };
    return quo;
}