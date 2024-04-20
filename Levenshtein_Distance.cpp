#include <iostream>
#include <fstream> 
#include <vector>
#include <string>
using namespace std;

#define min(a, b) ((a) < (b) ? (a) : (b))

int minDistance(string word1, string word2, vector<vector<int> >& dp, vector<vector<char> >& operations) {
    int m = word1.length();
    int n = word2.length();
    
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
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
    cout << "Do you want to provide inputs manually (M) or from secondary storage (S)? ";
    cin >> choice;
    
    if (choice == 'M' || choice == 'm') {
        string word1, word2;
        cout << "Enter first word: ";
        cin >> word1;
        cout << "Enter second word: ";
        cin >> word2;
        
        int m = word1.length();
        int n = word2.length();
        
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0));
        vector<vector<char> > operations(m + 1, vector<char>(n + 1, ' ')); 
        
        int distance = minDistance(word1, word2, dp, operations);
        cout << "Edit distance between '" << word1 << "' and '" << word2 << "' is: " << distance << endl;
    
        cout << "Operations performed:" << endl;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (operations[i][j] == 'S') {
                cout << word1[i - 1] << " -> " << word2[j - 1] << endl;
                i--;
                j--;
            } else if (operations[i][j] == 'I') {
                cout << " " << " -> " << word2[j - 1] << endl;
                j--;
            } else if (operations[i][j] == 'D') {
                cout << word1[i - 1] << " -> " << " " << endl;
                i--;
            } else {
                i--;
                j--;
            }
        }
        while (i > 0) {
            cout << word1[i - 1] << " -> " << " " << endl;
            i--;
        }
        while (j > 0) {
            cout << " " << " -> " << word2[j - 1] << endl;
            j--;
        }
    } else if (choice == 'S' || choice == 's') {
        ifstream inFile("input.txt"); 
        if (!inFile) {
            cout << "Unable to open file input.txt";
            return 1;
        }
        
        string word1, word2;
        inFile >> word1;
        inFile >> word2;
        
        inFile.close(); 
        
        int m = word1.length();
        int n = word2.length();
        
        vector<vector<int> > dp(m + 1, vector<int>(n + 1, 0)); 
        vector<vector<char> > operations(m + 1, vector<char>(n + 1, ' '));
        
        int distance = minDistance(word1, word2, dp, operations);
        cout << "Edit distance between '" << word1 << "' and '" << word2 << "' is: " << distance << endl;
        
        cout << "Operations performed:" << endl;
        int i = m, j = n;
        while (i > 0 && j > 0) {
            if (operations[i][j] == 'S') {
                cout << word1[i - 1] << " -> " << word2[j - 1] << endl;
                i--;
                j--;
            } else if (operations[i][j] == 'I') {
                cout << " " << " -> " << word2[j - 1] << endl;
                j--;
            } else if (operations[i][j] == 'D') {
                cout << word1[i - 1] << " -> " << " " << endl;
                i--;
            } else {
                i--;
                j--;
            }
        }
        while (i > 0) {
            cout << word1[i - 1] << " -> " << " " << endl;
            i--;
        }
        while (j > 0) {
            cout << " " << " -> " << word2[j - 1] << endl;
            j--;
        }
    } else {
        cout << "Invalid choice. Please choose either 'M' for manual input or 'S' for secondary storage input." << endl;
    }
    
    return 0;
}

