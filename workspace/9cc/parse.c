#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "9cc.h"


int pos = 0;
int variables = 0;
// エラーを報告するための関数
void error(char *str, char *i){
    fprintf(stderr, "%s%s\n", str, i);
    exit(1);
}

void error_token(int i){
    Token *t = tokens->data[i];
    error("予期せぬトークンです:", t->input);
}


int consume(int ty) {
    Token *t = tokens->data[pos];
    if (t->ty != ty)
        return 0;
    pos++;
    return 1;
}

Node *new_node(int ty, Node *lhs, Node *rhs) {
    Node *node = malloc(sizeof(Node));
    node->ty = ty;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

Node *new_node_num(int val) {
    Node *node = malloc(sizeof(Node));
    node->ty = ND_NUM;
    node->val = val;
    return node;
}

Node *new_node_ident(char *name) {
    Node *node = malloc(sizeof(Node));
    node->ty = ND_IDENT;
    node->name = name;
    return node;
}

int is_alnum(char c) {
    return ('a' <= c && c <= 'z') ||
           ('A' <= c && c <= 'Z') ||
           ('0' <= c && c <= '9') ||
           (c == '_');
}

int tokenize_comparable(Vector* tokens, int ty, char *p, char* token) {
    int len = strlen(token);
    if (strncmp(p, token, len) == 0) {
        add_token(tokens, ty, p);
        return 1;
    }
    return 0;
}
// pが指している文字列をトークンに分割してtokensに保存する
void tokenize(char *p) {
    while (*p) {
        // 空白文字列をスキップ
        if (isspace(*p)) {
            p++;
            continue;
        }

        if (strncmp(p, "return", 6) == 0 && !is_alnum(p[6])) {
            add_token(tokens, TK_RETURN, p);
            p += 6;
            continue;
        }

        if (tokenize_comparable(tokens, TK_EQ, p, "==")) { p += 2; continue; };
        if (tokenize_comparable(tokens, TK_NE, p, "!=")) { p += 2; continue; };
        if (tokenize_comparable(tokens, TK_LE, p, "<=")) { p += 2; continue; };
        if (tokenize_comparable(tokens, TK_GE, p, ">=")) { p += 2; continue; };
        if (tokenize_comparable(tokens, TK_L, p, "<")) { p += 1; continue; };
        if (tokenize_comparable(tokens, TK_G, p, ">")) { p += 1; continue; };

        if (strncmp(p, "if", 2) == 0 && !is_alnum(p[2])) {
            add_token(tokens, TK_IF, p);
            p += 2;
            continue;
        }

        if (*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '(' || *p == ')' || *p == '=' || *p == ';') {
            add_token(tokens, *p, p);
            p++;
            continue;
        }

        if (isdigit(*p)) {
            Token * t = add_token(tokens, TK_NUM, p);
            t->val = strtol(p, &p, 10);
            continue;
        }

        if (is_alnum(*p)) {
            char* init_p = p;
            int len = 0;
            // パースできる文字出るじゃない文字が出てくるまで
            Token *t = add_token(tokens, TK_IDENT, p);
            while(is_alnum(*p)){
                len++;
                p++;
            }
            char *name = (char *) malloc(len + 1);
            strncpy(name, init_p, len);
            t->name = name;
            continue;
        }

        fprintf(stderr, "トークナイズできません: %s\n", p);
        exit(1);
    }
    add_token(tokens, TK_EOF, p);
}

void program() {
    int i = 0;
    while(((Token *)tokens->data[pos])->ty != TK_EOF)
        code[i++] = control();
    code[i] = NULL;
}

Node *control() {
    Node *node = stmt();
    if (consume(TK_IF)) {
        node = new_node(TK_IF, node, control());
    }
    return node;
}

Node *stmt() {
    Node *node;
    if (consume(TK_RETURN)) {
        node = malloc(sizeof(Node));
        node->ty = ND_RETURN;
        node->lhs = assign();
    } else {
        node = assign();
    }
    if (!consume(';')) {
        Token *t = tokens->data[pos];
        error("';'ではないトークンです: %s", t->input);
    }
    return node;
}

Node *assign() {
    Node *lhs = equality();
    if (consume('='))
        return new_node('=', lhs, assign());
    return lhs;
}

Node *equality() {
    Node *lhs = relational();
    if(consume(TK_EQ))
        return new_node(TK_EQ, lhs, equality());
    if(consume(TK_NE))
        return new_node(TK_NE, lhs, equality());
    return lhs;
}

Node *relational() {
    Node *lhs = add();
    if(consume(TK_LE))
        return new_node(TK_LE, lhs, relational());
    if(consume(TK_L))
        return new_node(TK_L, lhs, relational());
    if(consume(TK_GE))
        return new_node(TK_GE, lhs, relational());
    if(consume(TK_G))
        return new_node(TK_G, lhs, relational());

    return lhs;
}

Node *add() {
    Node *lhs = mul();

    if(consume('+'))
        return new_node('+', lhs, add());

    if(consume('-'))
        return new_node('-', lhs, add());

    if (lhs->ty == ND_NUM)
        return lhs;
    return lhs;
}

Node *mul() {
    Node *lhs = term();
    Token *t = tokens->data[pos];
    if(t->ty == TK_EOF)
        return lhs;

    if(consume('*'))
        return new_node('*', lhs, mul());

    if(consume('/'))
        return new_node('/', lhs, mul());

    if (lhs->ty == ND_NUM)
        return lhs;
    return lhs;
}

Node *term() {
    Token *t = tokens->data[pos];
    if (t->ty == TK_NUM){
        return new_node_num(((Token *)tokens->data[pos++])->val);
    }

    if (t->ty == TK_IDENT) {
        // すでに使われた変数かどうか
        long offset = (long) map_get(variable_map, t->name);

        // 使われてなければ、識別子をキーとしてRBPからのオフセットを追加する
        if (offset == 0){
            offset = (variables + 1) * 8;

            map_put(variable_map, t->name, (void *) offset);
            variables++;
        }
        return new_node_ident(((Token *)tokens->data[pos++])->name);
    }

    if(consume('(')) {
        Node *node = assign();
        Token *t = tokens->data[pos];
        if (t->ty != ')') {
            error("閉じ括弧で閉じる必要があります: %s", t->input);
        }
        pos++;
        return node;
    }
    t = tokens->data[pos];
    error("数字でも開き括弧でもないトークンです: %s", t->input);
    exit(1);
}
