#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"

/* Create an empty queue */
struct list_head *q_new()
{
    struct list_head *new = malloc(sizeof(struct list_head));
    if (!new)
        return NULL;
    INIT_LIST_HEAD(new);
    return new;
}

/* Free all storage used by queue */
void q_free(struct list_head *head)
{
    if (!head)
        return;
    struct list_head *node, *safe;
    list_for_each_safe(node, safe, head) {
        element_t *elem = list_entry(node, element_t, list);
        free(elem->value);
        free(elem);
    }
    free(head);
}

/* Insert an element at head of queue */
/* cppcheck-suppress constParameterPointer */
bool q_insert_head(struct list_head *head, char *s)
{
    if (!head)
        return false;
    element_t *elem = malloc(sizeof(element_t));
    if (!elem)
        return false;

    elem->value = strdup(s);
    if (!elem->value) {
        free(elem);
        return false;
    }

    list_add(&elem->list, head);
    /* cppcheck-suppress memleak */
    return true;
}

/* Insert an element at tail of queue */
bool q_insert_tail(struct list_head *head, char *s)
{
    if (!head)
        return false;
    return q_insert_head(head->prev, s);
}

/* Remove an element from head of queue */
/* cppcheck-suppress constParameterPointer */
element_t *q_remove_head(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;

    element_t *elem = list_first_entry(head, element_t, list);
    if (sp && (elem->value)) {
        *(char *) stpncpy(sp, elem->value, bufsize - 1) = '\0';
    }
    list_del(&elem->list);
    return elem;
}

/* Remove an element from tail of queue */
element_t *q_remove_tail(struct list_head *head, char *sp, size_t bufsize)
{
    if (!head || list_empty(head))
        return NULL;
    return q_remove_head(head->prev->prev, sp, bufsize);
}

/* Return number of elements in queue */
int q_size(struct list_head *head)
{
    if (!head)
        return 0;

    int len = 0;
    struct list_head *list;

    list_for_each(list, head)
        len++;
    return len;
}

/* Delete the middle node in queue */
bool q_delete_mid(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;
    struct list_head *left = head->prev, *right = head->next;
    while (right != left && (right->next != left)) {
        left = left->prev;
        right = right->next;
    }
    element_t *entry = list_entry(left, element_t, list);
    list_del(&entry->list);
    if (entry->value)
        free(entry->value);
    free(entry);
    return true;
}

/* Delete all nodes that have duplicate string */
bool q_delete_dup(struct list_head *head)
{
    if (!head || list_empty(head))
        return false;
    struct list_head *left, *right;
    for (left = head->next, right = left->next; left != head;
         left = right, right = right->next) {
        while ((right != head) &&
               !strcmp(list_entry(left, element_t, list)->value,
                       list_entry(right, element_t, list)->value))
            right = right->next;
        if (right == left->next)
            continue;
        for (struct list_head *safe = left->next; left != right;
             left = safe, safe = left->next) {
            element_t *entry = list_entry(left, element_t, list);
            list_del(&entry->list);
            if (entry->value)
                free(entry->value);
            free(entry);
        }
    }
    return true;
}

/* Swap every two adjacent nodes */
void q_swap(struct list_head *head)
{
    struct list_head *node, *safe;
    list_for_each_safe(node, safe, head) {
        list_move(node, safe);
        safe = safe->next->next;
    }
}

/* Reverse elements in queue */
void q_reverse(struct list_head *head)
{
    if (!head || list_empty(head))
        return;
    struct list_head *safe, *node;
    list_for_each_safe(node, safe, head) {
        *(uintptr_t *) &node->prev ^= (uintptr_t) node->next;
        *(uintptr_t *) &node->next ^= (uintptr_t) node->prev;
        *(uintptr_t *) &node->prev ^= (uintptr_t) node->next;
    }
    *(uintptr_t *) &head->prev ^= (uintptr_t) head->next;
    *(uintptr_t *) &head->next ^= (uintptr_t) head->prev;
    *(uintptr_t *) &head->prev ^= (uintptr_t) head->next;

}

/* Reverse the nodes of the list k at a time */
void q_reverseK(struct list_head *head, int k)
{
    // https://leetcode.com/problems/reverse-nodes-in-k-group/
}

/* Sort elements of queue in ascending/descending order */
void q_sort(struct list_head *head, bool descend) {}

/* Remove every node which has a node with a strictly less value anywhere to
 * the right side of it */
int q_ascend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Remove every node which has a node with a strictly greater value anywhere to
 * the right side of it */
int q_descend(struct list_head *head)
{
    // https://leetcode.com/problems/remove-nodes-from-linked-list/
    return 0;
}

/* Merge all the queues into one sorted queue, which is in ascending/descending
 * order */
int q_merge(struct list_head *head, bool descend)
{
    // https://leetcode.com/problems/merge-k-sorted-lists/
    return 0;
}
