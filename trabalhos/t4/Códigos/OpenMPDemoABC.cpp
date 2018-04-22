#include <omp.h>
#include <algorithm>
#include <iostream>
#include <string>

using namespace std;

class SharedArray {

	private:
		char* array;
		int index;
		int size;

	public:
		SharedArray(int n) : size(n), index(0){
			array = new char[size];
			fill(array, array+size, '-');
		}
		~SharedArray() {
			delete[] array;
		}
		
		void addChar(char c) {
			array[index] = c;
			spendSomeTime();
			index++;    
		}
	   
		int countOccurrences(char c){
			return count(array, array+size, c);
		}
		
		string toString(){
			return string(array, size);
		}

	private:
		void spendSomeTime(){
			for (int i = 0; i < 10000; i++){
				for (int j = 0; j < 100; j++){
				}
			}
		}
};


class ArrayFiller {
	
	private:
		static const int nThreads = 3;
		static const int nTimes = 20;
		bool critical;
		SharedArray* array;
	
	public:
		ArrayFiller(bool usemutex){
			array = new SharedArray(nThreads * nTimes);
			critical = usemutex;
		}
	
		void fillArrayConcurrentlyAuto(){		
			if(critical){
				#pragma omp parallel for schedule(auto)
				for (int i = 0; i < nThreads * nTimes; ++i)
					#pragma omp critical
					array->addChar('A'+omp_get_thread_num());
			}
			else{
				#pragma omp parallel for schedule(auto)
				for (int i = 0; i < nThreads * nTimes; ++i)
					array->addChar('A'+omp_get_thread_num());
			}
		}
		
		void fillArrayConcurrentlyDynamic(){
			if(critical){
				#pragma omp parallel for schedule(dynamic)
				for (int i = 0; i < nThreads * nTimes; ++i)
					#pragma omp critical
					array->addChar('A'+omp_get_thread_num());
			}
			else{
				#pragma omp parallel for schedule(dynamic)
				for (int i = 0; i < nThreads * nTimes; ++i)
					array->addChar('A'+omp_get_thread_num());
			}
		}
		
		void fillArrayConcurrentlyGuided(){
			if(critical){
				#pragma omp parallel for schedule(guided)
				for (int i = 0; i < nThreads * nTimes; ++i)
					#pragma omp critical
					array->addChar('A'+omp_get_thread_num());
			}
			else{
				#pragma omp parallel for schedule(guided)
				for (int i = 0; i < nThreads * nTimes; ++i)
					array->addChar('A'+omp_get_thread_num());
			}
		}
		
		void fillArrayConcurrentlyRuntime(){
			if(critical){
				#pragma omp parallel for schedule(runtime)
				for (int i = 0; i < nThreads * nTimes; ++i)
					#pragma omp critical
					array->addChar('A'+omp_get_thread_num());
			}
			else{
				#pragma omp parallel for schedule(runtime)
				for (int i = 0; i < nThreads * nTimes; ++i)
					array->addChar('A'+omp_get_thread_num());
			}
		}
		
		void fillArrayConcurrentlyStatic(){
			if(critical){
				#pragma omp parallel for schedule(static)
				for (int i = 0; i < nThreads * nTimes; ++i)
					#pragma omp critical
					array->addChar('A'+omp_get_thread_num());
			}
			else{
				#pragma omp parallel for schedule(static)
				for (int i = 0; i < nThreads * nTimes; ++i)
					array->addChar('A'+omp_get_thread_num());
			}
		}
		
		void printStats(){
			cout << array->toString() << endl;
		for (int i = 0; i < nThreads; ++i)
			cout << (char) ('A'+i) << "=" 
			<< array->countOccurrences('A'+i) << " ";
			cout << endl;
		}
		
		~ArrayFiller(){
			delete array;
		}
};


int main() {

	cout << "Each thread should add its char to the array n times (n=20)" << endl;
	cout << "Correct results should total exactly nThreads*nTimes chars" << endl;
	
	omp_set_num_threads(3);
	
	cout << "\n\nSCHEDULE AUTO:" << endl;	
	cout << "\nCom critical:" << endl;
	ArrayFiller m1(true);
	m1.fillArrayConcurrentlyAuto();
	m1.printStats();
	   
	cout << "\nSem Critical:" << endl;
	ArrayFiller m2(false);
	m2.fillArrayConcurrentlyAuto();
	m2.printStats();
	
	cout << "\n\nSCHEDULE DYNAMIC:" << endl;
	cout << "\nCom critical:" << endl;
	ArrayFiller m3(true);
	m3.fillArrayConcurrentlyDynamic();
	m3.printStats();
	   
	cout << "\nSem Critical:" << endl;
	ArrayFiller m4(false);
	m4.fillArrayConcurrentlyDynamic();
	m4.printStats();
	
	cout << "\nSCHEDULE GUIDED:" << endl;
	cout << "\nCom critical:" << endl;
	ArrayFiller m5(true);
	m5.fillArrayConcurrentlyGuided();
	m5.printStats();
	   
	cout << "\nSem Critical:" << endl;
	ArrayFiller m6(false);
	m6.fillArrayConcurrentlyGuided();
	m6.printStats();
	
	cout << "\n\nSCHEDULE RUNTIME:" << endl;
	cout << "\nCom critical:" << endl;
	ArrayFiller m7(true);
	m7.fillArrayConcurrentlyRuntime();
	m7.printStats();
	   
	cout << "\nSem Critical:" << endl;
	ArrayFiller m8(false);
	m8.fillArrayConcurrentlyRuntime();
	m8.printStats();
	
	cout << "\n\nSCHEDULE STATIC:" << endl;
	cout << "\nCom critical:" << endl;
	ArrayFiller m9(true);
	m9.fillArrayConcurrentlyStatic();
	m9.printStats();
	   
	cout << "\nSem Critical:" << endl;
	ArrayFiller m10(false);
	m10.fillArrayConcurrentlyStatic();
	m10.printStats();
}
