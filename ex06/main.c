#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <ctype.h>

typedef struct stringArray {
	int length;
	char** items;
} stringArray;

typedef struct s_intArr {
	int length;
	int	*arr;
} intArr;

long long get_sum(intArr *dict, int dict_size)
{
	long long	res = 0;
	int			*arr = dict->arr;
	int			len = dict->length;
	int			prev_len = 0;

//	for (int i = 0; i < dict_size; i++)
//		printf("%d ", arr[i]);
//	printf("\n");
	for (int i = 0; i < dict_size; i++)
	{
		len -= arr[i];
		prev_len += arr[i];
//		printf("len is %d\n", len);
//		printf("prev_len is %d\n", prev_len);
		res += arr[i] * i * (prev_len - len - arr[i]);
//		printf("res is %lld\n", res);
	}
//	printf("returning %lld\n", res);
	return (res);
}

int getCableLength(int n_rows, int n_cols, stringArray image)
{
	intArr		dict_x[128];
	intArr		dict_y[128];
	long long	res = 0;
	char		**arr = image.items;

	for(int i = '0'; i <= '9'; i++)
	{
		dict_x[i].arr = calloc(n_cols - 1, sizeof(int));
		dict_x[i].length = 0;
		dict_y[i].arr = calloc(n_rows - 1, sizeof(int));
		dict_y[i].length = 0;
	}
	for(int i = 'A'; i <= 'Z'; i++)
	{
		dict_x[i].arr = calloc(n_cols - 1, sizeof(int));
		dict_y[i].arr = calloc(n_rows - 1, sizeof(int));
		dict_x[i + 32].arr = calloc(n_cols - 1, sizeof(int));
		dict_y[i + 32].arr = calloc(n_rows - 1, sizeof(int));
		dict_x[i].length = 0;
		dict_y[i].length = 0;
		dict_x[i + 32].length = 0;
		dict_y[i + 32].length = 0;
	}
	for(int i = 0; i < n_rows; i++)
	{
		for(int j = 0; j < n_cols; j++)
		{
			dict_y[(int)arr[i][j]].arr[i]++;
			dict_y[(int)arr[i][j]].length++;
			dict_x[(int)arr[i][j]].arr[j]++;
			dict_x[(int)arr[i][j]].length++;
		}
	}
	for(int i = '0'; i <= '9'; i++)
	{
		if (dict_x[i].length >= 2)
		{
//			printf("char %c\n", i);
//			printf("x array:\n");
			res += get_sum(dict_x + i, n_cols);
//			printf("y array:\n");
			res += get_sum(dict_y + i, n_rows);
		}
	}
	for(int i = 'A'; i <= 'Z'; i++)
	{
		if (dict_x[i].length >= 2)
		{
//			printf("char %c\n", i);
//			printf("x array:\n");
			res += get_sum(dict_x + i, n_cols);
			res += get_sum(dict_y + i, n_rows);
		}
		if (dict_x[i + 32].length >= 2)
		{
//			printf("char %c\n", i + 32);
//			printf("y array:\n");
			res += get_sum(dict_x + i + 32, n_cols);
			res += get_sum(dict_y + i + 32, n_rows);
		}
	}
	return ((res * 2) % (1000000000 + 7));
}

int main()
{
	stringArray image;

	image.length = 2;
	char *arr[] = {"ABC", "CBC"};
	image.items = arr;
	printf("%d\n", getCableLength(2, 3, image));
}
