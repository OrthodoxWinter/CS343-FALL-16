#ifndef __AUTOMATIC_SIGNAL_H__
#define __AUTOMATIC_SIGNAL_H__

#define AUTOMATIC_SIGNAL uCondition cond;

#define WAITUNTIL(pred, before, after)	\
	before;	\
	if (!(pred)) {	\
		while (! cond.empty()) cond.signal();	\
		while (!(pred)) {	\
			cond.wait();	\
		}	\
	}	\
	after;

#define RETURN(expr...)	\
	while (! cond.empty()) cond.signal();	\
	return expr;

#endif