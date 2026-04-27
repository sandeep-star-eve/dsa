




#include <stdio.h>
#include <string.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int lengthOfLongestSubstring(char *s) {
    // Array to store the last index of each character (initialized to -1)
    int last_seen[256];
    for (int i = 0; i < 256; i++) 
    last_seen[i] = -1;

    int max_len = 0;
    int left = 0;
    int n = strlen(s);

    for (int right = 0; right < n; right++) {
        // Use our special syntax to find if we've seen this char before
        unsigned char current_char = (unsigned char)s[right];

        // If the character was seen inside the current window, move 'left'
        if (last_seen[current_char] >= left) {
            left = last_seen[current_char] + 1;
        }

        // Update the last seen position of the character
        last_seen[current_char] = right;

        // Calculate current window length and update max
        max_len = MAX(max_len, right - left + 1);
    }

    return max_len;
}

int main() {
    char *s = "abcabcbbsdkhf";
    printf("Longest substring length: %d\n", lengthOfLongestSubstring(s));
    return 0;
}