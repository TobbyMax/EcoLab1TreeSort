#include "IEcoSystem1.h"
#include "IEcoInterfaceBus1.h"
#include "IEcoInterfaceBus1MemExt.h"
#include "CEcoLab1RBTree.h"

#include "IdEcoCalculatorA.h"
#include "IdEcoCalculatorB.h"
#include "IdEcoCalculatorD.h"
#include "IdEcoCalculatorE.h"
#include "CEcoLab1EnumConnectionPoints.h"
#include "IEcoConnectionPointContainer.h"
#include "IEcoLab1Events.h"

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
    IEcoUnknown *nonDelegatingUnk = (IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk;
    int16_t result;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    /* Проверка и получение запрошенного интерфейса */
    result = nonDelegatingUnk->pVTbl->QueryInterface(nonDelegatingUnk, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
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

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
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

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
}

int16_t ECOCALLMETHOD CEcoLab1RBTree_IEcoConnectionPointContainer_QueryInterface(/* in */
        struct IEcoConnectionPointContainer *me, /* in */ const UGUID *riid, /* out */ void **ppv) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *) - sizeof(struct IEcoUnknown *));
    IEcoUnknown *nonDelegating = (IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk;
    int16_t result;
    if (me == 0 || ppv == 0) {
        return -1;
    }
    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t
ECOCALLMETHOD CEcoLab1RBTree_IEcoConnectionPointContainer_AddRef(/* in */ struct IEcoConnectionPointContainer *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *) - sizeof(struct IEcoUnknown *));
    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
}

uint32_t
ECOCALLMETHOD CEcoLab1RBTree_IEcoConnectionPointContainer_Release(/* in */ struct IEcoConnectionPointContainer *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *) - sizeof(struct IEcoUnknown *));
    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
}

int16_t ECOCALLMETHOD CEcoLab1RBTree_IEcoConnectionPointContainer_EnumConnectionPoints(/* in */
        struct IEcoConnectionPointContainer *me, /* out */ struct IEcoEnumConnectionPoints **ppEnum) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *) - sizeof(struct IEcoUnknown *));
    int16_t result = 0;

    if (me == 0 || ppEnum == 0) {
        return -1;
    }

    result = createCEcoLab1EnumConnectionPoints((IEcoUnknown *) pCMe->m_pISys,
                                                (struct IEcoConnectionPoint *) &pCMe->m_pISinkCP->m_pVTblICP, ppEnum);

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1RBTree_IEcoConnectionPointContainer_FindConnectionPoint(/* in */
        struct IEcoConnectionPointContainer *me, /* in */ const UGUID *riid, /* out */
        struct IEcoConnectionPoint **ppCP) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *) - sizeof(struct IEcoUnknown *));
    int16_t result = 0;

    if (me == 0 || ppCP == 0) {
        return -1;
    }

    if (!IsEqualUGUID(riid, &IID_IEcoLab1Events)) {
        *ppCP = 0;
        /* CONNECT_E_NOCONNECTION */
        return -1;
    }

    if (pCMe->m_pISinkCP == 0) {
        /* E_FAIL */
        return -1;
    }

    pCMe->m_pISinkCP->m_pVTblICP->AddRef((struct IEcoConnectionPoint *) &pCMe->m_pISinkCP->m_pVTblICP);
    *ppCP = (struct IEcoConnectionPoint *) &pCMe->m_pISinkCP->m_pVTblICP;

    return 0;
}


/*
 *
 * <сводка>
 *   Функция Fire_OnPrintTreeCallback
 * </сводка>
 *
 * <описание>
 *   Функция вызова обратного интерфейса
 * </описание>
 *
 */
int16_t
ECOCALLMETHOD CEcoLab1RBTree_Fire_OnPrintTreeCallback(/* in */ struct IEcoLab1 *me, /* in */
                                                               struct RBNode *root, /* in */
                                                               int16_t bClear) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;
    int16_t result = 0;
    IEcoEnumConnections *pEnum = 0;
    IEcoLab1Events *pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0) {
        result = ((IEcoConnectionPoint *) pCMe->m_pISinkCP)->pVTbl->EnumConnections(
                (IEcoConnectionPoint *) pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0)) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void **) &pIEvents);
                if ((result == 0) && (pIEvents != 0)) {
                    result = pIEvents->pVTbl->OnPrintTreeCallback(pIEvents, root, bClear);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

/*
 *
 * <сводка>
 *   Функция Fire_OnTreeInsertStepCallback
 * </сводка>
 *
 * <описание>
 *   Функция вызова обратного интерфейса
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1RBTree_Fire_OnPrintTreeWithStatus(/* in */ struct IEcoLab1 *me,
        /* in */ struct RBNode *root,
        /* in */ struct RBNode *currNode,
        /* in */ int16_t isInserted,
        /* in */ void *p_Element) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;
    int16_t result = 0;
    IEcoEnumConnections *pEnum = 0;
    IEcoLab1Events *pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0) {
        result = ((IEcoConnectionPoint *) pCMe->m_pISinkCP)->pVTbl->EnumConnections(
                (IEcoConnectionPoint *) pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0)) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void **) &pIEvents);
                if ((result == 0) && (pIEvents != 0)) {
                    result = pIEvents->pVTbl->OnPrintTreeWithStatusCallback(pIEvents, root, currNode,
                                                                            isInserted, p_Element);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}

/*
 *
 * <сводка>
 *   Функция Fire_OnInorderTreeTraverseCallback
 * </сводка>
 *
 * <описание>
 *   Функция вызова обратного интерфейса
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1RBTree_Fire_OnInorderTreeTraverseCallback(/* in */ struct IEcoLab1 *me, /* in */
                                                                                 struct RBNode *root) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;
    int16_t result = 0;
    IEcoEnumConnections *pEnum = 0;
    IEcoLab1Events *pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0) {
        result = ((IEcoConnectionPoint *) pCMe->m_pISinkCP)->pVTbl->EnumConnections(
                (IEcoConnectionPoint *) pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0)) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void **) &pIEvents);
                if ((result == 0) && (pIEvents != 0)) {
                    result = pIEvents->pVTbl->OnInorderTreeTraversalCallback(pIEvents, root);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
}


int16_t ECOCALLMETHOD CEcoLab1RBTree_Fire_OnPrintTreeWithStatusCallback(/* in */ struct IEcoLab1* me,
        /* in */ struct RBNode* root,
        /* in */ struct RBNode* currNode,
        /* in */ int16_t isInserted,
        /* in */ void* p_Element) {
    CEcoLab1RBTree* pCMe = (CEcoLab1RBTree*) me;
    int16_t result = 0;
    IEcoEnumConnections* pEnum = 0;
    IEcoLab1Events* pIEvents = 0;
    EcoConnectionData cd;

    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pISinkCP != 0) {
        result = ((IEcoConnectionPoint*) pCMe->m_pISinkCP)->pVTbl->EnumConnections((IEcoConnectionPoint*) pCMe->m_pISinkCP, &pEnum);
        if ((result == 0) && (pEnum != 0)) {
            while (pEnum->pVTbl->Next(pEnum, 1, &cd, 0) == 0) {
                result = cd.pUnk->pVTbl->QueryInterface(cd.pUnk, &IID_IEcoLab1Events, (void**) &pIEvents);
                if ((result == 0) && (pIEvents != 0)) {
                    result = pIEvents->pVTbl->OnPrintTreeWithStatusCallback(pIEvents, root, currNode, isInserted, p_Element);
                    pIEvents->pVTbl->Release(pIEvents);
                }
                cd.pUnk->pVTbl->Release(cd.pUnk);
            }
            pEnum->pVTbl->Release(pEnum);
        }
    }
    return result;
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
RBNode *insert(struct IEcoLab1 *me, RBNode **root, void *val, size_t elem_size,
               int (__cdecl *compare)(const void *, const void *)) {
    CEcoLab1RBTree* pCMe = (CEcoLab1RBTree*) me;
    RBNode *current = *root;
    RBNode *inserted;

    CEcoLab1RBTree_Fire_OnPrintTreeCallback(me, *root, 1);

    if (*root == 0) {
        *root = newRBNode(pCMe, 0, val, elem_size);
        CEcoLab1RBTree_Fire_OnPrintTreeWithStatusCallback(me, *root, *root, 1, val);
        return *root;
    }
    while (current != 0) {
        CEcoLab1RBTree_Fire_OnPrintTreeWithStatusCallback(me, *root, current, 0, val);
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

    CEcoLab1RBTree_Fire_OnPrintTreeWithStatusCallback(me, *root, current, 1, val);

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
        struct IEcoLab1 *me,
        char *start_ptr,
        size_t elem_count,
        size_t elem_size,
        int (__cdecl *compare)(const void *, const void *)
) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) me;
    RBNode *root = 0;
    size_t byte_count = elem_size * elem_count;
    char *curr_ptr = start_ptr;
    char *end_ptr = start_ptr + byte_count;

    /* Строим КЧД */
    for (; curr_ptr < end_ptr; curr_ptr += elem_size) {
        root = insert(me, &root, curr_ptr, elem_size, compare);
    }

    CEcoLab1RBTree_Fire_OnPrintTreeCallback(me, root, 0);
    /* Получаем отсортированный массив */
    infixNonRecTraversal(root, &start_ptr, elem_size);
    CEcoLab1RBTree_Fire_OnInorderTreeTraverseCallback(me, root);
    CEcoLab1RBTree_Fire_OnPrintTreeCallback(me, root, 2);

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
    treeSort(me, pData, elem_count, elem_size, compare);

    return 0;
}

int16_t ECOCALLMETHOD CEcoLab1RBTree_IEcoCalculatorY_QueryInterface(
        /* in */ struct IEcoCalculatorY *me, /* in */ const UGUID *riid, /* out */ void **ppv
) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *));
    IEcoUnknown *nonDelegating = (IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk;
    int16_t result;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab1RBTree_IEcoCalculatorY_AddRef(/* in */ struct IEcoCalculatorY *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab1RBTree_IEcoCalculatorY_Release(/* in */ struct IEcoCalculatorY *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
}

int32_t ECOCALLMETHOD CEcoLab1RBTree_Multiplication(
        /* in */ struct IEcoCalculatorY *me, /* in */ int16_t a, /* in */ int16_t b
) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *));
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Multiplication(pCMe->m_pIY, a, b);
    }

    return result;
}

int16_t
ECOCALLMETHOD CEcoLab1RBTree_Division(/* in */ struct IEcoCalculatorY *me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *));
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pIY != 0) {
        result = pCMe->m_pIY->pVTbl->Division(pCMe->m_pIY, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1RBTree_IEcoCalculatorX_QueryInterface(/* in */ struct IEcoCalculatorX *me, /* in */
                                                                             const UGUID *riid, /* out */ void **ppv) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *));
    IEcoUnknown *nonDelegating = (IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk;
    int16_t result;

    /* Проверка указателей */
    if (me == 0 || ppv == 0) {
        return -1;
    }

    result = nonDelegating->pVTbl->QueryInterface(nonDelegating, riid, ppv);
    if (result != 0 && pCMe->m_pIUnkOuter != 0) {
        result = pCMe->m_pIUnkOuter->pVTbl->QueryInterface(pCMe->m_pIUnkOuter, riid, ppv);
    }
    return result;
}

uint32_t ECOCALLMETHOD CEcoLab1RBTree_IEcoCalculatorX_AddRef(/* in */ struct IEcoCalculatorX *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return pCMe->m_pVTblINondelegatingUnk->AddRef((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
}

uint32_t ECOCALLMETHOD CEcoLab1RBTree_IEcoCalculatorX_Release(/* in */ struct IEcoCalculatorX *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    return pCMe->m_pVTblINondelegatingUnk->Release((IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk);
}

int32_t
ECOCALLMETHOD CEcoLab1RBTree_Addition(/* in */ struct IEcoCalculatorX *me, /* in */ int16_t a, /* in */ int16_t b) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *));
    int32_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Addition(pCMe->m_pIX, a, b);
    }

    return result;
}

int16_t ECOCALLMETHOD CEcoLab1RBTree_Subtraction(
        /* in */ struct IEcoCalculatorX *me, /* in */ int16_t a, /* in */ int16_t b
) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *));
    int16_t result = 0;

    /* Проверка указателей */
    if (me == 0) {
        return -1;
    }

    if (pCMe->m_pIX != 0) {
        result = pCMe->m_pIX->pVTbl->Subtraction(pCMe->m_pIX, a, b);
    }

    return result;
}


/* Функция QueryInterface для интерфейса IEcoLab1 */
int16_t ECOCALLMETHOD CEcoLab1RBTree_NondelegatingQueryInterface(/* in */ struct IEcoUnknown *me, /* in */
                                                                          const UGUID *riid, /* out */ void **ppv) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *));
    int16_t result;
    if (me == 0 || ppv == 0) {
        return -1;
    }
    if (IsEqualUGUID(riid, &IID_IEcoLab1)) {
        *ppv = &pCMe->m_pVTblIEcoLab1;
        ++pCMe->m_cRef;
    } else if (IsEqualGUID(riid, &IID_IEcoCalculatorY)) {
        *ppv = &pCMe->m_pVTblIY;
        ++pCMe->m_cRef;
    } else if (IsEqualGUID(riid, &IID_IEcoCalculatorX)) {
        // передать запрос агрегируемому компоненту B
        if (pCMe->m_pInnerUnknown != 0) {
            // это неделигирующий unknown агрегируемого компонента
            result = pCMe->m_pInnerUnknown->pVTbl->QueryInterface(pCMe->m_pInnerUnknown, riid, ppv);
            return result;
        } else {
            *ppv = &pCMe->m_pVTblIX;
            ++pCMe->m_cRef;
        }
    } else if (IsEqualUGUID(riid, &IID_IEcoConnectionPointContainer)) {
        *ppv = &pCMe->m_pVTblICPC;
        pCMe->m_pVTblIEcoLab1->AddRef((IEcoLab1 *) pCMe);
    } else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = &pCMe->m_pVTblINondelegatingUnk;
        ++pCMe->m_cRef;
    } else {
        *ppv = 0;
        return -1;
    }
    return 0;
}

/* Функция AddRef для интерфейса IEcoLab1 */
uint32_t ECOCALLMETHOD CEcoLab1RBTree_NondelegatingAddRef(/* in */ struct IEcoUnknown *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    return ++pCMe->m_cRef;
}

/* Функция Release для интерфейса IEcoLab1 */
uint32_t ECOCALLMETHOD CEcoLab1RBTree_NondelegatingRelease(/* in */ struct IEcoUnknown *me) {
    CEcoLab1RBTree *pCMe = (CEcoLab1RBTree *) ((uint64_t) me - sizeof(struct IEcoLab1 *) -
                                               sizeof(struct IEcoCalculatorY *) -
                                               sizeof(struct IEcoCalculatorX *));

    /* Проверка указателя */
    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        if (pCMe->m_pInnerUnknown != 0) {
            if (pCMe->m_pInnerUnknown->pVTbl->Release(pCMe->m_pInnerUnknown) == 0) {
                pCMe->m_pInnerUnknown = 0;
            } else {
                pCMe->m_cRef = 1;
            }
        }
        if (pCMe->m_cRef == 0) {
            deleteCEcoLab1RBTree((IEcoLab1 *) pCMe);
        }
        return 0;
    }
    return pCMe->m_cRef;
}

/* Виртуальная таблица методов для IEcoLab1 */
IEcoLab1VTbl g_x277FC00C35624096AFCFC125B94EEC90VTbl = {
        CEcoLab1RBTree_QueryInterface,
        CEcoLab1RBTree_AddRef,
        CEcoLab1RBTree_Release,
        CEcoLab1RBTree_qsort
};

IEcoCalculatorXVTbl g_x9322111622484742AE0682819447843DVTblLab1 = {
        CEcoLab1RBTree_IEcoCalculatorX_QueryInterface,
        CEcoLab1RBTree_IEcoCalculatorX_AddRef,
        CEcoLab1RBTree_IEcoCalculatorX_Release,
        CEcoLab1RBTree_Addition,
        CEcoLab1RBTree_Subtraction
};

IEcoCalculatorYVTbl g_xBD6414C29096423EA90C04D77AFD1CADVTblLab1 = {
        CEcoLab1RBTree_IEcoCalculatorY_QueryInterface,
        CEcoLab1RBTree_IEcoCalculatorY_AddRef,
        CEcoLab1RBTree_IEcoCalculatorY_Release,
        CEcoLab1RBTree_Multiplication,
        CEcoLab1RBTree_Division
};

IEcoUnknownVTbl g_x000000000000000000000000000000AAVTblLab1 = {
        CEcoLab1RBTree_NondelegatingQueryInterface,
        CEcoLab1RBTree_NondelegatingAddRef,
        CEcoLab1RBTree_NondelegatingRelease
};

/* Create Virtual Table IEcoConnectionPointContainer */
IEcoConnectionPointContainerVTbl g_x0000000500000000C000000000000046VTblCPC = {
        CEcoLab1RBTree_IEcoConnectionPointContainer_QueryInterface,
        CEcoLab1RBTree_IEcoConnectionPointContainer_AddRef,
        CEcoLab1RBTree_IEcoConnectionPointContainer_Release,
        CEcoLab1RBTree_IEcoConnectionPointContainer_EnumConnectionPoints,
        CEcoLab1RBTree_IEcoConnectionPointContainer_FindConnectionPoint
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
    IEcoUnknown *pOuterUnknown = (IEcoUnknown *) me;
    int16_t result = -1;

    if (me == 0) {
        return result;
    }

    /* Сохранение указателя на системный интерфейс */
    pCMe->m_pISys = (IEcoSystem1 *) pIUnkSystem;

    /* Получение интерфейса для работы с интерфейсной шиной */
    result = pCMe->m_pISys->pVTbl->QueryInterface(pCMe->m_pISys, &IID_IEcoInterfaceBus1, (void **) &pIBus);

    /* Пробуем агрегировать CEcoCalculatorB для доступа к интерфейсу IEcoCalculatorX */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorB, pOuterUnknown, &IID_IEcoUnknown,
                                          (void **) &pCMe->m_pInnerUnknown);
    if (result != 0 || pCMe->m_pInnerUnknown == 0) {
        /* Если не удалось агрегировать CEcoCalculatorB, то включаем интерфейс IEcoCalculatorX из CEcoCalculatorA */
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorA, 0, &IID_IEcoCalculatorX,
                                              (void **) &pCMe->m_pIX);
    }

    /* Пробуем включить интерфейс IEcoCalculatorY из CEcoCalculatorD */
    result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorD, 0, &IID_IEcoCalculatorY, (void **) &pCMe->m_pIY);
    if (result != 0 || pCMe->m_pIY == 0) {
        /* Если не удалось включить из CEcoCalculatorD, то включаем интерфейс IEcoCalculatorY из CEcoCalculatorE */
        result = pIBus->pVTbl->QueryComponent(pIBus, &CID_EcoCalculatorE, 0, &IID_IEcoCalculatorY,
                                              (void **) &pCMe->m_pIY);
    }

    /* Создание точки подключения */
    result = createCEcoLab1ConnectionPoint((IEcoUnknown *) pCMe->m_pISys,
                                           (IEcoConnectionPointContainer *) &pCMe->m_pVTblICPC, &IID_IEcoLab1Events,
                                           (IEcoConnectionPoint **) &(pCMe->m_pISinkCP));
    if (result == 0 && pCMe->m_pISinkCP != 0) {
        result = 0;
    }

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

    /* Создание таблицы функций интерфейса IEcoConnectionPointContainer */
//    pCMe->m_pVTblICPC = &g_x0000000500000000C000000000000046VTblCPC;

    /* Создание таблицы функций интерфейса IEcoCalculatorX */
    pCMe->m_pVTblIX = &g_x9322111622484742AE0682819447843DVTblLab1;

    /* Создание таблицы функций интерфейса IEcoCalculatorY */
    pCMe->m_pVTblIY = &g_xBD6414C29096423EA90C04D77AFD1CADVTblLab1;

    /* Неделегирующий интерфейс IEcoUnknown */
    pCMe->m_pVTblINondelegatingUnk = &g_x000000000000000000000000000000AAVTblLab1;

    /* Создание таблицы функций интерфейса IEcoConnectionPointContainer */
    pCMe->m_pVTblICPC = &g_x0000000500000000C000000000000046VTblCPC;

    pCMe->m_pIUnkOuter = 0;

    /* Если не агрегируется, использовать неделигирующий интерфейс IEcoUnknown */
    if (pIUnkOuter != 0) {
        pCMe->m_pIUnkOuter = pIUnkOuter;
    } else {
        pCMe->m_pIUnkOuter = (IEcoUnknown *) &pCMe->m_pVTblINondelegatingUnk;
    }

    /* Инициализация данных */
    pCMe->m_Name = 0;

    pCMe->m_pIY = 0;

    pCMe->m_pIX = 0;

    pCMe->m_pInnerUnknown = 0;

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
        if (pCMe->m_pIX != 0) {
            pCMe->m_pIX->pVTbl->Release(pCMe->m_pIX);
        }
        if (pCMe->m_pIY != 0) {
            pCMe->m_pIY->pVTbl->Release(pCMe->m_pIY);
        }
        if (pCMe->m_pISys != 0) {
            pCMe->m_pISys->pVTbl->Release(pCMe->m_pISys);
        }
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
}