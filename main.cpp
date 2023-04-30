#include <iostream>
#include <fraction.h>
#include <cmath>

//THIS IS FOR LINEAR CLASSIFICATION ONLY
//THIS IS A PROTOTYPE, NOT THE FINAL ALGORITHM

class points {
    double a;
    double b;
    double c;
    double d;
    double e;
    
    public:
        points();
        points (double, double, double, double, double);
        
        double total();
        double diff();
        void constantMultiply(double);
        void print(int);

        points operator + (points);
        points operator - (points);
        points operator * (points);
        points operator / (points);
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
    Plane.constant.constantMultiply(multiplier);
    return Plane;
}

int main() {
    //put the points in here ;)
    points Base(0, 0, 0, 0, 0);
    points Ref(0, 0, 0, 0, 0);
    hyperPlane Plane = trainSVM(Base, Ref);

    std::cout << "g(x) = ";

    for(int i = 0; i < 5; i++) {
        Plane.constant.print(i);
        std::cout << "x" << i << " + ";
    }

    std::cout << Fraction(Plane.omegaBase).printFraction() << "\n";
}

points::points() {
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    e = 0;
}

points::points(double A, double B, double C, double D, double E) {
    a = A;
    b = B;
    c = C;
    d = D;
    e = E;
}

double points::total() {
    return a + b + c + d + e;
}

double points::diff() {
    return a - b - c - d - e;
}

void points::constantMultiply(double constant) {
    a * constant;
    b * constant;
    c * constant;
    d * constant;
    e * constant;
}

void points::print(int value) {
    Fraction printValue;
    switch(value) {
        case 0: printValue = Fraction(a); break;
        case 1: printValue = Fraction(b); break;
        case 2: printValue = Fraction(c); break;
        case 3: printValue = Fraction(d); break;
        case 4: printValue = Fraction(e); break;
        default: break;
    }
    std::cout << printValue.printFraction();
    return;
}

points points::operator + (points Point) {
    points total;
    total = {
        a + Point.a,
        b + Point.b,
        c + Point.c,
        d + Point.d,
        e + Point.e
    };
    return total;
}

points points::operator - (points Point) {
    points diff;
    diff = {
        a - Point.a,
        b - Point.b,
        c - Point.c,
        d - Point.d,
        e - Point.e
    };
    return diff;
}

points points::operator * (points Point) {
    points pro;
    pro = {
        a * Point.a,
        b * Point.b,
        c * Point.c,
        d * Point.d,
        e * Point.e
    };
    return pro;
}

points points::operator / (points Point) {
    points quo;
    quo = {
        a / Point.a,
        b / Point.b,
        c / Point.c,
        d / Point.d,
        e / Point.e
    };
    return quo;
}