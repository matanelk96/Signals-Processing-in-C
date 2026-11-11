/*
	Name: Matan Ronen & Matanel Kadosh
	Date: 14.07.2026
	Grader: ?
	File:circular_buffer.c
	This file implement the moving average filter buffer.
 */
#include "peripherals.h"

struct buffer idata cbuffer;
unsigned int t_oldest;

void cbuffer_reset(struct buffer *cbrptr) // clear the buffer
{
    int i;
    for (i = 0; i < FILTER_LENGTH; i++)
    {
        cbrptr->sample[i] = 0;			// Initialize all samples to zero
    }
    cbrptr->oldest_index = 0;			// Reset index pointer
    cbrptr->length = FILTER_LENGTH;		// Set buffer length
}

unsigned int update_cbuffer(struct buffer *cbrptr, unsigned int newsample)
{	   
    t_oldest = cbrptr->sample[cbrptr->oldest_index];	// Retrieve the oldest sample before overwriting it
    cbrptr->sample[cbrptr->oldest_index] = newsample;	// Store the new sample in the current index
    if (cbrptr->oldest_index < (cbrptr->length) - 1) 	// Update the index circularly
    {
        cbrptr->oldest_index++;
    }
    else
    {
        cbrptr->oldest_index = 0;
    }
    return t_oldest;			// Return the oldest sample to update the sum
}