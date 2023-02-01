//
// RegGetValueW Begin
#include <windows.h>

static VOID RegpApplyRestrictions(DWORD dwFlags,
DWORD 	dwType,
DWORD 	cbData,
PLONG 	ret
)
{
 // Check if the type is restricted by the passed flags 
 if (*ret == ERROR_SUCCESS || *ret == ERROR_MORE_DATA)
 {
	 DWORD dwMask = 0;

	 switch (dwType)
	 {
	 case REG_NONE: dwMask = RRF_RT_REG_NONE; break;
	 case REG_SZ: dwMask = RRF_RT_REG_SZ; break;
	 case REG_EXPAND_SZ: dwMask = RRF_RT_REG_EXPAND_SZ; break;
	 case REG_MULTI_SZ: dwMask = RRF_RT_REG_MULTI_SZ; break;
	 case REG_BINARY: dwMask = RRF_RT_REG_BINARY; break;
	 case REG_DWORD: dwMask = RRF_RT_REG_DWORD; break;
	 case REG_QWORD: dwMask = RRF_RT_REG_QWORD; break;
	 }

	 if (dwFlags & dwMask)
	 {
		 // Type is not restricted, check for size mismatch 
		 if (dwType == REG_BINARY)
		 {
			 DWORD cbExpect = 0;

			 if ((dwFlags & RRF_RT_ANY) == RRF_RT_DWORD)
				 cbExpect = 4;
			 else if ((dwFlags & RRF_RT_ANY) == RRF_RT_QWORD)
				 cbExpect = 8;

			 if (cbExpect && cbData != cbExpect)
				 *ret = ERROR_DATATYPE_MISMATCH;
		 }
	 }
	 else *ret = ERROR_UNSUPPORTED_TYPE;
 }
}

LSTATUS WINAPI
RegGetValueW(HKEY hKey,
LPCWSTR pszSubKey,
LPCWSTR pszValue,
DWORD dwFlags,
LPDWORD pdwType,
PVOID pvData,
LPDWORD pcbData)
{
	DWORD dwType, cbData = pcbData ? *pcbData : 0;
	PVOID pvBuf = NULL;
	LONG ret;

	if (pvData && !pcbData)
		return ERROR_INVALID_PARAMETER;
	if ((dwFlags & RRF_RT_REG_EXPAND_SZ) && !(dwFlags & RRF_NOEXPAND) &&
		((dwFlags & RRF_RT_ANY) != RRF_RT_ANY))
		return ERROR_INVALID_PARAMETER;

	if (pszSubKey && pszSubKey[0])
	{
		ret = RegOpenKeyExW(hKey, pszSubKey, 0, KEY_QUERY_VALUE, &hKey);
		if (ret != ERROR_SUCCESS) return ret;
	}

	ret = RegQueryValueExW(hKey, pszValue, NULL, &dwType, (LPBYTE) pvData, &cbData);

	// If we are going to expand we need to read in the whole the value even
	// if the passed buffer was too small as the expanded string might be
	// smaller than the unexpanded one and could fit into cbData bytes.
	if ((ret == ERROR_SUCCESS || ret == ERROR_MORE_DATA) &&
		dwType == REG_EXPAND_SZ && !(dwFlags & RRF_NOEXPAND))
	{
		do
		{
			HeapFree(GetProcessHeap(), 0, pvBuf);

			pvBuf = HeapAlloc(GetProcessHeap(), 0, cbData);
			if (!pvBuf)
			{
				ret = ERROR_NOT_ENOUGH_MEMORY;
				break;
			}

			if (ret == ERROR_MORE_DATA || !pvData)
				ret = RegQueryValueExW(hKey, pszValue, NULL,
					&dwType, (LPBYTE) pvBuf, &cbData);
			else
			{
				// Even if cbData was large enough we have to copy the
				// string since ExpandEnvironmentStrings can't handle
				// overlapping buffers. 
				CopyMemory(pvBuf, pvData, cbData);
			}

			// Both the type or the value itself could have been modified in
			// between so we have to keep retrying until the buffer is large
			// enough or we no longer have to expand the value. 
		} while (dwType == REG_EXPAND_SZ && ret == ERROR_MORE_DATA);

		if (ret == ERROR_SUCCESS)
		{
			// Recheck dwType in case it changed since the first call 
			if (dwType == REG_EXPAND_SZ)
			{
				cbData = ExpandEnvironmentStringsW((LPWSTR) pvBuf, (LPWSTR) pvData,
					pcbData ? *pcbData : 0) * sizeof(WCHAR);
				dwType = REG_SZ;
				if (pvData && pcbData && cbData > * pcbData)
					ret = ERROR_MORE_DATA;
			}
			else if (pvData)
				CopyMemory(pvData, pvBuf, *pcbData);
		}

		HeapFree(GetProcessHeap(), 0, pvBuf);
	}

	if (pszSubKey && pszSubKey[0])
		RegCloseKey(hKey);

	RegpApplyRestrictions(dwFlags, dwType, cbData, &ret);

	if (pvData && ret != ERROR_SUCCESS && (dwFlags & RRF_ZEROONFAILURE))
		ZeroMemory(pvData, *pcbData);

	if (pdwType)
		*pdwType = dwType;

	if (pcbData)
		*pcbData = cbData;

	return ret;
}
// RegGetValueW end
//