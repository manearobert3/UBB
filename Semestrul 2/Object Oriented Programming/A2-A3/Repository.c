#include "Repository.h"
#include <stdlib.h>
#include <assert.h>
Repository* createRepo()
{
    Repository* repo = malloc(sizeof(Repository));
    if (repo == NULL)
        return repo;
    repo->array = createDynamicArray(15, destroyOffer);
    //repo->arrOperation = createOperationDynamicArray(10, destroyOffer);
    return repo;
}


// frees the repository
void destroyRepository(Repository* repo) {
    destroyDynamicArray(repo->array);
    free(repo);
}

//void addToOperationList(Repository* repo) {
//    addToOperationArray(repo->arrOperation, repo->arr, repo->arrOperation->index);
//}
//
//void undoOperation(Repository* repo) {
//    destroyRepository(repo->arr);
//    repo=createRepo();
//    repo->arr = &repo->arrOperation[(repo->arrOperation->index) - 1];
//    (repo->arrOperation->index)--;
//}

Repository* makeCopyOfRepo(Repository* repoToBeCopied) {
    Repository* newRepository = createRepo();
    for (int index = 0; index < getSize(repoToBeCopied); index++) {
        addOffer(newRepository, getOfferByIndex(repoToBeCopied, index));
    }
    return newRepository;


}

//returns an int, the length of the repository (the number of elements in repo);
int getSize(Repository* repo) {
    return repo->array->length;
}

Offer* getOfferByIndex(Repository* repo, int index) {
    return &repo->array[index];
}

//adds an offer to the repository and verifies if it can fit on the previously allocated capacity of the dynamic array
int addOffer(Repository* repo, Offer* newOffer) {
    if (findOffer(repo, newOffer) == 1) {
        return 0;
    }   
    add(repo->array, newOffer);
    return 1;
}

int addOfferUndo(Repository* repo, Offer* newOffer) {
    add(repo->array, newOffer);
    return 1;
}
//updates an offer based on the input from the user
// first finds the offer based on destination and departureDate and swaps it with newOffer
int updateOffer(Repository* repo, char* destination, char* departureDate, Offer* newOffer)
{
    for (int index = 0; index < repo->array->length; index++) {
        Offer* current = repo->array->elements[index];
        if (strcmp(current->destination, destination) == 0 && strcmp(current->departureDate, departureDate) == 0) {
            repo->array->elements[index] = newOffer;
            return 1;
        }
    }
    return 0;
}
// removes an offer from the array
// it overwrites the offer to be removed by moving all the elements on unit to the left
//return 1 if the offer could be removed and 0 otherwise
int removeOffer(Repository* repo, Offer* existingOffer) {
    if (findOffer(repo, existingOffer) == 1) {
        for (int index = 0; index < repo->array->length; index++) {
            Offer* current = repo->array->elements[index];
            if (strcmp(current->destination, existingOffer->destination) == 0 && strcmp(current->departureDate, existingOffer->departureDate) == 0)
                for (int index2 = index; index2 < repo->array->length; index2++) {
                    repo->array->elements[index2] = repo->array->elements[index2 + 1];
                }
                repo->array->length--;
                return 1;
            }
        }
    return 0;
}

// return 1 if the offer exists in the repo
// return 0 otherwise
int findOffer(Repository* repo, Offer* offer) {
    for (int i = 0; i < repo->array->length; i++) {
        Offer* current = repo->array->elements[i];
        if (strcmp(current->destination, offer->destination) == 0 && strcmp(current->departureDate, offer->departureDate) == 0)
            return 1;
        }
   
    return 0;
}

// finds an offer by the destination and departure date given and returns 1 if it finds it, 0 otherwise
Offer* findOfferByDestinationAndDepartureDateReturningOffer(Repository* repo, char* destination, char* departureDate) {
    for (int i = 0; i < repo->array->length; i++) {
        Offer* current = repo->array->elements[i];
        if (strcmp(current->destination, destination) == 0 && strcmp(current->departureDate, departureDate) == 0)
        {
            Offer* currentOffer = createOffer(current->type, current->destination, current->departureDate, current->price);
            return currentOffer;

        }

    }
}

void interchangeAdd(Repository* repo, Repository* undo, int index) {
    Offer* undoOffer = undo->array->elements[index - 1];
    addOffer(repo, undoOffer);
}

void interchangeRemove(Repository* repo, Repository* undo, int index) {
    Offer* undoOffer = undo->array->elements[index-1];
    removeOffer(repo, undoOffer);
}

// finds an offer by the destination and departure date given and returns 1 if it finds it, 0 otherwise
int findOfferByDestinationAndDepartureDate(Repository* repo, char* destination, char* departureDate) {
    for (int i = 0; i < repo->array->length; i++) {
        Offer* current = repo->array->elements[i];
        if (strcmp(current->destination, destination) == 0 && strcmp(current->departureDate, departureDate) == 0)
            return 1;

    }

    return 0;
}

//returns a specific offer identified by destination and departureDate;

Offer* getOffer(Repository* repo, char* destination, char* departureDate) {
    for (int i = 0; i < repo->array->length; i++) {
        Offer* current = repo->array->elements[i];
        if (strcmp(current->destination, destination) == 0 && strcmp(current->departureDate, departureDate) == 0)
            return current;
        }
    }

//tests
    void testRepository() {
        Repository* repos = createRepo();
        assert(repos->array->length == 0);
        assert(repos->array->capacity == 10);
        Offer* o1 = createOffer("mountain", "brasov", "14/07/2018", 180);
        Offer* o2 = createOffer("seaside", "constanta", "26/11/2020", 800);
        Offer* o3 = createOffer("citybreak", "china", "17/02/2021", 500);
        Offer* o4 = createOffer("citybreak", "china", "17/02/2021", 100);

        addOffer(repos, o1);
        addOffer(repos, o2);
        addOffer(repos, o3);
        assert(getOffer(repos, "brasov", "14/07/2018") == o1);
        assert(findOffer(repos, o1) == 1);
        char destinationTest[30];
        char departureDateTest[30];
        strcpy(destinationTest, "brasov");
        strcpy(departureDateTest, "14/07/2018");
        assert(findOfferByDestinationAndDepartureDate(repos, destinationTest,departureDateTest) == 1);
        assert(removeOffer(repos, o2) == 1);
        assert(removeOffer(repos, o4) == 0);
        assert(getSize(repos) == 2);

}

