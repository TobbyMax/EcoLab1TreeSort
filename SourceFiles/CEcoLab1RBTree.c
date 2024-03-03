#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1RBTree.h"

#define BLACK 0
#define RED 1

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
int16_t ECOCALLMETHOD CEcoLab1RBTree_QueryInterface(/* in */ struct IEcoLab1 *me, /* in */ const UGUID *riid, /* out */
                                                             void **ppv) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;

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
uint32_t ECOCALLMETHOD CEcoLab1RBTree_AddRef(/* in */ struct IEcoLab1 *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;

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
uint32_t ECOCALLMETHOD CEcoLab1RBTree_Release(/* in */ struct IEcoLab1 *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1RBTree((IEcoLab1 *) pCMe);
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

typedef struct RBNode {
    void *val;
    struct RBNode *left;
    struct RBNode *right;
    struct RBNode *parent;
    unsigned char color;
} RBNode;

/*
 *
 * <сводка>
 *   Функция newRBNode
 * </сводка>
 *
 * <описание>
 *   Функция создания и выделения памяти для новой ноды КЧД. Возвращает указатель на новую ноду
 * </описание>
 *
 */
RBNode *newRBNode(CEcoLab1RBTree *pCMe, RBNode *p_Parent, void *p_val, size_t elem_size) {
    RBNode *node = (RBNode *) pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, sizeof(RBNode));
    if (node == 0) {
        return 0;
    }
    node->val = pCMe->m_pIMem->pVTbl->Alloc(pCMe->m_pIMem, elem_size);
    if (node->val == 0) {
        return 0;
    }
    copyBytes(node->val, p_val, elem_size);
    node->left = node->right = 0;
    node->parent = p_Parent;
    node->color = RED;
    return node;
}

/*
 *
 * <сводка>
 *   Функция balance
 * </сводка>
 *
 * <описание>
 *   Функция балансировки КЧД, обеспечивающая вращение дерева при вставке
 * </описание>
 *
 */
void balance(RBNode *node) {
    RBNode *child;
    RBNode *parent;
    RBNode *grand_parent;
    RBNode *great_grand_parent;

    if (node == 0 || node->parent == 0) {
        return;
    }

    child = node;
    if (node->color == BLACK || (node->parent)->color == BLACK) {
        return;
    }

    parent = node->parent;
    grand_parent = parent->parent;

    if (grand_parent == 0) {
        parent->color = BLACK;
        return;
    }

    if (grand_parent->right != 0 && (grand_parent->right)->color == RED &&
        grand_parent->left != 0 && (grand_parent->left)->color == RED) {
        (grand_parent->right)->color = BLACK;
        (grand_parent->left)->color = BLACK;
        grand_parent->color = RED;
        return;
    }

    great_grand_parent = grand_parent->parent;
    if (grand_parent->right == parent) {
        if (parent->right == node) {
            grand_parent->right = parent->left;
            if (parent->left != 0) {
                (parent->left)->parent = grand_parent;
            }
            parent->left = grand_parent;
            grand_parent->parent = parent;

            parent->parent = great_grand_parent;
            if (great_grand_parent != 0) {
                if (great_grand_parent->left != 0 &&
                    great_grand_parent->left == grand_parent) {
                    great_grand_parent->left = parent;
                } else {
                    great_grand_parent->right = parent;
                }
            }
            parent->color = BLACK;
            grand_parent->color = RED;
        } else {
            parent->left = child->right;
            if (child->right != 0) {
                (child->right)->parent = parent;
            }
            child->right = parent;
            parent->parent = child;

            grand_parent->right = child->left;
            if (child->left != 0) {
                (child->left)->parent = grand_parent;
            }
            child->left = grand_parent;
            grand_parent->parent = child;

            child->parent = great_grand_parent;
            if (great_grand_parent != 0) {
                if (great_grand_parent->left != 0 &&
                    great_grand_parent->left == grand_parent) {
                    great_grand_parent->left = child;
                } else {
                    great_grand_parent->right = child;
                }
            }
            child->color = BLACK;
            grand_parent->color = RED;
        }
    } else {
        if (parent->left == node) {
            grand_parent->left = parent->right;
            if (parent->right != 0) {
                (parent->right)->parent = grand_parent;
            }
            parent->right = grand_parent;
            grand_parent->parent = parent;

            parent->parent = great_grand_parent;
            if (great_grand_parent != 0) {
                if (great_grand_parent->left != 0 &&
                    great_grand_parent->left == grand_parent) {
                    great_grand_parent->left = parent;
                } else {
                    great_grand_parent->right = parent;
                }
            }
            parent->color = BLACK;
            grand_parent->color = RED;
        } else {
            parent->right = child->left;
            if (child->left != 0) {
                (child->left)->parent = parent;
            }
            child->left = parent;
            parent->parent = child;

            grand_parent->left = child->right;
            if (child->right != 0) {
                (child->right)->parent = grand_parent;
            }
            child->right = grand_parent;
            grand_parent->parent = child;

            child->parent = great_grand_parent;
            if (great_grand_parent != 0) {
                if (great_grand_parent->left != 0 &&
                    great_grand_parent->left == grand_parent) {
                    great_grand_parent->left = child;
                } else {
                    great_grand_parent->right = child;
                }
            }

            child->color = BLACK;
            grand_parent->color = RED;
        }
    }
}

/*
 *
 * <сводка>
 *   Функция insert
 * </сводка>
 *
 * <описание>
 *   Функция нерекурсивной вставки в КЧД
 * </описание>
 *
 */
RBNode *insert(CEcoLab1RBTree *pCMe, RBNode **root, void *val, size_t elem_size,
               int (__cdecl *compare)(const void *, const void *)) {
    RBNode *current = *root;
    RBNode *inserted;

    if (*root == 0) {
        return newRBNode(pCMe, 0, val, elem_size);
    }
    while (current != 0) {
        if ((*compare)(val, current->val) <= 0) {
            if (current->left == 0) {
                inserted = newRBNode(pCMe, current, val, elem_size);
                current->left = inserted;
                current = inserted;
                break;
            }
            current = current->left;
        } else {
            if (current->right == 0) {
                inserted = newRBNode(pCMe, current, val, elem_size);
                current->right = inserted;
                current = inserted;
                break;
            }
            current = current->right;
        }
    }

    while (current != *root) {
        balance(current);
        if (current->parent == 0) {
            *root = current;
            break;
        }
        current = current->parent;
        if (current == *root) {
            current->color = BLACK;
        }
    }

    return *root;
}

/*
 *
 * <сводка>
 *   Функция infixNonRecTraversal
 * </сводка>
 *
 * <описание>
 *   Функция обеспечивает инфиксный обход КЧД без рекурсии и записывает результат переданный массив по указателю
 * </описание>
 *
 */
void infixNonRecTraversal(RBNode *root, char **curr_ptr, size_t elem_size) {
    RBNode *current = root;
    RBNode *prev;
    while (current != 0) {
        if (current->left == 0) {
            copyBytes(*curr_ptr, current->val, elem_size);
            *curr_ptr += elem_size;
            current = current->right;
        } else {
            prev = current->left;
            while (prev->right != 0 && prev->right != current) {
                prev = prev->right;
            }
            if (prev->right == 0) {
                prev->right = current;
                current = current->left;
            } else {
                prev->right = 0;
                copyBytes(*curr_ptr, current->val, elem_size);
                *curr_ptr += elem_size;
                current = current->right;
            }
        }
    }
}

/*
 *
 * <сводка>
 *   Функция freeTree
 * </сводка>
 *
 * <описание>
 *   Функция освобождения экземпляра КЧД, которая освобождает память выделенную под  нерекурсивного постфиксного обхода дерева
 * </описание>
 *
 */
void freeTree(CEcoLab1RBTree *pCMe, RBNode *root) {
    RBNode *current = root;
    RBNode *up = 0;

    RBNode *left;
    RBNode *right;

    while (current != 0) {
        if (current->left != 0) {
            left = current->left;
            current->left = up;
            up = current;
            current = left;
        } else if (current->right != 0) {
            right = current->right;
            current->left = up;
            current->right = 0;
            up = current;
            current = right;
        } else {
            if (up == 0) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, current->val);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, current);
                current = 0;
            }
            while (up != 0) {
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, current->val);
                pCMe->m_pIMem->pVTbl->Free(pCMe->m_pIMem, current);
                if (up->right != 0) {
                    current = up->right;
                    up->right = 0;
                    break;
                }
                current = up;
                up = up->left;
            }
        }
    }
}

/*
 *
 * <сводка>
 *   Функция treeSort
 * </сводка>
 *
 * <описание>
 *   Функция сортировки с помощью построения КЧД и его инфиксного обхода
 * </описание>
 *
 */
void treeSort(
        CEcoLab1RBTree *pCMe,
        char *start_ptr,
        size_t elem_count,
        size_t elem_size,
        int (__cdecl *compare)(const void *, const void *)
) {
    RBNode *root = 0;
    size_t byte_count = elem_size * elem_count;
    char *curr_ptr = start_ptr;
    char *end_ptr = start_ptr + byte_count;

    /* Строим КЧД */
    for (; curr_ptr < end_ptr; curr_ptr += elem_size) {
        root = insert(pCMe, &root, curr_ptr, elem_size, compare);
    }

    /* Получаем отсортированный массив */
    infixNonRecTraversal(root, &start_ptr, elem_size);

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
int16_t ECOCALLMETHOD CEcoLab1RBTree_qsort(
        struct IEcoLab1 *me,
        void *pData,
        size_t elem_count,
        size_t elem_size,
        int (__cdecl *compare)(const void *, const void *)
) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;

    /* Проверка указателей */
    if (me == 0 || pData == 0 || compare == 0) {
        return -1;
    }

    // sort
    treeSort(pCMe, pData, elem_count, elem_size, compare);

    return 0;
}

/* Create Virtual Table IEcoLab1TreeSort */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
        CEcoLab1RBTree_QueryInterface,
        CEcoLab1RBTree_AddRef,
        CEcoLab1RBTree_Release,
        CEcoLab1RBTree_qsort
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
int16_t ECOCALLMETHOD initCEcoLab1RBTree(/*in*/ struct IEcoLab1 *me, /* in */ struct IEcoUnknown *pIUnkSystem) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;
    IEcoInterfaceBus1 *pIBus = 0;
    int16_t result = -1;

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
int16_t
ECOCALLMETHOD createCEcoLab1RBTree(/* in */ IEcoUnknown *pIUnkSystem, /* in */ IEcoUnknown *pIUnkOuter, /* out */
                                            IEcoLab1 **ppIEcoLab1) {
    int16_t result = -1;
    IEcoSystem1 *pISys = 0;
    IEcoInterfaceBus1 *pIBus = 0;
    IEcoInterfaceBus1MemExt *pIMemExt = 0;
    IEcoMemoryAllocator1 *pIMem = 0;
    CEcoLab1RBTree *pCMe = 0;
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
    pCMe = (CEcoLab1RBTree *) pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1RBTree));

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
void ECOCALLMETHOD deleteCEcoLab1RBTree(/* in */ IEcoLab1 *pIEcoLab1) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) pIEcoLab1;
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