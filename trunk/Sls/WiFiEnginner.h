#ifndef WIFI_ENGINNER_H_
#define WIFI_ENGINNER_H_


#define WLAN_MAX_NAME_LENGTH 256
#define DOT11_SSID_MAX_LENGTH   32      // 32 bytes
#define WLAN_NOTIFICATION_SOURCE_ACM 8
typedef struct _DOT11_SSID
{
    ULONG uSSIDLength;
    UCHAR ucSSID[DOT11_SSID_MAX_LENGTH];
} DOT11_SSID, * PDOT11_SSID;

typedef enum _DOT11_BSS_TYPE
{
    dot11_BSS_type_infrastructure = 1,
    dot11_BSS_type_independent = 2,
    dot11_BSS_type_any = 3
} DOT11_BSS_TYPE, * PDOT11_BSS_TYPE;

typedef DWORD WLAN_REASON_CODE, *PWLAN_REASON_CODE;

typedef enum _DOT11_PHY_TYPE
{
    dot11_phy_type_unknown = 0,
    dot11_phy_type_any = dot11_phy_type_unknown,
    dot11_phy_type_fhss = 1,
    dot11_phy_type_dsss = 2,
    dot11_phy_type_irbaseband = 3,
    dot11_phy_type_ofdm = 4,
    dot11_phy_type_hrdsss = 5,
    dot11_phy_type_erp = 6,
    dot11_phy_type_ht = 7,
    dot11_phy_type_IHV_start = 0x80000000,
    dot11_phy_type_IHV_end = 0xffffffff
} DOT11_PHY_TYPE, * PDOT11_PHY_TYPE;

#define WLAN_MAX_PHY_TYPE_NUMBER    8

typedef ULONG WLAN_SIGNAL_QUALITY, *PWLAN_SIGNAL_QUALITY;

typedef struct _NDIS_OBJECT_HEADER
{
    UCHAR   Type;
    UCHAR   Revision;
    USHORT  Size;
} NDIS_OBJECT_HEADER, *PNDIS_OBJECT_HEADER;

typedef enum _DOT11_AUTH_ALGORITHM
{
    DOT11_AUTH_ALGO_80211_OPEN = 1,
    DOT11_AUTH_ALGO_80211_SHARED_KEY = 2,
    DOT11_AUTH_ALGO_WPA = 3,
    DOT11_AUTH_ALGO_WPA_PSK = 4,
    DOT11_AUTH_ALGO_WPA_NONE = 5,               // used in NatSTA only
    DOT11_AUTH_ALGO_RSNA = 6,
    DOT11_AUTH_ALGO_RSNA_PSK = 7,
    DOT11_AUTH_ALGO_IHV_START = 0x80000000,
    DOT11_AUTH_ALGO_IHV_END = 0xffffffff
} DOT11_AUTH_ALGORITHM, * PDOT11_AUTH_ALGORITHM;

typedef struct DOT11_AUTH_ALGORITHM_LIST
{
    #define DOT11_AUTH_ALGORITHM_LIST_REVISION_1  1
    NDIS_OBJECT_HEADER Header;
    ULONG uNumOfEntries;
    ULONG uTotalNumOfEntries;
    DOT11_AUTH_ALGORITHM AlgorithmIds[1];
} DOT11_AUTH_ALGORITHM_LIST, * PDOT11_AUTH_ALGORITHM_LIST;

typedef enum _DOT11_CIPHER_ALGORITHM
{
    DOT11_CIPHER_ALGO_NONE = 0x00,
    DOT11_CIPHER_ALGO_WEP40 = 0x01,
    DOT11_CIPHER_ALGO_TKIP = 0x02,
    DOT11_CIPHER_ALGO_CCMP = 0x04,
    DOT11_CIPHER_ALGO_WEP104 = 0x05,
    DOT11_CIPHER_ALGO_WPA_USE_GROUP = 0x100,
    DOT11_CIPHER_ALGO_RSN_USE_GROUP = 0x100,
    DOT11_CIPHER_ALGO_WEP = 0x101,
    DOT11_CIPHER_ALGO_IHV_START = 0x80000000,
    DOT11_CIPHER_ALGO_IHV_END = 0xffffffff
} DOT11_CIPHER_ALGORITHM, * PDOT11_CIPHER_ALGORITHM;

typedef struct _WLAN_AVAILABLE_NETWORK
{
    WCHAR strProfileName[WLAN_MAX_NAME_LENGTH];
    DOT11_SSID dot11Ssid;
    DOT11_BSS_TYPE dot11BssType;
    ULONG uNumberOfBssids;
    BOOL bNetworkConnectable;
    WLAN_REASON_CODE wlanNotConnectableReason;
    ULONG uNumberOfPhyTypes;
    DOT11_PHY_TYPE dot11PhyTypes[WLAN_MAX_PHY_TYPE_NUMBER];
    // bMorePhyTypes is set to TRUE if the PHY types for the network
    // exceeds WLAN_MAX_PHY_TYPE_NUMBER.
    // In this case, uNumerOfPhyTypes is WLAN_MAX_PHY_TYPE_NUMBER and the
    // first WLAN_MAX_PHY_TYPE_NUMBER PHY types are returned.
    BOOL bMorePhyTypes;
    WLAN_SIGNAL_QUALITY wlanSignalQuality;
    BOOL bSecurityEnabled;
    DOT11_AUTH_ALGORITHM dot11DefaultAuthAlgorithm;
    DOT11_CIPHER_ALGORITHM dot11DefaultCipherAlgorithm;
    DWORD dwFlags;
    DWORD dwReserved;
} WLAN_AVAILABLE_NETWORK, *PWLAN_AVAILABLE_NETWORK;
typedef enum _WLAN_NOTIFICATION_ACM {
  wlan_notification_acm_start                        = 0,
  wlan_notification_acm_autoconf_enabled,
  wlan_notification_acm_autoconf_disabled,
  wlan_notification_acm_background_scan_enabled,
  wlan_notification_acm_background_scan_disabled,
  wlan_notification_acm_bss_type_change,
  wlan_notification_acm_power_setting_change,
  wlan_notification_acm_scan_complete,
  wlan_notification_acm_scan_fail,
  wlan_notification_acm_connection_start,
  wlan_notification_acm_connection_complete,
  wlan_notification_acm_connection_attempt_fail,
  wlan_notification_acm_filter_list_change,
  wlan_notification_acm_interface_arrival,
  wlan_notification_acm_interface_removal,
  wlan_notification_acm_profile_change,
  wlan_notification_acm_profile_name_change,
  wlan_notification_acm_profiles_exhausted,
  wlan_notification_acm_network_not_available,
  wlan_notification_acm_network_available,
  wlan_notification_acm_disconnecting,
  wlan_notification_acm_disconnected,
  wlan_notification_acm_adhoc_network_state_change,
  wlan_notification_acm_end 
} WLAN_NOTIFICATION_ACM, *PWLAN_NOTIFICATION_ACM;
typedef struct _WLAN_AVAILABLE_NETWORK_LIST
{
    DWORD dwNumberOfItems;
    DWORD dwIndex;
    WLAN_AVAILABLE_NETWORK Network[1];
} WLAN_AVAILABLE_NETWORK_LIST, *PWLAN_AVAILABLE_NETWORK_LIST;

typedef enum _WLAN_INTERFACE_STATE
{
    wlan_interface_state_not_ready,
    wlan_interface_state_connected,
    wlan_interface_state_ad_hoc_network_formed,
    wlan_interface_state_disconnecting,
    wlan_interface_state_disconnected,
    wlan_interface_state_associating,
    wlan_interface_state_discovering,
    wlan_interface_state_authenticating
} WLAN_INTERFACE_STATE, *PWLAN_INTERFACE_STATE;

typedef struct _WLAN_INTERFACE_INFO
{
    GUID InterfaceGuid;
    WCHAR strInterfaceDescription[WLAN_MAX_NAME_LENGTH];
    WLAN_INTERFACE_STATE isState;
} WLAN_INTERFACE_INFO, *PWLAN_INTERFACE_INFO;

typedef struct _WLAN_INTERFACE_INFO_LIST
{
    DWORD dwNumberOfItems;
    DWORD dwIndex;
    WLAN_INTERFACE_INFO InterfaceInfo[1];
} WLAN_INTERFACE_INFO_LIST, *PWLAN_INTERFACE_INFO_LIST;

typedef enum _WLAN_CONNECTION_MODE
{
    wlan_connection_mode_profile = 0,
    wlan_connection_mode_temporary_profile,
    wlan_connection_mode_discovery_secure,
    wlan_connection_mode_discovery_unsecure,
    wlan_connection_mode_auto,
    wlan_connection_mode_invalid
} WLAN_CONNECTION_MODE, *PWLAN_CONNECTION_MODE;
#define DOT11_RATE_SET_MAX_LENGTH 126
typedef struct _WLAN_RATE_SET {
  ULONG  uRateSetLength;
  USHORT usRateSet[DOT11_RATE_SET_MAX_LENGTH];
} WLAN_RATE_SET, *PWLAN_RATE_SET;

typedef UCHAR DOT11_MAC_ADDRESS[6];
typedef DOT11_MAC_ADDRESS * PDOT11_MAC_ADDRESS;
typedef struct _WLAN_BSS_ENTRY {
  DOT11_SSID        dot11Ssid;
  ULONG             uPhyId;
  DOT11_MAC_ADDRESS dot11Bssid;
  DOT11_BSS_TYPE    dot11BssType;
  DOT11_PHY_TYPE    dot11BssPhyType;
  LONG              lRssi;
  ULONG             uLinkQuality;
  BOOLEAN           bInRegDomain;
  USHORT            usBeaconPeriod;
  ULONGLONG         ullTimestamp;
  ULONGLONG         ullHostTimestamp;
  USHORT            usCapabilityInformation;
  ULONG             ulChCenterFrequency;
  WLAN_RATE_SET     wlanRateSet;
  ULONG             ulIeOffset;
  ULONG             ulIeSize;
} WLAN_BSS_ENTRY, *PWLAN_BSS_ENTRY;
typedef struct _WLAN_BSS_LIST {
  DWORD          dwTotalSize;
  DWORD          dwNumberOfItems;
  WLAN_BSS_ENTRY wlanBssEntries[1];
} WLAN_BSS_LIST, *PWLAN_BSS_LIST;


typedef struct DOT11_BSSID_LIST
{
    #define DOT11_BSSID_LIST_REVISION_1  1
    NDIS_OBJECT_HEADER Header;
    ULONG uNumOfEntries;
    ULONG uTotalNumOfEntries;
    DOT11_MAC_ADDRESS BSSIDs[1];
} DOT11_BSSID_LIST, * PDOT11_BSSID_LIST;

typedef struct _WLAN_CONNECTION_PARAMETERS
{
    WLAN_CONNECTION_MODE wlanConnectionMode;
    LPCWSTR strProfile;
    PDOT11_SSID pDot11Ssid;
    PDOT11_BSSID_LIST pDesiredBssidList;
    DOT11_BSS_TYPE dot11BssType;
    DWORD dwFlags;
} WLAN_CONNECTION_PARAMETERS, *PWLAN_CONNECTION_PARAMETERS;

typedef struct _WLAN_NOTIFICATION_DATA {
  DWORD NotificationSource;
  DWORD NotificationCode;
  GUID  InterfaceGuid;
  DWORD dwDataSize;
  PVOID pData;
} WLAN_NOTIFICATION_DATA, *PWLAN_NOTIFICATION_DATA;

typedef struct _WLAN_RAW_DATA {
  DWORD dwDataSize;
  BYTE  DataBlob[1];
} WLAN_RAW_DATA, *PWLAN_RAW_DATA;
#define WLAN_API_VERSION_1_0 1
#define WLAN_CONNECTION_HIDDEN_NETWORK 0x00000001
#define WLAN_CONNECTION_ADHOC_JOIN_ONLY 0x00000002
#define WLAN_CONNECTION_IGNORE_PRIVACY_BIT 0x00000004
#define WLAN_CONNECTION_EAPOL_PASSTHROUGH 0x00000008
typedef VOID ( WINAPI *WLAN_NOTIFICATION_CALLBACK )(
    PWLAN_NOTIFICATION_DATA data,
    PVOID context
);
VOID WINAPI WlanNotificationCallback (
	PWLAN_NOTIFICATION_DATA data,
    PVOID context
);
class  CWiFiEnginner 
{
private:
	static CWiFiEnginner *iInstance;
	CWiFiEnginner();
	~CWiFiEnginner();
	
private:
	typedef DWORD  (WINAPI *WLANOPENHANDLE)(DWORD dwClientVersion, PVOID pReserved,
        PDWORD pdwNegotiatedVersion, PHANDLE phClientHandle);
    typedef DWORD  (WINAPI *WLANENUMINTERFACES)(HANDLE hClientHandle, PVOID pReserved,
        PWLAN_INTERFACE_INFO_LIST *ppInterfaceList);
	typedef DWORD (WINAPI *WLANCLOSEHANDLE)(HANDLE hClientHandle, PVOID pReserved);
	typedef DWORD (WINAPI *WLANSCAN)(HANDLE hClientHandle,const GUID *pInterfaceGuid,const PDOT11_SSID pDot11Ssid,const PWLAN_RAW_DATA pIeData,PVOID pReserved);
	typedef DWORD (WINAPI *WLANGETNETWORKBSSLIST)( HANDLE hClientHandle,const GUID *pInterfaceGuid, const  PDOT11_SSID pDot11Ssid,DOT11_BSS_TYPE dot11BssType,BOOL bSecurityEnabled,PVOID pReserved,PWLAN_BSS_LIST *ppWlanBssList);
	typedef DWORD (WINAPI *WLANGETAVAILABLENETWORKLIST)(
          HANDLE hClientHandle,
          const GUID *pInterfaceGuid,
          DWORD dwFlags,
		PVOID pReserved,
         PWLAN_AVAILABLE_NETWORK_LIST *ppAvailableNetworkList
);

typedef DWORD (WINAPI *WLANCONNECT)(
          HANDLE hClientHandle,
          const GUID *pInterfaceGuid,
         const PWLAN_CONNECTION_PARAMETERS pConnectionParameters,
   PVOID pReserved
);
typedef DWORD (WINAPI *WLANGETPROFILE)(
           HANDLE hClientHandle,
           const GUID *pInterfaceGuid,
           LPCWSTR strProfileName,
     PVOID pReserved,
          LPWSTR *pstrProfileXml,
    DWORD *pdwFlags,
      PDWORD pdwGrantedAccess
);
typedef DWORD (WINAPI *WLANDISCONNECT)(
         HANDLE hClientHandle,
          const GUID *pInterfaceGuid,
    PVOID pReserved
);

typedef DWORD (WINAPI *WLANREGISTERNOTIFICATION)(
          HANDLE hClientHandle,
        DWORD dwNotifSource,
          BOOL bIgnoreDuplicate,
      WLAN_NOTIFICATION_CALLBACK  funcCallback,
      PVOID pCallbackContext,
	PVOID pReserved,
     PDWORD pdwPrevNotifSource
);
typedef DWORD (WINAPI *WLANSETPROFILE)(
          HANDLE hClientHandle,
        const GUID *pInterfaceGuid,
          DWORD dwFlags,
         LPCWSTR strProfileXml,
      LPCWSTR strAllUserProfileSecurity,
         BOOL bOverwrite,
    PVOID pReserved,
        DWORD *pdwReasonCode
);
typedef DWORD (*WLANREASONCODETOSTRING)(
        DWORD dwReasonCode,
          DWORD dwBufferSize,
          PWCHAR pStringBuffer,
    PVOID pReserved
);
typedef DWORD (*WLANREASONCODETOSTRING)(
         DWORD dwReasonCode,
          DWORD dwBufferSize,
          PWCHAR pStringBuffer,
    PVOID pReserved
);
typedef DWORD (WINAPI *WLANDELETEPROFILE)(
          HANDLE hClientHandle,
         const GUID *pInterfaceGuid,
         LPCWSTR strProfileName,
    PVOID pReserved
);

private:
	HANDLE iWifiHandle;
	HMODULE iLib;
	WLANCLOSEHANDLE WlanCloseHandle;
	WLANENUMINTERFACES WlanEnumInterfaces;
	WLANSCAN WlanScan;
	WLANGETNETWORKBSSLIST WlanGetNetworkBssList;
	WLANGETAVAILABLENETWORKLIST WlanGetAvailableNetworkList;
	WLANCONNECT WlanConnect;
	WLANGETPROFILE WlanGetProfile;
	WLANDISCONNECT WlanDisconnect;
	WLANSETPROFILE WlanSetProfile;
	WLANREASONCODETOSTRING WlanReasonCodeToString;
	WLANREGISTERNOTIFICATION WlanRegisterNotification;
	WLANDELETEPROFILE WlanDeleteProfile;
	GUID iInterfaceGuid;
	PWLAN_INTERFACE_INFO_LIST iAvailableInterfaces;
	WLAN_INTERFACE_STATE iInterfaceState;
	
public:
	BOOL InitLib();
	static CWiFiEnginner *GetInstance();
	static void Destroy();
	PWLAN_AVAILABLE_NETWORK_LIST ScanWifi();
	BOOL WiFiConnection(PWLAN_AVAILABLE_NETWORK netInfo,char *shareKey);
private:
	BOOL WifiSetProfile(PWLAN_AVAILABLE_NETWORK netInfo,char *shareKey);
};

#endif