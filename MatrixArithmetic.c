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







