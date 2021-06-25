#include <windows.h>
#include <iostream>
using namespace std;

HKEY OpenRegistryKey(HKEY hRootKey, wchar_t* strSubKey)
{
	HKEY hKey;
	LONG lError = RegOpenKeyEx(hRootKey, strSubKey, NULL, KEY_ALL_ACCESS, &hKey);

	if (ERROR_FILE_NOT_FOUND == lError)
	{
		//Create a key
		lError = RegCreateKeyEx(hRootKey, strSubKey, NULL, NULL, REG_OPTION_NON_VOLATILE, KEY_ALL_ACCESS, NULL, &hKey, NULL);
	}

	if (lError != ERROR_SUCCESS)
	{
		cout << "\nSomething is wrong. Could not Open or Create the Key";
	}

	return hKey;
}

void DeleteRegistryKeyAndConfirm(HKEY hRootKey, wchar_t* strSubKey)
{
	LONG lRes = RegDeleteKey(hRootKey, strSubKey);
	if (ERROR_SUCCESS == lRes)
	{
		MessageBox(NULL, L"Key Successfully Deleted", L"Delete Key", MB_ICONINFORMATION);
	}
	else
	{
		MessageBox(NULL, L"Could Not Delete the Key", L"Deletion Failed", MB_ICONINFORMATION);
	}
}

int main()
{
	DWORD dMyValue1, dMyValue2;
	HKEY hkey = OpenRegistryKey(HKEY_LOCAL_MACHINE, (wchar_t*)L"SOFTWARE\\Test");

	//Get the Values
	DeleteRegistryKeyAndConfirm(HKEY_LOCAL_MACHINE, (wchar_t*)L"SOFTWARE\\Test");

	RegCloseKey(hkey);
	return 0;
}