#ifndef __IOBSERVER_H__
#define __IOBSERVER_H__

class IObserver
{
public:
	virtual void Update(float price) = 0;
};



#endif
