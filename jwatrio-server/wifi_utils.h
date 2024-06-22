#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <windows.h>
#include <wlanapi.h>

// 연결된 WiFi 이름을 가져오는 함수 선언
int getConnectedSSID(char* ssid, size_t ssid_size);

// 필요한 초기화 및 정리 작업을 수행하는 함수 선언
HANDLE initializeWlanHandle();
void cleanupWlanHandle(HANDLE hClient);

#endif // WIFI_UTILS_H
