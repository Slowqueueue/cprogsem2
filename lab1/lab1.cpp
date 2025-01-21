//Функция находит минимальный элемент массива и возвращает указатель на него. С использованием этой функции реализовать сортировку выбором.
#include <stdio.h>
#include <iostream>
using namespace std;

int* find_min(int* arr, int num)
{
    int i, * min = arr;
    for (i = 1; i < num; ++i) if (*(arr + i) < *min) min = arr + i;
    return min;
}

void swap(int* a, int* b) {
    if (a != b) {
        int tmp = *a;
        *a = *b;
        *b = tmp;
    }
}

void selection_sort(int* arr, int num) {
    for (int i = 0; i < num - 1; ++i) swap(arr + i, find_min(arr + i, num - i));
}

int main()
{
    int num, i;
    printf("Enter number of numbers\n");
    cin >> num;
    if (num <= 0) {
        printf("Number of numbers must be positive");
        return 0;
    }
    int* arr = new int[num];
    printf("Enter %d numbers\n", num);
    for (i = 0; i < num; ++i) cin >> arr[i];
    printf("Minimal element = %d\n", *find_min(arr, num));
    selection_sort(arr, num);
    for (i = 0; i < num; ++i) printf("%d ", *(arr + i));
    return 0;
}