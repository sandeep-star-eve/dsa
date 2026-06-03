#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>

#define RING_BUFFER_SIZE 64 // Must be a power of 2 for optimization!

typedef struct {
    uint8_t buffer[RING_BUFFER_SIZE];
    volatile uint16_t head; 
    volatile uint16_t tail; 
} RingBuffer_t;

// Initialize the buffer
void RingBuffer_Init(RingBuffer_t *rb) {
    rb->head = 0;
    rb->tail = 0;
}

// Check if buffer is empty
bool RingBuffer_IsEmpty(RingBuffer_t *rb) {
    return (rb->head == rb->tail);
}

// Check if buffer is full
bool RingBuffer_IsFull(RingBuffer_t *rb) {
    return ((rb->head + 1) % RING_BUFFER_SIZE == rb->tail);
}

// PRODUCER: Called exclusively inside the ISR (e.g., UART RX ISR)
bool RingBuffer_Write(RingBuffer_t *rb, uint8_t data) {
    if (RingBuffer_IsFull(rb)) {
        return false; // Overflow! Data lost.
    }
    
    rb->buffer[rb->head] = data;
    // Wrap around using modulo (or bitwise mask if power of 2)
    rb->head = (rb->head + 1) % RING_BUFFER_SIZE; 
    
    return true;
}

// CONSUMER: Called exclusively in the Main Loop (Thread Mode)
bool RingBuffer_Read(RingBuffer_t *rb, uint8_t *p_data) {
    if (RingBuffer_IsEmpty(rb)) {
        return false; // No data available
    }
    
    *p_data = rb->buffer[rb->tail];
    rb->tail = (rb->tail + 1) % RING_BUFFER_SIZE;
    
    return true;
}
int main() {
    RingBuffer_t myBuffer;
    RingBuffer_Init(&myBuffer);
    
    // Simulate ISR writing data
    RingBuffer_Write(&myBuffer, 0x55);
    RingBuffer_Write(&myBuffer, 0xAA);
    
    // Simulate Main Loop reading data
    uint8_t data;
    while (RingBuffer_Read(&myBuffer, &data)) {
        // Process data (for demonstration, we just print it)
        printf("Read data: 0x%02X\n", data);
    }
    
    return 0;
}