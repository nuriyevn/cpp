#include <syslog.h>
#include <unistd.h>
int main()
{	
	setlogmask(LOG_UPTO(LOG_INFO));
	openlog("exampleprog", LOG_CONS | LOG_PID
		| LOG_NDELAY, LOG_LOCAL1);
	
	syslog(LOG_NOTICE, "Program start by User %d", getuid());
	syslog(LOG_NOTICE, "2nd: Program start by User %d", getuid());
	syslog(LOG_INFO, "A tree falls in a forest");

	closelog();
	system("tail -n 10 /var/log/messages");
}
