#include "9cc.h"

static int str_label;
Map *vars;
Vector *globals;
Vector *strings;
static int stacksize;

static Node *maybe_decay(Node *base, bool decay) {
    if (!decay || base->ty->ty != ARRAY)
        return base;
    Node *node = calloc(1, sizeof(Node));
    node->op = ND_ADDR;
    node->ty = ptr_to(base->ty->ptr_to);
    node->lhs = base;
    return node;
}

static void check_lval(Node *node) {
    int op = node->op;
    if (op != ND_LVAR && op != ND_GVAR && op != ND_DEREF && op != ND_DOT) {
        fprintf(stderr, "not an lvaleu: %d (%s)", op, node->name);
        exit(1);
    }
}

static Node *cast(Node *base, Type *ty) {
    Node *node = calloc(1, sizeof(Node));
    node->op = ND_CAST;
    node->ty = ty;
    node->lhs = base;
    return node;
}

Node *create_new_node(int ty, Node *lhs, Node *rhs) {
    Node *node = malloc(sizeof(Node));
    node->op = ty;
    node->ty = lhs->ty;
    node->lhs = lhs;
    node->rhs = rhs;
    return node;
}

static Node* walk(Node *node, bool decay);

Node *recreate_assgin_op(int ty, Node *lhs, Node *rhs) {
    Node* new_rhs = create_new_node(ty, lhs, rhs);
    return walk(create_new_node('=', lhs, new_rhs), true);
}

Var *new_global(Type* ty, char *name, char *data, int len, bool is_extern, bool is_static) {
    Var *var = calloc(1, sizeof(Var));
    var->ty = ty;
    var->is_local = false;
    var->is_extern = is_extern;
    var->is_static = is_static;
    var->data = data;
    var->len = len;
    var->name = name;
    return var;
}


static Node* walk(Node *node, bool decay) {
    switch (node->op) {
    case ND_NUM:
        return node;
    case ND_STR: {
        char *name = format(".L.str%d", str_label++);
        Var *var = new_global(node->ty, name, node->data, node->len, false, true);
        var->initializer = gvar_init_string(node->data, node->len);
        vec_push(globals, var);
        Node *ret = calloc(1, sizeof(Node));
        ret->op = ND_GVAR;
        ret->ty = node->ty;
        ret->name = name;
        return walk(ret, decay);
    }
    case ND_IDENT: {
        Var *var = map_get(vars, node->name);
        if (!var) {
            fprintf(stderr, "undefined variable: %s", node->name);
            exit(1);
        }
        if (var->is_local) {
            Node *ret = calloc(1, sizeof(Node));
            ret->op = ND_LVAR;
            ret->ty = var->ty;
            ret->offset = var->offset;
            ret->name = var->name;
            return maybe_decay(ret, decay);
        }

        Node *ret = calloc(1, sizeof(Node));
        ret->op = ND_GVAR;
        ret->ty = var->ty;
        ret->name = var->name;
        return maybe_decay(ret, decay);
    }
    case ND_LVAR:
        return node;
    case ND_DOT:
        node->lhs = walk(node->lhs, true);
        if (node->lhs->ty->ty != STRUCT) {
            fprintf(stderr, "struct expected before '.'");
            exit(1);
        }
        Type *ty = node->lhs->ty;
        if (!ty->members) {
            fprintf(stderr, "incomplete type");
            exit(1);
        }
        for (int i = 0; i < ty->members->len; i++) {
            Node *m = ty->members->data[i];
            if (strcmp(m->name, node->name))
                continue;
            node->ty = m->ty;
            node->offset = m->ty->offset;
            return maybe_decay(node, decay);
        }
        fprintf(stderr, "member missing: %s", node->name);
        exit(1);
    case ND_GVAR:
        if (decay && node->ty->ty == ARRAY)
            return maybe_decay(node, decay);
        return node;
    case ND_VARDEF:
        roundup(stacksize, node->ty->align);
        stacksize += node->ty->size;

        node->offset = stacksize;

        Var *var = calloc(1, sizeof(Var));
        var->ty = node->ty;
        var->offset = stacksize;
        var->is_local = true;
        var->name = node->name;
        map_put(vars, node->name, var);
        if (node->init)
            node->init = walk(node->init, true);
        return node;
    case ND_IF:
        node->cond= walk(node->cond, true);
        node->if_body = walk(node->if_body, true);
        if (node->else_body)
            node->else_body = walk(node->else_body, true);
        return node;
    case '?':
        node->cond = walk(node->cond, true);
        node->if_body = walk(node->if_body, true);
        node->else_body = walk(node->else_body, true);
        node->ty = node->if_body->ty;
        return node;
    case ND_FOR:
        node->lhs = walk(node->lhs, true);
        if (node->lhs2)
            node->lhs2 = walk(node->lhs2, true);
        node->rhs = walk(node->rhs, true);
        if (node->lhs3)
            node->lhs3 = walk(node->lhs3, true);
        return node;
    case ND_WHILE:
        node->lhs = walk(node->lhs, true);
        node->rhs = walk(node->rhs, true);
        return node;
    case ND_DO_WHILE:
        node->body = walk(node->body, true);
        node->cond = walk(node->cond, true);
        return node;
    case ND_MUL_EQ:
        return recreate_assgin_op('*', node->lhs, node->rhs);
    case ND_DIV_EQ:
        return recreate_assgin_op('/', node->lhs, node->rhs);
    case ND_MOD_EQ:
        return recreate_assgin_op('%', node->lhs, node->rhs);
    case ND_ADD_EQ:
        return recreate_assgin_op('+', node->lhs, node->rhs);
    case ND_SUB_EQ:
        return recreate_assgin_op('-', node->lhs, node->rhs);
    case ND_SHL_EQ:
        return recreate_assgin_op(ND_LSHIFT, node->lhs, node->rhs);
    case ND_SHR_EQ:
        return recreate_assgin_op(ND_RSHIFT, node->lhs, node->rhs);
    case ND_BITAND_EQ:
        return recreate_assgin_op('&', node->lhs, node->rhs);
    case ND_XOR_EQ:
        return recreate_assgin_op('^', node->lhs, node->rhs);
    case ND_BITOR_EQ:
        return recreate_assgin_op('|', node->lhs, node->rhs);
    case '=':
        node->lhs = walk(node->lhs, false);
        node->rhs = walk(node->rhs, true);
        if (node->lhs->ty->ty == BOOL)
            node->rhs = cast(node->rhs, bool_ty());
        node->ty = node->lhs->ty;
        return node;
    case ND_SWITCH:
        node->cond = walk(node->cond, true);
        node->body = walk(node->body, true);
        return node;
    case ND_DEFAULT:
    case ND_CASE:
        node->body = walk(node->body, true);
        return node;
    case '+':
    case '-':
    case '*':
    case '/':
    case '%':
    case '<':
    case '>':
    case ND_LOGAND:
    case ND_LOGOR:
    case '|':
    case '^':
    case '&':
    case ND_LSHIFT:
    case ND_RSHIFT:
    case ND_EQ:
    case ND_NE:
    case ND_LE:
        node->lhs = walk(node->lhs, true);
        node->rhs = walk(node->rhs, true);
        node->ty = node->lhs->ty;
        return node;
    case ND_DEREF:
        node->lhs = walk(node->lhs, true);
        if(node->lhs->ty->ty == ARRAY)
            fprintf(stderr, "operand is ARRAY\n");

        if(node->lhs->ty->ty != PTR) {
            fprintf(stderr, "operand must be a pointer");
            exit(1);
        }

        if(node->lhs->ty->ptr_to->ty == VOID) {
            fprintf(stderr, "cannot dereference void pointer");
            exit(1);
        }

        node->ty = node->lhs->ty->ptr_to; // *p の場合 tyはptr_of
        return maybe_decay(node, decay);
    case ND_ADDR:
        node->lhs = walk(node->lhs, true);
        check_lval(node->lhs);
        node->ty = ptr_to(node->lhs->ty);
        return node;
    case ND_PREINC:
    case ND_PREDEC:
    case ND_POSTINC:
    case ND_POSTDEC:
    case ND_NEG:
    case '~':
    case '!':
        node->lhs = walk(node->lhs, true);
        node->ty  = node->lhs->ty;
        return node;
    case ND_RETURN:
        if (node->lhs)
            node->lhs = walk(node->lhs, true);
        return node;
    case ND_BREAK:
    case ND_CONTINUE:
        return node;
    case ND_CALL: {
        Var *var = map_get(vars, node->name);
        if (var && var->ty->ty == FUNC) {
            node->ty = var->ty->returning;
        } else {
            fprintf(stderr, "bad function: %s\n", node->name);
            node->ty = int_ty();
        }
        for (int i = 0; i < node->args->len; i++)
            node->args->data[i] = walk(node->args->data[i], true);
        return node;
    }
    case ND_FUNC:
        for (int i = 0; i < node->args->len; i++)
            node->args->data[i] = walk(node->args->data[i], true);
        node->body = walk(node->body, true);
        return node;
    case ND_COMP_STMT:
        for (int i = 0; i < node->stmts->len; i++)
            node->stmts->data[i] = walk(node->stmts->data[i], true);
        return node;
    case ND_EXPR_STMT:
        node->lhs = walk(node->lhs, true);
        return node;
    case ND_STMT_EXPR:
        node->lhs = walk(node->lhs, true);
        return node;
    case ND_CAST:
        node->lhs = walk(node->lhs, true);
        return node;
    case ND_SIZEOF:
        node->lhs = walk(node->lhs, false);
        node->op = ND_NUM;
        node->ty = node->lhs->ty;
        node->val = node->lhs->ty->size;
        return node;
    case ND_ALIGNOF:
        node->lhs = walk(node->lhs, false);
        node->op = ND_NUM;
        node->ty = node->lhs->ty;
        node->val = node->lhs->ty->align;
        return node;
    case ND_NULL:
        return node;
    case ',':
        node->lhs = walk(node->lhs, true);
        node->rhs = walk(node->rhs, true);
        node->ty = node->rhs->ty;
        return node;
    default:
        assert(0 && "unknown node type");
        return NULL;
    }
}

void sema(Vector *nodes) {
    str_label = 0;
    if (!globals)
        globals = new_vector();
    vars = new_map();
    for (int i = 0; i < nodes->len; i++) {
        Node *node = nodes->data[i];

        // Global Variables
        if (node->op == ND_VARDEF) {
            Var *var = new_global(node->ty, node->name, node->data, node->len, node->is_extern, node->is_static);
            if (node->initializer) {
                var->initializer = node->initializer;
            }

            vec_push(globals, var);
            map_put(vars, node->name, var);
            continue;
        }

        assert(node->op == ND_DECL || node->op == ND_FUNC);
        Var *var = new_global(node->ty, node->name, "", 0, node->is_extern, node->is_static);
        map_put(vars, node->name, var);
        if (node->op == ND_DECL)
            continue;

        stacksize = 0;
        node = walk(node, true);
        node->stacksize = stacksize;
    }
    fprintf(stderr, "sema done\n");
}
