
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "json.h"
#include "json_ex.h"

/*
 * lurenfu@qq.com
 */

json_value* json_read_file(char *file)
{
    json_value  *jv = NULL;
    FILE        *fp;
    char        *buf;
    int          len;

    fp = fopen(file , "r");
    if (!fp) {
        return NULL;
    }

    fseek(fp, 0, SEEK_END);
    len = (int)ftell(fp);
    fseek(fp, 0, SEEK_SET);
    buf = (char *)malloc(len + 1);
    if (!buf) {
        fclose(fp);
        return NULL;
    }

    memset(buf, 0, len+1);
    fread(buf, len, 1, fp);
    fclose(fp);

    jv = json_parse(buf, len);

    free(buf);

    return jv;
}

json_value* json_create_object()
{
    json_value  *jv = (json_value *)calloc(1, sizeof(json_value));

    if (jv) {
        jv->parent = NULL;
        jv->type = json_object;
        jv->u.object.length = 0;
    }

    return jv;
}

json_value* json_create_array()
{
    json_value  *jv = (json_value *)calloc(1, sizeof(json_value));

    if (jv) {
        jv->parent = NULL;
        jv->type = json_array;
        jv->u.array.length = 0;
    }

    return jv;
}

json_value* json_add_object(json_value *jv, char *name)
{
    int         len;
    json_value  *njv;

    if (!jv || (json_object != jv->type && json_array != jv->type)) {
        return NULL;
    }

    njv = (json_value *)calloc(1, sizeof(json_value));
    if (!njv) {
        return NULL;
    }

    njv->parent = jv;
    njv->type = json_object;
    njv->u.array.length = 0;

    if (json_object == jv->type) {
        if (!name) {
            free(njv);
            return NULL;
        }
        len = jv->u.object.length;
        jv->u.object.values = realloc(jv->u.object.values, (len+1)*sizeof(*(jv->u.object.values)));
        if (!jv->u.object.values) {
            jv->u.object.length = 0;
            free(njv);
            return NULL;
        }
        jv->u.object.values[len].name = name;
        jv->u.object.values[len].name_length = strlen(name);
        jv->u.object.values[len].value = njv;
        jv->u.object.length++;
    } else if (json_array == jv->type) {
        len = jv->u.array.length;
        jv->u.array.values = realloc(jv->u.array.values, (len+1)*sizeof(*(jv->u.array.values)));
        if (!jv->u.array.values) {
            jv->u.array.length = 0;
            free(njv);
            return NULL;
        }
        jv->u.array.values[len] = njv;
        jv->u.array.length++;
    }

    return njv;
}

json_value* json_add_array(json_value *jv, char *name)
{
    int         len;
    json_value  *njv;

    if (!jv || (json_object != jv->type && json_array != jv->type)) {
        return NULL;
    }

    njv = (json_value *)calloc(1, sizeof(json_value));
    if (!njv) {
        return NULL;
    }

    njv->parent = jv;
    njv->type = json_array;
    njv->u.array.length = 0;

    if (json_object == jv->type) {
        if (!name) {
            free(njv);
            return NULL;
        }
        len = jv->u.object.length;
        jv->u.object.values = realloc(jv->u.object.values, (len+1)*sizeof(*(jv->u.object.values)));
        if (!jv->u.object.values) {
            jv->u.object.length = 0;
            free(njv);
            return NULL;
        }
        jv->u.object.values[len].name = name;
        jv->u.object.values[len].name_length = strlen(name);
        jv->u.object.values[len].value = njv;
        jv->u.object.length++;
    } else if (json_array == jv->type) {
        len = jv->u.array.length;
        jv->u.array.values = realloc(jv->u.array.values, (len+1)*sizeof(*(jv->u.array.values)));
        if (!jv->u.array.values) {
            jv->u.array.length = 0;
            free(njv);
            return NULL;
        }
        jv->u.array.values[len] = njv;
        jv->u.array.length++;
    }

    return njv;
}

int json_add_integer(json_value *jv, char *name, json_int_t v)
{
    int         len;
    json_value  *njv;

    if (!jv || (json_object != jv->type && json_array != jv->type)) {
        return -1;
    }

    njv = (json_value *)calloc(1, sizeof(json_value));

    if (!njv) {
        return -1;
    }

    njv->parent = jv;
    njv->type = json_integer;
    njv->u.integer = v;

    if (json_object == jv->type) {
        if (!name) {
            free(njv);
            return -1;
        }
        len = jv->u.object.length;
        jv->u.object.values = realloc(jv->u.object.values, (len+1)*sizeof(*(jv->u.object.values)));
        if (!jv->u.object.values) {
            jv->u.object.length = 0;
            free(njv);
            return -1;
        }
        jv->u.object.values[len].name = name;
        jv->u.object.values[len].name_length = strlen(name);
        jv->u.object.values[len].value = njv;
        jv->u.object.length++;
    } else if (json_array == jv->type) {
        len = jv->u.array.length;
        jv->u.array.values = realloc(jv->u.array.values, (len+1)*sizeof(*(jv->u.array.values)));
        if (!jv->u.array.values) {
            jv->u.array.length = 0;
            free(njv);
            return -1;
        }
        jv->u.array.values[len] = njv;
        jv->u.array.length++;
    }

    return 0;
}

int json_add_double(json_value *jv, char *name, double v)
{
    int         len;
    json_value  *njv;

    if (!jv || (json_object != jv->type && json_array != jv->type)) {
        return -1;
    }

    njv = (json_value *)calloc(1, sizeof(json_value));

    if (!njv) {
        return -1;
    }

    njv->parent = jv;
    njv->type = json_double;
    njv->u.dbl = v;

    if (json_object == jv->type) {
        if (!name) {
            free(njv);
            return -1;
        }
        len = jv->u.object.length;
        jv->u.object.values = realloc(jv->u.object.values, (len+1)*sizeof(*(jv->u.object.values)));
        if (!jv->u.object.values) {
            jv->u.object.length = 0;
            free(njv);
            return -1;
        }
        jv->u.object.values[len].name = name;
        jv->u.object.values[len].name_length = strlen(name);
        jv->u.object.values[len].value = njv;
        jv->u.object.length++;
    } else if (json_array == jv->type) {
        len = jv->u.array.length;
        jv->u.array.values = realloc(jv->u.array.values, (len+1)*sizeof(*(jv->u.array.values)));
        if (!jv->u.array.values) {
            jv->u.array.length = 0;
            free(njv);
            return -1;
        }
        jv->u.array.values[len] = njv;
        jv->u.array.length++;
    }

    return 0;
}

int json_add_string(json_value *jv, char *name, const char *v)
{
    int         len;
    json_value  *njv;

    if (!jv || !v || (json_object != jv->type && json_array != jv->type)) {
        return -1;
    }

    njv = (json_value *)calloc(1, sizeof(json_value));

    if (!njv) {
        return -1;
    }

    njv->parent = jv;
    njv->type = json_string;
    njv->u.string.length = strlen(v);
    njv->u.string.ptr = calloc(1, njv->u.string.length+1);
    if (!njv->u.string.ptr) {
        free(njv);
        return -1;
    }
    strcpy(njv->u.string.ptr, v);

    if (json_object == jv->type) {
        if (!name) {
            free(njv->u.string.ptr);
            free(njv);
            return -1;
        }
        len = jv->u.object.length;
        jv->u.object.values = realloc(jv->u.object.values, (len+1)*sizeof(*(jv->u.object.values)));
        if (!jv->u.object.values) {
            jv->u.object.length = 0;
            free(njv->u.string.ptr);
            free(njv);
            return -1;
        }
        jv->u.object.values[len].name = name;
        jv->u.object.values[len].name_length = strlen(name);
        jv->u.object.values[len].value = njv;
        jv->u.object.length++;
    } else if (json_array == jv->type) {
        len = jv->u.array.length;
        jv->u.array.values = realloc(jv->u.array.values, (len+1)*sizeof(*(jv->u.array.values)));
        if (!jv->u.array.values) {
            jv->u.array.length = 0;
            free(njv->u.string.ptr);
            free(njv);
            return -1;
        }
        jv->u.array.values[len] = njv;
        jv->u.array.length++;
    }

    return 0;
}

int json_add_boolean(json_value *jv, char *name, int v)
{
    int         len;
    json_value  *njv;

    if (!jv || (json_object != jv->type && json_array != jv->type)) {
        return -1;
    }

    njv = (json_value *)calloc(1, sizeof(json_value));

    if (!njv) {
        return -1;
    }

    njv->parent = jv;
    njv->type = json_boolean;
    njv->u.boolean = v;

    if (json_object == jv->type) {
        if (!name) {
            free(njv);
            return -1;
        }
        len = jv->u.object.length;
        jv->u.object.values = realloc(jv->u.object.values, (len+1)*sizeof(*(jv->u.object.values)));
        if (!jv->u.object.values) {
            jv->u.object.length = 0;
            free(njv);
            return -1;
        }
        jv->u.object.values[len].name = name;
        jv->u.object.values[len].name_length = strlen(name);
        jv->u.object.values[len].value = njv;
        jv->u.object.length++;
    } else if (json_array == jv->type) {
        len = jv->u.array.length;
        jv->u.array.values = realloc(jv->u.array.values, (len+1)*sizeof(*(jv->u.array.values)));
        if (!jv->u.array.values) {
            jv->u.array.length = 0;
            free(njv);
            return -1;
        }
        jv->u.array.values[len] = njv;
        jv->u.array.length++;
    }

    return 0;
}

int json_add_null(json_value *jv, char *name)
{
    int         len;
    json_value  *njv;

    if (!jv || (json_object != jv->type && json_array != jv->type)) {
        return -1;
    }

    njv = (json_value *)calloc(1, sizeof(json_value));

    if (!njv) {
        return -1;
    }

    njv->parent = jv;
    njv->type = json_null;

    if (json_object == jv->type) {
        if (!name) {
            free(njv);
            return -1;
        }
        len = jv->u.object.length;
        jv->u.object.values = realloc(jv->u.object.values, (len+1)*sizeof(*(jv->u.object.values)));
        if (!jv->u.object.values) {
            jv->u.object.length = 0;
            free(njv);
            return -1;
        }
        jv->u.object.values[len].name = name;
        jv->u.object.values[len].name_length = strlen(name);
        jv->u.object.values[len].value = njv;
        jv->u.object.length++;
    } else if (json_array == jv->type) {
        len = jv->u.array.length;
        jv->u.array.values = realloc(jv->u.array.values, (len+1)*sizeof(*(jv->u.array.values)));
        if (!jv->u.array.values) {
            jv->u.array.length = 0;
            free(njv);
            return -1;
        }
        jv->u.array.values[len] = njv;
        jv->u.array.length++;
    }

    return 0;
}

int json_get_output_string_length(const json_value *jv)
{
    int     i, n = 0;
    char    buf[64];

    switch(jv->type) {
    case    json_none:
        break;

    case    json_object:
        n += 1;
        for (i = 0; i < (int)jv->u.object.length; i++) {
            if (0 != i) {
                n += 1;
            }
            switch(jv->u.object.values[i].value->type) {
            case    json_none:
                break;

            case    json_object:
                n += strlen(jv->u.object.values[i].name) + 3;
                n += strlen(jv->u.object.values[i].value->u.string.ptr) + 2;
                break;

            case    json_array:
                n += strlen(jv->u.object.values[i].name) + 3;
                n += json_get_output_string_length(jv->u.object.values[i].value);
                break;

            case    json_integer:
                n += strlen(jv->u.object.values[i].name) + 3;
                n += sprintf(buf, "%ld", jv->u.object.values[i].value->u.integer);
                break;

            case    json_double:
                n += strlen(jv->u.object.values[i].name) + 3;
                n += sprintf(buf, "%f", jv->u.object.values[i].value->u.dbl);
                break;

            case    json_string:
                n += strlen(jv->u.object.values[i].name) + 3;
                n += strlen(jv->u.object.values[i].value->u.string.ptr) + 2;
                break;

            case    json_boolean:
                n += strlen(jv->u.object.values[i].name) + 3;
                n += jv->u.object.values[i].value->u.boolean?4:5;
                break;

            case    json_null:
                n += strlen(jv->u.object.values[i].name) + 3;
                n += 4;
                break;
            }
        }
        n += 1;
        break;

    case    json_array:
        n += 1;
        for (i = 0; i < (int)jv->u.array.length; i++) {
            if (0 != i) {
                n += 1;
            }
            switch(jv->u.array.values[i]->type) {
            case    json_none:
                break;

            case    json_object:
                n += json_get_output_string_length(jv->u.array.values[i]);
                break;

            case    json_array:
                n += json_get_output_string_length(jv->u.array.values[i]);
                break;

            case    json_integer:
                n += sprintf(buf, "%d", (int)jv->u.array.values[i]->u.integer);
                break;

            case    json_double:
                n += sprintf(buf, "%f", jv->u.array.values[i]->u.dbl);
                break;

            case    json_string:
                n += strlen(jv->u.array.values[i]->u.string.ptr) + 2;
                break;

            case    json_boolean:
                n += jv->u.array.values[i]->u.boolean?4:5;
                break;

            case    json_null:
                n += 4;
                break;
            }
        }
        n += 1;
        break;

    case    json_integer:
        n += sprintf(buf, "%d", (int)jv->u.integer);
        break;

    case    json_double:
        n += sprintf(buf, "%f", jv->u.dbl);
        break;

    case    json_string:
        n += strlen(jv->u.string.ptr) + 2;
        break;

    case    json_boolean:
        n += jv->u.boolean?4:5;
        break;

    case    json_null:
        n += 4;
        break;
    }

    return n;
}

int json_output_string(const json_value *jv, char *buf)
{
    int     i, n = 0;

    switch(jv->type) {
    case    json_none:
        break;

    case    json_object:
        n += sprintf(buf+n, "%s", "{");
        for (i = 0; i < (int)jv->u.object.length; i++) {
            if (0 != i) {
                n += sprintf(buf+n, "%s", ",");
            }
            switch(jv->u.object.values[i].value->type) {
            case    json_none:
                break;

            case    json_object:
                n += sprintf(buf+n, "\"%s\":", jv->u.object.values[i].name);
                n += json_output_string(jv->u.object.values[i].value, buf+n);
                break;

            case    json_array:
                n += sprintf(buf+n, "\"%s\":", jv->u.object.values[i].name);
                n += json_output_string(jv->u.object.values[i].value, buf+n);
                break;

            case    json_integer:
                n += sprintf(buf+n, "\"%s\":%ld", jv->u.object.values[i].name, jv->u.object.values[i].value->u.integer);
                break;

            case    json_double:
                n += sprintf(buf+n, "\"%s\":%f", jv->u.object.values[i].name, jv->u.object.values[i].value->u.dbl);
                break;

            case    json_string:
                n += sprintf(buf+n, "\"%s\":\"%s\"", jv->u.object.values[i].name, jv->u.object.values[i].value->u.string.ptr);
                break;

            case    json_boolean:
                n += sprintf(buf+n, "\"%s\":%s", jv->u.object.values[i].name, jv->u.object.values[i].value->u.boolean?"true":"false");
                break;

            case    json_null:
                n += sprintf(buf+n, "\"%s\":%s", jv->u.object.values[i].name, "null");
                break;
            }
        }
        n += sprintf(buf+n, "%s", "}");
        break;

    case    json_array:
        n += sprintf(buf+n, "%s", "[");
        for (i = 0; i < (int)jv->u.array.length; i++) {
            if (0 != i) {
                n += sprintf(buf+n, "%s", ",");
            }
            switch(jv->u.array.values[i]->type) {
            case    json_none:
                break;

            case    json_object:
                n += json_output_string(jv->u.array.values[i], buf+n);
                break;

            case    json_array:
                n += json_output_string(jv->u.array.values[i], buf+n);
                break;

            case    json_integer:
                n += sprintf(buf+n, "%d", (int)jv->u.array.values[i]->u.integer);
                break;

            case    json_double:
                n += sprintf(buf+n, "%f", jv->u.array.values[i]->u.dbl);
                break;

            case    json_string:
                n += sprintf(buf+n, "\"%s\"", jv->u.array.values[i]->u.string.ptr);
                break;

            case    json_boolean:
                n += sprintf(buf+n, "%s", jv->u.array.values[i]->u.boolean?"true":"false");
                break;

            case    json_null:
                n += sprintf(buf+n, "%s", "null");
                break;
            }
        }
        n += sprintf(buf+n, "%s", "]");
        break;

    case    json_integer:
        n += sprintf(buf+n, "%d", (int)jv->u.integer);
        break;

    case    json_double:
        n += sprintf(buf+n, "%f", jv->u.dbl);
        break;

    case    json_string:
        n += sprintf(buf+n, "\"%s\"", jv->u.string.ptr);
        break;

    case    json_boolean:
        n += sprintf(buf+n, "%s", jv->u.boolean?"true":"false");
        break;

    case    json_null:
        n += sprintf(buf+n, "%s", "null");
        break;
    }

    return n;
}

int json_get_format_string_length(const char *text)
{
    size_t pos = 0, text_length;
    unsigned int indentation = 0;    /* the current indentation level */
    char loop;
    int count = 0;

    text_length = strlen (text);

    while (pos < text_length)
    {
        switch (text[pos])
        {
        case '\x20':
        case '\x09':
        case '\x0A':
        case '\x0D':    /* JSON insignificant white spaces */
            pos++;
            break;

        case '{':
            indentation++;
            count += 2;
            count += indentation;
            pos++;
            break;

        case '}':
            indentation--;
            count += 1;
            count += indentation;
            count++;
            pos++;
            break;

        case '[':
            indentation++;
            count += 2;
            count += indentation;
            pos++;
            break;

        case ']':
            indentation--;
            count += 1;
            count += indentation;
            count++;
            pos++;
            break;

        case ':':
            count += 2;
            pos++;
            break;

        case ',':
            count += 2;
            count += indentation;
            pos++;
            break;

        case '\"':    /* open string */
            count++;
            pos++;
            loop = 1;    /* inner string loop trigger is enabled */
            while (loop)
            {
                if (text[pos] == '\\')    /* escaped sequence */
                {
                    count++;
                    pos++;
                    if (text[pos] == '\"')    /* don't consider a \" escaped sequence as an end of string */
                    {
                        count++;
                        pos++;
                    }
                }
                else if (text[pos] == '\"')    /* reached end of string */
                {
                    loop = 0;
                }

                count++;

                pos++;
                if (pos >= text_length)
                {
                    loop = 0;
                }
            }
            break;

        default:
            count++;
            pos++;
            break;
        }
    }

    return count;
}

/*
 *  json_format_string is stolen from https://sourceforge.net/projects/mjson/
 */

char* json_format_string(const char *text, char *outbuf, size_t size)
{
    size_t pos, text_length, len;
    unsigned int indentation = 0;    /* the current indentation level */
    unsigned int i;        /* loop iterator variable */
    char loop;
    int count = 0;
    char    *dst = NULL, *output = NULL;

    len = (size_t)json_get_format_string_length(text);
    if (outbuf) {
        if (size < (len+1)) {
            return NULL;
        }
        dst = outbuf;
    } else {
        output = (char *)malloc(len+1);
        if (!output) {
            return NULL;
        }
        dst = output;
    }

    memset(outbuf, 0, len+1);

    dst[len] = 0;
    text_length = strlen (text);
    pos = 0;
    while (pos < text_length)
    {
        switch (text[pos])
        {
        case '\x20':
        case '\x09':
        case '\x0A':
        case '\x0D':
            pos++;
            break;

        case '{':
            indentation++;
            strcat(dst, "{\n");
            count += 2;
            for (i = 0; i < indentation; i++)
            {
                dst[count++] = '\t';
            }
            pos++;
            break;

        case '}':
            indentation--;
            dst[count++] = '\n';
            for (i = 0; i < indentation; i++)
            {
                dst[count++] = '\t';
            }
            dst[count++] = '}';
            pos++;
            break;

        case '[':
            indentation++;
            strcat(dst, "[\n");
            count += 2;
            for (i = 0; i < indentation; i++)
            {
                dst[count++] = '\t';
            }
            pos++;
            break;

        case ']':
            indentation--;
            dst[count++] = '\n';
            for (i = 0; i < indentation; i++)
            {
                dst[count++] = '\t';
            }
            dst[count++] = ']';
            pos++;
            break;

        case ':':
            strcat(dst, ": ");
            count += 2;
            pos++;
            break;

        case ',':
            strcat(dst, ",\n");
            count += 2;
            for (i = 0; i < indentation; i++)
            {
                dst[count++] = '\t';
            }
            pos++;
            break;

        case '\"':    /* open string */
            dst[count++] = text[pos];
            pos++;
            loop = 1;    /* inner string loop trigger is enabled */
            while (loop)
            {
                if (text[pos] == '\\')    /* escaped sequence */
                {
                    dst[count++] = '\\';
                    pos++;
                    if (text[pos] == '\"')    /* don't consider a \" escaped sequence as an end of string */
                    {
                        dst[count++] = '\"';
                        pos++;
                    }
                }
                else if (text[pos] == '\"')    /* reached end of string */
                {
                    loop = 0;
                }

                dst[count++] = text[pos];

                pos++;
                if (pos >= text_length)
                {
                    loop = 0;
                }
            }
            break;

        default:
            dst[count++] = text[pos];
            pos++;
            break;
        }
    }

    return dst;
}

