#include <upload.h>

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
}
