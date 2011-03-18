#include "stdafx.h"
#include "WiFiEnginner.h"
#include "StringUtil.h"

CWiFiEnginner *CWiFiEnginner::iInstance=NULL;

static char g_profileTemplate[]="<?xml version=\"1.0\"?>" \
"<WLANProfile xmlns=\"http://www.microsoft.com/networking/WLAN/profile/v1\">" \
"	<name>%s</name>" \
"	<SSIDConfig> " \
"		<SSID> " \
"			<name>%s</name>" \
"		</SSID>" \
"	</SSIDConfig>" \
"	<connectionType>ESS</connectionType>" \
"	<MSM>" \
"		<security>" \
"			<authEncryption>" \
"				<authentication>WPA2PSK</authentication>" \
"				<encryption>AES</encryption>" \
"				<useOneX>false</useOneX>" \
"			</authEncryption>" \
"			<sharedKey>" \
"				<keyType>passPhrase</keyType>" \
"				<protected>false</protected>" \
"				<keyMaterial>%s</keyMaterial>" \
"			</sharedKey>" \
"		</security>" \
"	</MSM>" \
" </WLANProfile>";


CWiFiEnginner::CWiFiEnginner()
{
	iAvailableInterfaces=NULL;
	
}
VOID WINAPI WlanNotificationCallback(PWLAN_NOTIFICATION_DATA data,PVOID context)
{
	int reulst;
	if(data->NotificationCode==wlan_notification_acm_disconnected)
	{
		reulst=-1;
	}else if(data->NotificationCode==wlan_notification_acm_scan_complete)
	{
		reulst=-2;

	}
}
BOOL CWiFiEnginner::InitLib()
{
	DWORD dwVersion = 0;
	DWORD result;
	DWORD source;
//	 PWLAN_AVAILABLE_NETWORK_LIST bssList;
	iLib = ::LoadLibrary("wlanapi.dll");
	 if(iLib)
	 {
		 WLANOPENHANDLE WlanOpenHandle= (WLANOPENHANDLE)::GetProcAddress(iLib, "WlanOpenHandle");
		 WlanCloseHandle= (WLANCLOSEHANDLE)::GetProcAddress(iLib, "WlanCloseHandle");
		 WlanEnumInterfaces=(WLANENUMINTERFACES)::GetProcAddress(iLib, "WlanEnumInterfaces");
		 WlanScan=(WLANSCAN)::GetProcAddress(iLib, "WlanScan");
		WlanGetNetworkBssList= (WLANGETNETWORKBSSLIST)::GetProcAddress(iLib, "WlanGetNetworkBssList");
		WlanGetAvailableNetworkList=(WLANGETAVAILABLENETWORKLIST)::GetProcAddress(iLib, "WlanGetAvailableNetworkList");
		WlanConnect=(WLANCONNECT)::GetProcAddress(iLib, "WlanConnect");
		WlanGetProfile=(WLANGETPROFILE)::GetProcAddress(iLib, "WlanGetProfile");
		WlanDisconnect=(WLANDISCONNECT)::GetProcAddress(iLib, "WlanDisconnect");
		WlanRegisterNotification=(WLANREGISTERNOTIFICATION)::GetProcAddress(iLib, "WlanRegisterNotification");
		WlanSetProfile=(WLANSETPROFILE)::GetProcAddress(iLib, "WlanSetProfile");
		WlanReasonCodeToString=(WLANREASONCODETOSTRING)::GetProcAddress(iLib, "WlanReasonCodeToString");
		WlanDeleteProfile=(WLANDELETEPROFILE)::GetProcAddress(iLib, "WlanDeleteProfile");
		 result=WlanOpenHandle(WLAN_API_VERSION_1_0,NULL,&dwVersion,&iWifiHandle);
		 if(iWifiHandle)
		 {
			 result=WlanRegisterNotification(iWifiHandle,WLAN_NOTIFICATION_SOURCE_ACM,TRUE,WlanNotificationCallback,NULL,NULL,&source);
			result=WlanEnumInterfaces(iWifiHandle, NULL, &iAvailableInterfaces);
			if(iAvailableInterfaces->dwNumberOfItems>0)
			{
				iInterfaceGuid=iAvailableInterfaces->InterfaceInfo[0].InterfaceGuid;
			}else
			{
				return FALSE;
			}
		 }else
		 {
			return FALSE;
		 }
	 }else
	 {
		return FALSE;
	 }
	 return TRUE;
	 
}

PWLAN_AVAILABLE_NETWORK_LIST CWiFiEnginner::ScanWifi()
{
	PWLAN_AVAILABLE_NETWORK_LIST wifiList;
	wifiList=NULL;
	//LPWSTR xml;
	DWORD pdwFlags=0;
	DWORD pdwGrantedAccess=0;
	DWORD result;
	//result=WlanGetProfile(iWifiHandle,&iInterfaceGuid,L"JZX-A11",NULL,&xml,&pdwFlags,&pdwGrantedAccess);
	//wprintf(xml);
	result=WlanScan(iWifiHandle,&iInterfaceGuid,NULL,NULL,NULL);
	result=WlanGetAvailableNetworkList(iWifiHandle,&iInterfaceGuid,3,NULL,&wifiList);


	
	return wifiList;
}
CWiFiEnginner::~CWiFiEnginner()
{
	WlanCloseHandle(iWifiHandle,NULL);
}	

CWiFiEnginner *CWiFiEnginner::GetInstance()
{
	if(!iInstance)
	{
		iInstance=new CWiFiEnginner;
	}	
	return iInstance;
}
void CWiFiEnginner::Destroy()
{
	if(iInstance)
	{
		delete iInstance;
		iInstance=NULL;
	}
}

BOOL CWiFiEnginner::WiFiConnection(PWLAN_AVAILABLE_NETWORK netInfo,char *shareKey)
{
	DWORD result;
	LPWSTR ssid;
	WLAN_CONNECTION_PARAMETERS connParam;
	result=0;
	DWORD reasonCode;
	
	reasonCode=0;
	ssid=NULL;
	//ssid=new WCHAR[1024];
	WifiSetProfile(netInfo,shareKey);
	CStringUtil::MByteToWCharExt((LPCSTR)netInfo->dot11Ssid.ucSSID,ssid);
	connParam.pDot11Ssid=&(netInfo->dot11Ssid);
	connParam.strProfile=ssid;
	connParam.wlanConnectionMode=wlan_connection_mode_profile;
	connParam.pDesiredBssidList=NULL;
	connParam.dot11BssType=netInfo->dot11BssType;
	connParam.dwFlags=0;//WLAN_CONNECTION_HIDDEN_NETWORK|WLAN_CONNECTION_ADHOC_JOIN_ONLY|WLAN_CONNECTION_IGNORE_PRIVACY_BIT|WLAN_CONNECTION_EAPOL_PASSTHROUGH;
	//result=WlanDisconnect(iWifiHandle,&iInterfaceGuid,NULL);
	
	//result=WlanReasonCodeToString(reasonCode,1024,ssid,NULL);
	result=WlanConnect(iWifiHandle,&iInterfaceGuid,&connParam,NULL);
	//result=WlanDeleteProfile(iWifiHandle,&iInterfaceGuid,ssid,NULL);
	return result==0;
}

BOOL CWiFiEnginner::WifiSetProfile(PWLAN_AVAILABLE_NETWORK netInfo,char *shareKey)
{
	DWORD result;
	DWORD reasonCode;
	
	reasonCode=0;
	char buff[1024];
	LPWSTR ssid;
	sprintf(buff,g_profileTemplate,netInfo->dot11Ssid.ucSSID,netInfo->dot11Ssid.ucSSID,shareKey);
	CStringUtil::MByteToWCharExt((LPCSTR)buff,ssid);
	result=WlanSetProfile(iWifiHandle,&iInterfaceGuid,0,ssid,NULL,TRUE,NULL,&reasonCode);
	return result==0;

}