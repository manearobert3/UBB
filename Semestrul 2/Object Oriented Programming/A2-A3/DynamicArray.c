#include "DynamicArray.h"
#include <stdlib.h>
#include <assert.h>

DynamicArray* createDynamicArray(int capacity, destroyer destroyFunction)
{
    DynamicArray* array = malloc(sizeof(DynamicArray));
    if (array == NULL)
        return NULL;
    array->length = 0;
    array->capacity = capacity;
    array->elements = malloc(sizeof(TElem) * capacity); 
    if (array->elements == NULL)
        return NULL;
    array->destroyFunction = destroyFunction;
    return array;
}

void destroyDynamicArray(DynamicArray* array)
{
    int i;
    for (i = 0; i < array->length; i++) {
        array->destroyFunction(array->elements[i]);
    }
    free(array->elements);
    free(array);
}

int getLength(DynamicArray* array)
{
    return array->length;
}

TElem* get(DynamicArray* array, int pos)
{
    return array->elements[pos];
}

void resize(DynamicArray* array) {
    
    if (array == NULL)
        return;
    int aux_cap = array->capacity * 2;
    TElem* aux = realloc(array->elements, aux_cap * sizeof(TElem));
    if (aux == NULL)
        return;
    array->capacity = aux_cap;
    array->elements = aux;

}
void add(DynamicArray* array, TElem e)
{
    if (array == NULL)
        return;
    if (array->capacity == array->length) {
        resize(array);
    }
    array->elements[array->length++] = e;
}

void removeElement(DynamicArray* array, int position) {
    int i;
    free(array->elements[position]);
    for (i = position; i < array->length-1; i++)
        array->elements[i] = array->elements[i + 1];
    array->length--;
    
}

void testDynamicArray() {
    DynamicArray* array = createDynamicArray(2, destroyOffer);
    assert(array->length == 0);
    assert(array->capacity == 2);

    Offer* o1 = createOffer("mountain","brasov","14/07/2018",180);
    Offer* o2 = createOffer("seaside","constanta","26/11/2020",800);
    add(array, o1);
    add(array, o2);
    assert(array->length == 2);
    assert(array->capacity == 2);

    Offer* o3 = createOffer("citybreak", "china","17/02/2021", 500);
    add(array, o3);
    assert(array->capacity == 4);
    removeElement(array, 1);
    assert(array->length == 2);


    destroyDynamicArray(array);
}
