#include <upload.h>
#include <curl/curl.h>

namespace AlertWatchdog {
	UploadConfigure::UploadConfigure(string url) : remote_url(url) {}

	Data::Data(): timestamp(time(nullptr)), data("{}") {
		//auto obj = std::chrono::system_clock::now();
	}

	string Data::GetJson() const {
		return this->data.dump(4);
	}

	PostData::PostData(unsigned long type, string message) : Data() {
		this->data["version"] = version;
		this->data["message"] = message;
		this->data["type"] = type;
		this->data["timestamp"] = timestamp;
	}

	bool PostData::Post(UploadConfigure & uc) const {
		CURL* curl;
		CURLcode res;

		curl = curl_easy_init();
		if (curl) {
			curl_easy_setopt(curl, CURLOPT_URL, uc.GetUrl().c_str());
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, this->GetJson().c_str());

			res = curl_easy_perform(curl);
			if (res != CURLE_OK)
				throw UploadErrorException(res);

			curl_easy_cleanup(curl);
		}
		return true;
	}
}
