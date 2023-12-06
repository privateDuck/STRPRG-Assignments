#include <stdio.h>
#include <stdlib.h>

typedef int* table_t;

int table_index(int i, int j, int m, int n){
    return i * n + j;
}

int read_table(table_t t, int i, int j, int m, int n){
    return t[table_index(i,j,m,n)];
}

void InitTable(table_t table, int m, int n){
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            table[table_index(i,j,m,n)] = i+j+1;
        }
    }
}

void InitTableFromUser(table_t table, int m, int n){
    puts("\nEnter Table Values: \n");
    for(int i = 0; i < m; i++){
        for(int j = 0; j < n; j++){
            printf("Enter (%d, %d) th element: ",i+1,j+1);
            scanf("%d",&table[table_index(i,j,m,n)]);
        }
    }
}

void InitColumnFromUser(int* column, int cols){
    puts("\nEnter Column Values: \n");
    for(int i = 0; i < cols; i++){
        printf("Enter (%d) th element: ",i+1);
        scanf("%d",&column[i]);
    }
}

void print_table(table_t table, int m, int n){
    puts("\nTable (A):\n");
    for(int i = 0; i < m; i++){
            if(i > 0)puts("\n");
        for(int j = 0; j < n; j++){
            int d = read_table(table, i,j,m,n);
            printf(d > 9 ? "%d, " : " %d, ",d);
        }
    }
}

int main(){

    int rows,cols;
    puts("Input no of rows: ");
    scanf("%d", &rows);
    puts("\nInput no of columns: ");
    scanf("%d", &cols);

    table_t t = (table_t)malloc(cols*rows*sizeof(int));
    int* column = (int*)malloc(cols * sizeof(int));
    int* result = (int*)malloc(rows * sizeof(int));

    memset(result, 0, rows * sizeof(int));

    InitTableFromUser(t, rows, cols);
    InitColumnFromUser(column, cols);

    print_table(t,rows,cols);

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            result[i] += read_table(t, i, j, rows, cols) * column[j];
        }
    }
    puts("\n\nX: \n");
    for (int j = 0; j < cols; j++){
        int d = column[j];
        printf(d > 9 || d < 0 ? " X[%d]: %d\n" : " X[%d]:  %d\n",j+1,column[j]);
    }

    puts("\n\nResult (Y): \n");
    for (int j = 0; j < rows; j++){
        int d = result[j];
        printf(d > 9 || d < 0 ? " Y[%d]: %d\n" : " Y[%d]:  %d\n",j+1,result[j]);
    }
    free(t);
    free(column);
    free(result);
    getchar();
    getchar();
    return 0;
}

