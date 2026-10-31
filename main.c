#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

#define NOFARGS 3

int main(int argc, char **argv)
{

    /* args check */
    if (argc < NOFARGS) {
        fprintf(stderr, "unsufficient number of arguments.\n");
        return 1;
    }



    /* open and prepare database connection */
    sqlite3 *db;
    int tmp;

    tmp = sqlite3_open("artie.db", &db);

    if (tmp != SQLITE_OK) {
        fprintf(stderr, "could not open database.\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("database opened.\n");
    }

    tmp = sqlite3_exec(db, "PRAGMA foreign_keys = ON;", NULL, NULL, NULL);
    if (tmp != SQLITE_OK) {
        fprintf(stderr, "error: PRAGMA: %s\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("enabled constraint integrity checks.\n");
    }

    tmp = sqlite3_close(db);
    if (tmp != SQLITE_OK) {
        fprintf(stderr, "could not close database.\n", sqlite3_errmsg(db));
        return 1;
    } else {
        printf("database closed.");
    }

    /* insert into database */

    return 0;
}
