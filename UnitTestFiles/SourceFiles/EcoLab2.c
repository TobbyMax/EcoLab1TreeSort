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
#include "IdEcoCalculatorA.h"

#include "IdEcoLab1.h"
#include "IdEcoLab1RBTree.h"

#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

#include "IdEcoLab2.h"

#include <stdio.h>


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
 *   Функция EcoMain
 * </сводка>
 *
 * <описание>
 *   Функция EcoMain - точка входа
 * </описание>
 *
 */
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1BinTree = 0;
    IEcoLab1* pIEcoLab1RBTree = 0;
    IEcoCalculatorY* pIY = 0;
    IEcoCalculatorX* pIX = 0;

    IEcoLab1* pIEcoLab2 = 0;
    void *testArr = 0;
    size_t testSize = 10;

    /* Проверка и создание системного интерфейса */
    result = pIUnk->pVTbl->QueryInterface(pIUnk, &GID_IEcoSystem1, (void **)&pISys);
    if (result != 0 && pISys == 0) {
        goto Release;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **)&pIBus);
    if (result != 0 || pIBus == 0) {
        goto Release;
    }

    /* Получение интерфейса управления памятью */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoMemoryManager1, 0, &IID_IEcoMemoryAllocator1, (void**) &pIMem);
    if (result != 0 || pIMem == 0) {
        goto Release;
    }

    printf("__________________________________________\n\n");
    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1, 0, &IID_IEcoLab1, (void**) &pIEcoLab1BinTree);
    if (result != 0 || pIEcoLab1BinTree == 0) {
        goto Release;
    }
    printf("EcoLab1 component queried successfully\n");

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1RBTree, 0, &IID_IEcoLab1, (void**) &pIEcoLab1RBTree);
    if (result != 0 || pIEcoLab1RBTree == 0) {
        goto Release;
    }
    printf("EcoLab1RBTree component queried successfully\n");
    printf("\n");

    /* запрос интерфейса IEcoCalculatorX через IEcoLab1 */
    result = pIEcoLab1BinTree->pVTbl->QueryInterface(pIEcoLab1BinTree, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result != 0 || pIX == 0) {
        goto Release;
    }
    printf("EcoCalculatorX interface queried successfully from IEcoLab1\n");

    /* запрос интерфейса IEcoCalculatorY через IEcoLab1 */
    result = pIEcoLab1BinTree->pVTbl->QueryInterface(pIEcoLab1BinTree, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result != 0 || pIY == 0) {
        goto Release;
    }
    printf("EcoCalculatorY interface queried successfully from IEcoLab1\n");
    printf("__________________________________________\n");
    printf("\nCalculator Test Runs:\n");

    printf("\nIEcoCalculatorX:\n");
    printf("Addition: 121 + 99 = %d\n", pIX->pVTbl->Addition(pIX, 121, 99));
    printf("Subtraction test 118 - 31 = %d\n", pIX->pVTbl->Subtraction(pIX, 118, 31));
    pIX->pVTbl->Release(pIX);

    printf("\nIEcoCalculatorY:\n");
    printf("Multiplication: 7 * 13 = %d\n", pIY->pVTbl->Multiplication(pIY, 7, 13));
    printf("Division: 225 / 5 = %d\n", pIY->pVTbl->Division(pIY, 225, 5));
    pIY->pVTbl->Release(pIY);

    printf("__________________________________________\n");
    printf("\nTest that interfaces can be queried as expected:\n");

    result = pIEcoLab1BinTree->pVTbl->QueryInterface(pIEcoLab1BinTree, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        printf("+ IEcoCalculatorX can be queried from IEcoLab1\n");
        pIX->pVTbl->Release(pIX);
    } else {
        printf("- Failed to query IEcoCalculatorX from IEcoLab1\n");
    }
    result = pIEcoLab1BinTree->pVTbl->QueryInterface(pIEcoLab1BinTree, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        printf("+ IEcoCalculatorY can be queried from IEcoLab1\n");
        pIY->pVTbl->Release(pIY);
    } else {
        printf("- Failed to query IEcoCalculatorX from IEcoLab1\n");
    }
    result = pIEcoLab1BinTree->pVTbl->QueryInterface(pIEcoLab1BinTree, &IID_IEcoLab1, (void **) &pIEcoLab1BinTree);
    if (result == 0) {
        printf("+ IEcoLab1 can be queried from IEcoLab1\n");
        pIEcoLab1BinTree->pVTbl->Release(pIEcoLab1BinTree);
    } else {
        printf("- Failed to query IEcoLab1 from IEcoLab1\n");
    }
    printf("\n");

    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        printf("+ IEcoCalculatorX can be queried from IEcoCalculatorY\n");
        pIX->pVTbl->Release(pIX);
    } else {
        printf("- Failed to query IEcoCalculatorX from IEcoCalculatorY\n");
    }
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        printf("+ IEcoCalculatorY can be queried from IEcoCalculatorY\n");
        pIY->pVTbl->Release(pIY);
    } else {
        printf("- Failed to query IEcoCalculatorY from IEcoCalculatorY\n");
    }
    result = pIY->pVTbl->QueryInterface(pIY, &IID_IEcoLab1, (void **) &pIEcoLab1BinTree);
    if (result == 0) {
        printf("+ IEcoLab1 can be queried from IEcoCalculatorY\n");
        pIEcoLab1BinTree->pVTbl->Release(pIEcoLab1BinTree);
    } else {
        printf("- Failed to query IEcoLab1 from IEcoCalculatorY\n");
    }
    printf("\n");

    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result == 0) {
        printf("+ IEcoCalculatorX can be queried from IEcoCalculatorX\n");
        pIX->pVTbl->Release(pIX);
    } else {
        printf("- Failed to query IEcoCalculatorX from IEcoCalculatorX\n");
    }
    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result == 0) {
        printf("+ IEcoCalculatorY can be queried from IEcoCalculatorX\n");
        pIY->pVTbl->Release(pIY);
    } else {
        printf("- Failed to query IEcoCalculatorY from IEcoCalculatorX\n");
    }
    result = pIX->pVTbl->QueryInterface(pIX, &IID_IEcoLab1, (void **) &pIEcoLab1BinTree);
    if (result == 0) {
        printf("+ IEcoLab1 can be queried from IEcoCalculatorX\n");
        pIEcoLab1BinTree->pVTbl->Release(pIEcoLab1BinTree);
    } else {
        printf("- Failed to query IEcoLab1 from IEcoCalculatorX\n");
    }
    printf("__________________________________________\n");

    printf("\nTest IEcoLab1 interface aggregation by CEcoLab2 component:\n");
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab2, 0, &IID_IEcoLab1, (void**) &pIEcoLab2);
    if (result == 0) {
        printf("IEcoLab1 interface aggregated by CEcoLab2 queried successfully\n\n");
    }
    printf("Test sorting:\n");
    testArr = generateRandomIntArray(pIMem, testSize);
    printf("Before Sort:\n");
    printIntArray(testArr, testSize);

    pIEcoLab2->pVTbl->qsort(pIEcoLab2, testArr, testSize, sizeof(int), compareInt);

    printf("After Sort:\n");
    printIntArray(testArr, testSize);

    printf("\nCalculator Test Runs:\n");
    /* запрос интерфейса IEcoCalculatorX через IEcoLab2 */
    result = pIEcoLab1BinTree->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorX, (void **) &pIX);
    if (result != 0 || pIX == 0) {
        goto Release;
    }
    printf("EcoCalculatorX interface queried successfully from IEcoLab2\n");

    /* запрос интерфейса IEcoCalculatorY через IEcoLab2 */
    result = pIEcoLab1BinTree->pVTbl->QueryInterface(pIEcoLab2, &IID_IEcoCalculatorY, (void **) &pIY);
    if (result != 0 || pIY == 0) {
        goto Release;
    }
    printf("EcoCalculatorY interface queried successfully from IEcoLab2\n");
    printf("\nIEcoCalculatorX:\n");
    printf("Addition: 121 + 99 = %d\n", pIX->pVTbl->Addition(pIX, 121, 99));
    printf("Subtraction test 118 - 31 = %d\n", pIX->pVTbl->Subtraction(pIX, 118, 31));
    pIX->pVTbl->Release(pIX);

    printf("\nIEcoCalculatorY:\n");
    printf("Multiplication: 7 * 13 = %d\n", pIY->pVTbl->Multiplication(pIY, 7, 13));
    printf("Division: 225 / 5 = %d\n", pIY->pVTbl->Division(pIY, 225, 5));
    pIY->pVTbl->Release(pIY);
    printf("__________________________________________\n");

    pIMem->pVTbl->Free(pIMem, testArr);


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
    if (pIEcoLab1BinTree != 0) {
        pIEcoLab1BinTree->pVTbl->Release(pIEcoLab1BinTree);
    }

    /* Освобождение тестируемого интерфейса */
    if (pIEcoLab1RBTree != 0) {
        pIEcoLab1RBTree->pVTbl->Release(pIEcoLab1RBTree);
    }

    if (pIEcoLab2 != 0) {
        pIEcoLab2->pVTbl->Release(pIEcoLab2);
    }
    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

