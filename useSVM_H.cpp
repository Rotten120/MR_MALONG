#include <SVM.h>
#include <vector>
#include <ctime>
#include <cstdlib>

int main() {
    srand(time(0));

    int Size[10] = {10, 20, 40, 80, 100, 150, 200, 300, 500, 1000};

    for(int n = 0; n < 10; n++) {
        std::vector <points> Base(Size[n]);
        std::vector <points> Ref(Size[n]);

        int BaseA = 0, BaseB = 0, RefA = 0, RefB = 0;

        for(int i = 0; i < Size[n]; i++) {
            //TO GENERATE SAMPLES (DI KO RIN GETS YUNG CODE SORRY)

            BaseA = rand() % 34;
            RefA = (rand() % 24) + 16;

            if(BaseA <= 14) BaseB = rand() % 40;
            else BaseB = rand() % (40 - (BaseA * 2 - 29)) + (BaseA * 2 - 29);

            if(RefA >= 36) RefB = rand() % 40;
            else RefB = rand() % (RefA * 2 - 31);

            Base[i] = points(BaseA, BaseB, 1);
            Ref[i] = points(RefA, RefB, 1);
        }

        std::cout << "\n\nTest: " << Size[n] << " samples\n";
            hyperPlane plane = trainSVM(Base, Ref);
            plane.printEquation();
        std::cout << testSVM(Base, Ref, plane);
    }
}