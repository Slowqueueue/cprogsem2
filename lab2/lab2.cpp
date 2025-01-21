//Регистрационный номер автомобиля, марка, пробег.
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <stdbool.h>
#include <string.h>
#include <windows.h>

#define NOTES 300
#define NAME_SIZE 40
#define DATABASE_FILE "database.txt"

typedef struct Car
{
    char* carbrand;
    char* regnumber;
    int mileage;
} Car;

void input_car();
void print_car();
void sort_by_brand();
void sort_by_regnumber();
void sort_by_mileage();
void find_by_brand();
void find_by_regnumber();
void find_by_mileage();
void save_cars();
void get_cars();
void show_table();
void delete_car();
void redact_car();
void sum_mileage();

int func_sort(const char* s1, const char* s2, int l);

Car* cars;

bool sorted_brand, sorted_regnumber, sorted_mileage;

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "RUS");


    cars = (Car*)calloc(NOTES, sizeof(Car));
    sorted_brand = sorted_regnumber = sorted_mileage = false;

    int cmd = 0;
    do {
        printf("\n\tВозможные команды\n");
        printf("#1 Ввод записи с заданным номером\n");
        printf("#2 Вывод записи с заданным номером\n");
        printf("#3 Просмотр таблицы\n");
        printf("#4 Сортировка записей по марке автомобиля в порядке возрастания\n");
        printf("#5 Сортировка записей по регистрационному номеру в порядке возрастания\n");
        printf("#6 Сортировка записей по пробегу в порядке возрастания\n");
        printf("#7 Поиск записи по марке автомобиля\n");
        printf("#8 Поиск записи по регистрационному номеру\n");
        printf("#9 Поиск записи по наиболее близкому к заданному числу пробегу\n");
        printf("#10 Сохранение всех записей в файле\n");
        printf("#11 Чтение записей из файла\n");
        printf("#12 Удаление записи с заданным номером\n");
        printf("#13 Изменение записи с заданным номером\n");
        printf("#14 Посчитать общий пробег автомобилей\n");
        printf("#0 Выход из программы\n");

        printf("\nНомер команды: ");
        scanf("%d", &cmd);

        switch (cmd)
        {
        case 0: break;
        case 1: input_car(); break;
        case 2: print_car(); break;
        case 3: show_table(); break;
        case 4: sort_by_brand(); break;
        case 5: sort_by_regnumber(); break;
        case 6: sort_by_mileage(); break;
        case 7: find_by_brand(); break;
        case 8: find_by_regnumber(); break;
        case 9: find_by_mileage(); break;
        case 10: save_cars(); break;
        case 11: get_cars(); break;
        case 12: delete_car(); break;
        case 13: redact_car(); break;
        case 14: sum_mileage(); break;
        default: printf("Неверный номер комманды\n"); break;
        }
        printf("~~~~~~~~~~~~~~~~\n");
    } while (cmd != 0);
    return 0;
}

void input_car() {
    int number;

    printf("Номер: ");
    scanf("%d", &number);
    number--;

    cars[number].carbrand = (char*)calloc(NAME_SIZE, sizeof(char));
    cars[number].regnumber = (char*)calloc(NAME_SIZE, sizeof(char));

    printf("\n");

    printf("@ Марка автомобиля: ");
    scanf("%s", cars[number].carbrand);

    printf("@ Регистрационный номер: ");
    scanf("%s", cars[number].regnumber);

    printf("@ Пробег: ");
    scanf("%d", &cars[number].mileage);

    sorted_brand = sorted_regnumber = sorted_mileage = false;
}

void print_car() {
    int number;

    printf("Номер: ");
    scanf("%d", &number);
    number--;

    if (cars[number].carbrand != NULL) {
        printf("~ Запись %d ~\n", number + 1);
        printf("@ Марка автомобиля: %s\n", cars[number].carbrand);
        printf("@ Регистрационный номер: %s\n", cars[number].regnumber);
        printf("@ Пробег: %d\n", cars[number].mileage);
    }
    else {
        printf("Такой записи нет\n");
    }
}

void show_table() {
    bool empty = true;
    for (int number = 0; number < NOTES; number++) {
        if (cars[number].carbrand != NULL) {
            empty = false;
            printf("\n~ Запись %d ~\n", number + 1);
            printf("@ Марка автомобиля: %s\n", cars[number].carbrand);
            printf("@ Регистрационный номер: %s\n", cars[number].regnumber);
            printf("@ Пробег: %d\n", cars[number].mileage);
        }
    }
    if (empty == true) printf("Нет записей\n");
}

void sort_by_brand() {
    if (sorted_brand == false) {
        for (int loop = 0; loop < NOTES; loop++) {
            for (int number = 0; number < NOTES - 1; number++) {
                if (cars[number].carbrand == NULL ||
                    (cars[number + 1].carbrand != NULL &&
                        func_sort(cars[number].carbrand, cars[number + 1].carbrand, 0) < 0))
                {
                    Car temp = cars[number + 1];
                    cars[number + 1] = cars[number];
                    cars[number] = temp;
                }
            }
        }

        printf("База данных отсортированна\n");
        sorted_brand = true;
    }
}

void sort_by_regnumber() {
    if (sorted_regnumber == false) {
        for (int loop = 0; loop < NOTES; loop++) {
            for (int number = 0; number < NOTES - 1; number++) {
                if (cars[number].regnumber == NULL ||
                    (cars[number + 1].regnumber != NULL &&
                        func_sort(cars[number].regnumber, cars[number + 1].regnumber, 0) < 0))
                {
                    Car temp = cars[number + 1];
                    cars[number + 1] = cars[number];
                    cars[number] = temp;
                }
            }
        }

        printf("База данных отсортированна\n");
        sorted_regnumber = true;
    }
}

void sort_by_mileage() {
    if (sorted_mileage == false) {
        for (int loop = 0; loop < NOTES; loop++) {
            for (int number = 0; number < NOTES - 1; number++) {
                if (cars[number].mileage == NULL ||
                    (cars[number + 1].mileage != NULL &&
                        cars[number].mileage > cars[number + 1].mileage))
                {
                    Car temp = cars[number + 1];
                    cars[number + 1] = cars[number];
                    cars[number] = temp;
                }
            }
        }

        printf("База данных отсортированна\n");
        sorted_mileage = true;
    }
}

int func_sort(const char* s1, const char* s2, int l) {
    int ltr = l;
    int max_ltr;

    if (strlen(s1) < strlen(s2))
        max_ltr = strlen(s1);
    else
        max_ltr = strlen(s2);

    if (s1[ltr] > s2[ltr])
        return -1;
    else if (s2[ltr] > s1[ltr])
        return 1;
    else {
        if (ltr < max_ltr)
            return func_sort(s1, s2, ltr + 1);
        else {
            if (strlen(s1) > strlen(s2))
                return -1;
            else
                return 1;
        }
    }
}

void find_by_brand() {
    char brand[100];
    printf("Марка автомобиля: ");
    scanf("%s", brand);

    for (int note = 0; note < NOTES; note++) {
        if (cars[note].carbrand != NULL) {
            if (strcmp(cars[note].carbrand, brand) == 0) {
                printf("~ Запись %d ~\n", note + 1);
                printf("@ Марка автомобиля: %s\n", cars[note].carbrand);
                printf("@ Регистрационный номер: %s\n", cars[note].regnumber);
                printf("@ Пробег: %d\n", cars[note].mileage);
            }
        }
    }
}

void find_by_regnumber() {
    char regnumber[100];
    printf("Регистрационный номер: ");
    scanf("%s", regnumber);

    for (int note = 0; note < NOTES; note++) {
        if (cars[note].regnumber != NULL) {
            if (strcmp(cars[note].regnumber, regnumber) == 0) {
                printf("~ Запись %d ~\n", note + 1);
                printf("@ Марка автомобиля: %s\n", cars[note].carbrand);
                printf("@ Регистрационный номер: %s\n", cars[note].regnumber);
                printf("@ Пробег: %d\n", cars[note].mileage);
            }
        }
    }
}

void find_by_mileage() {
    int lower = 0, higher = 0, mileage = 0;
    bool found = false;
    printf("Пробег: ");
    scanf("%d", &mileage);
    lower = mileage;
    higher = mileage;
    while (found == false) {
        for (int note = 0; note < NOTES; note++) {
            if (cars[note].mileage != NULL) {
                if (cars[note].mileage >= lower && cars[note].mileage <= higher) {
                    found = true;
                    printf("~ Запись %d ~\n", note + 1);
                    printf("@ Марка автомобиля: %s\n", cars[note].carbrand);
                    printf("@ Регистрационный номер: %s\n", cars[note].regnumber);
                    printf("@ Пробег: %d\n", cars[note].mileage);
                }
            }
        }
        lower = lower - 100;
        higher = higher + 100;
    }
}

void save_cars() {
    FILE* file = fopen(DATABASE_FILE, "w");

    if (file != NULL) {
        int notes = 0;
        for (int note = 0; note < NOTES; note++) {
            if (cars[note].carbrand != NULL)
                notes++;
        }
        fprintf(file, "(%d)\n", notes);

        for (int note = 0; note < NOTES; note++) {
            if (cars[note].carbrand != NULL) {
                fprintf(file, "%s %s %d\n",
                    cars[note].carbrand, cars[note].regnumber, cars[note].mileage);
            }
        }

        printf("Сохранено\n");
    }
    else {
        printf("Ошибка сохранения\n");
    }

    fclose(file);
}

void get_cars() {
    FILE* file = fopen(DATABASE_FILE, "r");

    if (file != NULL) {
        for (int note = 0; note < NOTES; note++) {
            if (cars[note].carbrand != NULL)
                cars[note].carbrand = NULL;
        }

        int notes = 0;
        fscanf(file, "(%d)\n", &notes);

        for (int note = 0; note < notes; note++) {
            cars[note].carbrand = (char*)calloc(NAME_SIZE, sizeof(char));
            cars[note].regnumber = (char*)calloc(NAME_SIZE, sizeof(char));

            fscanf(file, "%s %s %d\n",
                cars[note].carbrand, cars[note].regnumber, &cars[note].mileage);
        }

        printf("Данные загружены\n");
    }
    else {
        printf("Ошибка чтения\n");
    }

    fclose(file);
    sorted_brand = sorted_regnumber = sorted_mileage = false;
}

void delete_car() {
    int number;
    int notebuf = 0;
    printf("Номер: ");
    scanf("%d", &number);
    number--;

    if (cars[number].carbrand != NULL) {
        for (int note = 0; note < NOTES - 1; note++) {
            if (note != number) {
                cars[note].carbrand = cars[notebuf].carbrand;
                cars[note].regnumber = cars[notebuf].regnumber;
                cars[note].mileage = cars[notebuf].mileage;
                notebuf++;
            }
            if (note == number) {
                cars[note].carbrand = cars[notebuf + 1].carbrand;
                cars[note].regnumber = cars[notebuf + 1].regnumber;
                cars[note].mileage = cars[notebuf + 1].mileage;
                notebuf++;
                notebuf++;
            }
        }
        printf("Запись удалена\n");
        sorted_brand = sorted_regnumber = sorted_mileage = false;
    }
    else {
        printf("Такой записи нет\n");
    }
}

void redact_car() {
    int number;

    printf("Номер: ");
    scanf("%d", &number);
    number--;

    cars[number].carbrand = (char*)calloc(NAME_SIZE, sizeof(char));
    cars[number].regnumber = (char*)calloc(NAME_SIZE, sizeof(char));

    printf("\n");

    printf("@ Марка автомобиля: ");
    scanf("%s", cars[number].carbrand);

    printf("@ Регистрационный номер: ");
    scanf("%s", cars[number].regnumber);

    printf("@ Пробег: ");
    scanf("%d", &cars[number].mileage);

    sorted_brand = sorted_regnumber = sorted_mileage = false;
}

void sum_mileage() {
    int sum = 0;

    for (int note = 0; note < NOTES; note++) {
        sum = sum + cars[note].mileage;
    }
    printf("Общий пробег всех автомобилей: %d\n", sum);
}