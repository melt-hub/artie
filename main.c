/* artie.c */

#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define NOFARGS 2

/* Testing SQLite library before diving into developement.. */
int main(int argc, char **argv)
{

    /* args check */
    if (argc < NOFARGS) {
        fprintf(stderr, "unsufficient number of arguments.\n");
        return 1;
    }

    /* database connection opening and setting */
    sqlite3 *db;

    if (sqlite3_open("artie.db", &db) != SQLITE_OK) {
        fprintf(stderr, "could not open database: %s.\n", sqlite3_errmsg(db));
        return 1;
    }

    int tmp = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);

    if (tmp != SQLITE_OK) {
        fprintf(stderr, "error: PRAGMA: %s\n", sqlite3_errmsg(db));
        return 1;
    }

    /* inserting an ingredient */
    const char *q1 = "INSERT INTO ingredient (name, category, prop) \
                      VALUES ('pasta', 'carb', 0.55)";
    sqlite3_stmt *s;

    if (sqlite3_prepare_v2(db, q1, -1, &s, 0) != SQLITE_OK) {
        fprintf(stderr, "could not prepare statement: %s.\n", sqlite3_errmsg(db));
        return 1;
    }
    if (sqlite3_step(s) != SQLITE_DONE) {
        fprintf(stderr, "could not insert new ingredient.\n");
        return 1;
    }

    if (sqlite3_finalize(s) != SQLITE_OK) {
        fprintf(stderr, "could not finalize statement: %s.\n", sqlite3_errmsg(db));
        return 1;
    }

    /* fetching data about an ingredient */
    const char *q2 = "SELECT * FROM ingredient";
    sqlite3_stmt *t;

    if (sqlite3_prepare_v2(db, q2, -1, &t, 0) != SQLITE_OK) {
        fprintf(stderr, "could not prepare statement: %s.\n", sqlite3_errmsg(db));
        return 1;
    }

    if (sqlite3_step(t) == SQLITE_ROW) {
        printf("query returned: (%s, %s, %f)\n",
               sqlite3_column_text(t, 1),
               sqlite3_column_text(t, 2),
               sqlite3_column_double(t, 3));
    }

    if (sqlite3_finalize(t) != SQLITE_OK) {
        fprintf(stderr, "could not finalize statement: %s.\n", sqlite3_errmsg(db));
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