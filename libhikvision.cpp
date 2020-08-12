#include <libhikvision.hpp>
#include <string.h>
#include <iostream>

namespace AlertWatchdog {
	ConnectInfo::ConnectInfo(const string& loc, const unsigned short& p, const string& user, const string& pwd) :
		url(loc), port(p), username(user), password(pwd), is_connect(false), user_id(0) {
		this->device_info = {};
		this->user_info = {};
		this->InitializeUserInfo();
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

	bool HikvisionClient::is_init = false;

	HikvisionClient::HikvisionClient(const ConnectInfo& c) : info(c) {
		this->arminfo = ArmInfo();
	}

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

	void HikvisionClient::Login() {
		this->info.Login();
	}

	void HikvisionClient::Logout() {
		this->info.Logout();
	}

	void HikvisionClient::SetCallbackFunction(MSGCallBack callback) {
		NET_DVR_SetDVRMessageCallBack_V30(callback, nullptr);
	}

	void ConnectInfo::Login() {
		this->user_id = NET_DVR_Login_V40(&this->user_info, &this->device_info);
		if (this->user_id < 0)
			throw OtherLoginException();
		this->is_connect = true;
	}

	void ConnectInfo::Logout() {
		if (!this->is_connect)
			throw NotLoginException();
		NET_DVR_Logout(this->user_id);
		this->is_connect = false;
	}

	void HikvisionClient::SetupAlarmChan() {
		this->arminfo.SetupAlarmChan(this->info.GetUserId());
	}

	void HikvisionClient::CloseAlarmChan() {
		this->arminfo.CloseAlarmChan();
	}

	ArmInfo::ArmInfo() {
		this->struAlarmParam.dwSize = sizeof(struAlarmParam);
		this->struAlarmParam.byAlarmInfoType = 0;
	}

	void ArmInfo::SetupAlarmChan(LONG userId) {
		if ((this->lHandle = NET_DVR_SetupAlarmChan_V41(userId, &this->struAlarmParam)) < 0) {
#ifndef NDEBUG
			std::cerr << "Setup alarm chan failure (" << NET_DVR_GetLastError() << ")\n";;
#else
			// TODO: Setup alarm chan failure
#endif
			return;
		};
		this->is_setup = true;
		//return this->lHandle;
	}

	bool ArmInfo::CloseAlarmChan() {
		if (!NET_DVR_CloseAlarmChan_V30(this->lHandle)) {
#ifndef NDEBUG
			std::cerr << "Close alarm chan failure (" << NET_DVR_GetLastError() << ")\n";
#else
			// TODO: Close alarm chan failure
#endif
			return false;
		}
		this->is_setup = false;
		return true;
	}

}