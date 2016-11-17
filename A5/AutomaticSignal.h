#ifndef __AUTOMATIC_SIGNAL_H__
#define __AUTOMATIC_SIGNAL_H__

#define AUTOMATIC_SIGNAL uCondLock cond;

#define WAITUNTIL(pred, before, after)	\
	before	\
	if (!(pred)) {	\
		cond.broadcast();	\
		while (!(pred)) {	\
			cond.wait();	\
		}	\
	}	\
	after

#define RETURN(expr...)	\
	cond.broadcast();	\
	return expr;

#endif