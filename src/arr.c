#include <assert.h>
#include "arr.h"
#include "err.h"

arr_metadata* internal_arr_get_metadata(byte* memory) {
  return ((arr_metadata*)(memory - sizeof(arr_metadata)));
}

byte* internal_arr_new(size_t len, size_t elem_size) {
  byte* memory = malloc(sizeof(arr_metadata) + len * elem_size);
  memcpy(memory, &(arr_metadata){
    .len = len,
    .count = 0,
    .elem_size = elem_size
  }, sizeof(arr_metadata));

  return memory + sizeof(arr_metadata);
}

byte* internal_arr_base_ptr(byte* memory) {
  return memory - sizeof(arr_metadata);
}

void arr_add(void* thing, void* item) {
  void** memory = thing;
  arr_metadata* data = internal_arr_get_metadata(*memory);

  if (data->len == data->count) {
    data->len *= 2;
    size_t new_size_in_bytes =
      sizeof(arr_metadata) + data->len * data->elem_size;
    byte* new_base_ptr = realloc(internal_arr_base_ptr(*memory),
                                 new_size_in_bytes);
    *memory = new_base_ptr + sizeof(arr_metadata);

    data = internal_arr_get_metadata(*memory);
  }

  memcpy(*memory + data->count * data->elem_size, item, data->elem_size);
  data->count++;
}

bool internal_arr_has(byte* memory, byte* element, size_t elem_size) {
  arr_metadata* data = internal_arr_get_metadata(memory);

  if (data->elem_size != elem_size) {
    throw_c("incompatible type");
  }

  for (int i = 0; i < data->count; i++) {
    byte* a = memory + data->elem_size * i;
    if (!memcmp(a, element, data->elem_size)) {
      return true;
    }
  }

  return false;
}

void internal_arr_del(byte* memory) {
  byte* base = internal_arr_base_ptr(memory);
  free(base);
}

void* internal_arr_at(byte* memory, size_t n) {
  arr_metadata* meta = internal_arr_get_metadata(memory);
  return memory + meta->elem_size * n;
}

void arr_clear(void* memory) {
  arr_metadata* meta = internal_arr_get_metadata(memory);
  meta->count = 0;
}

void arr_add_bulk(void* thing, void* src) {
  void** dst = thing;
  arr_metadata* dst_meta = internal_arr_get_metadata(*dst);
  arr_metadata* src_meta = internal_arr_get_metadata(src);

  if (src_meta->elem_size != dst_meta->elem_size) {
    throw_c("Mismatched element sizes in arr_add_bulk!");
  }

  size_t new_count = dst_meta->count + src_meta->count;
  if (new_count > dst_meta->len) {
    size_t next = (size_t)pow(2, ceil(log2((double)new_count)));

    void* new_memory = realloc(internal_arr_base_ptr(*dst),
                               sizeof(arr_metadata) +
                               next * dst_meta->elem_size);
    *dst = new_memory + sizeof(arr_metadata);

    dst_meta = internal_arr_get_metadata(*dst);
  }

  memcpy(*dst + dst_meta->count * dst_meta->elem_size, src,
         src_meta->count * src_meta->elem_size);
  dst_meta->count = new_count;
}

void* arr_end(void* memory) {
  arr_metadata* meta = internal_arr_get_metadata(memory);
  return memory + meta->elem_size * meta->count;
}

bool arr_is_empty(void* memory) {
  return internal_arr_get_metadata(memory)->count == 0;
}

char* arr_get_sz(char* memory) {
  char* str = malloc(arr_len(memory) + 1);
  memcpy(str, memory, arr_len(memory));
  str[arr_len(memory)] = '\0';
  return str;
}
