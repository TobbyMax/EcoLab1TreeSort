/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   EcoLab1
 * </сводка>
 *
 * <описание>
 *   Данный исходный файл является точкой входа
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2018 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */


/* Eco OS */
#include "IEcoSystem1.h"
#include "IdEcoMemoryManager1.h"
#include "IdEcoInterfaceBus1.h"
#include "IdEcoFileSystemManagement1.h"
#include "IdEcoLab1.h"
#include "IdEcoLab1RBTree.h"
#include <stdio.h>
#include <stdlib.h>

#define STRING_LEN 16

/*
 *
 * <сводка>
 *   Функция stdQsort
 * </сводка>
 *
 * <описание>
 *   Функция-обертка над стандартной qsort для соответствия сигнатуре метода IEcoLab1 qsort
 * </описание>
 *
 */
int16_t stdQsort(
        IEcoLab1 *me,
        void *pData,
        size_t elem_count,
        size_t elem_size,
        int (__cdecl *comp)(const void *, const void *)
) {
    qsort(pData, elem_count, elem_size, comp);
    return 0;
}

/*
 *
 * <сводка>
 *   Функция compareInt
 * </сводка>
 *
 * <описание>
 *   Компаратор для типа int
 * </описание>
 *
 */
int __cdecl compareInt(const void *a_ptr, const void *b_ptr) {
    int a = *(int *) a_ptr;
    int b = *(int *) b_ptr;
    return (a > b) - (a < b);
}

/*
 *
 * <сводка>
 *   Функция compareFloat
 * </сводка>
 *
 * <описание>
 *   Компаратор для типа float
 * </описание>
 *
 */
int __cdecl compareFloat(const void *a_ptr, const void *b_ptr) {
    float a = *(float *) a_ptr;
    float b = *(float *) b_ptr;
    return (a > b) - (a < b);
}

/*
 *
 * <сводка>
 *   Функция compareDouble
 * </сводка>
 *
 * <описание>
 *   Компаратор для типа double
 * </описание>
 *
 */
int __cdecl compareDouble(const void *a_ptr, const void *b_ptr) {
    double a = *(double *) a_ptr;
    double b = *(double *) b_ptr;
    return (a > b) - (a < b);
}

/*
 *
 * <сводка>
 *   Функция compareString
 * </сводка>
 *
 * <описание>
 *   Компаратор для типа char* 'aka' string
 * </описание>
 *
 */
int __cdecl compareString(const void *a_ptr, const void *b_ptr) {
    char *a = *(char **) a_ptr;
    char *b = *(char **) b_ptr;
    return strcmp(a, b);
}

/*
 *
 * <сводка>
 *   Функция generateAscendingIntArray
 * </сводка>
 *
 * <описание>
 *   Функция аллокации и генерации массива типа int, заданного размера с возрастающими значениями
 * </описание>
 *
 */
void *generateAscendingIntArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    for (i = 0; i < size; i++) {
        arr[i] = (int) i;
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция generateAscendingDoubleArray
 * </сводка>
 *
 * <описание>
 *   Функция аллокации и генерации массива типа double, заданного размера с возрастающими значениями
 * </описание>
 *
 */
void *generateAscendingDoubleArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    double *arr = (double *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(double));
    for (i = 0; i < size; i++) {
        arr[i] = (double) i / 10;
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция generateRandomIntArray
 * </сводка>
 *
 * <описание>
 *   Функция аллокации и генерации случайного массива типа int, заданного размера
 * </описание>
 *
 */
void *generateRandomIntArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    int *arr = (int *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(int));
    for (i = 0; i < size; i++) {
        arr[i] = rand() % 30001 - 15000;
    }
    return arr;
}


/*
 *
 * <сводка>
 *   Функция generateRandomFloatArray
 * </сводка>
 *
 * <описание>
 *  Функция аллокации и генерации случайного массива типа float, заданного размера
 * </описание>
 *
 */
void *generateRandomFloatArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    float *arr = (float *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(float));
    for (i = 0; i < size; i++) {
        arr[i] = ((float) (rand() % 30001 - 15000)) / ((float) (rand() % 100 + 1));
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция generateRandomDoubleArray
 * </сводка>
 *
 * <описание>
 *   Функция аллокации и генерации случайного массива типа double, заданного размера
 * </описание>
 *
 */
void *generateRandomDoubleArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i;
    double *arr = (double *) pIMem->pVTbl->Alloc(pIMem, size * sizeof(double));
    for (i = 0; i < size; i++) {
        arr[i] = ((double) (rand() % 30001 - 15000)) / ((float) (rand() % 1000 + 1));
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция generateRandomStringArray
 * </сводка>
 *
 * <описание>
 *   Функция аллокации и генерации случайного массива типа string, заданного размера
 * </описание>
 *
 */
void *generateRandomStringArray(IEcoMemoryAllocator1 *pIMem, size_t size) {
    size_t i, j, str_size;
    char **arr = (char **) pIMem->pVTbl->Alloc(pIMem, size * sizeof(char *));
    for (i = 0; i < size; i++) {
        arr[i] = (char *) pIMem->pVTbl->Alloc(pIMem, STRING_LEN * sizeof(char));
        str_size = rand() % 11 + 4;
        for (j = 0; j < str_size; ++j) {
            arr[i][j] = (char) (rand() % ('z' - 'a' + 1) + 'a');
        }
        arr[i][str_size] = 0;
    }
    return arr;
}

/*
 *
 * <сводка>
 *   Функция deleteArray
 * </сводка>
 *
 * <описание>
 *   Функция освобождения памяти, выделенной под массив простого типа
 * </описание>
 *
 */
void deleteArray(IEcoMemoryAllocator1 *pIMem, void *arr_ptr, size_t size) {
    pIMem->pVTbl->Free(pIMem, arr_ptr);
}

/*
 *
 * <сводка>
 *   Функция deleteStringArray
 * </сводка>
 *
 * <описание>
 *   Функция освобождения памяти, выделенной под массив строк (char*)
 * </описание>
 *
 */
void deleteStringArray(IEcoMemoryAllocator1 *pIMem, void *arr_ptr, size_t size) {
    size_t i;
    char **arr = (char **) arr_ptr;
    for (i = 0; i < size; ++i) {
        pIMem->pVTbl->Free(pIMem, arr[i]);
    }
    pIMem->pVTbl->Free(pIMem, arr_ptr);
}

/*
 *
 * <сводка>
 *   Функция cloneArray
 * </сводка>
 *
 * <описание>
 *   Функция создания копии массива простого типа (shallow-copy)
 * </описание>
 *
 */
void *cloneArray(IEcoMemoryAllocator1 *pIMem, void *src, uint32_t byte_count) {
    void *p_arr_copy_1 = pIMem->pVTbl->Alloc(pIMem, byte_count);
    pIMem->pVTbl->Copy(pIMem, p_arr_copy_1, src, byte_count);
    return p_arr_copy_1;
}

/*
 *
 * <сводка>
 *   Функция cloneStringArray
 * </сводка>
 *
 * <описание>
 *   Функция создания копии массива строк
 * </описание>
 *
 */
void *cloneStringArray(IEcoMemoryAllocator1 *pIMem, void *src, uint32_t byte_count) {
    char **src_arr = (char **) src;
    char **p_arr_copy_1 = pIMem->pVTbl->Alloc(pIMem, byte_count);
    size_t i, size = byte_count / sizeof(char *);
    for (i = 0; i < size; i++) {
        p_arr_copy_1[i] = (char *) pIMem->pVTbl->Alloc(pIMem, STRING_LEN * sizeof(char));
        pIMem->pVTbl->Copy(pIMem, p_arr_copy_1[i], src_arr[i], STRING_LEN);
    }
    return p_arr_copy_1;
}

/*
 *
 * <сводка>
 *   Функция printIntArray
 * </сводка>
 *
 * <описание>
 *   Функция для вывода в консоль массива типа int
 * </описание>
 *
 */
void printIntArray(void *p_arr, size_t size) {
    int *arr = (int *) p_arr;
    size_t i;
    for (i = 0; i < size; ++i) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

/*
 *
 * <сводка>
 *   Функция printFloatArray
 * </сводка>
 *
 * <описание>
 *   Функция для вывода в консоль массива типа float
 * </описание>
 *
 */
void printFloatArray(void *p_arr, size_t size) {
    float *arr = (float *) p_arr;
    size_t i;
    for (i = 0; i < size; ++i) {
        printf("%f ", arr[i]);
    }
    printf("\n");
}

/*
 *
 * <сводка>
 *   Функция printDoubleArray
 * </сводка>
 *
 * <описание>
 *   Функция для вывода в консоль массива типа double
 * </описание>
 *
 */
void printDoubleArray(void *p_arr, size_t size) {
    double *arr = (double *) p_arr;
    size_t i;
    for (i = 0; i < size; ++i) {
        printf("%lf ", arr[i]);
    }
    printf("\n");
}

/*
 *
 * <сводка>
 *   Функция printStringArray
 * </сводка>
 *
 * <описание>
 *   Функция для вывода в консоль массива типа string
 * </описание>
 *
 */
void printStringArray(void *p_arr, size_t size) {
    char **arr = (char **) p_arr;
    size_t i;
    for (i = 0; i < size; ++i) {
        printf("'%s' ", arr[i]);
    }
    printf("\n");
}

/*
 *
 * <сводка>
 *   Структура Sorter
 * </сводка>
 *
 * <описание>
 *   Структура для хранения вспомогательных данных и функций для конкретного типа данных
 * </описание>
 *
 */
typedef struct Sorter {
    const char *type_name;

    size_t elem_size;

    void *(*createArray)(IEcoMemoryAllocator1 *pIMem, size_t size);

    int (__cdecl *compare)(const void *a_ptr, const void *b_ptr);

    void (*deleteArray)(IEcoMemoryAllocator1 *pIMem, void *arr_ptr, size_t size);

    void *(*clone)(IEcoMemoryAllocator1 *pIMem, void *src, uint32_t byte_count);

    void (*printArray)(void *p_arr, size_t size);
} Sorter;

/*
 *
 * <сводка>
 *   Структура BenchResults
 * </сводка>
 *
 * <описание>
 *   Структура для хранения результатов замера времени выполнения сортировок
 * </описание>
 *
 */
typedef struct BenchResults {
    double bintree_sort;
    double std_qsort;
    double rbtree_sort;
} BenchResults;

/*
 *
 * <сводка>
 *   Функция benchmarkSortingFunc
 * </сводка>
 *
 * <описание>
 *   Функция фиксирует время выполнения конкретной сортировки.
 * </описание>
 *
 */
double benchmarkSortingFunc(
        int16_t(ECOCALLMETHOD sort)(
                struct IEcoLab1 *,
                void *,
                size_t,
                size_t,
                int (__cdecl *)(const void *, const void *)),
        IEcoLab1 *i_eco,
        void *p_data, size_t elem_count, size_t elem_size,
        int (__cdecl *compare)(const void *, const void *)) {
    clock_t before, after;
    before = clock();
    sort(i_eco, p_data, elem_count, elem_size, compare);
    after = clock();
    return (double) (after - before) / CLOCKS_PER_SEC;
}

/*
 *
 * <сводка>
 *   Функция benchSorting
 * </сводка>
 *
 * <описание>
 *   Функция фиксирует время выполнения трех видов сортировок при определенном типе данных и размере массива.
 * </описание>
 *
 */
BenchResults benchSorting(IEcoMemoryAllocator1 *pIMem, Sorter *sorting, size_t size, IEcoLab1 *lab1,
                          IEcoLab1 *lab1RBTree) {
    uint32_t byte_count = size * sorting->elem_size;
    void *p_arr = sorting->createArray(pIMem, size);
    void *p_arr_copy_1 = sorting->clone(pIMem, p_arr, byte_count);
    void *p_arr_copy_2 = sorting->clone(pIMem, p_arr, byte_count);
    double lab_sort_bintree, std_sort, lab_sort_rbtree;
    BenchResults result;

    lab_sort_bintree = benchmarkSortingFunc(lab1->pVTbl->qsort, lab1, p_arr, size, sorting->elem_size,
                                            sorting->compare);
    sorting->deleteArray(pIMem, p_arr, size);

    std_sort = benchmarkSortingFunc(stdQsort, 0, p_arr_copy_1, size, sorting->elem_size, sorting->compare);
    sorting->deleteArray(pIMem, p_arr_copy_1, size);

    lab_sort_rbtree = benchmarkSortingFunc(lab1RBTree->pVTbl->qsort, lab1RBTree, p_arr_copy_2, size, sorting->elem_size,
                                           sorting->compare);
    sorting->deleteArray(pIMem, p_arr_copy_2, size);

    result.bintree_sort = lab_sort_bintree;
    result.rbtree_sort = lab_sort_rbtree;
    result.std_qsort = std_sort;
    return result;
}

/*
 *
 * <сводка>
 *   Функция printSortingExamples
 * </сводка>
 *
 * <описание>
 *   Функция выводит на экран примеры массивов до и после сортировки
 * </описание>
 *
 */
void printSortingExamples(
        IEcoMemoryAllocator1 *pIMem, Sorter *sorting, IEcoLab1 *lab1, IEcoLab1 *lab1RBTree, size_t size
) {
    void *p_arr = sorting->createArray(pIMem, size);
    void *p_arr_copy_1 = sorting->clone(pIMem, p_arr, size * sorting->elem_size);
    void *p_arr_copy_2 = sorting->clone(pIMem, p_arr, size * sorting->elem_size);

    printf("testing sort for type: %s\n", sorting->type_name);
    printf("Array before sort:\n");
    sorting->printArray(p_arr, size);

    qsort(p_arr, size, sorting->elem_size, sorting->compare);
    lab1->pVTbl->qsort(lab1, p_arr_copy_1, size, sorting->elem_size, sorting->compare);
    lab1RBTree->pVTbl->qsort(lab1RBTree, p_arr_copy_2, size, sorting->elem_size, sorting->compare);

    printf("Array after standard qsort:\n");
    sorting->printArray(p_arr, size);
    printf("Array after Binary Tree sort:\n");
    sorting->printArray(p_arr_copy_1, size);
    printf("Array after Red-Black Tree sort:\n");
    sorting->printArray(p_arr_copy_2, size);
    printf("\n");

    sorting->deleteArray(pIMem, p_arr, size);
    sorting->deleteArray(pIMem, p_arr_copy_1, size);
    sorting->deleteArray(pIMem, p_arr_copy_2, size);
}

/*
 *
 * <сводка>
 *   Функция benchAndWriteResultToFile
 * </сводка>
 *
 * <описание>
 *   Функция замеряет время сортировок  и записывает результаты в файл
 * </описание>
 *
 */
void benchAndWriteResultToFile(FILE *file, IEcoMemoryAllocator1 *pIMem, IEcoLab1 *lab1, IEcoLab1 *lab1RBTree,
                               Sorter *sorting,
                               size_t size) {
    printf("Bench:\ttype=%s\tsize=%d ", sorting->type_name, size);
    BenchResults result = benchSorting(pIMem, sorting, size, lab1, lab1RBTree);
    printf("done.\n");
    fprintf(file, "%s,%s,%d,%lf\n", "bintree_sort", sorting->type_name, size, result.bintree_sort);
    fprintf(file, "%s,%s,%d,%lf\n", "rbtree_sort", sorting->type_name, size, result.rbtree_sort);
    fprintf(file, "%s,%s,%d,%lf\n", "qsort", sorting->type_name, size, result.std_qsort);
}

/*
 *
 * <сводка>
 *   Функция bench
 * </сводка>
 *
 * <описание>
 *   Функция бенчмаркинга времени выполнения сортировок на разных типах данных и разном размере массива
 * </описание>
 *
 */
void bench(IEcoMemoryAllocator1 *pIMem, Sorter *sorterByType, IEcoLab1 *pIEcoLab1, IEcoLab1 *pIEcoLab1RBTree) {
    FILE *resultFile;
    size_t i, j, sizes[10] = {3000, 5000, 10000, 20000, 30000, 100000, 250000, 500000, 1000000, 2000000};
    /* arrays with ascending values */
    Sorter sortersAscending[2] = {
            /* int */
            {"int_ascending", sizeof(int), generateAscendingIntArray, compareInt, deleteArray, cloneArray,
             printIntArray},
            /* double */
            {"double_ascending", sizeof(double), generateAscendingDoubleArray, compareDouble, deleteArray, cloneArray,
             printDoubleArray},
    };
    printf("Benchmarking sorting algorithms\n");
    printf("Results will be stored in 'results.csv'\n");
    fopen_s(&resultFile, "results.csv", "w");
    fprintf(resultFile, "algorithm,type,size,time\n");
    for (i = 0; i < 4; ++i) {
        for (j = 0; j < 2; j++) {
            benchAndWriteResultToFile(resultFile, pIMem, pIEcoLab1, pIEcoLab1RBTree, &sortersAscending[j], sizes[i]);
        }
    }
    for (i = 0; i < 10; ++i) {
        for (j = 0; j < 4; j++) {
            benchAndWriteResultToFile(resultFile, pIMem, pIEcoLab1, pIEcoLab1RBTree, &sorterByType[j], sizes[i]);
        }
    }
    fclose(resultFile);
}

/*
 *
 * <сводка>
 *   Функция example
 * </сводка>
 *
 * <описание>
 *   Функция для вывода на экран примеров сортировок на разных типах данных
 * </описание>
 *
 */
void example(IEcoMemoryAllocator1 *pIMem, Sorter *sorterByType, IEcoLab1 *pIEcoLab1, IEcoLab1 *pIEcoLab1RBTree) {
    size_t i;
    for (i = 0; i < 4; ++i) {
        printSortingExamples(pIMem, &sorterByType[i], pIEcoLab1, pIEcoLab1RBTree, 9);
    }
}

void test(IEcoMemoryAllocator1 *pIMem, IEcoLab1 *pIEcoLab1, IEcoLab1 *pIEcoLab1RBTree) {
    Sorter sorterByType[4] = {
            /* int */
            {"int",    sizeof(int),    generateRandomIntArray,    compareInt,    deleteArray,       cloneArray,       printIntArray},
            /* float */
            {"float",  sizeof(float),  generateRandomFloatArray,  compareFloat,  deleteArray,       cloneArray,       printFloatArray},
            /* double */
            {"double", sizeof(double), generateRandomDoubleArray, compareDouble, deleteArray,       cloneArray,       printDoubleArray},
            /* string */
            {"string", sizeof(char *), generateRandomStringArray, compareString, deleteStringArray, cloneStringArray, printStringArray}
    };
    // Инициализация seed для rand()
    srand(time(0));
    // Вывод на экран примеров сортировок
    example(pIMem, sorterByType, pIEcoLab1, pIEcoLab1RBTree);
    // Бенчмаркинг времени выполнения сортировок на разных типах данных и разном размере массива
    bench(pIMem, sorterByType, pIEcoLab1, pIEcoLab1RBTree);
}

/*
 *
 * <сводка>
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown *pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1 *pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1 *pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1 *pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1 *pIEcoLab1 = 0;
    IEcoLab1 *pIEcoLab1RBTree = 0;

    /* Проверка и создание системного интрефейса */
    if (pISys == 0) {
        result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **) &pISys);
        if (result != 0 && pISys == 0) {
            /* Освобождение системного интерфейса в случае ошибки */
            goto Release;
        }
    }
    if (result != 0 && pISys == 0) {
        goto Release;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **) &pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1,
                                          (void **) &pIMem);

    /* Проверка */
    if (result != 0 || pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        goto Release;
    }

    /* Получение тестируемого интерфейса бинарного дерева */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void **) &pIEcoLab1);
    if (result != 0 || pIEcoLab1 == 0) {
        goto Release;
    }

    /* Получение тестируемого интерфейса красно-черного дерева */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1RBTree, 0, &IID_IEcoLab1, (void **) &pIEcoLab1RBTree);
    if (result != 0 || pIEcoLab1RBTree == 0) {
        goto Release;
    }

    /* Тестирование сортировок */
    test(pIMem, pIEcoLab1, pIEcoLab1RBTree);

    Release:

    /* Освобождение интерфейса для работы с интерфейсной шиной */
    if (pIBus != 0) {
        pIBus->pVTbl->Release(pIBus);
    }

    /* Освобождение интерфейса работы с памятью */
    if (pIMem != 0) {
        pIMem->pVTbl->Release(pIMem);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1 != 0) {
        pIEcoLab1->pVTbl->Release(pIEcoLab1);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}
