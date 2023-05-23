#include <C:\Users\jhs2284-G9\Desktop\MR_MALONG\include\SVM.h>
#include <vector>
#include <ctime>
#include <cstdlib>

void generateSamples(std::vector <points>& Base, std::vector <points>& Ref, int sampleSize) {

    int BaseA = 0, BaseB = 0, RefA = 0, RefB = 0;

    for(int i = 0; i < sampleSize; i++) {
        //TO GENERATE SAMPLES (DI KO RIN GETS YUNG CODE SORRY)
        //equation: y = 2x - 30
        //support vector a: y = 2x - 29
        //support vector b: y = 2x - 31
        //range of points (0, 0) to (40, 40)

        //intersections of lines to the box:
        //line A: POTEK TINAMAD AKO BASTA AUN
        //CONSIDERED UNG INTERSECTION NG LINES TO THE BORDER NUNG RANGE

        BaseA = rand() % 34;
        RefA = (rand() % 24) + 16;

        if(BaseA <= 14) BaseB = rand() % 40;
        else BaseB = rand() % (40 - (BaseA * 2 - 29)) + (BaseA * 2 - 29);

        if(RefA >= 36) RefB = rand() % 40;
        else RefB = rand() % (RefA * 2 - 31);

        Base[i] = points(BaseA, BaseB, 0);
        Ref[i] = points(RefA, RefB, 0);
    }
}

int main() {
    srand(time(0));

    const unsigned int array = 10;
    int Size[array] = {10, 20, 40, 80, 100, 150, 200, 300, 500, 1000};

    for(int n = 0; n < array; n++) {
        std::vector <points> Base(Size[n]);
        std::vector <points> Ref(Size[n]);

        generateSamples(Base, Ref, Size[n]);        

        std::cout << "\n\nTest: " << Size[n] << " samples\n";
            hyperPlane plane = trainSVM(Base, Ref);
            plane.printEquation();
        std::cout << testSVM(Base, Ref, plane);
    }
}
