#include "absll.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct NODE* PNODE;

struct NODE {
    void* value;
    PNODE next;
};

struct ABSLL {
    unsigned int length;
    PNODE head;
    PNODE tail;
};

PABSLL ll_create() {
    PABSLL plist = (PABSLL)malloc(sizeof(struct ABSLL));
    plist -> length = 0;
    plist -> head = NULL;
    plist -> tail = NULL;
    return plist;
}

void ll_destroy(PABSLL plist, DESTROY_OBJECT del) {
    if(!del || !plist) {
        printf("ll_destroy: Parameter illegal.\n");
        exit(1);
    } else {
        ll_clear(plist, del);
        free(plist);
    }
}

void ll_clear(PABSLL plist, DESTROY_OBJECT del) {
    if(!plist || !del) {
        printf("ll_clear: Parameter illegal.\n");
        exit(1);
    }
    while(plist -> head) {
        PNODE t = plist -> head;
        plist -> head = t -> next;
        del(t -> value);
        free(t);
        plist -> length--;
    }
    plist -> tail = NULL;
}

void ll_delete(PABSLL plist, unsigned int pos, DESTROY_OBJECT del) {
    if(!del || !plist || pos < 0 || pos >= plist -> length) {
        printf("ll_delete: Parameter illegal.\n");
        exit(1);
    }
    if(pos == 0) {
        PNODE t = plist -> head;
        plist -> head = t -> next;
        if(!t -> next) {
            plist -> tail = NULL;
        }
        del(t -> value);
        free(t);
        plist -> length--;
    } else if(pos < plist -> length) {
        PNODE u = plist -> head, t;
        for(unsigned int i = 0; i < pos - 1; i++) {
            u = u -> next;
        }
        t = u -> next;
        u -> next = t -> next;
        if(!t -> next) {
            plist -> tail = u;
        }
        del(t -> value);
        free(t);
        plist -> length--;
    }
}

void ll_append(PABSLL plist, void* data) {
    if(!plist || !data) {
        printf("ll_append: Parameter illegal.\n");
        exit(1);
    }
    PNODE node = (PNODE)malloc(sizeof(struct NODE));
    node -> value = data;
    node -> next = NULL;
    if(!plist -> head) {
        plist -> head = node;
        plist -> tail = node;
    } else {
        plist -> tail -> next = node;
        plist -> tail = node;
    }
    plist -> length++;
}

void ll_insert(PABSLL plist, unsigned int pos, void* data) {
    if(!plist || !data || pos < 0 || pos >= plist -> length) {
        printf("ll_insert: Parameter illegal.\n");
        exit(1);
    }
    PNODE node = (PNODE)malloc(sizeof(struct NODE));
    node -> value = data;
    node -> next = NULL;
    if(pos == 0) {
        node -> next = plist -> head;
        plist -> head = node;
        plist -> length++;
    } else if(pos == plist -> length - 1) {
        ll_append(plist,node);
    } else {
        PNODE u = plist -> head;
        for(unsigned int i = 0; i < pos - 1; i++) {
            u = u -> next;
        }
        node -> next = u -> next;
        u -> next = node;
        plist -> length++;
    }
}

bool ll_is_empty(PABSLL plist) {
    if(!plist) {
        printf("ll_is_empty: Parameter illegal.\n");
        exit(1);
    }
    if(plist -> length == 0) {
        return true;
    }
    return false;
}

unsigned int ll_get_length(PABSLL plist) {
    if(!plist) {
        printf("ll_get_length: Parameter illegal.\n");
        exit(1);
    }
    return plist -> length;
}

void ll_traverse(PABSLL plist, MANIPULATE_OBJECT op) {
    if(!plist || !op) {
        printf("ll_traverse: Parameter illegal.\n");
        exit(1);
    }
    PNODE t = plist -> head;
    while(t) {
        op(t -> value);
        t = t -> next;
    }
}

bool ll_search(PABSLL plist, void* node, COMPARE_OBJECT cmp) {
    if(!plist || !node || !cmp) {
        printf("ll_search: Parameter illegal.\n");
        exit(1);
    }
    PNODE t = plist -> head;
    while(t) {
        if(cmp(node,t) == 0) {
            return true;
        }
        t = t -> next;
    }
    return false;
}