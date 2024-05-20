#include <iostream>
#include <fstream>
#include <iomanip>
#include <chrono>
#include <cstdlib> // for exit function 

using namespace std;
using namespace std::chrono;
int main()
{
	time_point<high_resolution_clock> startingTime;
	time_point<high_resolution_clock> endingTime;
	duration<double> deltaTime;
	long long sum;   //integer type for sum is not specified in textbook problem
	unsigned long long n;  // again, type for n is not specified in textbook problem
	const unsigned int numOfLoopFragments = 6;  //textbook indexes loop fragments from 1 to 6
	constexpr unsigned int numOfLoopFragmentsDim = numOfLoopFragments + 1;
	const unsigned int MaxNumOfTests = 10;  //Cardinality of each set of upper-bounds (the set of n's) 
	const unsigned int MaxNumOfSets = 7;    //This is number of sets of upper-bounds (the n's) 
	const unsigned int MaxNumTrials = 5;    //How many times we want to test a particular n
	const unsigned int setOfUpperBound_Ns[MaxNumOfSets][MaxNumOfTests]  //Store all the set of sets of n's
	{  //Here are the set of sets of n's
		/*0*/ { 10, 20, 30, 40, 50, 60, 70, 80, 90, 100 },
		/*1*/{ 100, 125, 150, 175, 200, 225, 250, 275, 300, 325 },
		/*2*/{ 100, 200, 300, 400, 500, 600, 700, 800, 900, 1000 },
		/*3*/{ 1000, 2000, 3000, 4000, 5000, 6000, 7000, 8000, 9000, 10000 },
		/*4*/{ 10000, 20000, 30000, 40000, 50000, 60000, 70000, 80000, 90000, 100000 },
		/*5*/{ 100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000, 1000000 },
		/*6*/{ 1000000, 2000000, 3000000, 4000000, 5000000, 6000000, 7000000, 8000000, 9000000, 10000000 }
	};
	unsigned int setIndex;

	//This code tests one loop at a time. The user chooses the loop to test. Then, chooses the 
	//set of Ns to use to show the asymptotic growth. Each N in the set of Ns are timed MaxNumTrails 
	//a number of trials. These times will be averaged giving a timing value for each N. 

	double results[numOfLoopFragmentsDim][MaxNumTrials][MaxNumOfTests] = { 0.0 }; //+1 for correspondence of text loop #
	unsigned int loopFragmentIndex = 0;  // loop number 0 default to exit immediately with no testing.  
	unsigned int nextNindex = 0; // column index for table of times for current N of the set of Ns

	//display the sets from which to choose
	std::cout << "Sets of Ns from which to choose.\n";
	for (unsigned int i = 0; i < MaxNumOfSets; i++) {
		cout << endl;
		cout << "Set " << i << " values: ";
		for (int j = 0; j < MaxNumOfTests; j++)
			cout << setOfUpperBound_Ns[i][j] << " ";
		cout << endl;
	}
	do {
		cout << "Enter loop fragment index (1 - 6) to time (0 to not test any loop): ";
		cin >> loopFragmentIndex;
	} while (loopFragmentIndex < 0 || loopFragmentIndex > numOfLoopFragments);
	if (loopFragmentIndex == 0) return 0; //exit early.

	//Now, time the chosen loop fragment and store in runtime file with suffix name of loop index

	// ofstream constructor opens a file
	string runTimesFileName = "runTimes";
	char loopIndex_cstr[2];
	_itoa_s(loopFragmentIndex, loopIndex_cstr, 10);
	runTimesFileName = runTimesFileName + loopIndex_cstr + ".txt";
	ofstream runTimesFile(runTimesFileName, ios::out);
	if (!runTimesFile) { // overload ! ios function returns true if problems opening file
		cerr << runTimesFileName << "could not be opened." << endl;
		exit(1);
	}
	cout << "Enter the set of Ns to used for loop number " << loopFragmentIndex << ": ";
	cin >> setIndex;
	// at this point all is well, file for storing the runtime results is open and ready for receiving run times of loops
	if (loopFragmentIndex == 1) {
		//first loop from Weiss textbook Problem 2.7
		cout << "Timing loop (" << loopFragmentIndex << ")" << endl;
		for (int trialNum = 0; trialNum < MaxNumTrials; trialNum++) {
			cout << "Trial Number: " << trialNum << endl;
			for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
				n = setOfUpperBound_Ns[setIndex][nextNindex];
				cout << "Input size N = " << n << endl;
				//time loop
				startingTime = high_resolution_clock::now();
				sum = 0;
				for (unsigned long long i = 0; i < n; ++i)
					++sum;
				endingTime = high_resolution_clock::now();
				deltaTime = duration_cast<duration<double>>(endingTime - startingTime);
				//finished timing, now store duration. 
				results[loopFragmentIndex][trialNum][nextNindex] = deltaTime.count();
			}
		}
	}  //end timing loopFragmentIndex 1
	else if (loopFragmentIndex == 2) {
		cout << "Timing loop (" << loopFragmentIndex << ")" << endl;
		for (int trialNum = 0; trialNum < MaxNumTrials; trialNum++) {
			cout << "Trial Number: " << trialNum << endl;
			for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
				n = setOfUpperBound_Ns[setIndex][nextNindex];
				cout << "Input size N = " << n << endl;

				//time loop
				startingTime = high_resolution_clock::now();
				//Put Nested Loop 
				sum = 0;
				for (long i = 0; i < n; i++)
					for (long j = 0; j < n; j++)
						sum++;
				endingTime = high_resolution_clock::now();
				deltaTime = duration_cast<duration<double>>(endingTime - startingTime);
				//finished timing, now store duration. 

				results[loopFragmentIndex][trialNum][nextNindex] = deltaTime.count();
			}
		}
	}
	else if (loopFragmentIndex == 3) {
		//You write this timing test like above: 
		cout << "Timing loop (" << loopFragmentIndex << ")" << endl;
		for (int trialNum = 0; trialNum < MaxNumTrials; trialNum++) {
			cout << "Trial Number: " << trialNum << endl;
			for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
				n = setOfUpperBound_Ns[setIndex][nextNindex];
				cout << "Input size N = " << n << endl;

				//time loop
				startingTime = high_resolution_clock::now();
				//Put Nested Loop Here
				//loop 3 
				sum = 0;
				for (long i = 0; i < n; ++i)
					for (long j = 0; j < n * n; ++j)
						++sum;
				endingTime = high_resolution_clock::now();
				deltaTime = duration_cast<duration<double>>(endingTime - startingTime);
				//finished timing, now store duration. 

				results[loopFragmentIndex][trialNum][nextNindex] = deltaTime.count();
			}
		}
	}
	else if (loopFragmentIndex == 4) {
		//You write this timing test like above:
		cout << "Timing loop (" << loopFragmentIndex << ")" << endl;
		for (int trialNum = 0; trialNum < MaxNumTrials; trialNum++) {
			cout << "Trial Number: " << trialNum << endl;
			for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
				n = setOfUpperBound_Ns[setIndex][nextNindex];
				cout << "Input size N = " << n << endl;

				//time loop
				startingTime = high_resolution_clock::now();
				//Put Nested Loop Here
				//loop4
				sum = 0;
				for (long i = 0; i < n; ++i)
					for (long j = 0; j < i; ++j)
						++sum;
				endingTime = high_resolution_clock::now();
				deltaTime = duration_cast<duration<double>>(endingTime - startingTime);
				//finished timing, now store duration. 

				results[loopFragmentIndex][trialNum][nextNindex] = deltaTime.count();
			}
		}
	}
	else if (loopFragmentIndex == 5) {
		//You write this timing test like above:
		cout << "Timing loop (" << loopFragmentIndex << ")" << endl;
		for (int trialNum = 0; trialNum < MaxNumTrials; trialNum++) {
			cout << "Trial Number: " << trialNum << endl;
			for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
				n = setOfUpperBound_Ns[setIndex][nextNindex];
				cout << "Input size N = " << n << endl;

				//time loop
				startingTime = high_resolution_clock::now();
				//Put Nested Loop Here
				//loop5
				sum = 0;
				for (long i = 0; i < n; ++i)
					for (long j = 0; j < i * i; ++j)
						for (long k = 0; k < j; ++k)
							++sum;
				endingTime = high_resolution_clock::now();
				deltaTime = duration_cast<duration<double>>(endingTime - startingTime);
				//finished timing, now store duration. 

				results[loopFragmentIndex][trialNum][nextNindex] = deltaTime.count();
			}
		}
	}
	else if (loopFragmentIndex == 6) {
		//You write this timing test like above:
		cout << "Timing loop (" << loopFragmentIndex << ")" << endl;
		for (int trialNum = 0; trialNum < MaxNumTrials; trialNum++) {
			cout << "Trial Number: " << trialNum << endl;
			for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
				n = setOfUpperBound_Ns[setIndex][nextNindex];
				cout << "Input size N = " << n << endl;

				//time loop
				startingTime = high_resolution_clock::now();
				//Put Nested Loop Here
				//loop 6 
				sum = 0;
				for (long i = 1; i < n; ++i)
					for (long j = 1; j < i * i; ++j)
						if (j % i == 0)
							for (long k = 0; k < j; ++k)
								++sum;
				endingTime = high_resolution_clock::now();
				deltaTime = duration_cast<duration<double>>(endingTime - startingTime);
				//finished timing, now store duration. 

				results[loopFragmentIndex][trialNum][nextNindex] = deltaTime.count();
			}
		}
	}
	//Print timing results for the chosen loop fragment
	if (1 <= loopFragmentIndex && loopFragmentIndex <= 6) {
		cout << endl;
		runTimesFile << endl;
		cout << setw(17) << "Results for loop fragment " << loopFragmentIndex << ": " << endl;
		runTimesFile << setw(17) << "Results for loop fragment " << loopFragmentIndex << ": " << endl;
		cout << setw(50) << "Values of Ns and times T(N) for loop fragment " << loopFragmentIndex << ":\n";
		runTimesFile << setw(50) << "Values of Ns and times, T(N), for loop fragment " << loopFragmentIndex << ":\n";
		//print "header": the values for Ns from chosen set of Ns. 
		cout << "Trial";
		runTimesFile << "Trial";
		for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
			cout << '\t' << setw(8) << setOfUpperBound_Ns[setIndex][nextNindex];   //don't worry about exact alignment
			runTimesFile << '\t' << setw(8) << setOfUpperBound_Ns[setIndex][nextNindex];  //will be copied into spreadsheet, then formatted
		}
		//print the times for chosen loopFragmentIndex
		cout << endl;
		runTimesFile << endl;
		cout << setprecision(7);
		runTimesFile << fixed << setprecision(7);
		for (unsigned int trialNum = 0; trialNum < MaxNumTrials; trialNum++) {
			cout << trialNum;
			runTimesFile << trialNum;
			for (nextNindex = 0; nextNindex < MaxNumOfTests; nextNindex++) {
				cout << '\t' << fixed << results[loopFragmentIndex][trialNum][nextNindex];
				runTimesFile << '\t' << fixed << results[loopFragmentIndex][trialNum][nextNindex];
			}
			cout << endl;
			runTimesFile << endl;
		}

		runTimesFile.close();
	}
	return 0;
}