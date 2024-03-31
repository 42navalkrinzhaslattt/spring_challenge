#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <json-c/json.h>
#include <locale.h>
#include <ctype.h>


/**
 * The height of each building.
 */
typedef struct intArray {
	int length;
	int* items;
} intArray;

/**
 * Representation of the n buildings
 */
typedef struct stringArray {
	int length;
	char** items;
} stringArray;

/**
 * @param n The number of buildings
 * @param building_map Representation of the n buildings
 * @return The height of each building.
 */
intArray buildingHeights(int n, stringArray building_map) {
	// Write your code here

	intArray int_array = {3, malloc(sizeof(int) * 3)};
	int_array.items[0] = 30;
	int_array.items[1] = 20;
	int_array.items[2] = 153;
	return int_array;

}

/* Ignore and do not change the code below */\

intArray findLargestCircle(int n_rows, int n_cols, stringArray image) {
	// Write your code here

	intArray int_array = {3, calloc(3, sizeof(int))};

	int max_size = 0;
	int begin;
	int end;

	for (int i = 1; i < n_rows; i++)
	{
		begin = 0;
		int j = 0;
		while ()
	}
	return int_array;

}