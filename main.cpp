#include "QuickSort.h"

#include <vector>
#include <chrono>
#include <ctime>
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstdlib>	

void OrderedVector(std::vector<int> & arr)
{
	int size = arr.size();
	while(size>=0)
		arr[size] = size--;
}

void reverseOrderedVector(std::vector<int>& arr)
{

	int i=arr.size();
	while(i >= 0)
		arr[arr.size() - i--] = i;
}

void RandomVector(std::vector<int>& arr)
{
	srand(time(NULL));
	int i = 0;
	while( i< arr.size())
		arr[i++] = rand() % 1000;
}

bool checkOrderCorrect(const std::vector<int> & arr)
{
	int prev = -1;
	for(auto a: arr)
	{
		if(	a<prev)
		{
			std::cout<<a<<" "<<prev;
			return false;
		}
		prev = a;
	}
	return true;
}


void print(std::vector<int> arr)
{
	std::cout<<std::endl;
	for(auto elm:arr)
		std::cout<<elm<< " ";
	std::cout<<std::endl;
}

double calculateTime(std::vector<int>& arr,PivotSelection type,bool shuffle)
{
	std::chrono::time_point<std::chrono::system_clock> start, end;
	if(shuffle)
	{
		random_shuffle(std::begin(arr), std::end(arr));
	}
    start = std::chrono::system_clock::now();
	QuickSort<int>::sort(&arr[0],arr.size(),type);
    end = std::chrono::system_clock::now();
    std::chrono::duration<double> elapsed_seconds = end-start;
	return elapsed_seconds.count();
}

std::string test(std::vector<int>& arr,std::function<void (std::vector<int>&)> arr_prep,PivotSelection type,bool shuffle, std::string message)
{
	double time = 0;
    for(int i=0;i<10;i++)
    {
    	arr_prep(arr);
    	time += calculateTime(arr,PICK_FIRST,shuffle);
    	if(!checkOrderCorrect(arr)) throw "wrong canisi";
    }

    std::ostringstream str;
	str<<message<< time / 10;
	return str.str();
}

int main(int argc, char **argv)
{
	int x = atoi(argv[1]);
	std::cout<< "element count: "<<x<<std::endl;
	std::ofstream file("timings.txt");
	std::vector<int> v(x);
	file<<std::endl<<test(v, OrderedVector, PICK_FIRST,false,"Pick First initially ordered array:  ");
	std::cout<< "1 done..."<<std::endl;
	file<<std::endl<<test(v, reverseOrderedVector, PICK_FIRST,false,"Pick First initially reverse ordered array:  ");
	std::cout<< "2 done..."<<std::endl;
	file<<std::endl<<test(v,RandomVector,PICK_FIRST,false,"Pick First initially random array:  ");
	std::cout<< "3 done..."<<std::endl;
	file<<std::endl<<test(v,OrderedVector,PICK_RANDOM,false,"Pick First initially ordered array:  ");
	std::cout<< "4 done..."<<std::endl;
	file<<std::endl<<test(v,reverseOrderedVector,PICK_RANDOM,false,"Pick First initially reverse ordered array:  ");
	std::cout<< "5 done..."<<std::endl;
	file<<std::endl<<test(v,RandomVector,PICK_RANDOM,false,"Pick First initially random array:  ");
	std::cout<< "6 done..."<<std::endl;
	file<<std::endl<<test(v,OrderedVector,PICK_RANDOM,true,"Pick First initially ordered array:  ");
	std::cout<< "7 done..."<<std::endl;
	file<<std::endl<<test(v,reverseOrderedVector,PICK_RANDOM,true,"Pick First initially reverse ordered array:  ");
	std::cout<< "8 done..."<<std::endl;
	file<<std::endl<<test(v,RandomVector,PICK_RANDOM,true,"Pick First initially random array:  ");
	std::cout<< "9 done..."<<std::endl;
	return 0;
}