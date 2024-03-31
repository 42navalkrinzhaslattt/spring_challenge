#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <json-c/json.h>
#include <locale.h>
#include <ctype.h>

typedef struct stringArray {
	int length;
	char** items;
} stringArray;

/**
 * @param n The size of the image
 * @param target_image The rows of the desired image, from top to bottom
 */

int get_max_index(int *arr, int size)
{
	int max = -1;
	int res = -1;
	for(int i = 0; i < size; i++)
	{
		if (arr[i] > max)
		{
			res = i;
			max = arr[i];
		}
	}
	return (res);
}

void print_arrays(int *arr1, int *arr2, int n)
{
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr1[i]);
	}
	printf("\n");
	for (int i = 0; i < n; i++)
	{
		printf("%d ", arr2[i]);
	}
	printf("\n");
}

stringArray solve(int n, stringArray target_image)
{
	stringArray string_array = {2 * n, calloc(2 * n ,sizeof(char*))};
	int arr_iter = 0;
	char	col_oper[10][4] = {"C 0", "C 1", "C 2", "C 3", "C 4", "C 5", "C 6", "C 7", "C 8", "C 9"};
	char	row_oper[10][4] = {"R 0", "R 1", "R 2", "R 3", "R 4", "R 5", "R 6", "R 7", "R 8", "R 9"};
	int		*col_counter = calloc(n, sizeof(int));
	int		*row_counter = calloc(n, sizeof(int));
	int prev_value = -1;
	int swap_flag = 0;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (target_image.items[i][j] == '.')
				row_counter[i]++;
			else
				col_counter[j]++;
		}
	}
	if (col_counter[get_max_index(col_counter, n)] != n)
	{
		int *temp;
		temp = col_counter;
		col_counter = row_counter;
		row_counter = temp;
		swap_flag = 1;
	}
	print_arrays(col_counter, row_counter, n);
	while (1)
	{
		int max_col_index;
		max_col_index = get_max_index(col_counter, n);
		if (max_col_index < 0)
			break ;
		if (prev_value > 0)
		{
			int max_row_index;
			for (int i = prev_value; i > col_counter[max_col_index]; i--)
			{
				max_row_index = get_max_index(row_counter, n);
				if (swap_flag)
					string_array.items[arr_iter++] = strdup(col_oper[max_row_index]);
				else
					string_array.items[arr_iter++] = strdup(row_oper[max_row_index]);
				row_counter[max_row_index] = -1;
				printf("after flushing rows:\n");
				print_arrays(col_counter, row_counter, n);
			}
		}
		if (swap_flag)
			string_array.items[arr_iter++] = strdup(row_oper[max_col_index]);
		else
			string_array.items[arr_iter++] = strdup(col_oper[max_col_index]);
		prev_value = col_counter[max_col_index];
		col_counter[max_col_index] = -1;
		printf("after flushing column:\n");
		print_arrays(col_counter, row_counter, n);
	}
	for (int i = 0; i < arr_iter / 2; i++)
	{
		char *temp = string_array.items[i];
		string_array.items[i] = string_array.items[arr_iter - i - 1];
		string_array.items[arr_iter - i - 1] = temp;
	}
	string_array.length = arr_iter;
	return string_array;
}

int main()
{
	stringArray image;
	stringArray answer;

//	char *arr[] = {".#.#..", ".#.#..", "...#..", ".#.#..", ".#.#..", ".#.#.."};
	char *arr[] = {"#.#", "...", "#.#"};
	image.items = arr;
	image.length = 3;
	for (int i = 0; i < image.length; i++)
	{
		printf("%s\n", arr[i]);
	}
	answer = solve(image.length, image);
	for (int i = 0; i < answer.length; i++)
	{
		printf("%s\n", answer.items[i]);
	}
}

/* Ignore and do not change the code below */
