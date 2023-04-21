#include <SVM.h>

int main() {
    points Base(6, 6, 6);
    points Ref(3, 9, 4);
    hyperPlane Plane = trainSVM(Base, Ref);
    Plane.printEquation();
}

