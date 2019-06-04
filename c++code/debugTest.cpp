#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

/*int main() {
        char *ptr = (char *) malloc(1024);
        ptr[0] = '0';
        // Now write beyond the block 
        ptr[1023] = '0';
        cout << ptr[1023];
        exit(0);
}*/

int main()
{
    int *x = (int *) malloc(2*sizeof(int));
    x[1] = 5;   // Violation here!!!
    printf("Die\n");
}