#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int start, stop, step, i, sign;
    bool finish;
} range;

void
argparse(int argc, char *argv[], int *start, int *stop, int *step)
{
    if (argc == 1) {
        printf("Info: %s [M] N [S]\n", argv[0]);
        printf("M - start position\n");
        printf("N - stop position\n");
        printf("S - step\n");
        exit(0);
    }
    if (argc == 2) {
        *stop = atoi(argv[1]);
    } else if (argc >= 3) {
        *start = atoi(argv[1]);
        *stop = atoi(argv[2]);
    }
    if (argc >= 4) {
        *step = atoi(argv[3]);
    } else {
        *step = 1;
    }
    if (*step == 0) {
        fprintf(stderr, "step param S can not be equal to 0\n");
        exit(1);
    }
}

void
range_init(range *r)
{
    r->finish = false;
    r->i = r->start;
    r->sign = (r->step > 0 ? 1 : -1);
}

bool
range_run(range *r)
{
    return !r->finish && (r->sign * r->i < r->sign * r->stop);
}

void
range_next(range *r)
{
    if (!range_run(r)) {
        r->finish = true;
    } else {
        r->i += r->step;
    }
}

int
range_get(range *r)
{
    return r->i;
}

int
main(int argc, char *argv[])
{
    range I;
    argparse(argc, argv, &I.start, &I.stop, &I.step);
    for (range_init(&I); range_run(&I); range_next(&I)) {
        printf("%d\n", range_get(&I));
    }
    return 0;
}
