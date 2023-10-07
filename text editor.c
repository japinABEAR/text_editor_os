#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINES 100
#define MAX_LINE_LENGTH 1000

// Define text formatting codes
#define RESET "\033[0m"
#define BOLD "\033[1m"
#define ITALIC "\033[3m"

int main()
{
    char filename[100];
    FILE *file;
    char lines[MAX_LINES][MAX_LINE_LENGTH];
    int numLines = 0;
    int cursorRow = 0;
    int cursorCol = 0;
    bool isBold = false;
    bool isItalic = false;

    printf("Enter the filename to open or create: ");
    scanf("%s", filename);

    // Open the file for reading and writing
    file = fopen(filename, "a+"); // "a+" mode opens for append and read

    if (file == NULL)
    {
        printf("Error opening the file.\n");
        exit(1);
    }

    // Read file contents into memory
    char line[MAX_LINE_LENGTH];
    while (fgets(line, sizeof(line), file) && numLines < MAX_LINES)
    {
        strcpy(lines[numLines], line);
        numLines++;
    }

    // Display file contents
    for (int i = 0; i < numLines; i++)
    {
        printf("%s", lines[i]);
    }

    printf("Enter text (Ctrl-D to save and exit):\n");

    // Input text to append to the file
    while (fgets(line, sizeof(line), stdin) != NULL)
    {
        if (numLines < MAX_LINES)
        {
            strcpy(lines[numLines], line);
            numLines++;
        }
    }

    // Move the cursor
    printf("\nCursor Navigation: (Press Ctrl-D to save and exit)\n");

    char ch;
    while ((ch = getchar()) != EOF)
    {
        if (ch == 'h' && cursorCol > 0)
        {
            cursorCol--;
        }
        else if (ch == 'l' && cursorCol < strlen(lines[cursorRow]) - 1)
        {
            cursorCol++;
        }
        else if (ch == 'j' && cursorRow < numLines - 1)
        {
            cursorRow++;
        }
        else if (ch == 'k' && cursorRow > 0)
        {
            cursorRow--;
        }
        else if (ch == 'q' || ch == EOF)
        {
            break; // Quit
        }
        else if (ch == 'b')
        {
            isBold = !isBold; // Toggle bold formatting
        }
        else if (ch == 'i')
        {
            isItalic = !isItalic; // Toggle italic formatting
        }

        // Clear the screen and redraw text
        system("clear");
        for (int i = 0; i < numLines; i++)
        {
            if (i == cursorRow)
            {
                printf("%s", lines[i]);
                if (isBold)
                {
                    printf(BOLD);
                }
                if (isItalic)
                {
                    printf(ITALIC);
                }
                printf("\n");
            }
            else
            {
                printf(" %s\n", lines[i]);
            }
        }
        printf(RESET); // Reset formatting
    }

    // Save the modified text to the file
    fseek(file, 0, SEEK_SET); // Move to the beginning of the file
    for (int i = 0; i < numLines; i++)
    {
        fputs(lines[i], file);
    }

    printf("Text saved to %s\n", filename);

    // Close the file
    fclose(file);

    return 0;
}
