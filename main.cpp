#include<thread>
#include<chrono>
//#include <numeric>
//#include <string>
#include "ThreadPool.h"

std::mutex mutex_;
typedef std::chrono::high_resolution_clock Clock;

//int main() {
//
//	int num_threads = std::thread::hardware_concurrency();
//	num_threads = (num_threads > 0) ? num_threads : 1;
//	num_threads = 2;
//	ThreadPool pool(num_threads);
//	cout << num_threads << " threads created." << std::endl;
//	auto time_start = Clock::now();
//	for (int i = 0; i < 20; i++)
//	{
//		cout << "Enquing: " << i << endl;
//		pool.Enqueue([i]() {
//			int sleep = 1000;
//			std::this_thread::sleep_for(std::chrono::milliseconds(sleep));;
//			mutex_.lock();
//			cout << "Processed: " << i << " Sleep Time: " << sleep << endl;
//			mutex_.unlock();
//		});
//	}
//	auto time_end = Clock::now();
//	getchar();
//	cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start).count() << std::endl;
//	getchar();
//	return 0;
//}