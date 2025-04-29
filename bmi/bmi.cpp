// KJN - it is good practice to insert comment about intended use, context, contributors, etc

#include <iostream>
#include <fstream>
#include <string>
#define DOCTEST_CONFIG_IMPLEMENT
#include "doctest.h"

using namespace std;

//Converts ounces to pounds
double ounces2pounds(int x)
{
    // Jesse - Changed data type and to double
    // Jesse - Changed from multiplying by 16 to dividing by 16.0
    return(x/16.0);
}

//Converts stones into pounds
double stones2pounds(int x)
{
    // Jesse - Changed data type and to double and 14 to 14.0
    return(x*14.0);
}
//Accepts stones, ounces and pounds. Converts stones and ounces to pounds. Adds all 3. Converts to kilograms
double weight2kg(int stones, int pounds, int ounces)
{
    return (stones2pounds(stones)+pounds+ounces2pounds(ounces))/2.2;
}

//Converts inches to feet
double inches2feet(int x)
{
    // Jesse - Added fucntion that accepts inches and converts it to feet
    return (x/12.0);
}

//Takes in a height in feet and inches. Converts it to meters
double height2metres(int feet, int inches)
{
    // Jesse - Changed 3.82 in return to 3.28 and added the inches converted to feet
    return((feet+inches2feet(inches))/3.28);
}

//Takes in weight and height. Calculates and grades BMI
char categorise(double kg, double metre)
{
    // Jesse - Changed bmi from weight^2/height to weight/height^2
    double bmi = kg/(metre*metre);
    char cat;
    if (bmi<19)
        cat='A';
    else if (bmi >=19 && bmi<25) 
        cat='B';
        // Jesse - changed <=26 to >=19 && <25
    else if (bmi >=25 && bmi<30)
        cat='C';
        // Jesse - changed <=30 to >=25 && <30
    else
        cat='D';
    return(cat);
}

void process_data(char* input_file, char* output_file)
{
    ifstream f_in;
    ofstream f_out;
    string data;
    string person_id;
    int pounds, stones, ounces, feet, inches;
    double kg, m;
    char cat;

    f_in.open(input_file,ios::in);
    f_out.open(output_file,ofstream::out);
    while (!f_in.eof())
    {
        // Jesse - Swapped order of stones and pounds when reading from file
    	f_in >> person_id >> stones >> pounds >> ounces >> feet >> inches;
        kg=weight2kg(int(stones),int(pounds),int(ounces));
        m =height2metres(int(feet),int(inches));
        cat=categorise(kg,m);
	f_out << person_id << " " << cat << endl;
    }
    f_in.close();
    f_out.close();
}
        
int main(int argc, char *argv[])
{
    // KJN - Need to check that 3 arguments were supplied upon execution
    // Jesse - Added check for number of arguments. Gives error message if failed
    doctest::Context context;
    int res = context.run();
    if(context.shouldExit())return res;
    if(argc != 3)
    {
        cerr  << "Insufficient number of arguments" << endl;
        return 1;
    }
    process_data(argv[1], argv[2]);
    return res;
}

//Testing if the ounces to pounds conversion is working
TEST_CASE("Testing ounces to pounds conversion")
{
    CHECK(ounces2pounds(16) == 1.0); //checks division 
    CHECK(ounces2pounds(0) == 0.0); //0 case
    CHECK(ounces2pounds(32) == 2.0); // multiple of 16
    CHECK(ounces2pounds(8) == 0.5); //non multiple of 16
    CHECK(ounces2pounds(-16) == -1.0); //negative case
}

//Testing if stones to pounds conversion is working
TEST_CASE("Testing stones to pounds conversion")
{
    CHECK(stones2pounds(1) == 14.0); //checks multiplication
    CHECK(stones2pounds(0) == 0.0); //0 case
    CHECK(stones2pounds(2) == 28.0); //multiple
    CHECK(stones2pounds(-1) == -14.0); //negative case
}

//Testing if weight to kilograms conversion is working
TEST_CASE("Testing weight to kg conversion")
{
    CHECK(weight2kg(6,13,12) == doctest::Approx(44.4318)); //checks first line in study.dat
    CHECK(weight2kg(7,10,3) == doctest::Approx(49.1761)); //checks second line in study.dat
}

//Testing if inches to feet conversion works
TEST_CASE("Testing inches to feet conversion")
{
    CHECK(inches2feet(12) == 1.0); //testing division
    CHECK(inches2feet(0) == 0.0); //0 case
    CHECK(inches2feet(24) == 2.0); //multiple
    CHECK(inches2feet(6) == 0.5); //non multiple
    CHECK(inches2feet(-12) == -1.0); //negative case
}

//Testing height to metres conversion is working
TEST_CASE("Testing height to metres conversion")
{
    CHECK(height2metres(5,9) == doctest::Approx(1.75305)); //checks first line in study.dat
    CHECK(height2metres(5,11) == doctest::Approx(1.80386)); //checks second line in study.dat
}

//Testing categorise function
TEST_CASE("Testing categorise")
{
    CHECK(categorise(44.4318,1.75305) == 'A'); //checks first line in study.dat
    CHECK(categorise(49.1761,1.80386) == 'A'); //checks second line in study.dat
}
