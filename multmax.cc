#include <iostream>
#include <type_traits>
#include <iomanip>

bool validateMatrixInputSize(char**);
void initArray(double**,int,int);
void populateArray(double**,int,int);
void printArray(double**,int,int);
void arrayResult(double**,double**,int,int,int,int);
//double product(double**,double**,int,int,int);


int main(int argc, char **argv){

    if(argc != 5){
        std::cerr << "Error :  5 arguments required - Dim of Mat A & Dim of Mat B" << std::endl;
        exit(EXIT_FAILURE);
    }else {
        if(validateMatrixInputSize(argv)){
                
            int rows_no_matrix_a = atoi(*(argv+1)), rows_no_matrix_b = atoi(*(argv+3));
            int cols_no_matrix_a = atoi(*(argv+2)), cols_no_matrix_b = atoi(*(argv+4));

            //std::cout << "Size of matrix A " << rows_no_matrix_a << "\t" << cols_no_matrix_a << std::endl;
            //std::cout << "Size of matrix B " << rows_no_matrix_b << "\t" << cols_no_matrix_b << std::endl;

                double **arrayA = new double*[rows_no_matrix_a];
                double **arrayB = new double*[rows_no_matrix_b];
                
                initArray(arrayA,rows_no_matrix_a,cols_no_matrix_a);
                initArray(arrayB,rows_no_matrix_b,cols_no_matrix_b);

            //std::cout << "Enter numbers of matrix A " << std::endl;
                    populateArray(arrayA,rows_no_matrix_a,cols_no_matrix_a);
                    //printArray(arrayA,rows_no_matrix_a,cols_no_matrix_a);

            //std::cout<<"Enter number of matrix B" << std::endl;
                    populateArray(arrayB,rows_no_matrix_b,cols_no_matrix_b);
                    //printArray(arrayB,rows_no_matrix_b,cols_no_matrix_b);

                    arrayResult(arrayA,arrayB,rows_no_matrix_a,cols_no_matrix_b,rows_no_matrix_b,cols_no_matrix_a);

        }else{ 
            std::cerr << "Error : Matrix size incomaptable" << std::endl;
            return -1;
        }
    }

    return 0;   
}

bool validateMatrixInputSize(char **array){
    return atoi(*(array + 2)) == atoi(*(array + 3));
}

void populateArray(double **array, int rows_no, int cols_no){
    for(int i = 0; i < rows_no; i++){
        for(int j = 0; j < cols_no; j++){
            std::cin >> array[i][j];
        }
    }
}

void initArray(double **array, int rows_no, int cols_no){
    for(int i = 0; i < rows_no; i++){
        array[i] = new double[cols_no];
    }
}

void printArray(double **array, int rows_no, int cols_no){
    for(int i = 0; i < rows_no; i++){
        for(int j = 0; j < cols_no; j++){
            std::cout << array[i][j];
            std::cout << std::setw(4);
        }
            std::cout << std::setw(0);
            std::cout << std::endl;
    }
}



void arrayResult(double **arrayA, double **arrayB, int rows_no_mat_a, int cols_no_mat_b,int rows_no_mat_b,int cols_no_mat_a){

    /*
        double **array = new double*[rows_no_mat_a];
        initArray(array,rows_no_mat_a,cols_no_mat_b);
        Since the resultant array isnt going to be reused again, its sufficent to just print the output directly
    */

        double product = 0;
        for(int i = 0; i < rows_no_mat_a; i++){
            for(int j = 0; j < cols_no_mat_b; j++){
                for(int k = 0; k < cols_no_mat_a; k++){
                    //array[i][j] = product(arrayA,arrayB,i,cols_no_mat_a,j);
                    product += (arrayA[i][k]*arrayB[k][j]);
                }
                std::cout << product;
                std::cout << std::setw(4);
                product = 0;
            }
            std::cout << std::setw(0);
            std::cout << std::endl;
        }

        /*
            Pass the resultant array to the printArray method
            printArray(array,rows_no_mat_a,cols_no_mat_b);
        */
}

/*
    Two out of many possible way to solve matrix mult is :
    1) Use two nested loop
    2) Use a function which returns the product of the thrid loop

        double product(double **arrayA, double **arrayB, int row_no_of_mat_a, int col_no_of_mat_a, int rows_no_of_mat_b){
                double prodcut = 0;
                for(int i = 0; i < col_no_of_mat_a; i++){
                     prodcut += (arrayA[row_no_of_mat_a][i] * arrayB[i][rows_no_of_mat_b]);
                }
                return prodcut;
        }

*/