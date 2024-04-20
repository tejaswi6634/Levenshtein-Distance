#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define min(a, b) ((a) < (b) ? (a) : (b))

int minDistance(char* word1, char* word2, int** dp, char** operations) {
    int m = strlen(word1);
    int n = strlen(word2);
int i,j;
    for (i = 0; i <= m; i++) {
        for (j = 0; j <= n; j++) {
            if (i == 0)
                dp[i][j] = j;
            else if (j == 0)
                dp[i][j] = i;
            else if (word1[i - 1] == word2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1];
                operations[i][j] = ' ';
            }
            else {
                dp[i][j] = 1 + min(min(dp[i][j - 1], dp[i - 1][j]), dp[i - 1][j - 1]);
                if (dp[i][j] == dp[i - 1][j - 1] + 1)
                    operations[i][j] = 'S'; 
                else if (dp[i][j] == dp[i][j - 1] + 1)
                    operations[i][j] = 'I'; 
                else
                    operations[i][j] = 'D'; 
            }
        }
    }

    return dp[m][n];
}

int main() {
    char choice;
    int i,j;
    printf("Do you want to provide inputs manually (M) or from secondary storage (S)? ");
    scanf(" %c", &choice);

    if (choice == 'M' || choice == 'm') {
        char word1[100], word2[100];
        printf("Enter first word: ");
        scanf("%s", word1);
        printf("Enter second word: ");
        scanf("%s", word2);

        int m = strlen(word1);
        int n = strlen(word2);

        int** dp = (int**)malloc((m + 1) * sizeof(int*));
        char** operations = (char**)malloc((m + 1) * sizeof(char*));
        for ( i = 0; i <= m; i++) {
            dp[i] = (int*)malloc((n + 1) * sizeof(int));
            operations[i] = (char*)malloc((n + 1) * sizeof(char));
        }

        int distance = minDistance(word1, word2, dp, operations);
        printf("Edit distance between '%s' and '%s' is: %d\n", word1, word2, distance);
        printf("Operations performed:\n");
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (operations[i][j] == 'S') {
                printf("%c -> %c\n", word1[i - 1], word2[j - 1]);
                i--;
                j--;
            } else if (operations[i][j] == 'I') {
                printf("  -> %c\n", word2[j - 1]);
                j--;
            } else if (operations[i][j] == 'D') {
                printf("%c ->  \n", word1[i - 1]);
                i--;
            } else {
                i--;
                j--;
            }
        }
        while (i > 0) {
            printf("%c ->  \n", word1[i - 1]);
            i--;
        }
        while (j > 0) {
            printf("  -> %c\n", word2[j - 1]);
            j--;
        }
    } else if (choice == 'S' || choice == 's') {
        FILE* inFile = fopen("input.txt", "r"); 
        if (!inFile) {
            fprintf(stderr, "Unable to open file input.txt");
            return 1;
        }

        char word1[100], word2[100];

        fscanf(inFile, "%s", word1);
        fscanf(inFile, "%s", word2);

        fclose(inFile); 

        int m = strlen(word1);
        int n = strlen(word2);

        int** dp = (int**)malloc((m + 1) * sizeof(int*));
        char** operations = (char**)malloc((m + 1) * sizeof(char*));
        for (i = 0; i <= m; i++) {
            dp[i] = (int*)malloc((n + 1) * sizeof(int));
            operations[i] = (char*)malloc((n + 1) * sizeof(char));
        }

        int distance = minDistance(word1, word2, dp, operations);
        printf("Edit distance between '%s' and '%s' is: %d\n", word1, word2, distance);

        printf("Operations performed:\n");
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (operations[i][j] == 'S') {
                printf("%c -> %c\n", word1[i - 1], word2[j - 1]);
                i--;
                j--;
            } else if (operations[i][j] == 'I') {
                printf("  -> %c\n", word2[j - 1]);
                j--;
            } else if (operations[i][j] == 'D') {
                printf("%c ->  \n", word1[i - 1]);
                i--;
            } else {
                i--;
                j--;
            }
        }
        while (i > 0) {
            printf("%c ->  \n", word1[i - 1]);
            i--;
        }
        while (j > 0) {
            printf("  -> %c\n", word2[j - 1]);
            j--;
        }
    } else {
        printf("Invalid choice. Please choose either 'M' for manual input or 'S' for secondary storage input.\n");
    }

    return 0;
}

