#include <stdio.h>
#include <stdlib.h>
#include <sqlite3.h>

int main(int argc, char **argv)
{
    sqlite3 *db_handle;
    int tmp;

    tmp = sqlite3_open("artie.db", &db_handle);

    if (tmp != SQLITE_OK) {
        printf("could not open database.\n");
    } else {
        printf("database opened.\n");
    }

    printf("Hello, world!");
    return 0;
}
