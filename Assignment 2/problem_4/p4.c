#include<stdio.h>
#include<math.h>

void M_V_Multication(int rows,int cols,int vector[cols],int matrix[rows][cols],int product[rows]){
    for (int i = 0; i < rows; i++)
    {
        product[i]=0;
        for (int j = 0; j < cols; j++)
        {
          product[i] += matrix[i][j]*vector[j];  
        }       
    }    
}

int main()
{
    int rows, cols ;

    printf("Enter the number of columns and rows of matrix res:\n");
    scanf("%d %d",&rows,&cols);

    int vector[cols];
    int matrix[rows][cols];
    int product[rows];

    printf("Enter the elements of matrix:\n");
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < cols; j++)
        {
            scanf("%d",&matrix[i][j]);
        }   
    }
    printf("Enter the elements of vector:\n");
    for (int i = 0; i < cols; i++)
    {
        scanf("%d",&vector[i]);
    }

    M_V_Multication(rows, cols, vector, matrix, product);

    printf("Product of matrix and vector is:\n");
    for (int i = 0; i < rows; i++) {
        printf("%d \n", product[i]);
    }

    return 0;
}
