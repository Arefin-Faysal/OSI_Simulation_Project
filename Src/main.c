#include <stdio.h>
#include "layers.h"

int main(int argc, char *argv[]) {
    const char *msg = "Hello OSI Model";

    if (argc > 1) {
        msg = argv[1];
    }

    printf("\n=== TRANSMISSION START ===\n\n");
    Application_Send(msg);

    return 0;
}
