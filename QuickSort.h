#pragma once
#include <functional>
#include <iostream>
#include <algorithm> 
#include <stdlib.h>
#include <time.h>   

enum PivotSelection{PICK_FIRST,PICK_RANDOM};

template <class T>
class QuickSort
{
public:
	static void sort(T arr[], int size, PivotSelection pivotType = PICK_RANDOM)
	{
		srand (time(NULL));
		switch(pivotType)
		{
			case PICK_FIRST:
				sort(arr,size,[](int) -> int { return 0;});
			break;
			case PICK_RANDOM:
				sort(arr,size,[](int s) -> int { return rand() % s;});
			break;
			default:
			break;
		}
	}

private:
	static void sort(T arr[], int size, std::function<int (const size_t size)> pivot_handler)
	{
		if(size <= 1)
			return;
		int pivotIndex = pivot_handler(size);
		int lower = 0, upper = size -1;
		std::swap(arr[lower],arr[pivotIndex]);
		pivotIndex = lower++;
		while(lower<upper)
		{
			while(lower<upper && arr[lower] <= arr[pivotIndex])lower++;
			while(lower<upper && arr[upper] >= arr[pivotIndex])upper--;
			std::swap(arr[upper--],arr[lower++]);
		}
		if(lower >= size) lower = size -1;
		while(lower != pivotIndex && arr[lower] >= arr[pivotIndex]) lower--;
		
		std::swap(arr[lower],arr[pivotIndex]);
		pivotIndex = lower;
		sort(&arr[0],lower,pivot_handler);
		sort(&arr[pivotIndex + 1],size - pivotIndex - 1,pivot_handler);
	}
};