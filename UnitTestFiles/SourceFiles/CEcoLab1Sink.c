/*
 * <кодировка символов>
 *   Cyrillic (UTF-8 with signature) - Codepage 65001
 * </кодировка символов>
 *
 * <сводка>
 *   CEcoLab1Sink
 * </сводка>
 *
 * <описание>
 *   Данный исходный код описывает реализацию интерфейсов CEcoLab1Sink
 * </описание>
 *
 * <автор>
 *   Copyright (c) 2016 Vladimir Bashev. All rights reserved.
 * </автор>
 *
 */

#include "CEcoLab1Sink.h"
#include "IEcoConnectionPointContainer.h"

#include "CEcoLab1RBTree.h"
#include "Utils.h"

#include <stdio.h>



/*
 *
 * <сводка>
 *   Функция QueryInterface
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_QueryInterface(/* in */ struct IEcoLab1Events* me, /* in */ const UGUID* riid, /* out */ void** ppv) {
    if (IsEqualUGUID(riid, &IID_IEcoLab1Events)) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    } else if (IsEqualUGUID(riid, &IID_IEcoUnknown)) {
        *ppv = me;
        me->pVTbl->AddRef(me);
        return 0;
    }

    *ppv = 0;

    return -1;
}

/*
 *
 * <сводка>
 *   Функция AddRef
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_AddRef(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) me;

    if (me == 0) {
        return -1;
    }

    pCMe->m_cRef++;
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция Release
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
uint32_t ECOCALLMETHOD CEcoLab1Sink_Release(/* in */ struct IEcoLab1Events* me) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) me;

    if (me == 0) {
        return -1;
    }

    /* Уменьшение счетчика ссылок на компонент */
    --pCMe->m_cRef;

    /* В случае обнуления счетчика, освобождение данных экземпляра */
    if (pCMe->m_cRef == 0) {
        deleteCEcoLab1Sink((IEcoLab1Events*) pCMe);
        return 0;
    }
    return pCMe->m_cRef;
}

/*
 *
 * <сводка>
 *   Функция PrintTree
 * </сводка>
 *
 * <описание>
 *   Функция для вывода бинарного дерева "на боку"
 * </описание>
 *
 */
#define SPACE 10
void ECOCALLMETHOD PrintTree(/* in */ struct IEcoLab1Events* me, /* in */ struct RBNode* p_Node, /* in */ int32_t curr_space) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) me;
    int32_t i;

    if (p_Node == 0 || pCMe->m_printFunc == 0) {
        return;
    }

    curr_space += SPACE;

    PrintTree(me, p_Node->right, curr_space);

    printf("\n");
    for (i = SPACE; i < curr_space; ++i) {
        printf(" ");
    }

    if (p_Node->color == 0) {
        pCMe->m_printFunc(p_Node->val);
        printf(" (%s)\n", BLACK_NODE);
    } else {
        pCMe->m_printFunc(p_Node->val);
        printf(" (%s)\n", RED_NODE);
    }

    PrintTree(me, p_Node->left, curr_space);
}

/*
 *
 * <сводка>
 *   Функция PrintTreeWithStatus
 * </сводка>
 *
 * <описание>
 *   Функция для вывода бинарного дерево "на боку" с выделенной вершиной
 *   Возможно выделение текущей вершины обхода или новой вставленной вершины в зависимости от параметра isInserted
 * </описание>
 *
 */
void ECOCALLMETHOD PrintTreeWithStatus(/* in */ struct IEcoLab1Events* me,
        /* in */ struct RBNode* p_Node,
        /* in */ struct RBNode* currNode,
        /* in */ int32_t currSpace,
        /* in */ int16_t isInserted) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) me;
    int32_t i;

    if (p_Node == 0 || currNode == 0 || pCMe->m_printFunc == 0) {
        return;
    }

    currSpace += SPACE;

    PrintTreeWithStatus(me, p_Node->right, currNode, currSpace, isInserted);

    printf("\n");
    for (i = SPACE; i < currSpace; ++i) {
        printf(" ");
    }

    if (p_Node == currNode) {
        if (isInserted == 0) {
            if (p_Node->color == 0) {
                pCMe->m_printFunc(p_Node->val);
                printf(" (%s)*%s*\n", BLACK_NODE, SELECTED_NODE);
            } else {
                pCMe->m_printFunc(p_Node->val);
                printf(" (%s)*%s*\n", RED_NODE, SELECTED_NODE);
            }
        } else {
            if (p_Node->color == 0) {
                pCMe->m_printFunc(p_Node->val);
                printf(" (%s)!%s!\n", BLACK_NODE, INSETED_NODE);
            } else {
                pCMe->m_printFunc(p_Node->val);
                printf(" (%s)!%s!\n", RED_NODE, INSETED_NODE);
            }
        }
    } else if (p_Node->color == 0) {
        pCMe->m_printFunc(p_Node->val);
        printf(" (%s)\n", BLACK_NODE);
    } else {
        pCMe->m_printFunc(p_Node->val);
        printf(" (%s)\n", RED_NODE);
    }

    PrintTreeWithStatus(me, p_Node->left, currNode, currSpace, isInserted);
}

/*
 *
 * <сводка>
 *   Функция inorderTreeTraversal
 * </сводка>
 *
 * <описание>
 *   Функция для инфиксного (in-order) обхода бинарного дерева
 *   с выделением текущей вершины
 * </описание>
 *
 */
void ECOCALLMETHOD inorderTreeTraversal(/* in */ struct IEcoLab1Events* me, struct RBNode* root, struct RBNode* p_Traveler) {
    if (p_Traveler != 0) {
        inorderTreeTraversal(me, root, p_Traveler->left);
        printf("\n\n");
        printf("Inorder tree traversal to get sorted array\n");
        PrintTreeWithStatus(me, root, p_Traveler, 0, 0);
        waitForEnterOrCPressed();
        inorderTreeTraversal(me, root, p_Traveler->right);
    }
}

/*
 *
 * <сводка>
 *   Функция OnPrintTreeCallback
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова для вывода дерева "на боку"
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_OnPrintTreeCallback(/* in */ struct IEcoLab1Events* me, /* in */ struct RBNode* root, /* in */ int16_t mode) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) me;

    if (me == 0 || pCMe->m_printFunc == 0) {
        return -1;
    }

    if (root == 0) {
        return 0;
    } else {
        if (mode == 0) {
            printf("Current Tree state:\n");
        } else if (mode == 1) {
            printf("Tree after balancing:\n");
        } else if (mode == 2) {
            printf("Final Tree:\n");
        }

        PrintTree(me, root, 0);
    }

    printf("_____________________________________\n");
    if (mode == 0 || mode == 1) {
        waitForEnterOrCPressed();
    }

    return 0;
}

/*
 *
 * <сводка>
 *   Функция OnPrintTreeWithStatusCallback
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова для вывода дерева с выделенной вершиной
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_OnPrintTreeWithStatusCallback(/* in */ struct IEcoLab1Events* me,
        /* in */ struct RBNode* root,
        /* in */ struct RBNode* currNode,
        /* in */ int16_t isInserted,
        /* in */ void* p_Element) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) me;

    if (me == 0 || pCMe->m_printFunc == 0) {
        return -1;
    }

    if (root == 0) {
        return 0;
    } else {
        printf("Finding place for: ");
        pCMe->m_printFunc(p_Element);
        printf("\n");
        PrintTreeWithStatus(me, root, currNode, 0, isInserted);
        waitForEnterOrCPressed();
    }

    printf("\n\n");

    return 0;
}

/*
 *
 * <сводка>
 *   Функция OnInorderTreeTraversalCallback
 * </сводка>
 *
 * <описание>
 *   Функция обратного вызова для инфиксного (in-order) обхода дерева
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_OnInorderTreeTraversalCallback(/* in */ struct IEcoLab1Events* me, /* in */ struct RBNode* root) {
    if (me == 0) {
        return -1;
    }

    inorderTreeTraversal(me, root, root);

    printf("\n\n");

    return 0;
}

/*
 *
 * <сводка>
 *   Функция Advise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_Advise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1* pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    int16_t result = 0;

    result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**) &pCPC);

    if (result == 0 && pCPC != 0) {
        result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
        pCPC->pVTbl->Release(pCPC);
        pCPC = 0;
        if (result == 0 && pCP != 0) {

            result = pCP->pVTbl->Advise(pCP, (IEcoUnknown*) me, &me->m_cCookie);
            pCP->pVTbl->Release(pCP);
            pCP = 0;
        }
    }

    return result;
}

/*
 *
 * <сводка>
 *   Функция Unadvise
 * </сводка>
 *
 * <описание>
 *   Функция
 * </описание>
 *
 */
int16_t ECOCALLMETHOD CEcoLab1Sink_Unadvise(/* in */ struct CEcoLab1Sink* me, /* in */IEcoLab1* pIEcoLab1) {
    IEcoConnectionPointContainer* pCPC = 0;
    IEcoConnectionPoint* pCP = 0;
    int16_t result = 0;

    if (me->m_cCookie) {
        result = pIEcoLab1->pVTbl->QueryInterface(pIEcoLab1, &IID_IEcoConnectionPointContainer, (void**) &pCPC);
        if (result == 0) {
            result = pCPC->pVTbl->FindConnectionPoint(pCPC, &IID_IEcoLab1Events, &pCP);
            pCPC->pVTbl->Release(pCPC);
            pCPC = 0;
            if (result == 0) {
                result = pCP->pVTbl->Unadvise(pCP, me->m_cCookie);
                pCP->pVTbl->Release(pCP);
                pCP = 0;
            }
        }
    }
    return result;
}

int16_t ECOCALLMETHOD CEcoLab1Sink_SetPrintFunction(/* in */ struct CEcoLab1Sink* me, /* in */ void (ECOCDECLMETHOD* fnPrinter)(const void*)) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) me;

    if (me == 0) {
        return -1;
    }

    pCMe->m_printFunc = fnPrinter;
    return 0;
}

/* Create Virtual Table IEcoLab1VTblEvents */
IEcoLab1VTblEvents g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents = {
        CEcoLab1Sink_QueryInterface,
        CEcoLab1Sink_AddRef,
        CEcoLab1Sink_Release,
        CEcoLab1Sink_OnPrintTreeCallback,
        CEcoLab1Sink_OnPrintTreeWithStatusCallback,
        CEcoLab1Sink_OnInorderTreeTraversalCallback
};

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
int16_t ECOCALLMETHOD createCEcoLab1Sink(/* in */ IEcoMemoryAllocator1* pIMem, /* out */ IEcoLab1Events** ppIEcoLab1Events) {
    int16_t result = -1;
    CEcoLab1Sink* pCMe = 0;

    /* Проверка указателей */
    if (ppIEcoLab1Events == 0 || pIMem == 0) {
        return result;
    }

    /* Выделение памяти для данных экземпляра */
    pCMe = (CEcoLab1Sink*) pIMem->pVTbl->Alloc(pIMem, sizeof(CEcoLab1Sink));

    /* Сохранение указателя на интерфейс для работы с памятью */
    pCMe->m_pIMem = pIMem;
    pCMe->m_pIMem->pVTbl->AddRef(pCMe->m_pIMem);

    /* Установка счетчика ссылок на компонент */
    pCMe->m_cRef = 1;

    /* Создание таблицы функций интерфейса IEcoP2PEvents */
    pCMe->m_pVTblIEcoLab1Events = &g_x2D2E3B9214F248A6A09ECB494B59C795VTblEvents;
    pCMe->SetPrintFunction = CEcoLab1Sink_SetPrintFunction;

    *ppIEcoLab1Events = (IEcoLab1Events*) pCMe;

    return 0;
};

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
void ECOCALLMETHOD deleteCEcoLab1Sink(IEcoLab1Events* pIEcoLab1Events) {
    CEcoLab1Sink* pCMe = (CEcoLab1Sink*) pIEcoLab1Events;
    IEcoMemoryAllocator1* pIMem = 0;

    if (pIEcoLab1Events != 0) {
        pIMem = pCMe->m_pIMem;
        /* Освобождение */
        pIMem->pVTbl->Free(pIMem, pCMe);
        pIMem->pVTbl->Release(pIMem);
    }
};
