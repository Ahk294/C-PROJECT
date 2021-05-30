// including the necessary header files
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

/* 
a method to generate random numbers for dictionary names and their line numbers
it takes in 2 values:   lower limit (the minimum number that will be generated)
                        upper limit (the maximum number that will be generated)
*/
int randomize(int lower, int upper){

/* 
since C does not have a built-in method to print a random number in a range
we have to make use of a formula to get our random numbers from a given range

the formula is: randomNumber = (rand() % (upper – lower + 1)) + lower
*/
    int randNum = (rand() % (upper - lower + 1)) + lower; 
}

/*
a method to read files, i.e. dictionaries, and to iterate through the dictionaries
*/
char *readFile(char path[100], int dictName, int lineNumber){

// declaring a constant char array that will store the randomly chosen word from the dictionary
    static char word[100];

// declaring a char array that will store the complete location of file with dictionary name
    char dictionary[100];

/*
the sprintf method works just like the printf method but instead of sending the formatted string
to the console, it assigns it to a variable, char dictionary[100].
Here we concatenated the complete file path (path, dictName).
*/
    sprintf(dictionary, "%s/%d", path, dictName);

// opening the randomly selected dictonary for 'reading' purpose. (To read the words in the dictionary at each line number)
    FILE *file = fopen(dictionary, "r");

// checking if the opened dictionary/file is not exists or not
    if(file != NULL){
    
// declaring a char array to store the word written on the randomly generated line number in the dictionary
        char line[100];

// declaring a counter variable to keep track of the line number being read in the dictionary
        int x = 0;
    
/*
the fgets method helps in copying words from the file and pasting it in the char array called 'line'
*/
        while(fgets(line, sizeof(line), file)){
            
// incrementing the counter variable everytime a line has been read by fgets
            x++;
    
// checking if the randomly generated line number has been reached by fgets
            if(x == lineNumber){

/*
the memset function helps in emptying the word array and setting it to basically null so that the randomly chosen
word from the dictionary can be stored in it
*/
                memset(&word[0], 0, sizeof(word));
    
/*
the strncpy method copies the content of the 'line' array (which is the word written at the randomly chosen line)
and pastes it into the 'word' array. However, we have to specify the number of characters it must copy from the 'line' array
, which is the length of the 'line' array - 1
*/
                strncpy(word, line, strlen(line) - 1);
                return word;
            }
        }

// closing the dictionary
        fclose(file);
    } else {

// error message if the file cannot be opened for reading
        printf("File does not exist.\n");
    }
}

// main method
int main(void){

// declaring an int variable to store the number of words the user wants in their password
    int numOfWords;

// declaring an int variable to store the randomly generated number for dictionary names
    int dictName;

// declaring an int variable to store the randomly generated number for line numbers in dictionaries
    int lineNumber;

// declaring a char pointer that will store the random word that the "readFile" method will return
    char *randomWord;

// declaring a char variable to store the characters of the 'password' file which stores the final output
    char password;

// do-while loop to prompt the user for input at least once and then check if the input is within the range
    do{
        printf("Enter the number of words: ");
        scanf("%d", &numOfWords);

// an if condition to check the input
        if(numOfWords <= 2 || numOfWords >= 5){

// prompting user to enter valid input
            printf("\nPlease enter a number between 2 and 5 (exclusive of 2 and 5).\n");
        }
    } while(numOfWords <= 2 || numOfWords >= 5);

    printf("Processing...\n\n");

// opening a new file 'password' to write the final etr password in it
    FILE *W_PassFile = fopen("/Users/hasee/Desktop/MDX/CST 1500 COMPUTER SYSTEMS & ARCHITECTURE/C PROJECT CW1/password", "w");

// checking if the file exists or not
    if(W_PassFile != NULL){

        fprintf(W_PassFile, "Your e-t-r password is: ");

/* 
the srand() method helps us by not letting the rand() method generate the same random numbers again and again. 
If srand() is not used, rand() will keep generating the same random numbers.
We seed it with time(0) because time is the only value that keeps changing in the computer.
*/
        srand(time(0));

// for loop to generate only as many words as the user has asked for
        for(int i = 1; i <= numOfWords; i++){

// calling the "randomize" method and using its output to select a random dictionary
            dictName = randomize(4, 7);

// calling the "randomize" method again and using its output to select a random line from the dictionary selected at line 135
            lineNumber = randomize(1, 500);

// storing the randomly generated word from the "readFile" method in the randomWord to be printed to the console
            randomWord = readFile("/Users/hasee/Desktop/MDX/CST 1500 COMPUTER SYSTEMS & ARCHITECTURE/C PROJECT CW1", dictName, lineNumber);
            printf("%d %s \n\n", i, randomWord);

// this prints the randomly generated word in the 'password' file
            fprintf(W_PassFile, "%s", randomWord);

// conditional statement to deal with the hyphen problem
            if(i != numOfWords){
                fprintf(W_PassFile, "-");
            }
        }

// closing the password file
        fclose(W_PassFile);
        } else {

// error message if the file cannot be opened for writing
        printf("Oops, there seems to be an error...\n");
    }

// opening the password file again but with the purpose of reading its contents
        FILE *R_PassFile = fopen("/Users/hasee/Desktop/MDX/CST 1500 COMPUTER SYSTEMS & ARCHITECTURE/C PROJECT CW1/password", "r");

// checking if the file exists or not
        if(R_PassFile != NULL){

/*
copying character from the password file and storing them in the password variable 
to print the statement that we store in the file to the console.
The getc() file function helps in getting individual characters from the file and storing them in the password variable
*/
            password = getc(R_PassFile);

/*
the while-loop is used to iterate through the characters of the sentence stored in the 'password' file till it reaches
the End-Of-File (EOF).
*/
            while(password != EOF){

// printing the character stored in the 'password' variable to the console with every iteration
                printf("%c", password);

// copying character from the 'password' file and storing them in the 'password' variable
                password = getc(R_PassFile);
            }
        } else {

// error message if the file cannot be opened for reading           
            printf("Oops, there seems to be an error...\n");
        }

// closing the password file        
        fclose(R_PassFile);
    
}