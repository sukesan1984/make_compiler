#include "9cc.h"

void assert(int cond) {
    if (cond) return;
    fprintf(stderr, "[ASSERT]\n");
    exit(EXIT_FAILURE);
}

char *format(char *fmt, int label) {
    char buf[2048];
    sprintf(buf, fmt, label);
    return strdup(buf);
}

// 可変長Vector
// 任意蝶の入力をサポートする
Vector *new_vector() {
    Vector *vec = malloc(sizeof(Vector));
    vec-> data = malloc(sizeof(void *) * 16);
    vec->capacity = 16;
    vec->len = 0;
    return vec;
}

void vec_push(Vector *vec, void *elem) {
    if (vec->capacity == vec->len) {
        vec->capacity *= 2;
        vec->data = realloc(vec->data, sizeof(void *) * vec->capacity);
    }
    vec->data[vec->len++] = elem;
}

void* vec_pop(Vector *v) {
    return v->data[--v->len];
}

Map *new_map() {
    Map *map = malloc(sizeof(Map));
    map->keys = new_vector();
    map->vals = new_vector();
    return map;
}

void map_put(Map *map, char *key, void *val) {
    vec_push(map->keys, key);
    vec_push(map->vals, val);
}

void map_puti(Map *map, char *key, int i) {
    vec_push(map->keys, key);
    vec_push(map->vals, (void*)(intptr_t)i);
}

void *map_get(Map *map, char *key) {
    for (int i = map->keys->len -1; i >= 0; i--)
        if (strcmp(map->keys->data[i], key) == 0)
            return map->vals->data[i];
    return NULL;
}

int map_geti(Map *map, char *key, int undef) {
    for (int i = map->keys->len -1; i >= 0; i--)
        if (!strcmp(map->keys->data[i], key))
            return (intptr_t)map->vals->data[i];
    return undef;
}

StringBuilder *new_sb() {
    StringBuilder *sb = malloc(sizeof(StringBuilder));
    sb->data = malloc(8);
    sb->capacity = 8;
    sb->len = 0;
    return sb;
}

static void sb_grow(StringBuilder *sb, int len) {
    if (sb->len + len <= sb->capacity)
        return;
    while (sb->len + len > sb->capacity)
        sb->capacity *= 2;
    sb->data = realloc(sb->data, sb->capacity);
}

void sb_add(StringBuilder *sb, char c) {
    sb_grow(sb, 1);
    sb->data[sb->len++] = c;
}

void sb_append(StringBuilder *sb, char *s) {
    sb_append_n(sb, s, strlen(s));
}

void sb_append_n(StringBuilder *sb, char *s, int len) {
    sb_grow(sb, len);
    memcpy(sb->data + sb->len, s, len);
    sb->len += len;
}

char *sb_get(StringBuilder *sb) {
    sb_add(sb, '\0');
    return sb->data;
}

bool map_exists(Map *map, char *key) {
    for (int i = map->keys->len -1; i >= 0; i--)
        if (strcmp(map->keys->data[i], key) == 0)
            return true;
    return false;
}

Type *ary_of(Type *base, size_t size) {
    Type *ty = calloc(1, sizeof(Type));
    ty->ty = ARRAY;
    ty->array_size = size;
    ty->ptr_to = base;
    ty->size = base->size * size;
    ty->align = base->align;
    return ty;
}

Type *ptr_to(Type *base) {
    Type *ty = calloc(1, sizeof(Type));
    ty->ty = PTR;
    ty->ptr_to = base;
    ty->align = 8;
    ty->size = 8;
    return ty;
}

// 指定されたファイルの内容を返す
char *read_file(char *path) {
    // ファイルを開く
    FILE *fp = fopen(path, "r");
    if (!fp) {
        fprintf(stderr, "cannnot open %s", path);
        exit(1);
    }

    // ファイルの長さを調べる
    if (fseek(fp, 0, SEEK_END) == -1) {
        fprintf(stderr, "%s: fseek", path);
        exit(1);
    }
    size_t size = ftell(fp);
    if (fseek(fp, 0, SEEK_SET) == -1) {
        fprintf(stderr, "%s: fseek", path);
        exit(1);
    }

    // ファイル内容を読み込む
    char *buf = malloc(size + 2);
    fread(buf, size, 1, fp);

    // ファイルが必ず"\n\0"で終わっているようにする
    if (size == 0 || buf[size - 1] != '\n')
        buf[size++] = '\n';
    buf[size] = '\0';
    fclose(fp);
    return buf;
}

int roundup(int x, int align) {
    return (x + align - 1) & ~(align - 1);
}
