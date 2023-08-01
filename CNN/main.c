#include <stdio.h>
#include <stdlib.h>

float **Conv2D(float **array, int rows, int cols, float **kernel, int kernel_size) {
    float **result = (float **) malloc((rows-kernel_size+1) * sizeof(float *));
    for(int i = 0; i < rows-kernel_size+1; i++) {
        *(result+i) = (float *) malloc((cols-kernel_size+1) * sizeof(float));
        for(int j = 0; j < cols-kernel_size+1; j++) {
            *(*(result+i)+j) = 0;
            for(int k = 0; k < kernel_size; k++)
                for(int l = 0; l < kernel_size; l++)
                    *(*(result+i)+j) += *(*(kernel+k)+l) * *(*(array+i+kernel_size-k-1)+j+kernel_size-l-1);
        }
    }
    return result;
}
float **getArray(int rows, int cols) {
    float **array = (float **) malloc(rows * sizeof(float *));
    printf("Specify the 2D Array\n");
    for(int i = 0; i < rows; i++) {
        *(array+i) = (float *) malloc(cols * sizeof(float));
        for(int j = 0; j < cols; j++)
            scanf("%f", *(array+i)+j);
    }
    return array;
}
float **getKernel(int size) {
    float **kernel = (float **) malloc(size * sizeof(float *));
    printf("Specify the Kernel\n");
    for(int i = 0; i < size; i++) {
        *(kernel+i) = (float *) malloc(size * sizeof(float));
        for(int j = 0; j < size; j++)
            scanf("%f", *(kernel+i)+j);
    }
    return kernel;
}

int main(int argc, char *argv[]) {
    int rows, cols, size;
    float **array, **kernel;
    size_t len = 256;
    char *line = (char *) malloc(len * sizeof(char));
    if( argc == 1 ) {
        printf("Enter the Number of Rows: ");
        scanf("%d", &rows);
        printf("Enter the Number of Coloumns : ");
        scanf("%d", &cols);
        array = getArray(rows, cols);
        printf("Enter the size of Kernel : ");
        scanf("%d", &size);
        kernel = getKernel(size);
    } else if( argc == 2 ) {
        FILE *arrayFile;
        arrayFile = fopen(*(argv+1), "r");
        getline(&line, &len, arrayFile);
        rows = atoi(line);
        getline(&line, &len, arrayFile);
        cols = atoi(line);
        array = (float **) malloc(rows * sizeof(float *));
        for(int i = 0; i < rows; i++) {
            *(array+i) = (float *) malloc(cols * sizeof(float));
            for(int j = 0; j < cols; j++) {
                getline(&line, &len, arrayFile);
                *(*(array+i)+j) = atof(line);
            }
        }
        printf("Enter the size of Kernel : ");
        scanf("%d", &size);
        kernel = getKernel(size);
    } else {
        FILE *arrayFile, *kernelFile;
        arrayFile = fopen(*(argv+1), "r");
        getline(&line, &len, arrayFile);
        rows = atoi(line);
        getline(&line, &len, arrayFile);
        cols = atoi(line);
        array = (float **) malloc(rows * sizeof(float *));
        for(int i = 0; i < rows; i++) {
            *(array+i) = (float *) malloc(cols * sizeof(float));
            for(int j = 0; j < cols; j++) {
                getline(&line, &len, arrayFile);
                *(*(array+i)+j) = atof(line);
            }
        }
        kernelFile = fopen(*(argv+2), "r");
        getline(&line, &len, kernelFile);
        size = atoi(line);
        kernel = (float **) malloc(size * sizeof(float *));
        for(int i = 0; i < size; i++) {
            *(kernel+i) = (float *) malloc(size * sizeof(float));
            for(int j = 0; j < size; j++) {
                getline(&line, &len, kernelFile);
                *(*(kernel+i)+j) = atof(line);
            }
        }
    }
    printf("Kernel\n");
    for(int i = 0; i < size; i++) {
        for(int j = 0; j < size; j++)
            printf("%f ", *(*(kernel+i)+j));
        printf("\n");
    }
    float **result = Conv2D(array, rows, cols, kernel, size);
    for(int i = 0; i < rows-size+1; i++) {
        for(int j = 0; j < cols-size+1; j++)
            printf("%f ", *(*(result+i)+j));
        printf("\n");
    }
    FILE *resultFile;
    if( argc == 4 ) {
        resultFile = fopen(*(argv+3), "w");
    } else {
        char *resultFileName = (char *) malloc(101 * sizeof(char));
        printf("Enter the Name of the File in which to store the Result : ");
        fgets(resultFileName, 101, stdin);
        resultFile = fopen(resultFileName, "w");
    }
    for(int i = 0; i < rows-size+1; i++) {
        for(int j = 0; j < cols-size+1; j++)
            fprintf(resultFile, "%f,", *(*(result+i)+j));
        fprintf(resultFile, "\n");
    }

    return 0;
}