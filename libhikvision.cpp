#include <libhikvision.hpp>
#include <string.h>

namespace AlertWatchdog {
	ConnectInfo::ConnectInfo(const string& loc, const unsigned short& p, const string& user, const string& pwd) :
		url(loc), port(p), username(user), password(pwd), is_connect(false), user_id(0) {
		this->device_info = {};
		this->user_info = {};
	}

	void ConnectInfo::InitializeUserInfo() {
		if (this->url.length() > NET_DVR_DEV_ADDRESS_MAX_LEN ||
			this->username.length() > NET_DVR_LOGIN_USERNAME_MAX_LEN ||
			this->password.length() > NET_DVR_LOGIN_PASSWD_MAX_LEN)
			throw OutOfLengthError();
#ifdef _MSC_VER
		strcpy_s(this->user_info.sDeviceAddress, this->url.c_str());
		strcpy_s(this->user_info.sUserName, this->username.c_str());
		strcpy_s(this->user_info.sPassword, this->password.c_str());
#else
		strcpy(this->user_info.sDeviceAddress, this->url.c_str());
		strcpy(this->user_info.sUserName, this->username.c_str());
		strcpy(this->user_info.sPassword, this->password.c_str());
#endif
		this->user_info.wPort = this->port;
		this->user_info.byLoginMode = 2;
		this->user_info.bUseAsynLogin = false;
	}

	//ConnectInfo::ConnectInfo(ConnectInfo& c)

/*	ConnectInfo::ClassConnectInfo::ClassConnectInfo(const ConnectInfo& c) {
		this->PasteParams(c.url, c.port, c.username, c.password);
	}

	void ConnectInfo::ClassConnectInfo::PasteParams(const string& loc, const unsigned short& p, const string& user, const string& pwd) {
		this->loc = new (std::nothrow) char[100], this->user = new (std::nothrow) char[100], this->password = new (std::nothrow) char[100];
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
	*/

	bool ConnectInfo::IsConnected() const {
		return this->is_connect;
	}

	bool HikvisionClient::is_init = false;

	HikvisionClient::HikvisionClient(const ConnectInfo& c) : info(c) {}

	void HikvisionClient::Initialize() {
		if (!is_init) {
			if (!NET_DVR_Init())
				throw OtherInitializeException();
			NET_DVR_SetReconnect(10000, true);
			is_init = true;
		}
		else {
			throw AlreadyInitializeException();
		}
	}

	void HikvisionClient::Cleanup() {
		if (is_init) {
			// logout first
			if (this->info.IsConnected())
				this->info.Logout();
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
		//ClassConnectInfo obj = ClassConnectInfo(this);
		//NET_DVR_Login_V30(obj.GetLocation(), obj.GetPort(), obj.GetUser(), obj.GetPassword(), &this->device_info);
		this->user_id = NET_DVR_Login_V40(&this->user_info, &this->device_info);
		if (this->user_id == -1)
			throw OtherLoginException();
		this->is_connect = true;
	}

	void ConnectInfo::Logout() {
		if (!this->is_connect)
			throw NotLoginException();
		NET_DVR_Logout(this->user_id);
		this->is_connect = false;
	}
}