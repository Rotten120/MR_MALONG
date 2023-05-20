#ifndef SVM_H
#define SVM_H

#include <iostream>
#include <fraction.h>
#include <vector>
#include <cmath>

typedef unsigned int posint;
class hyperPlane;

class points {
    double a;
    double b;
    double c;

    public:
        points();
        points (const double, const double, const double);
        
        double total() const;
        double diff() const;
        double getDistance(const points) const;
        points getConstantMultiply(const double) const;
        void print(const int);

        points operator + (const points) const;
        points operator - (const points) const;
        points operator * (const points) const;
        points operator / (const points) const;
        friend hyperPlane;
};

class hyperPlane { 
    points constant;
    double omegaBase;
    public:
        hyperPlane();
        hyperPlane(const points, const double);
        double getValue(points);
        void printEquation();
        friend points;
};

struct setIdentifier {
    double distance;
    int indexBase, indexRef;
};

double testSVM(std::vector <points> Base, std::vector <points> Ref, hyperPlane Plane) {
    int inBase = 0;
    int inRef = 0;

    for(int i = 0; i < Base.size(); i++) {
        if(Plane.getValue(Base[i]) >= 1)
            inBase++;
    }

    for(int i = 0; i < Ref.size(); i++) {
        if(Plane.getValue(Ref[i]) <= -1)
            inRef++;
    }

    double accuracy = double(inBase + inRef) / double(Base.size() + Ref.size());
    return accuracy;
}

hyperPlane getSVM(points Base, points Ref) {
    points omega = Base - Ref;
    Base = Base * omega;
    Ref = Ref * omega;

    double multiplier = 2 / (Base.total() - Ref.total());

    hyperPlane Plane (
        omega.getConstantMultiply(multiplier),
        1 - multiplier * Base.total()
    );
    
    return Plane;
}

hyperPlane trainSVM(std::vector <points> Base, std::vector <points> Ref) {
    int baseSize = Base.size();
    int refSize = Ref.size();
    int arraySize = baseSize * refSize;

    double lowestDistance = Base[0].getDistance(Ref[0]);
    points nearestBase = Base[0], nearestRef = Ref[0];

    int indexBase = 0, indexRef = 0;

    for(int i = 0; i < arraySize; i++) {
        indexBase = (i - (i % refSize)) / refSize;
        indexRef = i % refSize;

        double pointDistance = Base[indexBase].getDistance(Ref[indexRef]);

        if(lowestDistance > pointDistance) {
            lowestDistance = pointDistance;
            nearestBase = Base[indexBase];
            nearestRef = Ref[indexRef];
        }   
    }

    std::cout << "[";
        nearestBase.print(0);
    std::cout << ", ";
        nearestBase.print(1);
    std::cout << ", ";
        nearestBase.print(2);
    std::cout << "] || [";
        nearestRef.print(0);
    std::cout << ", ";
        nearestRef.print(1);
    std::cout << ", ";
        nearestRef.print(2);
    std::cout << "]\n";
    
    hyperPlane Plane = getSVM(nearestBase, nearestRef);
    return Plane;
}

hyperPlane::hyperPlane() {
    omegaBase = 0;
}

hyperPlane::hyperPlane(const points Points, const double Omega) {
    constant = Points;
    omegaBase = Omega;
}

void hyperPlane::printEquation() {
    std::cout << "g(x) = ";

    for(int i = 0; i < 3; i++) {
        constant.print(i);
        std::cout << "x" << i+1 << " + ";
    }

    std::cout << Fraction(omegaBase).printFraction() << "\n";
}

double hyperPlane::getValue(points w) {
    double valueA = w.a * constant.a;
    double valueB = w.b * constant.b;
    double valueC = w.c * constant.c;

    return valueA + valueB + valueC + omegaBase;
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

double points::getDistance(const points Point) const {
    return sqrt(pow(a - Point.a, 2) + pow(b - Point.b, 2) + pow(c - Point.c, 2));
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

#else
#endif