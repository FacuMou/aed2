/*
  @file sort.c
  @brief sort functions implementation
*/

#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include "helpers.h"
#include "sort.h"
#include "player.h"

bool goes_before(player_t x, player_t y){
    return (*x).rank <= (*y).rank;
}

bool array_is_sorted(player_t atp[], unsigned int length) {
    unsigned int i = 1u;
    while (i < length && goes_before(atp[i - 1u], atp[i])) {
        i++;
    }
    return (i == length);
}

// Quick sort functions:

void swap(player_t atp[], int x, int y){
    player_t aux = atp[x];
    atp[x] = atp[y];
    atp[y] = aux;
}

static unsigned int partition(player_t atp[], unsigned int izq, unsigned int der) {
    unsigned int i = izq+1;
    unsigned int j = der;
    unsigned int pivot = izq;

    while (i <= j){
        if (goes_before(atp[i], atp[pivot])){
            i++;
        }
        else if (goes_before(atp[pivot], atp[j])){
            j--;
        }
        else if (goes_before(atp[pivot], atp[i]) && goes_before(atp[j], atp[pivot])){
            swap(atp, i, j);
            }
    }
    swap(atp, pivot, j);
    pivot = j;
    return pivot;
}

static void quick_sort_rec(player_t atp[], unsigned int izq, unsigned int der) {
    unsigned int pivot;
    if (izq < der){
        pivot = partition(atp, izq, der);
        if(pivot > 0){
            quick_sort_rec(atp, izq, pivot-1);
            quick_sort_rec(atp, pivot+1, der);
        } else {
            quick_sort_rec(atp, izq, pivot);
            quick_sort_rec(atp, pivot+1, der);
        }
    }
}

void sort(player_t atp[], unsigned int length) {
    quick_sort_rec(atp, 0, 0 == length ? 0 : length-1);
}

