#include "types.h"
#include "io.h"
#include "asm.h"
#include "util.h"
#include "serial.h"

int kernel_main() {
  
    char *str = "balsdj3425alsdjghaslkkdjgflaöäösdjfoaisjfokasjdflaksjdgfoiasjhigujhaeoghnfasoiefdsa2345hfaosdjfhasldjgh";

    printLine(str, strlen(str), 0);
    logLine(str, strlen(str));
    return 0;
}