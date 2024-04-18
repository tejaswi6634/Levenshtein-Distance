def min_distance(word1, word2):
    m = len(word1)
    n = len(word2)
    
    dp = [[0] * (n + 1) for _ in range(m + 1)]
    operations = [[''] * (n + 1) for _ in range(m + 1)]
    
    for i in range(m + 1):
        for j in range(n + 1):
            if i == 0:
                dp[i][j] = j
            elif j == 0:
                dp[i][j] = i
            elif word1[i - 1] == word2[j - 1]:
                dp[i][j] = dp[i - 1][j - 1]
                operations[i][j] = ' '
           else:
                dp[i][j] = 1 + min(dp[i][j - 1], dp[i - 1][j], dp[i - 1][j - 1])
                if dp[i][j] == dp[i - 1][j - 1] + 1:
                    operations[i][j] = 'S' 
                elif dp[i][j] == dp[i][j - 1] + 1:
                    operations[i][j] = 'I' 
                else:
                    operations[i][j] = 'D' 
    
    return dp[m][n], operations

def display_operations(word1, word2, operations):
    i, j = len(word1), len(word2)
    while i > 0 and j > 0:
        if operations[i][j] == 'S':
            print(word1[i - 1], "->", word2[j - 1])
            i -= 1
            j -= 1
        elif operations[i][j] == 'I':
            print(" ", "->", word2[j - 1])
            j -= 1
        elif operations[i][j] == 'D':
            print(word1[i - 1], "->", " ")
            i -= 1
        else:
            i -= 1
            j -= 1
    while i > 0:
        print(word1[i - 1], "->", " ")
        i -= 1
    while j > 0:
        print(" ", "->", word2[j - 1])
        j -= 1

if __name__ == "__main__":
    choice = input("Do you want to provide inputs manually (M) or from secondary storage (S)? ")
    
    if choice.upper() == 'M':
        word1 = input("Enter first word: ")
        word2 = input("Enter second word: ")
        
        distance, operations = min_distance(word1, word2)
        print(f"Edit distance between '{word1}' and '{word2}' is: {distance}")
        
        print("Operations performed:")
        display_operations(word1, word2, operations)
        
    elif choice.upper() == 'S':
        try:
            with open("input.txt", "r") as f:
                word1 = f.readline().strip()
                word2 = f.readline().strip()
                
            distance, operations = min_distance(word1, word2)
            print(f"Edit distance between '{word1}' and '{word2}' is: {distance}")
            
            print("Operations performed:")
            display_operations(word1, word2, operations)
            
        except FileNotFoundError:
            print("Unable to open file input.txt")
    else:
        print("Invalid choice. Please choose either 'M' for manual input or 'S' for secondary storage input.")
