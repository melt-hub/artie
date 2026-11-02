/* artie.c */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <assert.h>

#define NOFARGS 2
#define DBPATH "./db/artie.db"

void usage(FILE *stream)
{
    fprintf(stderr, "usage: ./artie <input.ingr|input.meal|input.plan>\n");
}

char *slurp_file(const char *file_path)
{
    assert(0 && "not implemented");
    return 0;
}

int main(int argc, char **argv)
{

    /* args check */
    if (argc < NOFARGS) {
        usage(stderr);
        fprintf(stderr, "error: input file is not provided.\n");
        exit(1);
    }

    const char *input_file_path = argv[1];

    /* database connection opening and setting */
    sqlite3 *db;

    if (sqlite3_open(DBPATH, &db) != SQLITE_OK) {
        fprintf(stderr, "could not open database: %s.\n", sqlite3_errmsg(db));
        return 1;
    }

    int tmp = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    if (tmp != SQLITE_OK) {
        fprintf(stderr, "error: PRAGMA: %s\n", sqlite3_errmsg(db));
        return 1;
    }


    /* closing connection */
    if (sqlite3_close(db) != SQLITE_OK) {
        fprintf(stderr, "could not close database: %s.\n", sqlite3_errmsg(db));
        return 1;
    }

    return 0;
}

/* artie.c ends here */