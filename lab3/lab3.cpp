//Функция получает строку текста и возвращает динамический массив указателей на слова. Каждое слово копируется в отдельный массив в динамической памяти.
#include <stdio.h>
#include <windows.h>
#include <math.h>
#include <conio.h>

char** dynamic_array(char* string);
char* find_non_space(char* fstr);
char* find_space(char* fstr);
void string_out(char** strout, int wordnumber);

int main()
{
	char string[100], * p, ** pp;
	printf("Enter string: ");
	gets_s(string);
	p = string;
	pp = dynamic_array(p);
	delete[]pp;
	return 0;
}

char** dynamic_array(char* string)
{
	char* copystring = string;
	int wordnumber = 0;
	int wordsize = 0;

	for (; *string != '\0'; wordnumber++)
	{
		string = find_non_space(string);
		if (*string == '\0') break;
		string = find_space(string);
	}
	printf("\nNumber of words in string: %d\n", wordnumber);

	char** dynarrpoint = new char* [wordnumber];
	int k = 0, i = 0;

	for (; i < wordnumber; i++)
	{
		char* start, * finish;
		start = copystring = find_non_space(copystring);
		if (*copystring == '\0') break;
		finish = copystring = find_space(copystring);
		wordsize = (finish - start);
		dynarrpoint[i] = new char[wordsize + 1];
		for (k = 0; k < wordsize; k++, start++) dynarrpoint[i][k] = *start;
		dynarrpoint[i][k] = '\0';
	}
	string_out(dynarrpoint, wordnumber);
	return (dynarrpoint);
}

char* find_non_space(char* fstr)
{
	for (; *fstr == ' ' && *fstr != '\0'; fstr++);
	return(fstr);
}

char* find_space(char* fstr)
{
	for (; *fstr != ' ' && *fstr != '\0'; fstr++);
	return(fstr);
}

void string_out(char** strout, int wordnumber)
{
	for (int i = 0; i < wordnumber; i++)
	{
		for (int k = 0; strout[i][k] != '\0'; k++) putchar(strout[i][k]);
		printf(" ");
	}
}