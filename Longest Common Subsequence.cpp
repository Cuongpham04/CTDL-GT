#include <cstdio>    // For printf, scanf
#include <cstring>   // For strlen, etc.

using namespace std;

/*
    findLongestCommonSubstring
    --------------------------
    - Receives two C-style strings s1 and s2.
    - Uses a dynamic programming approach to figure out the longest
      contiguous substring shared by both strings.
    - Prints out that substring and its length.
*/
void findLongestCommonSubstring(const char* s1, const char* s2) {
    // Get the length of each string
    int len1 = strlen(s1);
    int len2 = strlen(s2);

    // A small 2D table where dp[i][j] indicates the length of the
    // longest common substring ending exactly at s1[i-1] and s2[j-1].
    static int dp[1001][1001];
    
    // Make sure we start with zeroed data
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            dp[i][j] = 0;
        }
    }

    int bestLength = 0;    // Will keep track of the maximum length found
    int endIndex   = 0;    // Where that substring ends in s1

    // Compute the DP table
    // If characters at positions i-1 and j-1 match, extend the
    // previous match by 1; otherwise, reset to zero.
    for (int i = 1; i <= len1; i++) {
        for (int j = 1; j <= len2; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
                if (dp[i][j] > bestLength) {
                    bestLength = dp[i][j];
                    endIndex   = i; // end position for the substring in s1
                }
            } else {
                dp[i][j] = 0;
            }
        }
    }

    // Reconstruct the actual substring from s1 using bestLength and endIndex
    char commonSub[1001];
    int startPos = endIndex - bestLength;
    for (int k = 0; k < bestLength; k++) {
        commonSub[k] = s1[startPos + k];
    }
    commonSub[bestLength] = '\0'; // Null-terminate

    // Print out the substring we found and its length
    printf("\nLongest Common Substring: %s\n", commonSub);
    printf("Length: %d\n", bestLength);
}

/*
    main
    ----
    - Asks for two input strings (up to 1000 chars each).
    - Invokes the function to find and display their longest common substring.
*/
int main() {
    // We'll read two strings, each up to 1000 characters
    char s1[1001];
    char s2[1001];

    printf("Enter the first string:\n");
    scanf("%1000s", s1);

    printf("Enter the second string:\n");
    scanf("%1000s", s2);

    // Call our function to find and print the LCSu
    findLongestCommonSubstring(s1, s2);

    return 0;
}
