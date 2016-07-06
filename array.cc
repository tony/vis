#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "array.hh"
#include "util.hh"

#define ARRAY_SIZE 16

void array_init(Array *arr) {
	array_init_sized(arr, sizeof(void*));
}

void array_init_sized(Array *arr, size_t elem_size) {
	memset(arr, 0, sizeof *arr);
	arr->elem_size = elem_size;
}

bool array_reserve(Array *arr, size_t count) {
	if (count < ARRAY_SIZE)
		count = ARRAY_SIZE;
	if (arr->count < count) {
		count = MAX(count, arr->count*2);
		char *items = realloc(arr->items, count * arr->elem_size);
		if (!items)
			return false;
		arr->count = count;
		arr->items = items;
	}
	return true;
}

void array_release(Array *arr) {
	if (!arr)
		return;
	free(arr->items);
	array_init_sized(arr, arr->elem_size);
}

void array_release_full(Array *arr) {
	if (!arr)
		return;
	for (size_t i = 0; i < arr->len; i++)
		free(array_get_ptr(arr, i));
	array_release(arr);
}

void array_clear(Array *arr) {
	arr->len = 0;
	if (arr->items)
		memset(arr->items, 0, arr->count * arr->elem_size);
}

void *array_get(Array *arr, size_t idx) {
	if (idx >= arr->len) {
		errno = EINVAL;
		return NULL;
	}
	return arr->items + (idx * arr->elem_size);
}

void *array_get_ptr(Array *arr, size_t idx) {
	if (arr->elem_size != sizeof(void*)) {
		errno = ENOTSUP;
		return NULL;
	}
	void **ptr = array_get(arr, idx);
	return ptr ? *ptr : NULL;
}

bool array_set(Array *arr, size_t idx, void *item) {
	if (idx >= arr->len) {
		errno = EINVAL;
		return false;
	}
	if (item)
		memcpy(arr->items + (idx * arr->elem_size), item, arr->elem_size);
	else
		memset(arr->items + (idx * arr->elem_size), 0, arr->elem_size);
	return true;
}

bool array_set_ptr(Array *arr, size_t idx, void *item) {
	if (arr->elem_size != sizeof(void*)) {
		errno = ENOTSUP;
		return false;
	}
	return array_set(arr, idx, &item);
}

bool array_add(Array *arr, void *item) {
	if (!array_reserve(arr, arr->len+1))
		return false;
	if (!array_set(arr, arr->len++, item)) {
		arr->len--;
		return false;
	}
	return true;
}

bool array_add_ptr(Array *arr, void *item) {
	if (!array_reserve(arr, arr->len+1))
		return false;
	if (!array_set_ptr(arr, arr->len++, item)) {
		arr->len--;
		return false;
	}
	return true;
}

size_t array_length(Array *arr) {
	return arr->len;
}
