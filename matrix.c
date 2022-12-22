#include "matrix.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <sys/types.h>  // needed for open
#include <sys/stat.h>   // needed for open
#include <fcntl.h>      // needed for open
#include <unistd.h>     // needed for read and write
#include <string.h>
#include <limits.h>
#include <errno.h> /* for ENOSYS */

int matrix_allocate(matrix_t *m, int rows, int columns) {
    /* implement the function here ... */

//     return -ENOSYS;  ENOSYS is a  standard error code that means 'function
//                        not implemented'. We use it to force the failure of tests
//                        while the functions are not written. Make sure to remove
//                        it when you start to work on a function 

    m->rows = rows;
    m->columns = columns;
    m->content = malloc(rows * sizeof(int*));

    if (!m->content)
        return -1;

    for (int i = 0; i < rows; i++) {
        m->content[i] = malloc(columns*sizeof(int));
        if (!m->content[i]) {
            for (int j = 0; j < i; j++)
                free(m->content[j]);
                free(m->content);

            return -1;
        }
    }
    return 0;
}
// }

void matrix_free(matrix_t *m) {
     // implement the function here ... 
    for (int i = 0; i < m->rows; i++)
        free(m->content[i]);
        free(m->content);
}

void matrix_init_zeros(matrix_t *m) {
    /* implement the function here ... */
    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            m->content[i][j] = 0;
        }
}
}

int matrix_init_identity(matrix_t *m){
    /* implement the function here ... */
    // return -ENOSYS;
    // double *result;
    if (m->rows != m->columns)
        return -1;

    // if (m->rows == 1)
    //     *result = m->content[0][0];
    // else
    //     *result = det(m->content, m->rows);
    // return 0;

    for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->rows; j++) {
            if (i == j)
                m->content[i][j] = 1;
            else m->content[i][j] = 0;
         
        }
}
    return 0;


}
void matrix_init_rand(matrix_t *m) {
    /* implement the function here ... */
        for (int i = 0; i < m->rows; i++) {
        for (int j = 0; j < m->columns; j++) {
            m->content[i][j] =  (-100 <= rand()) && ( rand()<=100);
        }
}
}

int matrix_equal(matrix_t *m1, matrix_t *m2) {
    /* implement the function here ... */
    // return -ENOSYS;
    // if (m1->rows != m2->rows && m1->columns != m2->columns)
    //     return -1;
    // for (int i = 0; i < m1->rows; i++)
    //     for (int j = 0; j < m1->columns; j++)
    //         if (m1->content[i][j] != m2->content[i][j])
    //             return -1;

    // return 0;
    // if (m1->rows != m2->columns){
    //        return -1;}
    if(m1->rows != m2->rows || m1->columns != m2->columns)
        return 0;  
    
     
    for (int i = 0; i < m1->rows; i++)
        for (int j = 0; j < m2->columns; j++)
                if (m1->content[i][j] == m2->content[i][j]){
                    return 1;
                }
                else if(m1->content[i][j] != m2->content[i][j]){
                    return 0;
                }
    return 0;
}

int matrix_sum(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    /* implement the function here ... */
    // return -ENOSYS;

    // if (m1->rows != m2->rows || m1->columns != m2->columns)
    //     return -1;

    if (matrix_allocate(result ,m1->rows, m1->columns) != 0)
        return -1;

    for (int i = 0; i < m1->rows; i++)
        for (int j = 0; j < m1->columns; j++)
            result->content[i][j] = m1->content[i][j] + m2->content[i][j];

    return 0;
}

int matrix_scalar_product(matrix_t *m, int scalar, matrix_t *result) {
    /* implement the function here ... */
    // return -ENOSYS;

    if (matrix_allocate(result, m->rows, m->columns) != 0)
        return -1;

    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->columns; j++)
            result->content[i][j] = m->content[i][j] * scalar;
    return 0;
}

int matrix_transposition(matrix_t *m, matrix_t *result) {
    /* implement the function here ... */
    // return -ENOSYS;

    if (matrix_allocate(result, m->columns, m->rows) != 0)
        return -1;
    for (int i = 0; i < m->rows; i++)
        for (int j = 0; j < m->columns; j++)
            result->content[j][i] = m->content[i][j];
    return 0;
}

int matrix_product(matrix_t *m1, matrix_t *m2, matrix_t *result) {
    /* implement the function here ... */
    // return -ENOSYS;
    // if ((m1->columns != m2->rows) || (m1->rows != m2->columns))
    //     return -1;

    if (matrix_allocate(result, m1->rows, m2->columns) != 0)
        return -1;

    for (int i = 0; i < m1->rows; i++) {
        for (int j = 0; j < m2->columns; j++) {
            result->content[i][j] = 0;
            for (int k = 0; k < m1->columns; k++)
                result->content[i][j] += m1->content[i][k] * m2->content[k][j];
        }
    }
    return 0;
}

int matrix_dump_file(matrix_t *m, char *output_file) {
    /* implement the function here ... */
    // return -ENOSYS;
    // char str[50];
    // FILE *fptr = fopen(output_file, "w");
    // if (fptr == NULL)
    // {
    //     return -1;
    // }
    // for(int i = 0; i < m->rows; i++)
    //     for(int j = 0; j < m->columns; j++)
    //         if(j == m->columns-1)
    //             fprintf(fptr,"%d.%s\n", i, str);
    //         else
    //             fprintf(fptr,"%d.%s\n", j, str);
    // return -1;

    // int fd1;
    // char *buffer = m;
    // fd1 = open(output_file, O_WRONLY | O_TRUNC | O_CREAT, S_IRUSR | S_IWUSR);
    // if(fd1 == NULL)
    //     return -1;
    // write(fd1, buffer, strlen(buffer));
    //  // if(write(fd1, buffer, strlen(buffer)) != strlen(buffer))
    //  //    return -1;

    // return 0;

    FILE *fptr = fopen(output_file, "w");
    if (fptr == NULL)
    {
        return -1;
    }
    char buf[500] = "";
    char str[50];
    for(int i=0; i<m->rows; i++){
        for(int j=0; j<m->columns; j++){
            if(j+1 !=m->columns){
                sprintf(str, "%d", m->content[i][j]);
            }
            else{
                sprintf(str, "%d", m->content[i][j]);
            }strcat(buf, str);
        }strcat(buf, "\n");
    }strcat(buf, "\0");

    if(fwrite(buf, 1, strlen(buf), fptr)!=strlen(buf)){
        return -1;
    }

    fclose(fptr);
    return 0;
}

int matrix_allocate_and_init_file(matrix_t *m, char *input_file) {
     // implement the function here ... 
    // return -ENOSYS;

    FILE *fptr = fopen(input_file, "r");
    if(fptr == NULL)
        return -1;
    char buffer[500] = {};
    int columns = 0;
    int rows = 0;
    
    fread(buffer, 1, 500, fptr);

    for(int i = 0; i<strlen(buffer); i++){
        if(buffer[i] == ' '){
            columns++;
        }else if(buffer[i] == '\n'){
            rows++;
            columns++;
        }else if(buffer[i] =='\0'){
            break;
        }else if((INT_MIN<buffer[i]) && (buffer[i]<INT_MAX)){
            continue;
        }else{
            return -1;
        }
    }
    columns = columns/rows;

    matrix_allocate(m, rows, columns);

    int number;
    rewind(fptr);
    for(int i =0; i<rows; i++){
        for(int j =0; j<columns; j++){
            fscanf(fptr, "%d", &number);
            m->content[i][j] = number;
        }
    }
    fclose(fptr);
    return 0;

}

