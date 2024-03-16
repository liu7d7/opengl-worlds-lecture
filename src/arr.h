#pragma once

#include <string.h>
#include <stdint.h>
#include "typedefs.h"

typedef struct arr_metadata arr_metadata;

struct arr_metadata {
  size_t len;
  size_t count;
  size_t elem_size;
};

typedef uint8_t byte;

arr_metadata* internal_arr_get_metadata(byte* memory);

byte* internal_arr_new(size_t len, size_t elem_size);

byte* internal_arr_base_ptr(byte* memory);

#define arr_new(type, initial_size) (type*) internal_arr_new(initial_size, sizeof(type))

void arr_add(void* memory, void* item);

bool internal_arr_has(byte* memory, byte* element, size_t elem_size);

#define arr_has(this, element) internal_arr_has((byte*) this, (byte*) &element, sizeof(element))
#define arr_has_i(this, type, ...) internal_arr_has((byte*) this, (byte*) &(type) {__VA_ARGS__}, sizeof(type))

#define arr_last(this) &(this)[arr_count(this) - 1]

#define arr_len(this) internal_arr_get_metadata((byte*) this)->count

void internal_arr_del(byte* memory);

#define arr_del(this) internal_arr_del((byte*) this)

void* internal_arr_at(byte* memory, size_t n);

#define arr_at(this, n) internal_arr_at((byte*) this, n)

void arr_clear(void* memory);

void arr_add_bulk(void* dst, void* src);

void* arr_end(void* memory);

bool arr_is_empty(void* memory);

char* arr_get_sz(char* memory);