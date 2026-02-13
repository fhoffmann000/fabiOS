#include "types.h"
#include "io.h"
#include "asm.h"

int kernel_main() {

    //for (int j=0; j<80; j++) {
        for (int i=0; i<25; i++) {
            writeLetterToFramebuffer('X', i, i, GREEN, WHITE);
        }
    //}

    moveCursor(200);
    scroll(10);
    
    return 0;
}