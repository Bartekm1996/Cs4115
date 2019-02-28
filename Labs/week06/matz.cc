#include <iostream>
#include <string>
#include <sstream>
#include <math.h>


using namespace std;

int readMatrix(int,int,double**);
void prepMatrix(int,int,double**);
void clearMatrix(int,int,double**);
void formatzMar(int,int,double**);
int zeroCount(int,int,double**);



int main(int argc,char **argv){

    int row_count = 0,col_count = 0,zero_count = 0;

    if(argc != 3){
        
        cerr << "Incorrect number of arguments given \n Required 3 : Row Noumber Col number" << endl;
        exit(1);
    
    }else{

        row_count = atoi(*(argv+1));
        col_count = atoi(*(argv+2));
        cout << row_count << endl;
        double **mat = new double*[row_count];
        prepMatrix(row_count,col_count,mat);
        zero_count = readMatrix(row_count,col_count,mat);
        
        for(int i = 0; i < row_count; i++){
            formatzMar(i,col_count,mat);
        }

        cout << zero_count << endl;
        clearMatrix(row_count,col_count,mat);
    }

    return 0;
}

void clearMatrix(int row_number,int col_count, double **matrix){
    for(int i = 0; i < row_number; i++){
         delete[]matrix[i];
    }
    delete[]matrix;
}


int readMatrix(int row_number, int col_count, double **matrix){
    int zero_count = 0;
    for(int i = 0; i < row_number; i++){
        for(int j = 0;j < col_count; j++){
            cin >> matrix[i][j];
            if(matrix[i][j] != 0)zero_count++;
        }
    }
    return zero_count;
}

void prepMatrix(int row_number, int col_number, double **matrix){
    for(int i = 0; i < row_number; i++){
            matrix[i] = new double[col_number];
    }
}

void formatzMar(int row_number,int col_number,double **matrix){
    ostringstream strs;
    int zer_count = 0;
    for(int i = 0; i < col_number; i++){    
        if(matrix[row_number][i] != 0){
             zer_count++;
             strs << i+1 << " " << matrix[row_number][i] << " ";
         }
    }
    string str = strs.str();
    cout << zer_count << str << endl;
}

