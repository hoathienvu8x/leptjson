#ifndef LEPTJSON_H__
#define LEPTJSON_H__

#include <stddef.h> /* size_t */

typedef enum {
  LEPT_NULL,
  LEPT_FALSE,
  LEPT_TRUE,
  LEPT_NUMBER,
  LEPT_FLOAT,
  LEPT_STRING,
  LEPT_ARRAY,
  LEPT_OBJECT
} lept_type;

typedef struct lept_value lept_value;
typedef struct lept_member lept_member;

struct lept_value {
  union {
    struct {
      char* s; /*string*/
      size_t len;
    } s;
    struct {
      lept_value* e;
      size_t size;
    } a;
    struct {
      lept_member* m; /*object*/
      size_t size;
    }o;
    double n; /*number*/
  } u;
  lept_type type;
};

struct lept_member {
  char* k; /*member key string*/
  size_t klen; /*key string length */
  lept_value v; /* member value */
};

enum {
  LEPT_PARSE_OK = 0,
  LEPT_PARSE_EXPECT_VALUE,
  LEPT_PARSE_INVALID_VALUE,
  LEPT_PARSE_ROOT_NOT_SINGULAR,
  LEPT_PARSE_NUMBER_TOO_BIG,
  LEPT_PARSE_MISS_QUOTATION_MARK,
  LEPT_PARSE_INVALID_STRING_ESCAPE,
  LEPT_PARSE_INVALID_STRING_CHAR,
  LEPT_PARSE_INVALID_UNICODE_SURROGATE,
  LEPT_PARSE_INVALID_UNICODE_HEX,
  LEPT_PARSE_MISS_COMMA_OR_SQUARE_BRACKET,
  LEPT_PARSE_MISS_KEY,
  LEPT_PARSE_MISS_COLON,
  LEPT_PARSE_MISS_COMMA_OR_CURLY_BRACKET,
  LEPT_STRINGIFY_OK
};

int lept_parse(lept_value* v, const char* json);

lept_type lept_get_type(const lept_value* v);

void lept_free(lept_value* v);

int lept_is_equal(const lept_value* lhs, const lept_value* rhs);

#define lept_init(v) do {(v)->type = LEPT_NULL; } while (0)
#define lept_set_null(v) lept_free(v)

int lept_get_boolean(const lept_value* v);
void lept_set_boolean(lept_value* v, lept_type b);

double lept_get_number(const lept_value* v);
void lept_set_number(lept_value* v, double n);

const char* lept_get_string(const lept_value* v);
size_t lept_get_string_length(const lept_value* v);
void lept_set_string(lept_value* v, const char* s, size_t len);

size_t lept_get_array_size(const lept_value* v);
lept_value* lept_get_array_element(const lept_value* v, size_t index);

size_t lept_get_object_size(const lept_value* v);
const char* lept_get_object_key(const lept_value* v, size_t index);
size_t lept_get_object_key_length(const lept_value* v, size_t index);
lept_value* lept_get_object_value(const lept_value* v, size_t index);

#define lept_find_object_index(...) lept_find_object_index(__VA_ARGS__, 0)
size_t (lept_find_object_index)(const lept_value* v, const char* key, size_t klen, ...);

#define lept_find_object_value(...) lept_find_object_value(__VA_ARGS__, 0)
lept_value* (lept_find_object_value)(const lept_value* v, const char* key, size_t klen, ...);

int lept_stringify(const lept_value* v, char** json, size_t* length);

#endif /* LEPTJSON_H__ */
