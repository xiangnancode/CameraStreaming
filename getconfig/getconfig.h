#ifndef H_GETCONFIG
#define H_GETCONFIG

using namespace std;

struct Net
{
	string ipaddr;
	string port;
};

struct User
{
	int userID;
	string username;
	string password;
};

class get_Config
{

public:
	Net *getNetInfo(){
		ifstream netfile ("./Data/config_net.ini");
		if(!netfile.is_open()) {
			cout << "Unable to open config_net.ini" << endl;
		}
		Net *netinfo = new Net;
		string line;
		getline(netfile, line, '"');
		getline(netfile, line, ' ');
		netinfo->ipaddr = line;
		for (int i = 0; i < 6 ; ++i) {
			getline(netfile, line);
		}
		getline(netfile, line, '"');
		getline(netfile, line, ' ');
		netinfo->port = line;
		netfile.close();
		return netinfo;
	}
	User *getUserInfo(int ID){
		ifstream userfile ("./Data/config_user.ini");
		if(!userfile.is_open()) {
			cout << "Unable to open config_user.ini" << endl;
		}
		User *userinfo = new User;
		string line;
		for (int i = 0; i < ID ; ++i) {
			for (int j = 0; j < 5; ++j) {
				getline(userfile, line);
			}
		}
		if(!userfile.good()) {
			userinfo->userID = -1;
			cout << "no user are able to login" << endl;
			return userinfo;
		}
		userinfo->userID = ID;
		getline(userfile, line, '"');
		getline(userfile, line, ' ');
		userinfo->username = line;
		getline(userfile, line);
		getline(userfile, line, '"');
		getline(userfile, line, ' ');
		userinfo->password = line;
		userfile.close();
		return userinfo;
	}
	void freeMemory(Net *netinfo, User *userinfo){
		delete netinfo;
		delete userinfo;
	}
};


#endif