//count number of substrings without repeating characters
//Input: s = "abcabcbb"
//Output: 3 abc
//Input: s = "bbbbb"
//Output: 1 bbbbb

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX(a,b) (a > b ? a : b)

int lengthofLongestSubstring(char *);

int main(void){
    char *s= "abcdefgabcbb";
    printf("%d\n", lengthofLongestSubstring(s));
    return 0;
}

int lengthofLongestSubstring(char * s){
    int right =0, left = 0, max_len=0;
    int last_seen[256];
    unsigned char c;
    int n = strlen(s);
    for (int i = 0; i < 256; i++) 
    last_seen[i] = -1;  

    for( right = 0; right < n; right++){
        c = s[right];
        if(last_seen[c] >= left){
            left = last_seen[c];
        }
        last_seen[c] = right + 1;
        max_len = MAX(max_len, right - left + 1 );
    }
   
    return  max_len ;
}   
