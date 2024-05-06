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

#include "IEcoCalculatorY.h"
#include "IEcoCalculatorX.h"

#include "IEcoConnectionPointContainer.h"
#include "IEcoConnectionPoint.h"
#include "IEcoLab1Events.h"
#include "CEcoLab1Sink.h"

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
        arr[i] = rand() % 100 - 50;
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
 *   Функция printInt
 * </сводка>
 *
 * <описание>
 *   Функция для вывода типа int
 * </описание>
 *
 */
void ECOCDECLMETHOD printInt(const int* a) {
    printf("%3d", *a);
}

/*
 *
 * <сводка>
 *   Функция printDouble
 * </сводка>
 *
 * <описание>
 *   Функция для вывода типа double
 * </описание>
 *
 */
void ECOCDECLMETHOD printDouble(const double_t* a) {
    printf("%.3f", *a);
}

/*
 *
 * <сводка>
 *   Функция printString
 * </сводка>
 *
 * <описание>
 *   Функция для вывода cтроки
 * </описание>
 *
 */
void ECOCDECLMETHOD printString(const char_t** a) {
    printf("%s", *a);
}


// Функция EcoMain - точка входа
int16_t EcoMain(IEcoUnknown* pIUnk) {
    int16_t result = -1;
    /* Указатель на системный интерфейс */
    IEcoSystem1* pISys = 0;
    /* Указатель на интерфейс работы с системной интерфейсной шиной */
    IEcoInterfaceBus1* pIBus = 0;
    /* Указатель на интерфейс работы с памятью */
    IEcoMemoryAllocator1* pIMem = 0;
    /* Указатель на тестируемый интерфейс */
    IEcoLab1* pIEcoLab1RBTree = 0;
    void *p_arr = 0;
    size_t test_size = 8;

    /* Указатель на интерфейс контейнера точек подключения */
    IEcoConnectionPointContainer* pICPC = 0;
    /* Указатель на интерфейс точки подключения */
    IEcoConnectionPoint* pICP = 0;
    /* Указатель на обратный интерфейс */
    IEcoLab1Events* pIEcoLab1Sink = 0;
    IEcoUnknown* pISinkUnk = 0;
    uint32_t cAdvise = 0;

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

    /* Получение тестируемого интерфейса */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoLab1RBTree, 0, &IID_IEcoLab1, (void**) &pIEcoLab1RBTree);
    if (result != 0 || pIEcoLab1RBTree == 0) {
        goto Release;
    }
    printf("Queried CEcoLab1RBTree component Successfully\n");

    /* Проверка поддержки подключений обратного интерфейса */
    result = pIEcoLab1RBTree->pVTbl->QueryInterface(pIEcoLab1RBTree, &IID_IEcoConnectionPointContainer, (void **)&pICPC);
    if (result != 0 || pICPC == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    printf("Queried CPContainer Successfully\n");

    /* Запрос на получения интерфейса точки подключения */
    result = pICPC->pVTbl->FindConnectionPoint(pICPC, &IID_IEcoLab1Events, &pICP);
    if (result != 0 || pICP == 0) {
        /* Освобождение интерфейсов в случае ошибки */
        goto Release;
    }
    /* Освобождение интерфейса */
    pICPC->pVTbl->Release(pICPC);
    printf("Found connection point\n");

    /* Создание экземпляра обратного интерфейса */
    result = createCEcoLab1Sink(pIMem, (IEcoLab1Events**)&pIEcoLab1Sink);

    if (pIEcoLab1Sink != 0) {
        result = pIEcoLab1Sink->pVTbl->QueryInterface(pIEcoLab1Sink, &IID_IEcoUnknown,(void **)&pISinkUnk);
        if (result != 0 || pISinkUnk == 0) {
            /* Освобождение интерфейсов в случае ошибки */
            goto Release;
        }
        /* Подключение */
        result = pICP->pVTbl->Advise(pICP, pISinkUnk, &cAdvise);
        /* Проверка */
        if (result == 0 && cAdvise == 1) {
            /* Сюда можно добавить код */
        }
        /* Освобождение интерфейса */
        pISinkUnk->pVTbl->Release(pISinkUnk);
    }
    printf("Sink created\n");

    printf("_________________________________\n");
    printf("Testing Red-Black Tree Sorting\n");

    p_arr = generateRandomIntArray(pIMem, test_size);
    printf("\nInitial array:\n");
    printIntArray(p_arr, test_size);
    printf("\nSorting Visualization:\n\n");

    ((CEcoLab1Sink *) pIEcoLab1Sink)->SetPrintFunction(pIEcoLab1Sink, printInt);

    pIEcoLab1RBTree->pVTbl->qsort(pIEcoLab1RBTree, p_arr, test_size, sizeof(int), compareInt);

    printf("\nSorted Array:\n");
    printIntArray(p_arr, test_size);

    pIMem->pVTbl->Free(pIMem, p_arr);

    if (pIEcoLab1Sink != 0) {
        /* Отключение */
        result = pICP->pVTbl->Unadvise(pICP, cAdvise);
        pIEcoLab1Sink->pVTbl->Release(pIEcoLab1Sink);
        pICP->pVTbl->Release(pICP);
    }


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
    if (pIEcoLab1RBTree != 0) {
        pIEcoLab1RBTree->pVTbl->Release(pIEcoLab1RBTree);
    }

    /* Освобождение системного интерфейса */
    if (pISys != 0) {
        pISys->pVTbl->Release(pISys);
    }

    return result;
}

