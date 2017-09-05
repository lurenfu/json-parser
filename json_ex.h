#ifndef __JSON_EX_H__
#define __JSON_EX_H__

/*
 * lurenfu@qq.com
 */

#ifdef  __cplusplus
extern "C" {
#endif

#include "json.h"

json_value* json_read_file(char*);

json_value* json_create_object(void);
json_value* json_create_array(void);

json_value* json_add_object(json_value *jv, char *name);
json_value* json_add_array(json_value *jv, char *name);

int json_add_integer(json_value *jv, char *name, json_int_t v);
int json_add_double(json_value *jv, char *name, double v);
int json_add_string(json_value *jv, char *name, const char *v);
int json_add_boolean(json_value *jv, char *name, int v);
int json_add_null(json_value *jv, char *name);

int json_get_output_string_length(const json_value *jv);
int json_output_string(const json_value *jv, char *buf);

int     json_get_format_string_length(const char *text);
char*   json_format_string(const char *text, char *outbuf, size_t size);

#ifdef  __cplusplus
}
#endif

#endif  // __JSON_EX_H__

