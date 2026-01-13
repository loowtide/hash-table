#include "hash_table.h"
#include <math.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

// get new item for hash table
static ht_item *ht_new_item(const char *k, const char *v) {
  ht_item *i = malloc(sizeof(ht_item));
  i->key = strdup(k);
  i->value = strdup(v);
  return i;
}

// initialise a new hash table
ht_hash_table *ht_new() {
  ht_hash_table *ht = malloc(sizeof(ht_hash_table));
  ht->size = 53;
  ht->count = 0;
  ht->items = calloc((size_t)ht->size, sizeof(ht_item *));
  return ht;
}

// delete items from hash table
static void ht_del_items(ht_item *i) {
  free(i->key);
  free(i->value);
  free(i);
}

// delete the hash table
void ht_del_hash_table(ht_hash_table *ht) {
  for (int i = 0; i < ht->size; i++) {
    ht_item *item = ht->items[i];
    if (item != NULL)
      ht_del_items(item);
  }
  free(ht->items);
  free(ht);
}

static int ht_hash(const char *s, const int a, const int m) {
  long hash = 0;
  const int len = strlen(s);
  for (int i = 0; i < len; i++) {
    hash += pow(a, len - (i + 1)) * s[i];
    hash %= m;
  }
  return (int)hash;
}

static int ht_get_hash(const char *s, const int num_brackets,
                       const int attempt) {
  const int hash_a = ht_hash(s, HT_PRIME_1, num_brackets);
  const int hash_b = ht_hash(s, HT_PRIME_2, num_brackets);
  return (hash_a + (attempt * (hash_b + 1))) % num_brackets;
}

static void ht_insert(ht_hash_table *ht, const char *key, const char *value) {
  ht_item *item = ht_new_item(key, value);
  int index = ht_get_hash(item->key, ht->size, 0);
  ht_item *cur_item = ht->items[index];
  int i = 1;
  while (cur_item != NULL) {
    index = ht_get_hash(item->key, ht->size, i);
    cur_item = ht->items[index];
    i++;
  }
  ht->items[index] = item;
  ht->count++;
}

static int ht_search(ht_hash_table *ht, const char *key) {
  const int index = ht_get_hash(key, ht->size, 0);
  ht_item *item = ht->items[index];
  int i = 1;
  while (item != NULL) {
    if (strcmp(key, item->key)) {
      return item->value;
    }
    index = ht_get_hash(key, ht->size, i);
    item = ht->items[index];
    i++;
  }
  return NULL;
}
