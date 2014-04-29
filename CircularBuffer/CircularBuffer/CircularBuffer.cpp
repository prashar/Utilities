#include <iostream>
#include <random>
#include <cstdlib>
#include <ctime>

#define MAX_SIZE 4096

using namespace std ;
typedef unsigned char BYTE ; 
/* 
Write a program which reads in a "very long" binary file(assume an infinitely 
sized stream) and writes to a circular buffer of a specified size. 
*/

BYTE * g_buffer ; 
size_t g_curSize = 0 ; 

int WriteToBuffer(unsigned char * data, int numBytes)
{
	size_t remBytes = 0 ;  
	int hrValue = 0 ; 

	// Assume buffer initialized 
	if(!g_buffer)
	{
		hrValue = -1 ;
		goto EXIT ; 
	}
	
	// Keep looping until you are done sending the packet. 
	while(remBytes < numBytes)
	{
		for(int i=remBytes ; i < numBytes ; i++)
		{
			try
			{
				g_buffer[g_curSize] = data[i] ; 
				g_curSize ++ ;
				remBytes ++ ;
			
				// RESET counter if index @ 4095
				if(g_curSize == MAX_SIZE-1)
				{
					cout << "Buffer Full ( Resetting to 0 ) " << endl ;
					// Call a function to clean up the buffer or send the buffer. 
					// SendOrClean(buffer) ; 
					g_curSize = 0 ; 
				}
			}
			catch(...)
			{
				hrValue=-1 ; 
			}
		}
	}

	EXIT:
		return hrValue ; 
}

int main() 
{
	g_buffer = new unsigned char[MAX_SIZE] ; 
	srand(time(NULL)) ; 
	
	unsigned char * sendData = NULL ; 

	for(int i=0 ; i < 10 ; i++)
	{
		int random_num = rand() % 2501 ; 
	
		cout << "--->Asked to send  " << random_num << " bytes." << endl ; 
		sendData = new unsigned char[random_num] ; 
		WriteToBuffer(sendData,random_num) ;
		cout << "--->Buf Head @ " << g_curSize << " after sending" << endl ; 
		cout << "--->Rem Bytes before buffer is sent " << MAX_SIZE - g_curSize << endl ; 
	}

	return 0;
}