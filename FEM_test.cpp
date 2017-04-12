#include<thread>
#include <string>
#include<chrono>
#include "ThreadPool.h"

typedef std::chrono::high_resolution_clock Clock;
int N = 100;
int* shared_array = new int[N];


class CIntPoint{
public:
	int id;
	CIntPoint(int _id) : id(_id) 
	{}
	CIntPoint() 
	{
		CIntPoint(0);
	}

};

void RadialReturn(CIntPoint *p) {
	//int num = shared_array[0];
	std::cout << "Integration point " << p->id << " processing start." << std::endl;
	int sleep = 1000;
	std::this_thread::sleep_for(std::chrono::milliseconds(sleep));;
	std::cout << "Integration point " << p->id << " processing done." << std::endl;
}

//void RadialReturn() {
//	std::cout << "Integration point " << 0 << " processing start.";
//	int sleep = 1000;
//	std::this_thread::sleep_for(std::chrono::milliseconds(sleep));;
//	std::cout << "Integration point " << 0 << " processing done.";
//}

class Model {
public:
	int cFEs = 0;
	Model(int _cFEs): cFEs(_cFEs){}
};

void FE_solve(Model* pModel, ThreadPool* ptr_pool) {
	for (int iFE = 0; iFE<pModel->cFEs; iFE++)
	{
		for (int iPoint = 0; iPoint<4; iPoint++)
		{
			int id = iFE * 4 + iPoint;
			CIntPoint *ptr_IntPoint = new CIntPoint(id);
			ptr_pool->Enqueue(std::bind(&RadialReturn, ptr_IntPoint));
		}
	}
}


int main() {
	for (int i = 0; i < N; i++) {
		shared_array[i] = i % 20;
	}
	int num_threads = std::thread::hardware_concurrency();
	num_threads = (num_threads > 0) ? num_threads : 1;
	//num_threads = 1;
	ThreadPool pool(num_threads);
	cout << num_threads << " threads created." << std::endl;
	auto time_start = Clock::now();
	Model* ptr_model = new Model(30);
	FE_solve(ptr_model, &pool);
	//pool.Enqueue([]() {
	//			int sleep = 1000;
	//			std::this_thread::sleep_for(std::chrono::milliseconds(sleep));;
	//			cout << "Processed: " << 0 << " Sleep Time: " << sleep << endl;
	//		});
	auto time_end = Clock::now();
	getchar();
	cout << "elapsed time: " << std::chrono::duration_cast<std::chrono::microseconds>(time_end - time_start).count() << std::endl;
	getchar();
	return 0;
}