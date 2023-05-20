#define HAVE_STRUCT_TIMESPEC
#define _CRT_SECURE_NO_WARNINGS
#include <cstdlib>
#include <iostream>
#include <cstring>
#include <pthread.h>
#include <iomanip>
#include <ctime>
#include <time.h> 
using namespace std;

const int num_threads = 4;

struct param {
	int rank;
	const char* order;
};

/* Функция, которую будет исполнять созданный поток */
void* thread_job(void* arg)
{
	clock_t start = clock();
	param* pArguments = (param*)arg;
	int b = 5;
	for (int i = 1; i < 10e6; i++)
	{
		b = b + 1;
	}
	clock_t end = clock();
	double thread_time = (double)(end - start) / CLOCKS_PER_SEC;
	cout << "Thread_job time: " << fixed << setprecision(10) << thread_time << endl;
	//cout << "Thread is running... " << b << endl;
	std::cout << "Thread " << pArguments->rank << " write " << pArguments->order << endl;
	return ((void*)b);
}
int main()
{
	// Определяем переменные: идентификатор потока и код ошибки
	pthread_t thread;
	pthread_t threads[num_threads];
	pthread_attr_t thread_attrs[num_threads];
	int err;
	const char* messages[] = { "First", "Second", "Third", "Fourth" };


	param param[num_threads];
	for (int i = 0; i < num_threads; ++i) {
		param[i].rank = i + 1;
		param[i].order = messages[i];
	}



	for (int i = 0; i < num_threads; i++) {
		err = pthread_attr_init(&thread_attrs[i]);
		if (err != 0) {
			cout << "Cannot create thread attribute: " << strerror(err) << endl;
			exit(-1);
		}
		pthread_attr_setdetachstate(&thread_attrs[i], PTHREAD_CREATE_JOINABLE);
		err = pthread_attr_setstacksize(&thread_attrs[i], 1024 * 1024 * i);
		if (err != 0) {
			cout << "Setting stack size attribute failed: " << strerror(err)
				<< endl;
			exit(-1);
		}



		clock_t start = clock();
		err = pthread_create(&threads[i], &thread_attrs[i], thread_job, (void*)&param[i]);

		if (err != 0) {
			cout << "Cannot create a thread: " << strerror(err) << endl;
			exit(-1);
		}
		clock_t end = clock();
		double thread_time = (double)(end - start) / CLOCKS_PER_SEC;
		cout << "Create thread time: " << fixed << setprecision(30) << thread_time << endl;

	}

	for (auto& thread : threads) {
		pthread_join(thread, nullptr);
	}


	for (auto& thread_attr : thread_attrs) {
		pthread_attr_destroy(&thread_attr);
	}
	
	pthread_exit(NULL);
}
