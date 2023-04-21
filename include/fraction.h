#include <iostream>
#include <math.h>
using namespace std;

//friendly reminders:

/*to return the operation in fraction form(string):
  num1.addTo(num2).printFraction();             */

/*to return the operation in decimal form(double):
  num1.addTo(num2).fraction();                  */

/*incredibly fucking unstable because of the following functions:
  - void lowTerm()
  - Fraction lowTerm(Fraction F)
  - Fraction estimateFraction(Fraction F)
  - double estimate (double x)                                */

/*changes from previous fraction files for reminders of me: 
  - change lowTerm to private
  - add estimateFraction and estimate
  - combine moveNeg and estimateFunction with lowTerm
  - change all getDenum and getNum to .denum and .num 
  - change some setDenum and setNum to F.denum/num       */

/*changes:
  change lowTerm(Fraction F) to lowestTerm(Fraction F)
  added lowTerm(Fraction F)
  added estimate(double x) to:
    functions that returns doubles
    printedFraction                                 */

class Fraction
{
    //only accepts double or int value types
    private:
        double num, denum;
        void lowTerm() {*this = lowTerm(*this);}
        void moveNeg() {*this = moveNeg(*this);}
        void estimateFraction() {*this = estimateFraction(*this);}

        //functions that are automatically done after a function is modified or made
        //it does the following: get the lowest term, transfer negatives, estimation

        //returns the lowest term and moveNeg of a fraction
        Fraction lowTerm(Fraction F) {return lowestTerm(moveNeg(F));}
        //gets the lowest term
        Fraction lowestTerm(Fraction F)
        {
            double factor = GCF(F.num, F.denum);
            if(F.num == F.denum) factor = 1;
            F.num /= factor; F.denum /= factor;
            return F;
        }
        //returns the moved negative sign in the fraction
        Fraction moveNeg(Fraction F)
        {
            if(F.denum < 0)
            {
                F.num = -F.num;
                F.denum = -F.denum;
            }
            return F;
        }
        //estimates the fractions numerator and denominator values
        Fraction estimateFraction(Fraction F)
        {
            F.num = estimate(F.num);
            F.denum = estimate(F.denum);
            return F;
        }
        //estimates a decimal in three places or until the next non zero number
        double estimate(double x)
        {
            double T = 1000, n = x * T;
            if(n - (int)n < 1  && fabs(x) > 0.001)
                return ((double)(int)(n)) / T;
            return x;
        }
        //
        //functions that help getting certain values
        
        //it changes the fraction based on the LCD
        double convertF(Fraction F, double commonDenum) {return commonDenum / F.denum * F.num;}
        //removes excess zeroes
        string zeroBreaker(string number)
        {
            if(number.find('.') != -1)
            {
                while(number[number.length() - 1] == '0')
                    number.erase(number.length() - 1);
                if(number[number.length() - 1] == '.')
                    number.erase(number.length() - 1);
            }
            return number;
        }
        //counts the length of decimals
        int doubleBreaker(string number)
        {
            number = zeroBreaker(number);
            if(number.find('.') == -1) return 0;
            number.erase(0, number.find('.') + 1);
            return number.length();
        }
        //returns lcm
        double LCM (double x, double y) 
        {
            double div, result = 1;
            while(div != 1)
            {
                div = GCF(x, y);
                x /= div; y /= div;
                result *= div;
            }
            return fabs(result * x * y);
        }
        //returns gcf
        double GCF(double x, double y)
        {
            if(x < y) swap(x, y);
            if(fabs(y) < 0.001) return x;
            else return (GCF(fabs(y), fabs(x - floor(x / y) * y)));
        }
    
    public:
        //constructor

        //creates 0/1
        Fraction() {num = 0; denum = 1;}
        //creates a fraction from either decimal or whole number
        Fraction(double dc)
        {
            int expo = doubleBreaker(to_string(dc));
            num = dc * pow(10, expo); denum = pow(10, expo);
            lowTerm();
        }
        //creates a fraction
        Fraction(double n, double d) {num = n; denum = d; lowTerm();}

        //returns Fractions values

//fix dis ----------------------------------------------------------------------------------------------------------------------------
        //returns the value of fraction in decimals
        double fraction() {return estimate(num / denum);}
        //returns the numerator
        double getNum() {return estimate(num);}
        //returns the denomenator
        double getDenum() {return estimate(denum);}

        //process two fractions returning a fraction

        //adds two fractions returns fraction
        Fraction addTo(Fraction F)
        {
            double LCD = LCM(denum, F.denum);
            double sumNum = convertF(*this, LCD) + convertF(F, LCD);
            Fraction result (sumNum, LCD);
            return result;
        }
        //subtracts two fractions returns fraction
        Fraction subTo(Fraction F)
        {
            double LCD = LCM(denum, F.denum);
            double diffNum = convertF(*this, LCD) - convertF(F, LCD);
            Fraction result (diffNum, LCD);
            return result;
        }
        //multiply two fractions returns fraction
        Fraction mulTo(Fraction F)
        {
            Fraction result (num * F.num, denum * F.denum);
            return result;
        }
        //divide two fractions returns fraction
        Fraction divTo(Fraction F)
        {
            Fraction result (num * F.denum, denum * F.num);
            return result;
        }

        //returns the fraction in fraction form in string (cannot do it with expressions)
        string printFraction() {return zeroBreaker(to_string(estimate(num))) + "/" + zeroBreaker(to_string(estimate(denum)));}

        //change Fraction's value

        //change the numerator
        void setNum(double n) {num = n; lowTerm();}
        //change the denominator
        void setDenum(double d) {denum = d; lowTerm();}
        //change the value of the fraction from a double value
        void setFraction(double n)
        {
            Fraction temp (n);
            *this = temp;
        }
        //change the value of the fraction
        void setFraction(double n, double d) {setNum(n); setDenum(d);}
        //change the value of the fraction from the value of another fraction
        void setFraction(Fraction F) {setNum(F.num); setDenum(F.denum);}
};

/*
Private functions lists:

//fraction modifiers:
void lowTerm()
void moveNeg()
void estimateFraction()
double estimate(double x)
Fraction lowTerm(Fraction F)
Fraction moveNeg(Fraction F)
Fraction estimateFraction(Fraction F)

//returns values based on fraction's variables:
double LCM(double x, double y)
double GCF(double x, double y)
int doubleBreaker(string number)
string zeroBreaker(string number)
double convertF(Fraction F, double commonDenum)
*/

/*
Public functions lists:

constructors:
Fraction()
Fraction(double dc)
Fraction(int n, int d)

get values:
int getNum()
int getDenum()
double fraction()
string printFraction()

arithmetic operators:
Fraction addTo(Fraction F)
Fraction subTo(Fraction F)
Fraction mulTo(Fraction F)
Fraction divTo(Fraction F)

change values:
void setNum(int n)
void setDenum(int d)
void setFraction(double n)
void setFraction(Fraction F)
void setFraction(int n, int d)
*/