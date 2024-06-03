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
#include <windows.h>
#include <stdio.h>

#define HOTKEY_ID 1

HHOOK keyboardHook;
int sum = 0;

LRESULT CALLBACK KeyboardProc(int nCode, WPARAM wParam, LPARAM lParam)
{
    if (nCode == HC_ACTION && (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN))
    {
        KBDLLHOOKSTRUCT *kbdStruct = (KBDLLHOOKSTRUCT *)lParam;

        if (kbdStruct->vkCode >= '0' && kbdStruct->vkCode <= '9')
        {
            int number = kbdStruct->vkCode - '0';
            sum += number;
            printf("%d ", number);
        }
    }

    return CallNextHookEx(keyboardHook, nCode, wParam, lParam);
}

LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
    switch (uMsg)
    {
    case WM_CREATE:
        RegisterHotKey(hwnd, HOTKEY_ID, MOD_CONTROL | 0x4000, 'C');
        keyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardProc, GetModuleHandle(NULL), 0);
        break;

    case WM_HOTKEY:
        if (wParam == HOTKEY_ID)
        {
            printf("\nSum: %d\n", sum);
        }
        break;

    case WM_CLOSE:
        UnregisterHotKey(hwnd, HOTKEY_ID);
        DestroyWindow(hwnd);
        break;

    case WM_DESTROY:
        UnhookWindowsHookEx(keyboardHook);
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }

    return 0;
}

int main()
{
    WNDCLASS wc = {0};
    HWND hwnd;
    MSG Msg;
    printf("*** TSR Program ***\n\n");
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = GetModuleHandle(NULL);
    wc.lpszClassName = "MyWindowClass";
    RegisterClass(&wc);

    hwnd = CreateWindowEx(0, "MyWindowClass", "TSR Program", 0, 0, 0, 0, 0, HWND_MESSAGE, 0, 0, 0);

    if (hwnd == NULL)
    {
        return 0;
    }

    ShowWindow(hwnd, SW_HIDE);

    while (GetMessage(&Msg, NULL, 0, 0) > 0)
    {
        TranslateMessage(&Msg);
        DispatchMessage(&Msg);
    }

    return Msg.wParam;
}
