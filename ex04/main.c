#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//#include <json-c/json.h>
#include <locale.h>
#include <ctype.h>
#include <math.h>

/**
 * The parameters of the largest circle [centerRow, centerCol, radius].
 */
typedef struct intArray {
	int length;
	int* items;
} intArray;

/**
 * Pixels of the image, given row by row from top to bottom.
 */
typedef struct stringArray {
	int length;
	char** items;
} stringArray;

/**
 * @param n_rows The height of the image.
 * @param n_cols The width of the image.
 * @param image Pixels of the image, given row by row from top to bottom.
 * @return The parameters of the largest circle [centerRow, centerCol, radius].
 */

typedef struct s_set
{
	int		left;
	int		right;
	int		top;
	int		bottom;
	char	ch;
	int		res_x;
	int		res_y;
	int		res_radius;
}	t_set;

//void	check_set(stringArray image, t_set *set, int max)
//{
//	int max_max = set->right - set->left > set->bottom - set->top ? set->right - set->left : set->bottom - set->top;
//	int temp = 0;
//
//	for(int k = max + 1; k < max_max; k++)
//	{
//		for(int i = set->top + k; i <= set->bottom - k; i++)
//		{
//			for(int j = set->left + k; j <= set->right - k; j++)
//			{
//				if (check_circle(i, j, k, image, set->ch))
//				{
//					set->res_radius = k;
//					set->res_y = i;
//					set->res_x = j;
//				}
//			}
//		}
//	}
//}

int	check_circle(int mid_y, int mid_x, int radius, stringArray image, char ch)
{
	int y_start;
	int y_end;
	for (int i = mid_x - radius; i <= mid_x; i++)
	{
		y_start = floor(mid_y - sqrt(pow(radius + 1, 2) - pow(mid_x - i, 2)) + 1);
		y_end = floor(mid_y - sqrt(pow(radius, 2) - pow(mid_x - i, 2)));
//		printf("%f %f\n", mid_y - sqrt(pow(radius + 1, 2) - pow(mid_x - i, 2)), mid_y - sqrt(pow(radius, 2) - pow(mid_x - i, 2)));
//		printf("in %d column we should check between %d and %d\n", i, y_start, y_end);
		while (y_start <= y_end)
		{
//			printf("%c at (%d, %d)\n", image.items[y_start][i], y_start, i);
//			if (mid_y == 8 && mid_x == 4)
//				exit(0);
//			printf("checking (%d, %d) (%d, %d), (%d, %d) and (%d, %d)\n", y_start, i, 2 * mid_y - y_start, i, y_start, 2 * mid_x - i, 2 * mid_y - y_start, 2 * mid_x - i);
			if (image.items[y_start][i] != ch || image.items[2 * mid_y - y_start][i] != ch
				|| image.items[y_start][2 * mid_x - i] != ch || image.items[2 * mid_y - y_start][2 * mid_x - i] != ch)
				return (0);
			y_start++;
		}
	}
	return (1);
}

intArray findLargestCircle(int n_rows, int n_cols, stringArray image) {
	// Write your code here

	intArray int_array = {3, calloc(3, sizeof(int))};

	int max = 0;
	int max_size = 0;
//	int begin;
//	int end;

	for (int i = 1; i < n_rows; i++)
	{
		for (int j = 1; j < n_cols; j++)
		{
			max_size = i;
			if (max_size > j)
				max_size = j;
			if (max_size > n_rows - 1 - i)
				max_size = n_rows - 1 - i;
			if (max_size > n_cols - 1 - j)
				max_size = n_cols - 1 - j;
			for (int k = max + 1; k <= max_size; k++)
			{
				printf("checking circle in the center of (%d, %d) of size %d and char %c\n", i, j, k, image.items[i][j + k]);
				if (check_circle(i, j, k, image, image.items[i][j + k]))
				{
					printf("found circle of size %d at (%d %d)\n", k, i, j);
					int_array.items[0] = i;
					int_array.items[1] = j;
					int_array.items[2] = k;
					max = k;
				}
			}
		}
	}
	return int_array;
}

int main()
{
	stringArray image;
	char *arr[] = {"DBABADCB", "ACCCAABD", "CBBADBBB", "DDDDAAAC", "DAAABBCC", "DCACBDDC", "DAAAABCA", "BABADDAC", "AAAAABAB", "CAABCDDA"};

	image.length = 10;
	image.items = arr;

	findLargestCircle(10, 8, image);
}

//int main()
//{
//	stringArray image;
//	char *arr[] = {"bbCCCCC3cC3c", "1CAABBBC3c3c", "aCAAbbbC312A", "aCCBbabCB111", "3CBBbbbC2C12", "CCBAca3C2a1C", "2ACCCCCaaaaa", "b33ccccccccc"};
//
//	image.length = 8;
//	image.items = arr;
//	printf("%d\n", check_circle(3, 4, 3, image, 'C'));
//	printf("%d\n", check_circle(4, 4, 4, image, 'b'));
//}