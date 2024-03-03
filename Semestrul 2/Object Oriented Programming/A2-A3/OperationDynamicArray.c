#include "OperationDynamicArray.h"
#include <stdlib.h>
#include <assert.h>
#include <stdio.h>

OperationDynamicArray* createOperationDynamicArray(int capacity, destroyer destroyFunction)
{
    OperationDynamicArray* arrayOperation = malloc(sizeof(OperationDynamicArray));
    if (arrayOperation == NULL)
        return NULL;
    arrayOperation->length = 0;
    arrayOperation->index = 0;
    arrayOperation->capacity = capacity;
    arrayOperation->operationType = 0;
    arrayOperation->elements = malloc(sizeof(TElem) * capacity);
    if (arrayOperation->elements == NULL)
        return NULL;
    arrayOperation->arrayOfCommands= malloc(sizeof(int) * capacity);
    if (arrayOperation->arrayOfCommands== NULL)
        return NULL;
    arrayOperation->destroyFunction = destroyFunction;
    return arrayOperation;
}

void destroyOperationDynamicArray(OperationDynamicArray* currentArray)
{
    int i;
    for (i = 0; i < currentArray->length; i++) {
        currentArray->destroyFunction(currentArray->elements[i]);
    }
    free(currentArray->elements);
    free(currentArray);
}

void destroyOperation(OperationDynamicArray* currentArray) {
    for (int index = currentArray->index + 1; index < currentArray->capacity; index++) {
        currentArray->destroyFunction(currentArray->elements[index]);
    }
}

//void printOperation(OperationDynamicArray* currentArray) {
//    int index;
//    for (index = 0; index < currentArray->length; index++) {
//        printf("%d", currentArray->elements[index]);
//    }
//}

int getLengthOperationDynamicArray(OperationDynamicArray* currentArray)
{
    return currentArray->length;
}

TElem* getOperations(OperationDynamicArray* currentArray, int pos)
{
    return currentArray->elements[pos];
}

void resizeOperation(OperationDynamicArray* currentArray) {

    if (currentArray == NULL)
        return;
    int aux_cap = currentArray->capacity * 2;
    TElem* aux = (TElem*)realloc(currentArray->elements, aux_cap * sizeof(TElem));
    if (aux == NULL)
        return;
    currentArray->capacity = aux_cap;
    currentArray->elements = aux;

}

void popOperation(OperationDynamicArray* currentArray) {
    if (currentArray == NULL)
        return;
    currentArray->length--;
    currentArray->elements[currentArray->length] = 0;
    currentArray->operationType[&currentArray->length] = 0;
}

TElem* returnLastOperation(OperationDynamicArray* currentArray) {
    if (currentArray == NULL)
        return;
    return currentArray->elements[currentArray->length];
}

TElem* returnLastOperationType(OperationDynamicArray* currentArray) {
    if (currentArray == NULL)
        return;
    return currentArray->arrayOfCommands[currentArray->length];
}

void addToOperationArray(OperationDynamicArray* currentArray, TElem element, int operationType)
{
    if (currentArray == NULL)
        return;
    if (currentArray->capacity == currentArray->length) {
        resize(currentArray);
    }
    currentArray->arrayOfCommands[currentArray->length] = operationType;
    currentArray->elements[currentArray->length] = element;
    currentArray->length++;
    currentArray->index++;
}

void addToOperationArrayUpdate(OperationDynamicArray* currentArray, TElem elementInitial ,TElem elementAfterUpdate, int operationType)

{
    if (currentArray == NULL)
        return;
    if (currentArray->capacity == currentArray->length) {
        resize(currentArray);
    }
    currentArray->arrayOfCommands[currentArray->length] = operationType;
    currentArray->elements[currentArray->length] = elementInitial;
 
    if (currentArray->capacity == currentArray->length) {
        resize(currentArray);
    }
    currentArray->arrayOfCommands[currentArray->length] = operationType;
    currentArray->elements[currentArray->length+1] = elementAfterUpdate;
    currentArray->length++;
    currentArray->index++;
}

void removeElementOperationArray(OperationDynamicArray* currentArray, int poz) {
    int index;
    free(currentArray->elements[currentArray->index]);
    for (index = currentArray->index; index < currentArray->length; index++)
        currentArray->elements[index] = currentArray->elements[index + 1];
    currentArray->length--;
    currentArray->index--;

}

//void testDynamicArray() {
//    OperationDynamicArray* arr = createOperationDynamicArray(2, destroyOffer);
//    assert(arr->length == 0);
//    assert(arr->capacity == 2);
//
//    Offer* o1 = createOffer("mountain", "brasov", "14/07/2018", 180);
//    Offer* o2 = createOffer("seaside", "constanta", "26/11/2020", 800);
//    add(arr, o1);
//    add(arr, o2);
//    assert(arr->length == 2);
//    assert(arr->capacity == 2);
//
//    Offer* o3 = createOffer("citybreak", "china", "17/02/2021", 500);
//    add(arr, o3);
//    assert(arr->capacity == 4);
//    removeElement(arr, 1);
//    assert(arr->length == 2);
//
//
//    destroyDynamicArray(arr);
//}
