// Name - Pratham Agarwal
// Date - 11/12/2023
// 1e. Find the exact execution time of a program but not by timestamp only.
// Program Name - ProgTimeAnalyz_14.c
// gcc (tdm64-1) 10.3.0

// Algorithm:
// 1.	Read the input text file and load the necessary data into memory for program execution.
// 2.	Record the start time before the program execution begins. This can be achieved using a timestamp-based method.
// 3.	Execute the program, allowing it to perform its tasks as it normally would.
// 4.	Record the end time after the program execution completes. Again, use a timestamp-based method for this purpose.
// 5.	Calculate the time elapsed between the start time and end time to obtain an initial estimate of the execution time. This estimate may still be subject to inaccuracies due to system fluctuations.
// 6.	Employ an iterative or repetition mechanism to execute the program multiple times, preferably under varying system conditions. This will aid in the recognition and alleviation of disparities in execution time.
// 7.	Gather additional data during each program run, such as CPU usage, memory consumption, and any other relevant performance metrics. These metrics will contribute to a more accurate measurement of execution time.
// 8.	Analyse the collected data to identify and mitigate any outliers or anomalies in the execution time measurements. Statistical techniques may be employed for this purpose.
// 9.	Calculate the final execution time by taking into account the average or median of the recorded execution times, factoring in any relevant performance metrics, and adjusting for potential variations.
// 10.	Write the final execution time and relevant performance metrics to the output text file for further analysis or reporting.
// 11.	The resulting execution time measurement, combined with additional data, will provide a more accurate representation of the program's performance than timestamp-based measurements alone.
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <Windows.h>
#include <psapi.h>

#define MAX_PATH_LENGTH 100
#define NUM_RUNS 10

void measureExecutionTime(const char *programPath)
{
    double totalExecutionTime = 0;
    double totalCpuTime = 0;
    double totalMemoryUsage = 0;

    char compileCommand[MAX_PATH_LENGTH + 20]; // +20 for additional options like -o, -std, etc.

    sprintf(compileCommand, "gcc -std=gnu99 -o temp %s", programPath);
    system(compileCommand);

    for (int i = 0; i < NUM_RUNS; ++i)
    {
        // Record the starting time
        clock_t start_time = clock();

        // Run the compiled program
        int result = system("temp.exe");

        // Record the ending time
        clock_t end_time = clock();

        // Check if the specified program ran successfully
        if (result == 0)
        {
            // Calculate the execution time in seconds
            double execution_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;
            totalExecutionTime += execution_time;

            // Measure CPU time
            FILETIME createTime, exitTime, kernelTime, userTime;
            GetProcessTimes(GetCurrentProcess(), &createTime, &exitTime, &kernelTime, &userTime);
            double cpu_time = (kernelTime.dwHighDateTime + userTime.dwHighDateTime) * 1e-7 +
                              (kernelTime.dwLowDateTime + userTime.dwLowDateTime) * 1e-7;
            totalCpuTime += cpu_time;

            // Measure memory usage
            PROCESS_MEMORY_COUNTERS_EX pmc;
            if (GetProcessMemoryInfo(GetCurrentProcess(), (PROCESS_MEMORY_COUNTERS *)&pmc, sizeof(pmc)))
            {
                totalMemoryUsage += (double)pmc.PrivateUsage / (1024.0 * 1024.0); // Convert to MB
            }

            // Print the measurements for each run
            printf("Run %d - Execution Time: %f seconds, CPU Time: %f seconds, Memory Usage: %f MB\n",
                   i + 1, execution_time, cpu_time, totalMemoryUsage);
        }
        else
        {
            printf("Error running temp.exe\n");
            return; // Exit if there is an error in any run
        }
    }

    // Calculate and print the average measurements
    double averageExecutionTime = totalExecutionTime / NUM_RUNS;
    double averageCpuTime = totalCpuTime / NUM_RUNS;
    double averageMemoryUsage = totalMemoryUsage / NUM_RUNS;
    printf("For File-%s, Average - Execution Time: %f seconds, CPU Time: %f seconds, Memory Usage: %f MB\n", programPath, averageExecutionTime, averageCpuTime, averageMemoryUsage);
}

int main()
{
    // Get the program path from the user
    char programPath[MAX_PATH_LENGTH];
    printf("Enter the program path to measure execution time: ");
    scanf("%s", programPath);

    // Measure the execution time, CPU time, and memory usage of the specified program
    measureExecutionTime(programPath);

    return 0;
}
