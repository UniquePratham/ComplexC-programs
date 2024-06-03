// Name - Pratham Agarwal
// Date - 11/12/2023
// 1k. Write a TSR program to add a series of integer numbers.
// Program Name - TSR_Integer_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Initialize the TSR program within the desired environment.
// 2.	Create a variable 'sum' and set it initially to 0. This variable will be used to store the sum of the entered numbers.
// 3.	Continuously monitor user input.
// a.	If user inputs an integer, add that integer to the 'sum' and continue waiting for the next input.
// b.	If user inputs a specific command (e.g., 'calculate' / 'show') proceed to step 4.
// 4.	Upon receiving the command to calculate and display the sum:
// a.	Calculate the sum of all the previously entered integers stored in the 'sum' variable.
// b.	Display the calculated sum on the screen.
// 5.	The program will remain active and resident in memory, allowing the user to input more integers and calculate the sum again by repeating steps 3 and 4.
// 6.	Optionally, provide an exit command to terminate the TSR program and release memory resources when the user is done.
#include <dos.h>
#include <stdio.h>
#include <conio.h>

#define CTRL_C 0x2E03 // Ctrl+C key combination

void interrupt (*oldInt9)(); // Pointer to the original interrupt handler
int sum = 0;                 // Variable to store the sum

void interrupt newInt9()
{
    int key = _bios_keybrd(_NKEYBRD_READY);

    if (key != 0)
    {
        int ascii = _bios_keybrd(_NKEYBRD_READ);
        if (ascii >= '0' && ascii <= '9')
        {
            int number = ascii - '0';
            sum += number;
            printf("%d ", number);
        }
        else if (ascii == CTRL_C)
        {
            printf("\nSum: %d\n", sum);
            printf("Press any key to continue or Ctrl+C to exit...\n");
            sum = 0;
        }
    }

    (*oldInt9)();
}

void main()
{
    clrscr();
    printf("TSR Program: Enter integers, use Ctrl+C to calculate and display sum.\n");

    oldInt9 = getvect(0x09); // Get the current interrupt handler
    setvect(0x09, newInt9);  // Set the new interrupt handler

    keep(0, _SS); // Stay resident in memory

    // The program will continue to run in the background, and the user can input integers.
    // Pressing Ctrl+C will display the sum.

    // To exit the program, the user can use an external utility or a specific exit command.

    // Note: This code is specific to DOS and may not work on modern systems.
}
