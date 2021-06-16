#include <stdio.h>
#include <stdlib.h>
#include "job.h"

__inline void job_fetch(job* self, const uop* uops) {
	self->uops = self->func = uops;
	self->next = NULL;
}

__inline job* job_last(job* self) {
	while (NULL != self->next)
		self = self->next;
	return self;
}

__inline void job_pending(job* self) {
	job_last(self)->next = self;
}

__inline void job_next(job* self, int state) {
	job_last(self)->next = self;
	self->func = &(self->uops[state]);
}

__inline void job_invoke(job* parent, job* self) {
	job_last(parent)->next = self;
	self->next = NULL;
}

__inline void job_resume(job* self) {
	for (job* cur = self; NULL != cur;) {
		(*cur->func)(cur);
		job* old = cur;
		cur = old->next;
		old->next = NULL;
	}
}
