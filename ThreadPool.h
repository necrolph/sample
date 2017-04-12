// Threadpool C++ 11 пример с https://alexagafonov.com/2015/05/05/thread-pool-implementation-in-c-11/

#pragma once

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <iostream>
//#include <unistd.h>
#include <io.h>

using namespace std;

class CIntPoint;

class ThreadPool
{
public:

	// Constructor.
	ThreadPool(int threads);

	// Destructor.
	~ThreadPool();

	// Adds task to a task queue.
	void Enqueue(function<void()> f);

	// Shut down the pool.
	void ShutDown();

private:
	// Thread pool storage.
	vector<thread> threadPool;

	// Queue to keep track of incoming tasks.
	//queue<function<void()>> tasks;
	queue<function<void()>> tasks;

	// Task queue mutex.
	mutex tasksMutex;

	// Condition variable.
	condition_variable condition;

	// Indicates that pool needs to be shut down.
	bool terminate;

	// Indicates that pool has been terminated.
	bool stopped;

	// Function that will be invoked by our threads.
	void Invoke();
};
