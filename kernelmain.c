#include "types.h"
#include "io.h"
#include "asm.h"
#include "util.h"
#include "serial.h"
#include "gdt.h"

int kernel_main() {
  
    gdt_init();

    char *str = "balsdj3425alsdjghaslkkdjgflaöäösdjfoaisjfokasjd";

    printLine(str, strlen(str), 0);
    logLine(str, strlen(str));
    return 0;
}