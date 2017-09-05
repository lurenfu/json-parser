/*
 * lurenfu@qq.com
 * gcc -W -Wall -Wno-unused-parameter -I../ -o json_ex_test json_ex_test.c ../json.c ../json_ex.c -lm
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json_ex.h"

int main()
{
    int     len;
    char    buf[1024], fmt_buf[1024];
    json_value  *ajv, *jv;

    jv = json_create_object();
    if (!jv) {
        printf("%d error\n", __LINE__);
        return -1;
    }

    json_add_string(jv, "name", "json_ex");

    json_add_string(jv, "author", "lurenfu@qq.com");

    ajv = json_add_array(jv, "birth");
    if (!ajv) {
        json_value_free(jv);
        printf("%d error\n", __LINE__);
        return -1;
    }
    json_add_integer(ajv, NULL, 2014);
    json_add_integer(ajv, NULL, 6);
    json_add_integer(ajv, NULL, 6);

    len = json_get_output_string_length(jv);
    printf("json_ex lenthg: %d\n", len);
    json_output_string(jv, buf);
    printf("buf lenthg: %d\n", (int)strlen(buf));
    printf("buf content:\n");
    printf("%s\n\n", buf);

    json_value_free(jv);

    len = json_get_format_string_length(buf);

    printf("format json_ex length: %d\n", len);
    json_format_string(buf, fmt_buf, sizeof(fmt_buf)-1);
    printf("fmt_buf length: %d\n", (int)strlen(fmt_buf));
    printf("fmt_buf content:\n");
    printf("%s\n", fmt_buf);

    return 0;
}

