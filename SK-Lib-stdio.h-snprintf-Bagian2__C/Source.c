#pragma warning(disable:4996)

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

/*
    Source by Microsoft
    Modified For Learn by RK
    I.D.E : VS2019
*/

#if !defined(__cplusplus)
typedef int bool;
const bool true = 1;
const bool false = 0;
#endif

#define FAIL 0 // change to 1 and see what happens

int main(void) {
    char buffer[200];
    const static char s[] = "computer"
#if FAIL
        "computercomputercomputercomputercomputercomputercomputercomputer"
        "computercomputercomputercomputercomputercomputercomputercomputer"
        "computercomputercomputercomputercomputercomputercomputercomputer"
        "computercomputercomputercomputercomputercomputercomputercomputer"
#endif
        ;
    const char c = 'l';
    const int i = 35;
#if FAIL
    const double fp = 1e300; // doesn't fit in the buffer
#else
    const double fp = 1.7320534;
#endif
    /* !subtract one to prevent "squeezing out" the terminal null! */
    const int bufferSize = sizeof(buffer) / sizeof(buffer[0]) - 1;
    int bufferUsed = 0;
    int bufferLeft = bufferSize - bufferUsed;
    bool bSuccess = true;
    buffer[0] = 0;

    /* Format and print various data: */

    if (bufferLeft > 0) {
        int perElementBufferUsed = _snprintf(&buffer[bufferUsed],
            bufferLeft, "   String: %s\n", s); // C4996
            // Note: _snprintf is deprecated; consider _snprintf_s instead
        
        if (bSuccess = (perElementBufferUsed >= 0)) {
            bufferUsed += perElementBufferUsed;
            bufferLeft -= perElementBufferUsed;
            
            if (bufferLeft > 0) {
                int perElementBufferUsed = _snprintf(&buffer[bufferUsed],
                    bufferLeft, "   Character: %c\n", c); // C4996
                
                if (bSuccess = (perElementBufferUsed >= 0)) {
                    bufferUsed += perElementBufferUsed;
                    bufferLeft -= perElementBufferUsed;
                    
                    if (bufferLeft > 0) {
                        int perElementBufferUsed = _snprintf(&buffer
                            [bufferUsed], bufferLeft, "   Integer: %d\n", i); // C4996
                        
                        if (bSuccess = (perElementBufferUsed >= 0)) {
                            bufferUsed += perElementBufferUsed;
                            bufferLeft -= perElementBufferUsed;
                            
                            if (bufferLeft > 0) {
                                int perElementBufferUsed = _snprintf(&buffer
                                    [bufferUsed], bufferLeft, "   Real: %f\n", fp); // C4996
                                
                                if (bSuccess = (perElementBufferUsed >= 0)) {
                                    bufferUsed += perElementBufferUsed;
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    if (!bSuccess) {
        printf("%s\n", "failure");
    } else {
        /* !store null because _snprintf doesn't necessarily (if the string
         * fits without the terminal null, but not with it)!
         * bufferUsed might be as large as bufferSize, which normally is
         * like going one element beyond a buffer, but in this case
         * subtracted one from bufferSize, so we're ok.
         */
        buffer[bufferUsed] = 0;
        printf("Output:\n%s\ncharacter count = %d\n", buffer, bufferUsed);
    }

    _getch();
    return EXIT_SUCCESS;
}