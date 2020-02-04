/*	Microsoft C5.0 doesn't have gamma, so you must link
	this
*/
#include "hoc.h"
double
gamma()
{
	execerror("gamma","not available on this system");
}
int signgam;
