#pragma once

#include <curl/curl.h>
#include <nlohmann/json.hpp>
#include <string>
//#include <chrono>
#include <ctime>
#include <nlohmann/json.hpp>
#include <exception>

namespace AlertWatchdog {
	using std::string;
	class Data {
	protected:
		nlohmann::json data;
		long long timestamp;
	public:
		Data();
		//Data(string);
		virtual string GetJson() const;
	};

	class UploadConfigure {
	private:
		string remote_url;
	public:
		//UploadConfigure(const UploadConfigure& c);
		UploadConfigure(string);
		string GetUrl() const {
			return this->remote_url;
		}
	};

	class PostData : public Data {
		const static unsigned long version = 0x1;
	public:
		PostData(unsigned long type, string message);
		bool Post(UploadConfigure&) const;
	};

	class UploadException : std::exception {};

#ifdef _MSC_VER
#pragma warning( disable : 26812 )
#endif
	class UploadErrorException : UploadException {
		const char * error_msg;
	public:
		UploadErrorException(CURLcode& res) : UploadException() {
			this->error_msg = curl_easy_strerror(res);
		}
		const char* GetMsg() const {
			return this->error_msg;
		}
	};
}