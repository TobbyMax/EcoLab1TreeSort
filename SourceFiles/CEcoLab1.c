#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1.h"

/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция QueryInterface для интерфейса IEcoLab1
 * </описание>
 *
 */
int16_t
ECOCALLMETHOD CEcoLab1_QueryInterface(/* in */ struct IEcoLab1 *me, /* in */ const UGUID *riid, /* out */ void **ppv) {
    CEcoLab1 *pCMe = (CEcoLab1 *) me;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1 *) pCMe);
    } else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1 *) pCMe);
    } else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция AddRef для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_AddRef(/* in */ struct IEcoLab1 *me) {
    CEcoLab1 *pCMe = (CEcoLab1 *) me;

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция Release для интерфейса IEcoLab1
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1_Release(/* in */ struct IEcoLab1 *me) {
    CEcoLab1 *pCMe = (CEcoLab1 *) me;

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1((IEcoLab1 *) pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция copyBytes
 * </сводка>
 *
 * <описание>
 *   Функция копирования заданного количества байт
 * </описание>
 *
 */
void copyBytes(char *dst, char *src, size_t size) {
    char *end = src + size;
    while (src < end) {
        *(dst++) = *(src++);
    }
}

typedef struct Node {
    char *val;
    struct Node *left, *right;
} Node;


/*
 *
 * <сводка>
 *   Функция newNode
 * </сводка>
 *
 * <описание>
 *   Функция создания и выделения памяти для новой ноды бинарного дерева. Возвращает указатель на новую ноду
 * </описание>
 *
 */
Node *newNode(CEcoLab1 *pCMe, char *item, size_t elem_size) {
    Node *node = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(Node));
    if (node == 0) {
        return 0;
    }
    node->val = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, elem_size);
    if (node->val == 0) {
        return 0;
    }
    copyBytes(node->val, item, elem_size);
    node->left = node->right = 0;
    return node;
}

/*
 *
 * <сводка>
 *   Функция insert
 * </сводка>
 *
 * <описание>
 *   Функция рекурсивной вставки в бинарное дерево
 * </описание>
 *
 */
Node *insert(CEcoLab1 *pCMe, Node *node, char *curr_ptr, size_t elem_size, int (__cdecl *compare)(const void *, const void *)) {
    if (node == 0) return newNode(pCMe, curr_ptr, elem_size);

    if (compare(curr_ptr, node->val) <= 0) {
        node->left = insert(pCMe, node->left, curr_ptr, elem_size, compare);
    } else {
        node->right = insert(pCMe, node->right, curr_ptr, elem_size, compare);
    }

    return node;
}

/*
 *
 * <сводка>
 *   Функция infixNonRecTraversal
 * </сводка>
 *
 * <описание>
 *   Функция обеспечивает рекурсивный инфиксный обход бинарного дерева и записывает результат в массив
 * </описание>
 *
 */
void infixDFSTraversal(Node *root, char **curr_ptr, size_t elem_size) {
    if (root != 0) {
        infixDFSTraversal(root->left, curr_ptr, elem_size);
        copyBytes(*curr_ptr, root->val, elem_size);
        *curr_ptr += elem_size;
        infixDFSTraversal(root->right, curr_ptr, elem_size);
    }
}

void freeTree(CEcoLab1 *pCMe, Node *root) {
    if (root != 0) {
        freeTree(pCMe, root->left);
        freeTree(pCMe, root->right);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, root->val);
        pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, root);
    }
}

/*
 *
 * <сводка>
 *   Функция treeSort
 * </сводка>
 *
 * <описание>
 *   Функция сортировки с помощью построения бинарного и его инфиксного обхода
 * </описание>
 *
 */
void treeSort(
        CEcoLab1 *pCMe,
        char *start_ptr,
        size_t elem_count,
        size_t elem_size,
        int (__cdecl *compare)(const void *, const void *)
) {
    Node *root = 0;
    size_t byte_count = elem_size * elem_count;
    char *curr_ptr = start_ptr;
    char *end_ptr = start_ptr + byte_count;

    /* Строим бинарное дерево */
    for (; curr_ptr < end_ptr; curr_ptr += elem_size) {
        root = insert(pCMe, root, curr_ptr, elem_size, compare);
    }

    /* Получаем отсортированный массив */
    infixDFSTraversal(root, &start_ptr, elem_size);

    freeTree(pCMe, root);
}

/*
 *
 * <сводка>
 *   Функция qsort (tree sort)
 * </сводка>
 *
 * <описание>
 *   Функция сортировки деревом, использует сигнатуру qsort.
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1_qsort(
        struct IEcoLab1 *me,
        void *pData,
        size_t elem_count,
        size_t elem_size,
        int (__cdecl *compare)(const void *, const void *)
) {
    CEcoLab1 *pCMe = (CEcoLab1 *) me;

    /* Проверка указателей */
    if (me == 0 || pData == 0 || compare == 0) {
        return -1;
    }

    // sort
    treeSort(pCMe, pData, elem_count, elem_size, compare);

    return 0;
}

/* Create Virtual Table IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
        CEcoLab1_QueryInterface,
        CEcoLab1_AddRef,
        CEcoLab1_Release,
        CEcoLab1_qsort
};



/*
 *
 * <сводка>
 *   Функция Init
 * </сводка>
 *
 * <описание>
 *   Функция инициализации экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD initCEcoLab1(/*in*/ struct IEcoLab1* me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1* pCMe = (CEcoLab1*)me;
    IEcoInterfaceBus1* pIBus = 0;
    int16_t result = -1;

    /* Проверка указателей */
    if (me == 0) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1 *) pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **) &pIBus);

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1 *) pIUnkSystem;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return result;
}

/*
 *
 * <сводка>
 *   Функция Create
 * </сводка>
 *
 * <описание>
 *   Функция создания экземпляра
 * </описание>
 *
 */
int16_t ECOCALLMETHOD createCEcoLab1(/* in */ IEcoUnknown *pIUnkSystem, /* in */ IEcoUnknown *pIUnkOuter, /* out */
                                              IEcoLab1 **ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1 *pISys = 0;
    IEcoInterfaceBus1 *pIBus = 0;
    IEcoInterfaceBus1MemExt *pIMemExt = 0;
    IEcoMemoryAllocator1 *pIMem = 0;
    CEcoLab1 *pCMe = 0;
    UGUID *rcid = (UGUID *) &CID_EcoMemoryManager1;

    /* Проверка указателей */
    if (ppIEcoLab1 == 0 || pIUnkSystem == 0) {
        return result;
    }

    /* Получение системного интерфейса приложения */
    result = pIUnkSystem->pVTbl->QueryInterface(pIUnkSystem, &GID_IEcoSystem1, (void **) &pISys);

    /* Проверка */
    if (result != 0 && pISys == 0) {
        return result;
    }

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pISys->pVTbl->QueryInterface(pISys, &IID_IEcoInterfaceBus1, (void **) &pIBus);

    /* Получение идентификатора компонента для работы с памятью */
    result = pIBus->pVTbl->QueryInterface(pIBus, &IID_IEcoInterfaceBus1MemExt, (void **) &pIMemExt);
    if (result == 0 && pIMemExt != 0) {
        rcid = (UGUID *) pIMemExt->pVTbl->get_Manager(pIMemExt);
        pIMemExt->pVTbl->Release(pIMemExt);
    }

    /* Получение интерфейса распределителя памяти */
    pIBus->pVTbl->QueryComponent(pIBus, rcid, 0, &IID_IEcoMemoryAllocator1, (void **) &pIMem);

    /* Проверка */
    if (result != 0 && pIMem == 0) {
        /* Освобождение системного интерфейса в случае ошибки */
        pISys->pVTbl->Release(pISys);
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1 *) pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1));

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = pISys;

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoLab1 */
    pCMe->m_pVTblIEcoLab1 = &g_x277FC00C35624096AFCFC125B94EEC90VTbl;

    /* Инициализация данных */
    pCMe->m_Name = 0;

    /* Возврат указателя на интерфейс */
    *ppIEcoLab1 = (IEcoLab1 *) pCMe;

    /* Освобождение */
    pIBus->pVTbl->Release(pIBus);

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Delete
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра
 * </описание>
 *
 */
void ECOCALLMETHOD deleteCEcoLab1(/* in */ IEcoLab1 *pIEcoLab1) {
    CEcoLab1 *pCMe = (CEcoLab1 *) pIEcoLab1;
    IEcoMemoryAllocator1 *pIMem = 0;

    if (pIEcoLab1 != 0) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        if (pCMe->m_Name != 0) {
            pIMem->pVTbl->Free(pIMem, pCMe->m_Name);
        }
        if (pCMe->m_pISys != 0) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}