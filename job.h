#ifndef __JOB_H__
#define __JOB_H__

typedef void(*uop)(void*);

typedef struct job {
	const uop* uops;
	const uop* func;
	struct job* next;
} job;

extern void job_fetch(job* self, const uop* uops);
extern void job_resume(job* self);
extern void job_pending(job* self);
extern void job_next(job* self, int state);
extern void job_invoke(job* parent, job* self);

#endif//__JOB_H__
