/*
 * ============================================================================
 * STM32 4x4 Matrix Multiplication - SWD Debug Friendly
 * ============================================================================
 * 
 * Target: Any STM32 Cortex-M (F0/F1/F4/H7/etc.)
 * IDE: STM32CubeIDE | Debug: SWD Only (No UART/SWO/Printf)
 * 
 * Expected Result (C = A × B):
 *   C[0][0]=70  C[0][1]=80  C[0][2]=90  C[0][3]=100
 *   C[1][0]=158 C[1][1]=184 C[1][2]=210 C[1][3]=236
 *   C[2][0]=246 C[2][1]=288 C[2][2]=330 C[2][3]=372
 *   C[3][0]=334 C[3][1]=392 C[3][2]=450 C[3][3]=508
 * ============================================================================
 */

#include <stdint.h>


#define MATRIX_SIZE 4

/* Input Matrix A (4x4) */
volatile float matrix_A[MATRIX_SIZE][MATRIX_SIZE] = {
    {1.0f,  2.0f,  3.0f,  4.0f},
    {5.0f,  6.0f,  7.0f,  8.0f},
    {9.0f,  10.0f, 11.0f, 12.0f},
    {13.0f, 14.0f, 15.0f, 16.0f}
};

/* Input Matrix B (4x4) */
volatile float matrix_B[MATRIX_SIZE][MATRIX_SIZE] = {
    {1.0f,  0.0f,  0.0f,  1.0f},
    {0.0f,  1.0f,  0.0f,  1.0f},
    {0.0f,  0.0f,  1.0f,  1.0f},
    {1.0f,  1.0f,  1.0f,  0.0f}
};

/* Output Matrix C (4x4) - Initialized to zero */
volatile float matrix_C[MATRIX_SIZE][MATRIX_SIZE] = {
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f},
    {0.0f, 0.0f, 0.0f, 0.0f}
};

/* Debug loop counters - visible in Live Expressions during execution */
volatile int debug_i = 0;  /* Current row index */
volatile int debug_j = 0;  /* Current column index */
volatile int debug_k = 0;  /* Current dot-product index */

/* Status flag */
volatile uint8_t calculation_complete = 0;

/* ============================================================================
 * Algorithm: Standard triple-nested loop O(N³)
 * 
 * For each element C[i][j]:
 *   C[i][j] = Σ(A[i][k] × B[k][j]) for k = 0 to N-1
 * 
 */
void multiply_matrices_4x4(void)
{
    int i, j, k;
    
    /* Reset status flag before starting */
    calculation_complete = 0;
    
    /* Outer loop: iterate over rows of result matrix C */
    for (i = 0; i < MATRIX_SIZE; i++)
    {
        debug_i = i;  /* Update global counter for debugging */
        
        /* Middle loop: iterate over columns of result matrix C */
        for (j = 0; j < MATRIX_SIZE; j++)
        {
            debug_j = j;  /* Update global counter for debugging */
            
            /* Initialize accumulator for this element */
            float sum = 0.0f;
            
            /* Inner loop: compute dot product of A[row i] and B[col j] */
            for (k = 0; k < MATRIX_SIZE; k++)
            {
                debug_k = k;  /* Update global counter for debugging */
                
                /* Accumulate: A[i][k] * B[k][j] */
                sum += matrix_A[i][k] * matrix_B[k][j];
                
                /* 
                 * DEBUG TIP: Place a breakpoint here to watch the 
                 * accumulation happen step-by-step in Live Expressions.
                 * You'll see 'sum' grow with each iteration of k.
                 */
            }
            
            /* Store final dot product result */
            matrix_C[i][j] = sum;
        }
    }
    
    /* Mark calculation as complete */
    calculation_complete = 1;
}

/* ============================================================================
 * MAIN FUNCTION
 * ============================================================================
 */
int main(void)
{
    /* HAL Initialization (uncomment if using STM32CubeMX generated code) */
    // HAL_Init();
    // SystemClock_Config();
    // MX_GPIO_Init();
    
    /* Perform matrix multiplication */
    multiply_matrices_4x4();
    
    /* Infinite loop - typical embedded pattern */
    while (1)
    {
        __NOP();  /* Prevent optimizer from removing empty loop */
                  /* Place breakpoint here to inspect final results */
    }
}