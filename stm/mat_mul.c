/*
 * ============================================================================
 * STM32 Matrix Multiplication - Beginner Friendly Example
 * ============================================================================
 *
 * Target: Any STM32 with ARM Cortex-M4 core 
 * IDE: STM32CubeIDE
 * Debug Interface: SWD + SWO/ITM (optional for printf)
 *
 * Expected Result:
 *   A = {{1, 2}, {3, 4}}
 *   B = {{5, 6}, {7, 8}}
 *   C = {{19, 22}, {43, 50}}
 * ============================================================================
 */

#include <stdio.h>      /* For printf (if using ITM/SWO) */
#include <stdint.h>     /* For standard integer types */

/* ============================================================================
 * GLOBAL MATRIX DECLARATIONS
 * ============================================================================
 *
 * WHY VOLATILE?
 *   - Tells compiler: "This variable may change unexpectedly"
 *   - Prevents compiler from optimizing away reads/writes
 *   - Essential for debugging with Live Expressions
 *   - Without volatile, debugger may show stale/incorrect values
 *
 * WHY GLOBAL?
 *   - Local variables disappear when function returns
 *   - Global variables persist and can be monitored continuously
 *   - Live Expressions can only watch global/static variables reliably
 *
 * STORAGE ORDER:
 *   Row-major format: matrix[row][col]
 *   matrix[0][0] = first row, first column
 *   matrix[0][1] = first row, second column
 *   matrix[1][0] = second row, first column
 *   matrix[1][1] = second row, second column
 */

/* Input Matrix A (2x2) */
volatile float matrix_A[2][2] = {
    {1.0f, 2.0f},   /* Row 0: [1, 2] */
    {3.0f, 4.0f}    /* Row 1: [3, 4] */
};

/* Input Matrix B (2x2) */
volatile float matrix_B[2][2] = {
    {5.0f, 6.0f},   /* Row 0: [5, 6] */
    {7.0f, 8.0f}    /* Row 1: [7, 8] */
};

/* Output Matrix C (2x2) - Result of A × B */
volatile float matrix_C[2][2] = {
    {0.0f, 0.0f},   /* Will be calculated */
    {0.0f, 0.0f}    /* Will be calculated */
};

/* Status flag to indicate calculation is complete */
volatile uint8_t calculation_complete = 0;

/* ============================================================================
 * MATRIX MULTIPLICATION FUNCTION
 * ============================================================================
 *
 * Mathematical Formula for 2×2 Matrix Multiplication:
 *
 *   | a11  a12 |   | b11  b12 |   | c11  c12 |
 *   |          | × |          | = |          |
 *   | a21  a22 |   | b21  b22 |   | c21  c22 |
 *
 * Where:
 *   c11 = (a11 × b11) + (a12 × b21)
 *   c12 = (a11 × b12) + (a12 × b22)
 *   c21 = (a21 × b11) + (a22 × b21)
 *   c22 = (a21 × b12) + (a22 × b22)
 *
 * General Formula:
 *   C[i][j] = Σ(A[i][k] × B[k][j]) for k = 0 to N-1
 */
void multiply_matrices_2x2(void)
{
    /* Temporary variables for clarity */
    float a11, a12, a21, a22;
    float b11, b12, b21, b22;

    /* Step 1: Read input matrices into local variables */
    a11 = matrix_A[0][0];  /* Top-left element of A */
    a12 = matrix_A[0][1];  /* Top-right element of A */
    a21 = matrix_A[1][0];  /* Bottom-left element of A */
    a22 = matrix_A[1][1];  /* Bottom-right element of A */

    b11 = matrix_B[0][0];  /* Top-left element of B */
    b12 = matrix_B[0][1];  /* Top-right element of B */
    b21 = matrix_B[1][0];  /* Bottom-left element of B */
    b22 = matrix_B[1][1];  /* Bottom-right element of B */

    /* Step 2: Perform matrix multiplication */

    /* Calculate C[0][0]: First row of A × First column of B */
    matrix_C[0][0] = (a11 * b11) + (a12 * b21);
    /* = (1.0 × 5.0) + (2.0 × 7.0) = 5.0 + 14.0 = 19.0 */

    /* Calculate C[0][1]: First row of A × Second column of B */
    matrix_C[0][1] = (a11 * b12) + (a12 * b22);
    /* = (1.0 × 6.0) + (2.0 × 8.0) = 6.0 + 16.0 = 22.0 */

    /* Calculate C[1][0]: Second row of A × First column of B */
    matrix_C[1][0] = (a21 * b11) + (a22 * b21);
    /* = (3.0 × 5.0) + (4.0 × 7.0) = 15.0 + 28.0 = 43.0 */

    /* Calculate C[1][1]: Second row of A × Second column of B */
    matrix_C[1][1] = (a21 * b12) + (a22 * b22);
    /* = (3.0 × 6.0) + (4.0 × 8.0) = 18.0 + 32.0 = 50.0 */

    /* Set flag to indicate calculation is complete */
    calculation_complete = 1;
}

/* ============================================================================
 * OPTIONAL: ITM/SWO Printf Function
 * ============================================================================
 *
 * ITM (Instrumentation Trace Macrocell) allows printf-like output
 * through the SWD debug interface without using UART hardware.
 *
 * REQUIREMENTS:
 *   1. Enable ITM in STM32CubeIDE debug configuration
 *   2. Configure SWO pin in .ioc file
 *   3. Set correct CPU clock frequency in debug settings
 *   4. Open "SWV ITM Data Console" view in STM32CubeIDE
 */
#ifdef USE_ITM_PRINTF

#include "stm32fxxx_hal.h"  /* Replace xxx with your STM32 family */

#define ITM_PORT_NUMBER  0

/**
 * @brief  Send a character via ITM/SWO
 */
static int ITM_SendChar(int ch)
{
    if ((ITM->TCR & ITM_TCR_ITMENA_Msk) &&
        (ITM->TER & (1UL << ITM_PORT_NUMBER)))
    {
        while (ITM->PORT[ITM_PORT_NUMBER].u32 == 0)
        {
            /* Wait for transmitter ready */
        }
        ITM->PORT[ITM_PORT_NUMBER].u8 = (uint8_t)ch;
    }
    return ch;
}

/**
 * @brief  Redirect printf to ITM/SWO
 */
int _write(int file, char *ptr, int len)
{
    int i;
    for (i = 0; i < len; i++)
    {
        ITM_SendChar(*ptr++);
    }
    return len;
}

#endif /* USE_ITM_PRINTF */

/* ============================================================================
 * MAIN FUNCTION
 * ============================================================================
 */
int main(void)
{
    /* HAL Initialization (generated by STM32CubeMX) */
    // HAL_Init();
    // SystemClock_Config();
    // MX_GPIO_Init();

    /* Optional: Print initial matrix values if using ITM */
    #ifdef USE_ITM_PRINTF
    printf("\r\n=== STM32 Matrix Multiplication Demo ===\r\n");
    printf("Matrix A:\r\n");
    printf("[%.1f  %.1f]\r\n", matrix_A[0][0], matrix_A[0][1]);
    printf("[%.1f  %.1f]\r\n", matrix_A[1][0], matrix_A[1][1]);
    printf("\r\nMatrix B:\r\n");
    printf("[%.1f  %.1f]\r\n", matrix_B[0][0], matrix_B[0][1]);
    printf("[%.1f  %.1f]\r\n", matrix_B[1][0], matrix_B[1][1]);
    #endif

    /* Perform matrix multiplication */
    multiply_matrices_2x2();

    /* Optional: Print results if using ITM */
    #ifdef USE_ITM_PRINTF
    printf("\r\nResult Matrix C = A × B:\r\n");
    printf("[%.1f  %.1f]\r\n", matrix_C[0][0], matrix_C[0][1]);
    printf("[%.1f  %.1f]\r\n", matrix_C[1][0], matrix_C[1][1]);
    printf("\r\nExpected: [19.0  22.0] / [43.0  50.0]\r\n");
    printf("Calculation %s\r\n",
           calculation_complete ? "COMPLETE" : "FAILED");
    #endif

    /* Infinite loop - typical for embedded systems */
    while (1)
    {
        /* Place breakpoint here to inspect variables in debugger */
        __NOP();  /* Prevents optimizer from removing loop */
    }
}
