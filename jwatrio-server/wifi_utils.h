#ifndef WIFI_UTILS_H
#define WIFI_UTILS_H

#include <windows.h>
#include <wlanapi.h>

// ����� WiFi �̸��� �������� �Լ� ����
int getConnectedSSID(char* ssid, size_t ssid_size);

// �ʿ��� �ʱ�ȭ �� ���� �۾��� �����ϴ� �Լ� ����
HANDLE initializeWlanHandle();
void cleanupWlanHandle(HANDLE hClient);

#endif // WIFI_UTILS_H
