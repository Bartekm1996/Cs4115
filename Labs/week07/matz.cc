#include <iostream>
#include <string>
#include <sstream>
#include <math.h>

using namespace std;
void readFromCin(bool,double);


int main(int argc,char **argv){

    double epsilon = 0;
    bool eps = false;
    
    if(argc != 1 && argc != 3){

        cerr << "Incorrect number of arguments given \nFormat Required : eg -> ./matz -e 0.25 < name_of_file " << endl;
        exit(1);
    
    }else{
    
        if(argc == 3){
            epsilon = fabs(strtod(*(argv+2),0));
            eps = true;
        }
       readFromCin(eps,epsilon);
    }

    return 0;
}



void readFromCin(bool eps,double epsilon){

    string inputLine = "";
    double firstValue = 0;
    int col = 0;

    while(getline(cin,inputLine)){
        istringstream lstream(inputLine);
        ostringstream strs;
        while(lstream >> firstValue){
            if(eps){
                if(firstValue != 0 && (firstValue > epsilon || firstValue < epsilon*-1 )){
                    strs << col+1 << " " << firstValue << " ";
                }
            }else{
                if(firstValue != 0)
                {
                    strs << col+1 << " " << firstValue << " ";
                }
            }
            col++;
        }
        string str = strs.str();
        cout << str << endl;
        col = 0;
    }
}
