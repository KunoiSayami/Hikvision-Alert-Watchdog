#include <libhikvision.hpp>

namespace AlertWatchdog {
	ConnectInfo::ConnectInfo(const string& loc, const unsigned short& p, const string& user, const string& pwd) :
		url(loc), port(p), username(user), password(pwd) {
		this->device_info = {};
	}

	//ConnectInfo::ConnectInfo(ConnectInfo& c)

	ConnectInfo::ClassConnectInfo::ClassConnectInfo(const ConnectInfo& c) {
		this->PasteParams(c.url, c.port, c.username, c.password);
	}

	void ConnectInfo::ClassConnectInfo::PasteParams(const string& loc, const unsigned short& p, const string& user, const string& pwd) {
		this->loc = new char[100], this->user = new char[100], this->password = new char[100];
		if (loc.length() > 100 || user.length() > 100 || pwd.length() > 100)
			throw OutOfLengthError();
		strcpy(this->loc, loc.c_str());
		strcpy(this->user, user.c_str());
		strcpy(this->password, pwd.c_str());
		this->port = p;
	}

	ConnectInfo::ClassConnectInfo::ClassConnectInfo(const ConnectInfo* c) : ClassConnectInfo::ClassConnectInfo(*c) {}

	ConnectInfo::ClassConnectInfo::ClassConnectInfo(const string& loc, const unsigned short& p, const string& user, const string& pwd) {
		this->PasteParams(loc, p, user, pwd);
	}

	ConnectInfo::ClassConnectInfo::~ClassConnectInfo() {
		delete[] this->loc, delete[] this->user, delete[] this->password;
	}

	PCHAR ConnectInfo::ClassConnectInfo::GetLocation() {
		return this->loc;
	}

	PCHAR ConnectInfo::ClassConnectInfo::GetUser() {
		return this->user;
	}

	PCHAR ConnectInfo::ClassConnectInfo::GetPassword() {
		return this->password;
	}

	unsigned short ConnectInfo::ClassConnectInfo::GetPort() {
		return this->port;
	}

	HikvisionClient::HikvisionClient(const ConnectInfo& c) : info(c) {}

	void HikvisionClient::Initialize() throw (InitializeException) {
		if (!is_init) {
			if (!NET_DVR_Init())
				throw OtherInitializeException();
			is_init = true;
		}
		else {
			throw AlreadyInitializeException();
		}
	}

	void HikvisionClient::Cleanup() throw (CleanupException) {
		if (is_init) {
			if (!NET_DVR_Cleanup())
				throw OtherCleanupException();
			is_init = false;
		}
		else {
			throw AlreadyCleanupException();
		}
	}

	bool HikvisionClient::Initialized() const {
		return is_init;
	}



	void ConnectInfo::Login() {
		ClassConnectInfo obj = ClassConnectInfo(this);
		NET_DVR_Login(obj.GetLocation(), obj.GetPort(), obj.GetUser(), obj.GetPassword(), &this->device_info);
	}



	void HikvisionClient::Login() {
		
	}
}