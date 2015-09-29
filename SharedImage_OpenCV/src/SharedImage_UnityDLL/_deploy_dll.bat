if exist ..\..\bin\unity_dll\x86 (
	copy ..\..\bin\unity_dll\x86\SharedImage_UnityDLL.dll ..\..\..\SharedImage_Unity\Assets\SharedImage\Plugins\x86
)
if exist ..\..\bin\unity_dll\x64 (
	copy ..\..\bin\unity_dll\x64\SharedImage_UnityDLL.dll ..\..\..\SharedImage_Unity\Assets\SharedImage\Plugins\x64
)
