#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_REFERENCES 2

typedef struct Object Object;

struct Object {
    int id;
    bool marked;
    size_t reference_count;
    Object *references[MAX_REFERENCES];
    Object *next;
};

static Object *heap;

static Object *allocate_object(int id)
{
    Object *object = calloc(1, sizeof(*object));
    if (object == NULL) {
        perror("calloc");
        exit(EXIT_FAILURE);
    }

    object->id = id;
    object->next = heap;
    heap = object;
    printf("Allocate object %d\n", id);
    return object;
}

static void add_reference(Object *from, Object *to)
{
    if (from->reference_count == MAX_REFERENCES) {
        fprintf(stderr, "Object %d has no free reference slots\n", from->id);
        exit(EXIT_FAILURE);
    }

    from->references[from->reference_count++] = to;
}

static bool is_heap_object(const Object *candidate)
{
    for (const Object *object = heap; object != NULL; object = object->next) {
        if (object == candidate) {
            return true;
        }
    }
    return false;
}

static void mark(Object *candidate)
{
    if (!is_heap_object(candidate) || candidate->marked) {
        return;
    }

    candidate->marked = true;
    printf("Mark object %d\n", candidate->id);

    for (size_t i = 0; i < candidate->reference_count; i++) {
        mark(candidate->references[i]);
    }
}

static size_t collect(Object *const roots[], size_t root_count)
{
    printf("\nMark phase:\n");
    for (size_t i = 0; i < root_count; i++) {
        mark(roots[i]);
    }

    printf("\nSweep phase:\n");
    size_t reclaimed = 0;
    Object **current = &heap;
    while (*current != NULL) {
        Object *object = *current;
        if (object->marked) {
            object->marked = false;
            current = &object->next;
        } else {
            printf("Free object %d\n", object->id);
            *current = object->next;
            free(object);
            reclaimed++;
        }
    }
    return reclaimed;
}

int main(void)
{
    Object *a = allocate_object(1);
    Object *b = allocate_object(2);
    Object *c = allocate_object(3);
    Object *unreachable_a = allocate_object(4);
    Object *unreachable_b = allocate_object(5);

    add_reference(a, b);
    add_reference(a, c);
    add_reference(b, a);
    add_reference(unreachable_a, unreachable_b);
    add_reference(unreachable_b, unreachable_a);

    Object *roots[] = {a};
    size_t reclaimed = collect(roots, 1);
    if (reclaimed != 2) {
        fprintf(stderr, "Expected to reclaim 2 unreachable objects, got %zu\n",
                reclaimed);
        return EXIT_FAILURE;
    }

    puts("\nDrop the only root and collect again:");
    roots[0] = NULL;
    reclaimed = collect(roots, 1);
    if (reclaimed != 3) {
        fprintf(stderr, "Expected to reclaim 3 unrooted objects, got %zu\n",
                reclaimed);
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
