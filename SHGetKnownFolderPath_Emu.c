// 
// SHGetKnownFolderPath begin
//#include <windows.h>
//#include <shellapi.h>
#include <shlobj.h>
//#include "llvm/Support/Windows/WindowsSupport.h"


//#include "llvm/ADT/STLExtras.h"
//#include "llvm/Support/ConvertUTF.h"
//#include "llvm/Support/WindowsError.h"
//#include <fcntl.h>
//#include <sys/stat.h>
//#include <sys/types.h>
//#include <guiddef.h>
//#include <userenv.h>
// compiler include	Userenv.lib
//#include <intrin.h>
// assets
//#include <assert.h>


//#ifndef STATUS_RESOURCE_NOT_OWNED    
//#define STATUS_RESOURCE_NOT_OWNED               ((NTSTATUS)0xC0000264)
//#endif
//// init
//#ifndef NT_SUCCESS
//#define NT_SUCCESS(Status) (((NTSTATUS)(Status)) >= 0)
//#include <ntstatus.h>
//#endif
// fileinfo class and types
//#include <winternl.h>
//#include <winnt.h>
//#include <tchar.h>
//#include <stdio.h>
//#include <malloc.h>


DECLSPEC_IMPORT
BOOL __stdcall GetProfilesDirectoryW(
                                     LPWSTR lpProfileDir,
                                     LPDWORD lpcchSize);

DECLSPEC_IMPORT
BOOL __stdcall GetAllUsersProfileDirectoryW(LPWSTR lpProfileDir,
                                         LPDWORD lpcchSize);


WCHAR* FOLDERID_Desktop_Path_Pointer = 0;
WCHAR* FOLDERID_InternetFolder_Path_Pointer = 0; // 0x0001 "InternetFolder"
WCHAR* FOLDERID_Programs_Path_Pointer = 0;
WCHAR* FOLDERID_ControlPanelFolder_Path_Pointer = 0;
WCHAR* FOLDERID_PrintersFolder_Path_Pointer = 0;
WCHAR* FOLDERID_LocalDocuments_Path_Pointer = 0;
WCHAR* FOLDERID_Favorites_Path_Pointer = 0;
WCHAR* FOLDERID_Startup_Path_Pointer = 0; // 0x0007 // "Startup"
WCHAR* FOLDERID_Recent_Path_Pointer = 0;
WCHAR* FOLDERID_SendTo_Path_Pointer = 0;
WCHAR* FOLDERID_RecycleBinFolder_Path_Pointer = 0;
WCHAR* FOLDERID_StartMenu_Path_Pointer = 0;
WCHAR* FOLDERID_Documents_Path_Pointer = 0;
WCHAR* FOLDERID_Music_Path_Pointer = 0;
WCHAR* FOLDERID_Videos_Path_Pointer = 0;
WCHAR* FOLDERID_PublicDesktop_Path_Pointer = 0; // 0x0010 // // <user name>\Desktop
WCHAR* FOLDERID_ComputerFolder_Path_Pointer = 0; // 0x0011 // "DriveFolder"
WCHAR* FOLDERID_NetworkFolder_Path_Pointer = 0; 
WCHAR* FOLDERID_NetHood_Path_Pointer = 0;
WCHAR* FOLDERID_Fonts_Path_Pointer = 0; // 0x0014 // "Fonts"
WCHAR* FOLDERID_Templates_Path_Pointer = 0;
WCHAR* FOLDERID_CommonStartMenu_Path_Pointer = 0;
WCHAR* FOLDERID_CommonPrograms_Path_Pointer = 0;
WCHAR* FOLDERID_CommonStartup_Path_Pointer = 0;
WCHAR* FOLDERID_AppDataDesktop_Path_Pointer = 0; // 0x0019 // "Common Desktop"
WCHAR* FOLDERID_RoamingAppData_Path_Pointer = 0;
WCHAR* FOLDERID_PrintHood_Path_Pointer = 0;
WCHAR* FOLDERID_LocalAppData_Path_Pointer = 0; // 0x001c // "Local AppData"
WCHAR* FOLDERID_StartMenuAllPrograms_Path_Pointer = 0;
WCHAR* FOLDERID_CommonStartMenuPlaces_Pointer = 0;
WCHAR* FOLDERID_AppDataFavorites_Path_Pointer = 0;
WCHAR* FOLDERID_InternetCache_Path_Pointer = 0; // 0x0020 // "Cache"
WCHAR* FOLDERID_Cookies_Path_Pointer = 0;
WCHAR* FOLDERID_History_Path_Pointer = 0;
WCHAR* FOLDERID_LocalAppDataLow_Path_Pointer = 0;
WCHAR* FOLDERID_Windows_Path_Pointer = 0; // 0x0024 // "Windows"
WCHAR* FOLDERID_System_Path_Pointer = 0;
WCHAR* FOLDERID_ProgramFiles_Path_Pointer = 0;
WCHAR* FOLDERID_Pictures_Path_Pointer = 0;
WCHAR* FOLDERID_Profile_Path_Pointer = 0;
WCHAR* FOLDERID_SystemX86_Path_Pointer = 0;
WCHAR* FOLDERID_ProgramFilesX86_Path_Pointer = 0;
WCHAR* FOLDERID_ProgramFilesCommon_Path_Pointer = 0;
WCHAR* FOLDERID_ProgramFilesCommonX86_Path_Pointer = 0;
WCHAR* FOLDERID_CommonTemplates_Path_Pointer = 0;
WCHAR* FOLDERID_PublicDocuments_Path_Pointer = 0;
WCHAR* FOLDERID_CommonAdminTools_Path_Pointer = 0;
WCHAR* FOLDERID_AdminTools_Path_Pointer = 0; // 0x0030 // "Administrative Tools"
WCHAR* FOLDERID_ConnectionsFolder_Path_Pointer = 0;
WCHAR* FOLDERID_PublicMusic_Path_Pointer = 0;
WCHAR* FOLDERID_PublicPictures_Path_Pointer = 0;
WCHAR* FOLDERID_PublicVideos_Path_Pointer = 0;
WCHAR* FOLDERID_ResourceDir_Path_Pointer = 0;
WCHAR* FOLDERID_LocalizedResourcesDir_Path_Pointer = 0;
WCHAR* FOLDERID_CommonOEMLinks_Path_Pointer = 0;
WCHAR* FOLDERID_CDBurning_Path_Pointer = 0;
WCHAR* FFOLDERID_NetworkFolder_Path_Pointer = 0; // 0x003b // "ComputersNearMe"
// extra misc
WCHAR* FOLDERID_Public_Path_Pointer = 0;
WCHAR* FOLDERID_QuickLaunch_Path_Pointer = 0;
WCHAR* FOLDERID_UserProfiles_Path_Pointer = 0;
WCHAR* FOLDERID_Downloads_Path_Pointer = 0;
// csidl 
int csidl = 0;

void convert_CSIDL_FLAGS(DWORD convert_dwflags)
{
	if (convert_dwflags & KF_FLAG_CREATE)
		csidl |= CSIDL_FLAG_CREATE;

	if (convert_dwflags & KF_FLAG_CREATE)
		csidl |= CSIDL_FLAG_CREATE;

	if (convert_dwflags & KF_FLAG_DONT_VERIFY)
		csidl |= CSIDL_FLAG_DONT_VERIFY;

	if (convert_dwflags & KF_FLAG_NO_ALIAS)
		csidl |= CSIDL_FLAG_NO_ALIAS;

	if (convert_dwflags & KF_FLAG_INIT)
		csidl |= CSIDL_FLAG_PER_USER_INIT;
}

__declspec(noinline)
HRESULT
WINAPI
SHGetKnownFolderPath(
	REFKNOWNFOLDERID rfid,
	DWORD dwflags,
	HANDLE token,
	PWSTR* path
)
{
	wchar_t folder[512 + 1] = { 0 };
	DWORD flags = SHGFP_TYPE_CURRENT;
	DWORD Size = 0;

	csidl = 0; // init always with 0

	if (dwflags & KF_FLAG_DEFAULT_PATH)
		flags = SHGFP_TYPE_DEFAULT;

	if (dwflags & ~(KF_FLAG_CREATE | KF_FLAG_DONT_VERIFY | KF_FLAG_NO_ALIAS | KF_FLAG_INIT))
	{
		return E_INVALIDARG;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Desktop)) // All Users\My Music
	{
		if (FOLDERID_Desktop_Path_Pointer)
		{
            free(FOLDERID_Desktop_Path_Pointer);
		}

		csidl = CSIDL_DESKTOP;  // 0x0000 // <desktop>

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);
		
		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Desktop_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Desktop_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR) FOLDERID_Desktop_Path_Pointer;
		return return_SHGetFolderPathW;
			
	}

	if (IsEqualGUID(rfid, &FOLDERID_InternetFolder)) // All Users\My Music
	{
		if (FOLDERID_InternetFolder_Path_Pointer)
		{
            free(FOLDERID_InternetFolder_Path_Pointer);
		}

		csidl = CSIDL_INTERNET;// 0x0001 "InternetFolder"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_InternetFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_InternetFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_InternetFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Programs)) 
	{
		if (FOLDERID_Programs_Path_Pointer)
		{
			free (FOLDERID_Programs_Path_Pointer);
		}

		csidl = CSIDL_PROGRAMS;// 0x0002 // "Programs"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Programs_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Programs_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Programs_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ControlPanelFolder))
	{
		if (FOLDERID_ControlPanelFolder_Path_Pointer)
		{
			free (FOLDERID_ControlPanelFolder_Path_Pointer);
 		}

		csidl = CSIDL_CONTROLS; // 0x0003 // "ControlPanelFolder"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ControlPanelFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ControlPanelFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ControlPanelFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_PrintersFolder)) 
	{
		if (FOLDERID_PrintersFolder_Path_Pointer)
		{
			free (FOLDERID_PrintersFolder_Path_Pointer);
		}

		csidl = CSIDL_PRINTERS;// 0x0004  // "PrintersFolder"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_PrintersFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_PrintersFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_PrintersFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}
	// LLVM 1 times
	if (IsEqualGUID(rfid, &FOLDERID_LocalDocuments))
	{
		if (FOLDERID_LocalDocuments_Path_Pointer)
		{
			free (FOLDERID_LocalDocuments_Path_Pointer);
		}

		csidl = CSIDL_PERSONAL; // 0x0005 // "Personal"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_LocalDocuments_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_LocalDocuments_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_LocalDocuments_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Favorites))
	{
		if (FOLDERID_Favorites_Path_Pointer)
		{
			free (FOLDERID_Favorites_Path_Pointer);
		}

		csidl = CSIDL_FAVORITES; // 0x0006 // "Favorites"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Favorites_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Favorites_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Favorites_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Startup))
	{
		if (FOLDERID_Startup_Path_Pointer)
		{
			free (FOLDERID_Startup_Path_Pointer);
		}

		csidl = CSIDL_STARTUP; // 0x0007 // "Startup"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Startup_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Startup_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Startup_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Recent)) 
	{
		if (FOLDERID_Recent_Path_Pointer)
		{
			free (FOLDERID_Recent_Path_Pointer);
		}

		csidl = CSIDL_RECENT; // 0x0008 // "Recent"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Recent_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Recent_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Recent_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_SendTo))
	{
		if (FOLDERID_SendTo_Path_Pointer)
		{
			free (FOLDERID_SendTo_Path_Pointer);
		}

		csidl = CSIDL_SENDTO; // 0x0009 // "SendTo

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_SendTo_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_SendTo_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_SendTo_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_RecycleBinFolder)) 
	{
		if (FOLDERID_RecycleBinFolder_Path_Pointer)
		{
			free (FOLDERID_RecycleBinFolder_Path_Pointer);
		}

		csidl = CSIDL_BITBUCKET; // 0x000a  // "RecycleBinFolder"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_RecycleBinFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_RecycleBinFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_RecycleBinFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_StartMenu))
	{
		if (FOLDERID_StartMenu_Path_Pointer)
		{
			free (FOLDERID_StartMenu_Path_Pointer);
		}

		csidl = CSIDL_STARTMENU; // 0x000a  // "Start Menu"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_StartMenu_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_StartMenu_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_StartMenu_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Documents))
	{
		if (FOLDERID_Documents_Path_Pointer)
		{
			free (FOLDERID_Documents_Path_Pointer);
		}

		csidl = CSIDL_MYDOCUMENTS; // 0x0005 same as "Personal"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Documents_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Documents_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Documents_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Music))
	{
		if (FOLDERID_Music_Path_Pointer)
		{
			free (FOLDERID_Music_Path_Pointer);
		}

		csidl = CSIDL_MYMUSIC; // 0x000d // "My Music" 

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Music_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Music_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Music_Path_Pointer;
		return return_SHGetFolderPathW;
	}
 
	if (IsEqualGUID(rfid, &FOLDERID_Videos))
	{
		if (FOLDERID_Videos_Path_Pointer)
		{
			free (FOLDERID_Videos_Path_Pointer);
		}

		csidl = CSIDL_MYVIDEO; // 0x000e // "My Video" 

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Videos_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Videos_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Videos_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_PublicDesktop))
	{
		if (FOLDERID_PublicDesktop_Path_Pointer)
		{
			free (FOLDERID_PublicDesktop_Path_Pointer);
 		}

		csidl = CSIDL_DESKTOPDIRECTORY; // 0x0010 // // <user name>\Desktop

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_PublicDesktop_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_PublicDesktop_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_PublicDesktop_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ComputerFolder))
	{
		if (FOLDERID_ComputerFolder_Path_Pointer)
		{
			free (FOLDERID_ComputerFolder_Path_Pointer);
 		}

		csidl = CSIDL_DRIVES; // 0x0011 // "DriveFolder"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ComputerFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ComputerFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ComputerFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_NetworkFolder))
	{
		if (FOLDERID_NetworkFolder_Path_Pointer)
		{
			free (FOLDERID_NetworkFolder_Path_Pointer);
 		}

		csidl = CSIDL_NETWORK; // 0x0012 // "NetworkFolder"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_NetworkFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_NetworkFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_NetworkFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_NetHood))
	{
		if (FOLDERID_NetHood_Path_Pointer)
		{
			free (FOLDERID_NetHood_Path_Pointer);
 		}

		csidl = CSIDL_NETHOOD; // 0x0013 // "NetHood"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_NetHood_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_NetHood_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_NetHood_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Fonts))
	{
		if (FOLDERID_Fonts_Path_Pointer)
		{
			free (FOLDERID_Fonts_Path_Pointer);
 		}

		csidl = CSIDL_FONTS; // 0x0014 // "Fonts"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Fonts_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Fonts_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Fonts_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Templates))
	{
		if (FOLDERID_Templates_Path_Pointer)
		{
			free (FOLDERID_Templates_Path_Pointer);
 		}

		csidl = CSIDL_TEMPLATES; // 0x0015 // "Templates"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Templates_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Templates_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Templates_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_CommonStartMenu))
	{
		if (FOLDERID_CommonStartMenu_Path_Pointer)
		{
			free (FOLDERID_CommonStartMenu_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_STARTMENU; // 0x0016 // "Common Start Menu"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);
		
		FOLDERID_CommonStartMenu_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CommonStartMenu_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CommonStartMenu_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_CommonPrograms))
	{
		if (FOLDERID_CommonPrograms_Path_Pointer)
		{
			free (FOLDERID_CommonPrograms_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_PROGRAMS; // 0x0017 // "Common Programs"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_CommonPrograms_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CommonPrograms_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CommonPrograms_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_CommonStartup)) 
	{
		if (FOLDERID_CommonStartup_Path_Pointer)
		{
			free (FOLDERID_CommonStartup_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_STARTUP; // 0x0018 // "Common Startup"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_CommonStartup_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CommonStartup_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CommonStartup_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_AppDataDesktop))
	{
		if (FOLDERID_AppDataDesktop_Path_Pointer)
		{
			free (FOLDERID_AppDataDesktop_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_DESKTOPDIRECTORY; // 0x0019 // "Common Desktop"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_AppDataDesktop_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_AppDataDesktop_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_AppDataDesktop_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_RoamingAppData))
	{
		if (FOLDERID_RoamingAppData_Path_Pointer)
		{
			free (FOLDERID_RoamingAppData_Path_Pointer);
 		}

		csidl = CSIDL_APPDATA; // 0x001a // "AppData"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_RoamingAppData_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_RoamingAppData_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_RoamingAppData_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_PrintHood))
	{
		if (FOLDERID_PrintHood_Path_Pointer)
		{
			free (FOLDERID_PrintHood_Path_Pointer);
 		}

		csidl = CSIDL_PRINTHOOD; // 0x001b // "PrintHood"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_PrintHood_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_PrintHood_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_PrintHood_Path_Pointer;
		return return_SHGetFolderPathW;
	}
	// LLVM 2 times
	if (IsEqualGUID(rfid, &FOLDERID_LocalAppData)) 
	{
		if (FOLDERID_LocalAppData_Path_Pointer)
		{
			free (FOLDERID_LocalAppData_Path_Pointer);
 		}

		csidl = CSIDL_LOCAL_APPDATA; // 0x001c // "Local AppData"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_LocalAppData_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_LocalAppData_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_LocalAppData_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_StartMenuAllPrograms))
	{
		if (FOLDERID_StartMenuAllPrograms_Path_Pointer)
		{
			free (FOLDERID_StartMenuAllPrograms_Path_Pointer);
 		}

		csidl = CSIDL_ALTSTARTUP; // 0x001d // "AltStartup" // unknown

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_StartMenuAllPrograms_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_StartMenuAllPrograms_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_StartMenuAllPrograms_Path_Pointer;
		return return_SHGetFolderPathW;
	}


	if (IsEqualGUID(rfid, &FOLDERID_CommonStartMenuPlaces))
	{
		if (FOLDERID_CommonStartMenuPlaces_Pointer)
		{
			free (FOLDERID_CommonStartMenuPlaces_Pointer);
 		}

		csidl = CSIDL_COMMON_ALTSTARTUP; // 0x001e // "Common AltStartup" // unknown // comman ) all users
	    //The file system directory that corresponds to the nonlocalized Startup program group for all users.

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_CommonStartMenuPlaces_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CommonStartMenuPlaces_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CommonStartMenuPlaces_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_AppDataFavorites))
	{
		if (FOLDERID_AppDataFavorites_Path_Pointer)
		{
			free (FOLDERID_AppDataFavorites_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_FAVORITES; // 0x001f // "Common Favorites"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_AppDataFavorites_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_AppDataFavorites_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_AppDataFavorites_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_InternetCache))
	{
		if (FOLDERID_InternetCache_Path_Pointer)
		{
			free (FOLDERID_InternetCache_Path_Pointer);
 		}

		csidl = CSIDL_INTERNET_CACHE; // 0x0020 // "Cache"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_InternetCache_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_InternetCache_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_InternetCache_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Cookies))
	{
		if (FOLDERID_Cookies_Path_Pointer)
		{
			free (FOLDERID_Cookies_Path_Pointer);
 		}

		csidl = CSIDL_COOKIES; // 0x0021 // "Cookies"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Cookies_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Cookies_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Cookies_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_History))
	{
		if (FOLDERID_History_Path_Pointer)
		{
			free (FOLDERID_History_Path_Pointer);
 		}

		csidl = CSIDL_COOKIES; // 0x0022 // "History"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_History_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_History_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_History_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_LocalAppDataLow))
	{
		if (FOLDERID_LocalAppDataLow_Path_Pointer)
		{
			free (FOLDERID_LocalAppDataLow_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_APPDATA; // 0x0023 // "Common AppData"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_LocalAppDataLow_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_LocalAppDataLow_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_LocalAppDataLow_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Windows))
	{
		if (FOLDERID_Windows_Path_Pointer)
		{
			free (FOLDERID_Windows_Path_Pointer);
 		}

		csidl = CSIDL_WINDOWS; // 0x0024 // "Windows"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Windows_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Windows_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Windows_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_System))
	{
		if (FOLDERID_System_Path_Pointer)
		{
			free (FOLDERID_System_Path_Pointer);
 		}

		csidl = CSIDL_SYSTEM; // 0x0025 // "System"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_System_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_System_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_System_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ProgramFiles))
	{
		if (FOLDERID_ProgramFiles_Path_Pointer)
		{
			free (FOLDERID_ProgramFiles_Path_Pointer);
 		}

		csidl = CSIDL_PROGRAM_FILES; // 0x0026 // "ProgramFiles"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ProgramFiles_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ProgramFiles_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ProgramFiles_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Pictures))
	{
		if (FOLDERID_Pictures_Path_Pointer)
		{
			free (FOLDERID_Pictures_Path_Pointer);
 		}

		csidl = CSIDL_MYPICTURES; // 0x0027 // "My Pictures"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Pictures_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Pictures_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Pictures_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Profile))
	{
		if (FOLDERID_Profile_Path_Pointer)
		{
			free (FOLDERID_Profile_Path_Pointer);
 		}

		csidl = CSIDL_PROFILE; // 0x0028 // "Profile"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Profile_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Profile_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_Profile_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_SystemX86))
	{
		if (FOLDERID_SystemX86_Path_Pointer)
		{
			free (FOLDERID_SystemX86_Path_Pointer);
 		}

		csidl = CSIDL_SYSTEMX86; // 0x0029 // "SystemX86"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_SystemX86_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_SystemX86_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_SystemX86_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ProgramFilesX86))
	{
		if (FOLDERID_ProgramFilesX86_Path_Pointer)
		{
			free (FOLDERID_ProgramFilesX86_Path_Pointer);
 		}

		csidl = CSIDL_PROGRAM_FILESX86; // 0x002a // "ProgramFilesX86"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ProgramFilesX86_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ProgramFilesX86_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ProgramFilesX86_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ProgramFilesCommon))
	{
		if (FOLDERID_ProgramFilesCommon_Path_Pointer)
		{
			free (FOLDERID_ProgramFilesCommon_Path_Pointer);
 		}

		csidl = CSIDL_PROGRAM_FILES_COMMON; // 0x002b // "CommonProgramFiles"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ProgramFilesCommon_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ProgramFilesCommon_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ProgramFilesCommon_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ProgramFilesCommonX86))
	{
		if (FOLDERID_ProgramFilesCommonX86_Path_Pointer)
		{
			free (FOLDERID_ProgramFilesCommonX86_Path_Pointer);
 		}

		csidl = CSIDL_PROGRAM_FILES_COMMONX86; // 0x002c // "CommonProgramFilesX86"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ProgramFilesCommonX86_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ProgramFilesCommonX86_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ProgramFilesCommonX86_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_CommonTemplates))
	{
		if (FOLDERID_CommonTemplates_Path_Pointer)
		{
			free (FOLDERID_CommonTemplates_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_TEMPLATES; // 0x002d // "Common Templates"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_CommonTemplates_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CommonTemplates_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CommonTemplates_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_PublicDocuments))
	{
		if (FOLDERID_PublicDocuments_Path_Pointer)
		{
			free (FOLDERID_PublicDocuments_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_DOCUMENTS; // 0x002e // "Common Documents"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_PublicDocuments_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_PublicDocuments_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_PublicDocuments_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_CommonAdminTools))
	{
		if (FOLDERID_CommonAdminTools_Path_Pointer)
		{
			free (FOLDERID_CommonAdminTools_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_ADMINTOOLS; // 0x002f // "Common Administrative Tools"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_CommonAdminTools_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CommonAdminTools_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CommonAdminTools_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_AdminTools))
	{
		if (FOLDERID_AdminTools_Path_Pointer)
		{
			free (FOLDERID_AdminTools_Path_Pointer);
 		}

		csidl = CSIDL_ADMINTOOLS; // 0x0030 // "Administrative Tools"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_AdminTools_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_AdminTools_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_AdminTools_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ConnectionsFolder))
	{
		if (FOLDERID_ConnectionsFolder_Path_Pointer)
		{
			free (FOLDERID_ConnectionsFolder_Path_Pointer);
 		}

		csidl = CSIDL_CONNECTIONS; // 0x0031 // "ConnectionsFolder"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ConnectionsFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ConnectionsFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ConnectionsFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_PublicMusic))
	{
		if (FOLDERID_PublicMusic_Path_Pointer)
		{
			free (FOLDERID_PublicMusic_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_MUSIC; // 0x0035 //  "CommonMusic"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_PublicMusic_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_PublicMusic_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_PublicMusic_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_PublicPictures))
	{
		if (FOLDERID_PublicPictures_Path_Pointer)
		{
			free (FOLDERID_PublicPictures_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_PICTURES; // 0x0036 //  "CommonPictures"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_PublicPictures_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_PublicPictures_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_PublicPictures_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_PublicVideos))
	{
		if (FOLDERID_PublicVideos_Path_Pointer)
		{
			free (FOLDERID_PublicVideos_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_VIDEO; // 0x0037 //  "CommonVideo"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_PublicVideos_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_PublicVideos_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_PublicVideos_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_ResourceDir))
	{
		FOLDERID_ResourceDir_Path_Pointer = 0;
		if (FOLDERID_ResourceDir_Path_Pointer)
		{
			free (FOLDERID_ResourceDir_Path_Pointer);
 		}

		csidl = CSIDL_RESOURCES; // 0x0038 //  "ResourceDir"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_ResourceDir_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_ResourceDir_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_ResourceDir_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_LocalizedResourcesDir))
	{
		if (FOLDERID_LocalizedResourcesDir_Path_Pointer)
		{
			free (FOLDERID_LocalizedResourcesDir_Path_Pointer);
 		}

		csidl = CSIDL_RESOURCES_LOCALIZED; // 0x0039 // "LocalizedResourcesDir"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_LocalizedResourcesDir_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_LocalizedResourcesDir_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_LocalizedResourcesDir_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_CommonOEMLinks))
	{
		if (FOLDERID_CommonOEMLinks_Path_Pointer)
		{
			free (FOLDERID_CommonOEMLinks_Path_Pointer);
 		}

		csidl = CSIDL_COMMON_OEM_LINKS; // 0x003a // "OEM Links"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_CommonOEMLinks_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CommonOEMLinks_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CommonOEMLinks_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_CDBurning))
	{
		if (FOLDERID_CDBurning_Path_Pointer)
		{
			free (FOLDERID_CDBurning_Path_Pointer);
 		}

		csidl = CSIDL_CDBURN_AREA; // 0x003b // "CD Burning"

		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_CDBurning_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_CDBurning_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_CDBurning_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_NetworkFolder))
	{
		if (FOLDERID_NetworkFolder_Path_Pointer)
		{
			free (FOLDERID_NetworkFolder_Path_Pointer);
 		}
		csidl = CSIDL_COMPUTERSNEARME; // 0x003b // "ComputersNearMe"
		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		// function call with flags
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);
		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_NetworkFolder_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_NetworkFolder_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2)+2));
		*path = (PWSTR)FOLDERID_NetworkFolder_Path_Pointer;
		return return_SHGetFolderPathW;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Public))
	{
		if (FOLDERID_Public_Path_Pointer)
		{
			free (FOLDERID_Public_Path_Pointer);
 		}
		Size = sizeof(folder);
		GetAllUsersProfileDirectoryW(folder, &Size);
		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Public_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Public_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2) + 2));
		*path = (PWSTR)FOLDERID_Public_Path_Pointer;
		return S_OK;
	}

	if (IsEqualGUID(rfid, &FOLDERID_QuickLaunch))
	{
		if (FOLDERID_QuickLaunch_Path_Pointer)
		{
			free (FOLDERID_QuickLaunch_Path_Pointer);
 		}
		ExpandEnvironmentStringsW(L"%APPDATA%", folder, MAX_PATH);
		lstrcatW(folder, L"\\Microsoft\\Internet Explorer\\Quick");
		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_QuickLaunch_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_QuickLaunch_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2) + 2));
		*path = (PWSTR)FOLDERID_QuickLaunch_Path_Pointer;
		return S_OK;
	}

	if (IsEqualGUID(rfid, &FOLDERID_UserProfiles))
	{
		if (FOLDERID_UserProfiles_Path_Pointer)
		{
			free (FOLDERID_UserProfiles_Path_Pointer);
 		}
		Size = sizeof(folder);
		GetProfilesDirectoryW(folder, (LPDWORD) &Size);
		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);
		
		FOLDERID_UserProfiles_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_UserProfiles_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2) + 2));
		*path = (PWSTR)FOLDERID_UserProfiles_Path_Pointer;
		return S_OK;
	}

	if (IsEqualGUID(rfid, &FOLDERID_Downloads))
	{
		if (FOLDERID_Downloads_Path_Pointer)
		{
			free (FOLDERID_Downloads_Path_Pointer);
 		}
		csidl = CSIDL_PROFILE;
		// change global csidl with flags
		convert_CSIDL_FLAGS(dwflags);
		int return_SHGetFolderPathW = SHGetFolderPathW(NULL, csidl, token, flags, folder);
		lstrcatW(folder, L"\\Downloads");

		unsigned int SHGetKnownFolderPath_Len = lstrlenW(folder);

		FOLDERID_Downloads_Path_Pointer = malloc (SHGetKnownFolderPath_Len);
		memcpy(FOLDERID_Downloads_Path_Pointer, (void*)folder, ((SHGetKnownFolderPath_Len * 2) + 2));
		*path = (PWSTR)FOLDERID_Downloads_Path_Pointer;
		return return_SHGetFolderPathW;
	}
	//return S_FALSE;
	return S_OK;
}
// SHGetKnownFolderPath end
//
