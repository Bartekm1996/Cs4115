#include <iostream>
#include <string>
#include <sstream>
#include <math.h>
#include <list>
#include <vector>

using namespace std;

/*
template <class T>
void clearMatrix(int row_number,int col_count, T **matrix,bool transpose){
    int rows = row_number;
    if(transpose)rows = col_count;
    for(int i = 0; i < rows; i++){
         delete[]matrix[i];
    }
    delete[]matrix;
}
*/
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
            node *current = head;
            while(current != nullptr){
                free(current);
                current = current -> next;
            }
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


/*
void printMatrix(int rows,linked_list a){
    
    a.transpose();
    int maxRow = rows,maxCol = a.getMaxCol();

    if(maxRow < maxCol)maxRow = maxCol;
    else maxCol = maxRow;
    ostringstream stream;

    node **matrix = new node*[maxCol];
    for(int i = 0; i < maxCol; i++){
        matrix[i] = new node[maxRow];
    }

    node *current = a.getNode();
    while(current != nullptr){
        matrix[current->data.getRowPos()-1][current->data.getColPos()-1] = *(current);
        current = current -> next;
    }

    ostringstream strema;
    for(int i = 0; i < maxRow-1; i++){
       for(int j = 0; j < maxCol; j++){
           if(matrix[i][j].data.getNumber() != 0){
                stream << matrix[i][j].data;
           }
       }
       stream << endl;
    }

    cout << stream.str();

    clearMatrix(maxRow,maxCol,matrix,true);
};
*/

void readFromCin(bool eps,double epsilon){

    string inputLine = "";
    linked_list row;
    int rows = 1;

    while(getline(cin,inputLine)){
        istringstream lstream(inputLine);
        nz next;
        while(lstream >> next){
            if(eps){ 
                if(next.getNumber() != 0 && (next.getNumber() > epsilon || next.getNumber() < epsilon*-1 )){
                        next.setRowPos(rows);
                        row.push_back(next);
          
                }
            }else{
                if(next.getNumber() != 0)
                {
                        next.setRowPos(rows);
                        row.push_back(next);  
                }
            }
        }
        rows++;
    }

    //printMatrix(rows,row);
    row.transpose();
    row.reverse();
    printMatrixTranspose(row,rows);
    row.clear();
}

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
