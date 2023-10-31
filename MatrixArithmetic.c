#include <stdlib.h>
#include <stdio.h>

void matrixMultiply(double** m1, double** m2, int row, int col, int n, double** multi)
{

    for(int i=0;i<row;i++)
    {
        for(int j=0;j<n;j++)
        {
            multi[i][j] = 0;
        }
    }

    for(int i=0;i<row;i++) 
    {
        for(int j=0;j<n;j++) 
        {
            for(int z=0;z<col;z++) 
            {
                multi[i][j] += m1[i][z] * m2[z][j];
            }
        }
    }

}




void vectorMultiply(double** m,double* v, int row,int col, double* vct) 
{
    
    for(int i=0;i<row;i++) 
    {
        vct[i] = 0;
    }

    for(int i=0;i<row;i++) 
    {
        for(int j=0;j<col;j++) 
        {
            vct[i] += m[i][j] * v[j];
        }
    }
}



void getTranspose(double ** m,int row,int col, double** tp)
{
    for(int i=0; i<col;i++) 
    {
        for(int j=0; j<row; j++) 
        {
            tp[i][j] = m[j][i];
        }
    }
    
}



void getInverse(double ** m,int n, double** inv) 
{   

    double temp;

    for(int i=0;i<n; i++)
    {
        for(int j=0;j<n;j++)
        {
            if(i==j)
            {
                inv[i][j]= 1;
            }
            else
            inv[i][j]=0;
        }
    }   

    for(int i=0;i<n;i++)
    {
        temp = m[i][i];
        for(int j =0; j<n; j++)
        {
            m[i][j] = m[i][j]/temp;
            inv[i][j] = inv[i][j]/temp;
        }
        
        for(int z=i+1;z<n;z++)
        {
            temp = m[z][i];
            for(int x=0;x<n;x++)
            {
                m[z][x] = m[z][x] - (m[i][x]*temp);
                inv[z][x] = inv[z][x] - (inv[i][x]*temp);
            }
            
        }
    } 

    for(int i = n-1; i>=0; i--)
    {
        for(int j = i-1; j>=0; j--)
        {
            temp = m[j][i];
            for(int z =0; z<n; z++)
            {
                m[j][z] = m[j][z] - (m[i][z]*temp);
                inv[j][z] = inv[j][z] - (inv[i][z]*temp);
            }
            
        }
    }

} 




int main(int argc,char ** argv) 
{
    //get data from args
    char filename[6];
    char* trainLoc = argv[1];
    char* dataLoc = argv[2];

    //open the files from args
    FILE* trainfile = fopen(trainLoc,"r");
    FILE* datafile = fopen(dataLoc,"r");
    //get the values from the open files
    fscanf(trainfile,"%s",filename);

    int trainCol;
    int trainRow;
    fscanf(trainfile,"%d",&trainCol);
    fscanf(trainfile,"%d",&trainRow);
    trainCol++;

    //allocate all the memory for the matrices
    double** matrix1 = (double**) malloc(trainCol*sizeof(double*)); 
    double** matrix2 = (double**) malloc(trainCol*sizeof(double*)); 
    double** train = (double**) malloc(trainRow*sizeof(double*));
    double** temp = (double**) malloc(trainRow*sizeof(double*));
    double** data = (double**) malloc(trainRow*sizeof(double*));
    double** transposed  = (double**) malloc(trainCol*sizeof(double*));
    double** inversed = (double**) malloc(trainCol*sizeof(double*)); 
    double* weights = (double*) malloc(trainCol*sizeof(double*));
    double* prices = (double*) malloc(trainRow*sizeof(double*)); 
    double* vector = (double*) malloc(trainRow*sizeof(double*)); 
    
    //allocate memory for pointer for the 2d matrices
    for(int i=0;i<trainCol;i++) 
    {
        transposed[i] = (double*) malloc(trainRow * sizeof(double));
        inversed[i] = (double*) malloc(trainCol * sizeof(double));
        matrix1[i] = (double*) malloc(trainCol * sizeof(double));
        matrix2[i] = (double*) malloc(trainRow * sizeof(double));

    } 
    
    for(int i=0;i<trainRow;i++)
    {
        train[i] = (double*) malloc(trainCol * sizeof(double));
        temp[i] = (double*) malloc(trainCol * sizeof(double));

    }

    for(int i=0;i<trainRow;i++) 
    {
        train[i][0] = 1; 
    }

    // get the double values
    for(int i=0;i<trainRow;i++) {
        
        for(int j=0; j<trainCol; j++) {

            fscanf(trainfile,"%lf",&temp[i][j]); 
        }
    }

    
    for(int i=0;i<trainRow;i++) 
    { 
        for(int j=1;j<trainCol;j++) 
        {
            train[i][j] = temp[i][j-1];
        }
    }

    for(int i=0; i<trainRow;i++) 
    {
        prices[i] = temp[i][trainCol-1];
    }
    
    //use the algorithm provided to get the weights
    getTranspose(train,trainRow,trainCol, transposed); 
    matrixMultiply(transposed,train,trainCol,trainRow,trainCol, matrix1);       
    getInverse(matrix1,trainCol, inversed);
    matrixMultiply(inversed,transposed,trainCol,trainCol,trainRow, matrix2); 
    vectorMultiply(matrix2,prices,trainCol,trainRow, weights);
    
    int dataCol;
    int dataRow;

    //get values from the datafile
    fscanf(datafile,"%s",filename);
    fscanf(datafile,"%d",&dataCol);
    fscanf(datafile,"%d",&dataRow);
    dataCol++; 

    for(int i=0;i<dataRow;i++) {
        data[i] = (double*) malloc(dataCol * sizeof(double));
        data[i][0] = 1; 
    }
    
    for(int i=0;i<dataRow;i++) 
    {
        for(int j=1;j<dataCol;j++) 
        {
           fscanf(datafile,"%lf",&data[i][j]);
        }
    }
    // multiply the data with the weights to get the prediction model
    vectorMultiply(data,weights,dataRow,dataCol,vector);

    for(int i=0;i<dataRow;i++) 
    {
        printf("%.0f\n",vector[i]);
    }

    // free the pointers inside the 2d matrices
    for(int i=0;i<dataCol;i++)
    {
        free(transposed[i]);
        free(matrix1[i]);  
        free(matrix2[i]);
        free(inversed[i]); 
    }
    // free the rest of the matrices
    free(transposed);
    free(matrix1);
    free(matrix2);   
    free(inversed); 
    free(weights);
    free(prices);
    free(vector);

    for(int i=0;i<dataRow;i++)
    {
        free(data[i]); 
    }
    free(data); 
   exit(0);
}





