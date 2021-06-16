#include <stdio.h>
#include <stdlib.h>
#include "job.h"

typedef struct job1 {
	job job;
	int count;
	int finish;
} job1;

typedef struct job2 {
	job job;
	int count;
	job1 job1;
} job2;

static void func1(job1* self) {
	printf("start!\n");
	job_next((job*)self, 1);
	self->count = 0;
}

static void func3(job1* self) {
	printf("end!\n");
	self->finish = 1;
}

static func2(job1* self) {
	if (self->count < 10) {
		printf("count=%d\n", self->count++);
		job_pending((job*)self);
	}
	else {
		job_next((job*)self, 2);
	}
}

static const uop uops1[] = { func1, func2, func3 };

static void funcA(job2* self) {
	self->job1.finish = 0;
	printf("count=%d\n", self->count++);
	job_fetch((job*)&self->job1, (uop*)uops1);
	job_invoke((job*)&self->job, (job*)&self->job1);
	job_next((job*)self, 1);
}

static void funcB(job2* self) {
	if (self->job1.finish)
		job_next((job*)self, 0);
	else
		job_pending((job*)self);
}

static const uop uops2[] = { funcA, funcB };


int main(void) {

	job1 j1;
	j1.count = 0;
	j1.finish = 0;
	job_fetch(&j1.job, uops2);
	job_resume(&j1.job);

	return 1;
}
