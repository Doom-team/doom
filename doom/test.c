#include <pthread.h>
#include <stdio.h>
 
//размеры матриц
#define N 4
#define M 4
 
//специальная структура для данных потока
typedef struct{
	int rowN; //номер обрабатываемой строки
	int rowSize; //размер строки
	//указатели на матрицы
	int** array1; 
	int** array2;
	int** resArr;
} pthrData;
 
void* threadFunc(void* thread_data){
	//получаем структуру с данными
	pthrData *data = (pthrData*) thread_data;
 
	//складываем элементы строк матриц и сохраняем результат
	for(int i = 0; i < data->rowSize; i++)
		data->resArr[data->rowN][i] = data->array1[data->rowN][i] + data->array2[data->rowN][i];
 
	return NULL;
}
 
int main(){
	//выделяем память под двумерные массивы
	int** matrix1 = (int**) malloc(N * sizeof(int*));
	int** matrix2 = (int**) malloc(N * sizeof(int*));
	int** resultMatrix = (int**) malloc(N * sizeof(int*));
 
	//выделяем память под элементы матриц
	for(int i = 0; i < M; i++){
		matrix1[i] = (int*) malloc(M * sizeof(int));
		matrix2[i] = (int*) malloc(M * sizeof(int));
		resultMatrix[i] = (int*) malloc(M * sizeof(int));
	}
 
	//инициализируем начальными значениями
	for(int i = 0; i < N; i++){
		for(int j = 0; j < M; j++){
			matrix1[i][j] = i;
			matrix2[i][j] = j;
			resultMatrix[i][j] = 0;
		}
	}
 
	//выделяем память под массив идентификаторов потоков
	pthread_t* threads = (pthread_t*) malloc(N * sizeof(pthread_t));
	//сколько потоков - столько и структур с потоковых данных
	pthrData* threadData = (pthrData*) malloc(N * sizeof(pthrData));
 
	//инициализируем структуры потоков
	for(int i = 0; i < N; i++){
		threadData[i].rowN = i;
		threadData[i].rowSize = M;
		threadData[i].array1 = matrix1;
		threadData[i].array2 = matrix2;
		threadData[i].resArr = resultMatrix;
 
		//запускаем поток
		pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
	}
 
	//ожидаем выполнение всех потоков
	for(int i = 0; i < N; i++)
		pthread_join(threads[i], NULL);
 
    for(int i = 0; i < N; i++){
        for (int j = 0; j < threadData[i].rowSize; j++){
		    printf("%d",threadData[i].resArr[j]);
        printf("\n");
        }
		//запускаем поток
		pthread_create(&(threads[i]), NULL, threadFunc, &threadData[i]);
	}
	//освобождаем память
	free(threads);
	free(threadData);
	for(int i = 0; i < N; i++){
		free(matrix1[i]);
		free(matrix2[i]);
		free(resultMatrix[i]);
	}
	free(matrix1);
	free(matrix2);
	free(resultMatrix);
	return 0;
}