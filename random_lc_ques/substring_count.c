//count number of substrings without repeating characters
//Input: s = "abcabcbb"
//Output: 3 abc,abc,bb
//Input: s = "bbbbb"
//Output: 1 b
#include <stdio.h>
#include <string.h>

#include <stdio.h>

int countSubstrings(char *s) {
    int count = 0;
    int seen[256] = {0}; 
    int i = 0;
    
    while ( s[i] != '\0') {
        if (seen[(unsigned char)s[i]] == 1) {
            count++; 
            
            // 2. Empty the bucket for the next chunk
            for (int j = 0; j < 256; j++) 
            seen[j] = 0;
        }
        
        // 3. Put the current letter in the bucket
        seen[(unsigned char)s[i]] = 1;
        i++;
    }

    // 4. If there's anything left in the bucket at the end, count it
    return (s[0] == '\0') ? 0 : count ;
}

int main() {
    char s1[] = "abcabcbb";
    char s2[] = "bbbbba";
    
    printf("Input: %s -> Output: %d\n", s1, countSubstrings(s1));
    printf("Input: %s -> Output: %d\n", s2, countSubstrings(s2)); 
    return 0;
}