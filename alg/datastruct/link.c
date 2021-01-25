/* 
 */
#include <stdio.h>
#include <stdlib.h>

typedef struct _node_s {
    int                 val;
    struct _node_s      *next;
}node_t, list_t;

list_t* create_list() {
    list_t* tmp = malloc(sizeof(node_t));
    if (NULL == tmp) {
        return NULL;
    }
    tmp->val = 0;   // 
    tmp->next = NULL;

    return tmp;
}

int append_list(list_t* list, int val) {
    list_t *tmp = malloc(sizeof(node_t));
    tmp->val = val;
    tmp->next = NULL;

    while (list->next) {
        list = list->next;
    }
    list->next = tmp;

    return 0;
}

void traverse(list_t* list) {
    while (list->next) {
        printf("%d ", list->next->val);
        list = list->next;
    }
    puts("\n");
}

int reverse(list_t* list) {
    node_t* cur = list->next;
    node_t* next = cur->next;
    node_t* tmp = NULL;
    cur->next = NULL;

    while (next) {
        tmp = next->next;
        next->next = cur;
        cur = next;
        next = tmp;
    }
    list->next = cur;

    return 0;
} 

list_t* merge_sorted_list(list_t* foo, list_t* bar) {
    list_t* ret = create_list();
    node_t* f = foo->next;
    node_t* b = bar->next;
    while (b && f) {
        if (b->val < f->val) {
            append_list(ret, b->val);
            b = b->next;
        }
        if (b->val > f->val) {
            append_list(ret, f->val);
            f = f->next;
        }
    }
    while (b) {
        append_list(ret, b->val);
        b = b->next;
    }
    while (f) {
        append_list(ret, f->val);
        f = f->next;
    }
    return ret;
}

int main(int argc, char** argv)
{
    list_t* list = create_list();
    for (int i=0; i<10; i++) {
        append_list(list, i);
    }

    traverse(list);

    reverse(list);

    traverse(list);

    list_t* foo = create_list();
    list_t* bar = create_list();
    for (int i=0; i<10; i++) {
        append_list(foo, 2*i);
        append_list(bar, 2*i + 1);
    }
    traverse(foo);
    traverse(bar);
    traverse(merge_sorted_list(foo, bar));
    return 0;
}
