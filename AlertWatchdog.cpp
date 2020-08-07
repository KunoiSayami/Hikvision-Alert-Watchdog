#include "AlertWatchdog.h"
using namespace std;

void MeessageCallback(LONG lCommand, NET_DVR_ALARMER* pAlarmer, char* pAlarmInfo, DWORD dwBufLen, void* puser) {
	NET_DVR_ALARMINFO struAlarmInfo;
#ifdef _MSC_VER
	memcpy_s(&struAlarmInfo, sizeof(NET_DVR_ALARMINFO), pAlarmInfo, sizeof(NET_DVR_ALARMINFO));
#else
	memcpy(&struAlarmInfo, pAlarmInfo, sizeof(NET_DVR_ALARMINFO));
#endif
	switch (lCommand) {
	case COMM_ALARM:
		switch (struAlarmInfo.dwAlarmType) {
		case 3:
			for (int channel = 0; channel < MAX_CHANNUM; channel++) {
				if (struAlarmInfo.dwChannel[channel] == 1) {
					
				}
			}
			break;
		}
	}
}

int main()
{
	return 0;
}
