#include "getconfig.h"

int main (int argc, char * const argv[]) 
{
    get_Config configinfo;
    Net *netinfo = configinfo.getNetInfo();
	cout << netinfo->ipaddr << endl;
	cout << netinfo->port << endl;
	User *userinfo = configinfo.getUserInfo(0);
	cout << userinfo->userID << endl;
	cout << userinfo->username << endl;
	cout << userinfo->password << endl;
	configinfo.freeMemory(netinfo, userinfo);
    return 0;
}