#include "wifi.h"
#include <stdio.h>

// 무선 LAN 핸들을 초기화하는 함수
HANDLE initializeWlanHandle() {
    HANDLE hClient = NULL;
    DWORD dwMaxClient = 2;
    DWORD dwCurVersion = 0;
    DWORD dwResult = WlanOpenHandle(dwMaxClient, NULL, &dwCurVersion, &hClient);

    if (dwResult != ERROR_SUCCESS) {
        printf("WlanOpenHandle failed with error: %u\n", dwResult);
        return NULL;
    }

    return hClient;
}

// 무선 LAN 핸들을 정리하는 함수
void cleanupWlanHandle(HANDLE hClient) {
    if (hClient != NULL) {
        WlanCloseHandle(hClient, NULL);
    }
}

// 연결된 WiFi 이름을 출력하는 함수
void printConnectedSSID() {
    HANDLE hClient = initializeWlanHandle();
    if (hClient == NULL) {
        return;
    }

    PWLAN_INTERFACE_INFO_LIST pIfList = NULL;
    DWORD dwResult = WlanEnumInterfaces(hClient, NULL, &pIfList);
    if (dwResult != ERROR_SUCCESS) {
        printf("WlanEnumInterfaces failed with error: %u\n", dwResult);
        cleanupWlanHandle(hClient);
        return;
    }

    for (unsigned int i = 0; i < pIfList->dwNumberOfItems; i++) {
        PWLAN_INTERFACE_INFO pIfInfo = &pIfList->InterfaceInfo[i];

        if (pIfInfo->isState == wlan_interface_state_connected) {
            PWLAN_AVAILABLE_NETWORK_LIST pBssList = NULL;
            dwResult = WlanGetAvailableNetworkList(hClient,
                &pIfInfo->InterfaceGuid,
                0,
                NULL,
                &pBssList);

            if (dwResult != ERROR_SUCCESS) {
                printf("WlanGetAvailableNetworkList failed with error: %u\n", dwResult);
                WlanFreeMemory(pIfList);
                cleanupWlanHandle(hClient);
                return;
            }

            for (unsigned int j = 0; j < pBssList->dwNumberOfItems; j++) {
                PWLAN_AVAILABLE_NETWORK pBssEntry = &pBssList->Network[j];

                if (pBssEntry->dwFlags & WLAN_AVAILABLE_NETWORK_CONNECTED) {
                    printf("Connected SSID: %.*s\n", pBssEntry->dot11Ssid.uSSIDLength, pBssEntry->dot11Ssid.ucSSID);
                    break;
                }
            }

            WlanFreeMemory(pBssList);
        }
    }

    WlanFreeMemory(pIfList);
    cleanupWlanHandle(hClient);
}
