#include <stdio.h>
int main() {
int n[256] = {0};
char s[] = "CABBDA";

for(int i = 0; s[i] != '\0'; i++) {
    n[(unsigned char)s[i]]++; 
}
for(int i = 0; i < 256; i++) {
    if(n[i] > 0) {
        printf("Character '%c' appears %d times\n", i, n[i]);
    }
}
return 0;
}