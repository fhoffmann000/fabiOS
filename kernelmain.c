#include "types.h"
#include "io.h"
#include "asm.h"
#include "util_lib.h"

int kernel_main() {

    const char *text = "balaslkdjhaslkdfhaslkfd";
    
    writeToScreen(text, strlen(text));

    return 0;
}