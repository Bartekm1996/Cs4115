#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <list>
#include <vector>

using namespace std;
#define MAX(a,b) ((a) > (b) ? (a) : (b))


template <class T>
void clearMatrix(int row_number,int col_count, T **matrix,bool transpose){
    int rows = row_number;
    if(transpose)rows = col_count;
    for(int i = 0; i < rows; i++){
         delete[]matrix[i];
    }
    delete[]matrix;
}

class nz{

    public:
        nz(){
            number = 0;
            rowPosition = 0;
            colPosition = 0;
        }
        nz(double val,int row,int col){
            number = val;
            rowPosition = row;
            colPosition = col;
        };
        double getNumber(){
            return number;
        };
        int getRowPos(){
            return rowPosition;
        };
        int getColPos(){
            return colPosition;
        };
        void setColPos(int col){
            this->colPosition = col;
        };
        void setRowPos(int row){
            this->rowPosition = row;
        };

        void setNumber(int number){
            this->number = number;
        }
        
        friend istringstream& operator >>(istringstream &is,nz &obj){
            is >> obj.colPosition >> obj.number;
            return is;
        };

        friend ostringstream& operator <<(ostringstream &is,nz &obj){
            is << obj.getColPos() << " " << obj.getNumber() << " ";
            return is;
        }

        void transPos(){
            int tempCol = colPosition;
            colPosition = rowPosition;
            rowPosition = tempCol;
        };
    
    private:
        double number;
        int rowPosition;
        int colPosition;
};

struct node{
    nz data;
    node *next;
};

class linked_list{
    private:
        node *head;
        int size;
        int rowsCount;
    public:

        linked_list(){head = nullptr;}

        node* getNode(){return head;}
        
        void push_back(nz n){
            struct node* new_node = new node; 
                         new_node->data = n; 
                         new_node->next = head; 
                         head = new_node;
                         this->size++;               
        }
   
        int getSize(){
            return this->size;
        }

        int getMaxCol(){
            node *current = head;
            int max = current->data.getColPos();
            int prev = 0;
            while(current != nullptr){
                if(current -> next != nullptr)prev = current -> next -> data.getColPos();
                if(prev > max)max = prev;
                current = current -> next;
            }
            return max;
        }

        int getMaxRow(){
            node *current = head;
            int max = current->data.getRowPos();
            int prev = 0;
            while(current != nullptr){
                if(current -> next != nullptr)prev = current -> next -> data.getRowPos();
                if(prev > max)max = prev;
                current = current -> next;
            }
            return max;
        }

        bool isEmpty(){
            return head == nullptr;
        }

        void transpose(){
            node* current = head;
            while(current != nullptr){
                current -> data.transPos();
                current = current -> next;
            }
        }

        void clear(){
             node* iterator = head;
    
             while (iterator != nullptr){
                head = iterator->next;
                delete[] iterator;
                iterator = head;
            }
             delete head;
        }

        void setRowsCount(int rows){
            this->rowsCount = rows;
        }

        int getRowsCount(){
            return this->rowsCount;
        }


        void reverse() { 
       
        node *current = head; 
        node *prev = NULL, *next = NULL; 
        while (current != NULL) 
        { 
            next = current->next; 
            current->next = prev; 
            prev = current; 
            current = next; 
        } 
             head = prev; 
        } 


};

void printMatrixTranspose(linked_list &a,int rows){
        ostringstream stream;
        int row = 0;
        if(a.getMaxRow() > rows)row = a.getMaxRow()+1;
        else row = rows;
            for(int i = 1; i < row ; i++){
            node *current = a.getNode();
            while(current != nullptr){
                    if(current->data.getRowPos() == i){
                        stream << current -> data;
                    }
                    current = current -> next;
            }
                stream << endl;
            }
            cout << stream.str();
}

void printMatrix(linked_list &a){
        ostringstream stream;
        a.reverse();
        int row = MAX(a.getMaxRow(),a.getRowsCount());
            for(int i = 1; i < row ; i++){
            node *current = a.getNode();
            while(current != nullptr){
                    if(current->data.getRowPos() == i && current->data.getNumber() != 0){
                        stream << current -> data;
                    }
                    current = current -> next;
            }
                stream << endl;
            }
            cout << stream.str();
}

linked_list readFromCin(){

    string inputLine = "";
    linked_list row;
    int rows = 1;

    while(getline(cin,inputLine)){
        istringstream lstream(inputLine);
        nz next;
        while(lstream >> next){
                if(next.getNumber() != 0)
                {
                        next.setRowPos(rows);
                        row.push_back(next);  
                }
        }
        rows++;
    }
           row.setRowsCount(rows);
    return row;
}


double **matrix(linked_list &a){
    int rows = MAX(a.getMaxRow(),a.getRowsCount());
    int cols = a.getMaxCol();

    double **array = new double*[rows];

    for(int i = 0; i < rows; i++){
        array[i] = new double[cols];
    }

    for(int i = 0; i < rows; i++){
        for(int j = 0; j < cols; j++){
            array[i][j] = 0;
        }
    }

    node *current = a.getNode();
    while(current != nullptr){
        array[current->data.getRowPos()-1][current->data.getColPos()-1] = current->data.getNumber();
        current = current -> next;
    }

    return array;
}

void matmult(linked_list &a,linked_list &b,linked_list &c){
   
    double **arrayA = matrix(a); 
    double **arrayB = matrix(b);
    int rows_of_a = MAX(a.getMaxRow(),a.getRowsCount());
    int rows_of_b = MAX(b.getMaxRow(),b.getRowsCount());
    int cols_of_b = b.getMaxCol();
    int cols_of_a = a.getMaxCol();
    c.clear();
    double product = 0;
    for(int i = 0; i < rows_of_a; i++){
            for(int j = 0; j < cols_of_b; j++){
                for(int k = 0; k < cols_of_a; k++){
                    product += (arrayA[i][k]*arrayB[k][j]);
                }
                c.push_back(nz(product,i+1,j+1));
                product = 0;
            }
    }
    clearMatrix(rows_of_a,cols_of_a,arrayA,false);
    clearMatrix(rows_of_b,cols_of_b,arrayB,false);
 
}

int main(int argc,char **argv){
    
   if(argc != 2){
       cerr << "Wromg format required power of mat " << endl; 
   }else{ 
       
    int power = 0;
        std::istringstream iss (*(argv+1));
    iss >> power;
    

    if(power <= 0){
        cerr << "Wrong power input " << endl;
        exit(0);
    }

    linked_list a = readFromCin();
    linked_list c;
    if(power == 1){
        matmult(a,a,c);
    }else if(power > 1){
        matmult(a,a,c);
        for(int i = 0; i < power-1; i++){
            matmult(a,c,c);
        }    
    }
        printMatrix(c);
        a.clear();
                   
   }              
    return 0;
}
