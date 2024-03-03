#include <iostream>
#include<string>
#include<vector>

class DenseToSparse {

public :
    DenseToSparse() 
    : num_nz {0}, columnidx {nullptr}, row_ptr {nullptr} { 
    }
    
    DenseToSparse (const DenseToSparse &original)
    {
        num_nz = original.num_nz;
        size1 = original.size1;
        columnidx = new int[num_nz];
        values = new double[num_nz];
        row_ptr = new int[size1+1];

        for (size_t i=0; i<num_nz; i++)
            {
              columnidx[i] = original.columnidx[i];
              values[i] = original.values[i];
            }
        
        for (size_t i=0; i<size1+1; i++)
            row_ptr[i] = original.row_ptr[i];
    }

    void convert_dense_to_sparse(size_t size1, size_t size2, std::vector<std::vector<double>> dense_matrix, int maxrow);

    ~DenseToSparse(){
        delete [] columnidx;
        delete [] row_ptr;
        delete [] values;
    }

 public :
    int num_nz;
    int *columnidx;
    int *row_ptr;
    double *values;
    size_t size1;
};

void DenseToSparse::convert_dense_to_sparse(size_t size1, size_t size2, std::vector<std::vector<double>> dense_matrix, int maxrow)
{
    
    columnidx = new int[size1*maxrow] {};
    row_ptr = new int [size1+1] {};
    values = new double [size1*maxrow] {};

    row_ptr[0] = 0;

    for (size_t i=0; i<size1; i++){
        for (size_t j=0; j<size2; j++){
            if(dense_matrix[i][j] != 0)
            {
                num_nz +=1;
                columnidx[num_nz-1] = j;
                values[num_nz-1] = dense_matrix[i][j];
            }
        }
        row_ptr[i+1] = num_nz+1;
    }
}

void display_non_zero_values(DenseToSparse obj)
{
    std::cout << "The non-zero values are: " << std::endl; 
    for(size_t i=0 ; i<obj.num_nz; i++)
        {
           std::cout << "Non zero value: " << obj.values[i] << ", ";
           std:: cout << "Column id: " << obj.columnidx[i] << std::endl;
        } 
}

int main()
{
   std::vector <std::vector<double>> dense_matrix {{1,0,0,0,2,0},{2,3,0,0,0,0},{0,0,0,0,6,7}};

   size_t size1 {dense_matrix.size()};
   size_t size2 {6};     
   
   DenseToSparse sparseobj1;
   int maxrow = static_cast<int>(size2);
   sparseobj1.size1 = size1;
   sparseobj1.convert_dense_to_sparse(size1, size2, dense_matrix, maxrow);

   std::cout << "Number of non-zero elements" << sparseobj1.num_nz << std::endl;
   
   display_non_zero_values(sparseobj1);

}