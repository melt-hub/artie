/* artie.c */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>
#include <assert.h>
#include <string.h>

#define NOFARGS 2
#define DBPATH "./db/artie.db"

void usage(FILE *stream)
{
    fprintf(stream, "usage: ./artie <input.ingr|input.meal|input.plan>\n");
}

int get_file_ext_code(const char *file_path)
{
    int code = -1;
    const char *ext = strrchr(file_path, '.');
    if (!ext) return code;
    ext = ext + 1;

    if (strcmp(ext, "ingr") == 0) {
        code = 1;
    } else if (strcmp(ext, "meal") == 0) {
        code = 2;
    } else if (strcmp(ext, "plan") == 0) {
        code = 3;
    }

    return code;
}

int main(int argc, char **argv)
{

    /* args check */
    if (argc < NOFARGS) {
        usage(stderr);
        fprintf(stderr, "error: input file is not provided.\n");
        exit(1);
    }

    const char *farg = argv[1];
    int ecode = get_file_ext_code(farg);

    if (ecode > 0) {
        /* csv_table *data = chop_it_csv_parse(farg);
        artie_update_db(data); */
        printf("got here");
    } else {
        assert(0 && "not implemented");
    }

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