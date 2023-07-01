// dllmain.cpp : Defines the entry point for the DLL application.
#include <shlobj.h>
#include <cstdio>
#include <d3d11.h>
#include <dxgi.h>

#include "Helpers.h"
#pragma comment(lib, "detours.lib")
#pragma region winmm.dll Spoofing
#pragma comment(linker, "/EXPORT:CloseDriver=C:\\Windows\\System32\\winmm.CloseDriver")
#pragma comment(linker, "/EXPORT:DefDriverProc=C:\\Windows\\System32\\winmm.DefDriverProc")
#pragma comment(linker, "/EXPORT:DriverCallback=C:\\Windows\\System32\\winmm.DriverCallback")
#pragma comment(linker, "/EXPORT:DrvGetModuleHandle=C:\\Windows\\System32\\winmm.DrvGetModuleHandle")
#pragma comment(linker, "/EXPORT:GetDriverModuleHandle=C:\\Windows\\System32\\winmm.GetDriverModuleHandle")
#pragma comment(linker, "/EXPORT:NotifyCallbackData=C:\\Windows\\System32\\winmm.NotifyCallbackData")
#pragma comment(linker, "/EXPORT:OpenDriver=C:\\Windows\\System32\\winmm.OpenDriver")
#pragma comment(linker, "/EXPORT:PlaySound=C:\\Windows\\System32\\winmm.PlaySound")
#pragma comment(linker, "/EXPORT:PlaySoundA=C:\\Windows\\System32\\winmm.PlaySoundA")
#pragma comment(linker, "/EXPORT:PlaySoundW=C:\\Windows\\System32\\winmm.PlaySoundW")
#pragma comment(linker, "/EXPORT:SendDriverMessage=C:\\Windows\\System32\\winmm.SendDriverMessage")
#pragma comment(linker, "/EXPORT:WOW32DriverCallback=C:\\Windows\\System32\\winmm.WOW32DriverCallback")
#pragma comment(linker, "/EXPORT:WOW32ResolveMultiMediaHandle=C:\\Windows\\System32\\winmm.WOW32ResolveMultiMediaHandle")
#pragma comment(linker, "/EXPORT:WOWAppExit=C:\\Windows\\System32\\winmm.WOWAppExit")
#pragma comment(linker, "/EXPORT:aux32Message=C:\\Windows\\System32\\winmm.aux32Message")
#pragma comment(linker, "/EXPORT:auxGetDevCapsA=C:\\Windows\\System32\\winmm.auxGetDevCapsA")
#pragma comment(linker, "/EXPORT:auxGetDevCapsW=C:\\Windows\\System32\\winmm.auxGetDevCapsW")
#pragma comment(linker, "/EXPORT:auxGetNumDevs=C:\\Windows\\System32\\winmm.auxGetNumDevs")
#pragma comment(linker, "/EXPORT:auxGetVolume=C:\\Windows\\System32\\winmm.auxGetVolume")
#pragma comment(linker, "/EXPORT:auxOutMessage=C:\\Windows\\System32\\winmm.auxOutMessage")
#pragma comment(linker, "/EXPORT:auxSetVolume=C:\\Windows\\System32\\winmm.auxSetVolume")
#pragma comment(linker, "/EXPORT:joy32Message=C:\\Windows\\System32\\winmm.joy32Message")
#pragma comment(linker, "/EXPORT:joyConfigChanged=C:\\Windows\\System32\\winmm.joyConfigChanged")
#pragma comment(linker, "/EXPORT:joyGetDevCapsA=C:\\Windows\\System32\\winmm.joyGetDevCapsA")
#pragma comment(linker, "/EXPORT:joyGetDevCapsW=C:\\Windows\\System32\\winmm.joyGetDevCapsW")
#pragma comment(linker, "/EXPORT:joyGetNumDevs=C:\\Windows\\System32\\winmm.joyGetNumDevs")
#pragma comment(linker, "/EXPORT:joyGetPos=C:\\Windows\\System32\\winmm.joyGetPos")
#pragma comment(linker, "/EXPORT:joyGetPosEx=C:\\Windows\\System32\\winmm.joyGetPosEx")
#pragma comment(linker, "/EXPORT:joyGetThreshold=C:\\Windows\\System32\\winmm.joyGetThreshold")
#pragma comment(linker, "/EXPORT:joyReleaseCapture=C:\\Windows\\System32\\winmm.joyReleaseCapture")
#pragma comment(linker, "/EXPORT:joySetCapture=C:\\Windows\\System32\\winmm.joySetCapture")
#pragma comment(linker, "/EXPORT:joySetThreshold=C:\\Windows\\System32\\winmm.joySetThreshold")
#pragma comment(linker, "/EXPORT:mci32Message=C:\\Windows\\System32\\winmm.mci32Message")
#pragma comment(linker, "/EXPORT:mciDriverNotify=C:\\Windows\\System32\\winmm.mciDriverNotify")
#pragma comment(linker, "/EXPORT:mciDriverYield=C:\\Windows\\System32\\winmm.mciDriverYield")
#pragma comment(linker, "/EXPORT:mciExecute=C:\\Windows\\System32\\winmm.mciExecute")
#pragma comment(linker, "/EXPORT:mciFreeCommandResource=C:\\Windows\\System32\\winmm.mciFreeCommandResource")
#pragma comment(linker, "/EXPORT:mciGetCreatorTask=C:\\Windows\\System32\\winmm.mciGetCreatorTask")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDA=C:\\Windows\\System32\\winmm.mciGetDeviceIDA")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDA=C:\\Windows\\System32\\winmm.mciGetDeviceIDFromElementIDA")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDFromElementIDW=C:\\Windows\\System32\\winmm.mciGetDeviceIDFromElementIDW")
#pragma comment(linker, "/EXPORT:mciGetDeviceIDW=C:\\Windows\\System32\\winmm.mciGetDeviceIDW")
#pragma comment(linker, "/EXPORT:mciGetDriverData=C:\\Windows\\System32\\winmm.mciGetDriverData")
#pragma comment(linker, "/EXPORT:mciGetErrorStringA=C:\\Windows\\System32\\winmm.mciGetErrorStringA")
#pragma comment(linker, "/EXPORT:mciGetErrorStringW=C:\\Windows\\System32\\winmm.mciGetErrorStringW")
#pragma comment(linker, "/EXPORT:mciGetYieldProc=C:\\Windows\\System32\\winmm.mciGetYieldProc")
#pragma comment(linker, "/EXPORT:mciLoadCommandResource=C:\\Windows\\System32\\winmm.mciLoadCommandResource")
#pragma comment(linker, "/EXPORT:mciSendCommandA=C:\\Windows\\System32\\winmm.mciSendCommandA")
#pragma comment(linker, "/EXPORT:mciSendCommandW=C:\\Windows\\System32\\winmm.mciSendCommandW")
#pragma comment(linker, "/EXPORT:mciSendStringA=C:\\Windows\\System32\\winmm.mciSendStringA")
#pragma comment(linker, "/EXPORT:mciSendStringW=C:\\Windows\\System32\\winmm.mciSendStringW")
#pragma comment(linker, "/EXPORT:mciSetDriverData=C:\\Windows\\System32\\winmm.mciSetDriverData")
#pragma comment(linker, "/EXPORT:mciSetYieldProc=C:\\Windows\\System32\\winmm.mciSetYieldProc")
#pragma comment(linker, "/EXPORT:mid32Message=C:\\Windows\\System32\\winmm.mid32Message")
#pragma comment(linker, "/EXPORT:midiConnect=C:\\Windows\\System32\\winmm.midiConnect")
#pragma comment(linker, "/EXPORT:midiDisconnect=C:\\Windows\\System32\\winmm.midiDisconnect")
#pragma comment(linker, "/EXPORT:midiInAddBuffer=C:\\Windows\\System32\\winmm.midiInAddBuffer")
#pragma comment(linker, "/EXPORT:midiInClose=C:\\Windows\\System32\\winmm.midiInClose")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsA=C:\\Windows\\System32\\winmm.midiInGetDevCapsA")
#pragma comment(linker, "/EXPORT:midiInGetDevCapsW=C:\\Windows\\System32\\winmm.midiInGetDevCapsW")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextA=C:\\Windows\\System32\\winmm.midiInGetErrorTextA")
#pragma comment(linker, "/EXPORT:midiInGetErrorTextW=C:\\Windows\\System32\\winmm.midiInGetErrorTextW")
#pragma comment(linker, "/EXPORT:midiInGetID=C:\\Windows\\System32\\winmm.midiInGetID")
#pragma comment(linker, "/EXPORT:midiInGetNumDevs=C:\\Windows\\System32\\winmm.midiInGetNumDevs")
#pragma comment(linker, "/EXPORT:midiInMessage=C:\\Windows\\System32\\winmm.midiInMessage")
#pragma comment(linker, "/EXPORT:midiInOpen=C:\\Windows\\System32\\winmm.midiInOpen")
#pragma comment(linker, "/EXPORT:midiInPrepareHeader=C:\\Windows\\System32\\winmm.midiInPrepareHeader")
#pragma comment(linker, "/EXPORT:midiInReset=C:\\Windows\\System32\\winmm.midiInReset")
#pragma comment(linker, "/EXPORT:midiInStart=C:\\Windows\\System32\\winmm.midiInStart")
#pragma comment(linker, "/EXPORT:midiInStop=C:\\Windows\\System32\\winmm.midiInStop")
#pragma comment(linker, "/EXPORT:midiInUnprepareHeader=C:\\Windows\\System32\\winmm.midiInUnprepareHeader")
#pragma comment(linker, "/EXPORT:midiOutCacheDrumPatches=C:\\Windows\\System32\\winmm.midiOutCacheDrumPatches")
#pragma comment(linker, "/EXPORT:midiOutCachePatches=C:\\Windows\\System32\\winmm.midiOutCachePatches")
#pragma comment(linker, "/EXPORT:midiOutClose=C:\\Windows\\System32\\winmm.midiOutClose")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsA=C:\\Windows\\System32\\winmm.midiOutGetDevCapsA")
#pragma comment(linker, "/EXPORT:midiOutGetDevCapsW=C:\\Windows\\System32\\winmm.midiOutGetDevCapsW")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextA=C:\\Windows\\System32\\winmm.midiOutGetErrorTextA")
#pragma comment(linker, "/EXPORT:midiOutGetErrorTextW=C:\\Windows\\System32\\winmm.midiOutGetErrorTextW")
#pragma comment(linker, "/EXPORT:midiOutGetID=C:\\Windows\\System32\\winmm.midiOutGetID")
#pragma comment(linker, "/EXPORT:midiOutGetNumDevs=C:\\Windows\\System32\\winmm.midiOutGetNumDevs")
#pragma comment(linker, "/EXPORT:midiOutGetVolume=C:\\Windows\\System32\\winmm.midiOutGetVolume")
#pragma comment(linker, "/EXPORT:midiOutLongMsg=C:\\Windows\\System32\\winmm.midiOutLongMsg")
#pragma comment(linker, "/EXPORT:midiOutMessage=C:\\Windows\\System32\\winmm.midiOutMessage")
#pragma comment(linker, "/EXPORT:midiOutOpen=C:\\Windows\\System32\\winmm.midiOutOpen")
#pragma comment(linker, "/EXPORT:midiOutPrepareHeader=C:\\Windows\\System32\\winmm.midiOutPrepareHeader")
#pragma comment(linker, "/EXPORT:midiOutReset=C:\\Windows\\System32\\winmm.midiOutReset")
#pragma comment(linker, "/EXPORT:midiOutSetVolume=C:\\Windows\\System32\\winmm.midiOutSetVolume")
#pragma comment(linker, "/EXPORT:midiOutShortMsg=C:\\Windows\\System32\\winmm.midiOutShortMsg")
#pragma comment(linker, "/EXPORT:midiOutUnprepareHeader=C:\\Windows\\System32\\winmm.midiOutUnprepareHeader")
#pragma comment(linker, "/EXPORT:midiStreamClose=C:\\Windows\\System32\\winmm.midiStreamClose")
#pragma comment(linker, "/EXPORT:midiStreamOpen=C:\\Windows\\System32\\winmm.midiStreamOpen")
#pragma comment(linker, "/EXPORT:midiStreamOut=C:\\Windows\\System32\\winmm.midiStreamOut")
#pragma comment(linker, "/EXPORT:midiStreamPause=C:\\Windows\\System32\\winmm.midiStreamPause")
#pragma comment(linker, "/EXPORT:midiStreamPosition=C:\\Windows\\System32\\winmm.midiStreamPosition")
#pragma comment(linker, "/EXPORT:midiStreamProperty=C:\\Windows\\System32\\winmm.midiStreamProperty")
#pragma comment(linker, "/EXPORT:midiStreamRestart=C:\\Windows\\System32\\winmm.midiStreamRestart")
#pragma comment(linker, "/EXPORT:midiStreamStop=C:\\Windows\\System32\\winmm.midiStreamStop")
#pragma comment(linker, "/EXPORT:mixerClose=C:\\Windows\\System32\\winmm.mixerClose")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsA=C:\\Windows\\System32\\winmm.mixerGetControlDetailsA")
#pragma comment(linker, "/EXPORT:mixerGetControlDetailsW=C:\\Windows\\System32\\winmm.mixerGetControlDetailsW")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsA=C:\\Windows\\System32\\winmm.mixerGetDevCapsA")
#pragma comment(linker, "/EXPORT:mixerGetDevCapsW=C:\\Windows\\System32\\winmm.mixerGetDevCapsW")
#pragma comment(linker, "/EXPORT:mixerGetID=C:\\Windows\\System32\\winmm.mixerGetID")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsA=C:\\Windows\\System32\\winmm.mixerGetLineControlsA")
#pragma comment(linker, "/EXPORT:mixerGetLineControlsW=C:\\Windows\\System32\\winmm.mixerGetLineControlsW")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoA=C:\\Windows\\System32\\winmm.mixerGetLineInfoA")
#pragma comment(linker, "/EXPORT:mixerGetLineInfoW=C:\\Windows\\System32\\winmm.mixerGetLineInfoW")
#pragma comment(linker, "/EXPORT:mixerGetNumDevs=C:\\Windows\\System32\\winmm.mixerGetNumDevs")
#pragma comment(linker, "/EXPORT:mixerMessage=C:\\Windows\\System32\\winmm.mixerMessage")
#pragma comment(linker, "/EXPORT:mixerOpen=C:\\Windows\\System32\\winmm.mixerOpen")
#pragma comment(linker, "/EXPORT:mixerSetControlDetails=C:\\Windows\\System32\\winmm.mixerSetControlDetails")
#pragma comment(linker, "/EXPORT:mmDrvInstall=C:\\Windows\\System32\\winmm.mmDrvInstall")
#pragma comment(linker, "/EXPORT:mmGetCurrentTask=C:\\Windows\\System32\\winmm.mmGetCurrentTask")
#pragma comment(linker, "/EXPORT:mmTaskBlock=C:\\Windows\\System32\\winmm.mmTaskBlock")
#pragma comment(linker, "/EXPORT:mmTaskCreate=C:\\Windows\\System32\\winmm.mmTaskCreate")
#pragma comment(linker, "/EXPORT:mmTaskSignal=C:\\Windows\\System32\\winmm.mmTaskSignal")
#pragma comment(linker, "/EXPORT:mmTaskYield=C:\\Windows\\System32\\winmm.mmTaskYield")
#pragma comment(linker, "/EXPORT:mmioAdvance=C:\\Windows\\System32\\winmm.mmioAdvance")
#pragma comment(linker, "/EXPORT:mmioAscend=C:\\Windows\\System32\\winmm.mmioAscend")
#pragma comment(linker, "/EXPORT:mmioClose=C:\\Windows\\System32\\winmm.mmioClose")
#pragma comment(linker, "/EXPORT:mmioCreateChunk=C:\\Windows\\System32\\winmm.mmioCreateChunk")
#pragma comment(linker, "/EXPORT:mmioDescend=C:\\Windows\\System32\\winmm.mmioDescend")
#pragma comment(linker, "/EXPORT:mmioFlush=C:\\Windows\\System32\\winmm.mmioFlush")
#pragma comment(linker, "/EXPORT:mmioGetInfo=C:\\Windows\\System32\\winmm.mmioGetInfo")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcA=C:\\Windows\\System32\\winmm.mmioInstallIOProcA")
#pragma comment(linker, "/EXPORT:mmioInstallIOProcW=C:\\Windows\\System32\\winmm.mmioInstallIOProcW")
#pragma comment(linker, "/EXPORT:mmioOpenA=C:\\Windows\\System32\\winmm.mmioOpenA")
#pragma comment(linker, "/EXPORT:mmioOpenW=C:\\Windows\\System32\\winmm.mmioOpenW")
#pragma comment(linker, "/EXPORT:mmioRead=C:\\Windows\\System32\\winmm.mmioRead")
#pragma comment(linker, "/EXPORT:mmioRenameA=C:\\Windows\\System32\\winmm.mmioRenameA")
#pragma comment(linker, "/EXPORT:mmioRenameW=C:\\Windows\\System32\\winmm.mmioRenameW")
#pragma comment(linker, "/EXPORT:mmioSeek=C:\\Windows\\System32\\winmm.mmioSeek")
#pragma comment(linker, "/EXPORT:mmioSendMessage=C:\\Windows\\System32\\winmm.mmioSendMessage")
#pragma comment(linker, "/EXPORT:mmioSetBuffer=C:\\Windows\\System32\\winmm.mmioSetBuffer")
#pragma comment(linker, "/EXPORT:mmioSetInfo=C:\\Windows\\System32\\winmm.mmioSetInfo")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCA=C:\\Windows\\System32\\winmm.mmioStringToFOURCCA")
#pragma comment(linker, "/EXPORT:mmioStringToFOURCCW=C:\\Windows\\System32\\winmm.mmioStringToFOURCCW")
#pragma comment(linker, "/EXPORT:mmioWrite=C:\\Windows\\System32\\winmm.mmioWrite")
#pragma comment(linker, "/EXPORT:mmsystemGetVersion=C:\\Windows\\System32\\winmm.mmsystemGetVersion")
#pragma comment(linker, "/EXPORT:mod32Message=C:\\Windows\\System32\\winmm.mod32Message")
#pragma comment(linker, "/EXPORT:mxd32Message=C:\\Windows\\System32\\winmm.mxd32Message")
#pragma comment(linker, "/EXPORT:sndPlaySoundA=C:\\Windows\\System32\\winmm.sndPlaySoundA")
#pragma comment(linker, "/EXPORT:sndPlaySoundW=C:\\Windows\\System32\\winmm.sndPlaySoundW")
#pragma comment(linker, "/EXPORT:tid32Message=C:\\Windows\\System32\\winmm.tid32Message")
#pragma comment(linker, "/EXPORT:timeBeginPeriod=C:\\Windows\\System32\\winmm.timeBeginPeriod")
#pragma comment(linker, "/EXPORT:timeEndPeriod=C:\\Windows\\System32\\winmm.timeEndPeriod")
#pragma comment(linker, "/EXPORT:timeGetDevCaps=C:\\Windows\\System32\\winmm.timeGetDevCaps")
#pragma comment(linker, "/EXPORT:timeGetSystemTime=C:\\Windows\\System32\\winmm.timeGetSystemTime")
#pragma comment(linker, "/EXPORT:timeGetTime=C:\\Windows\\System32\\winmm.timeGetTime")
#pragma comment(linker, "/EXPORT:timeKillEvent=C:\\Windows\\System32\\winmm.timeKillEvent")
#pragma comment(linker, "/EXPORT:timeSetEvent=C:\\Windows\\System32\\winmm.timeSetEvent")
#pragma comment(linker, "/EXPORT:waveInAddBuffer=C:\\Windows\\System32\\winmm.waveInAddBuffer")
#pragma comment(linker, "/EXPORT:waveInClose=C:\\Windows\\System32\\winmm.waveInClose")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsA=C:\\Windows\\System32\\winmm.waveInGetDevCapsA")
#pragma comment(linker, "/EXPORT:waveInGetDevCapsW=C:\\Windows\\System32\\winmm.waveInGetDevCapsW")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextA=C:\\Windows\\System32\\winmm.waveInGetErrorTextA")
#pragma comment(linker, "/EXPORT:waveInGetErrorTextW=C:\\Windows\\System32\\winmm.waveInGetErrorTextW")
#pragma comment(linker, "/EXPORT:waveInGetID=C:\\Windows\\System32\\winmm.waveInGetID")
#pragma comment(linker, "/EXPORT:waveInGetNumDevs=C:\\Windows\\System32\\winmm.waveInGetNumDevs")
#pragma comment(linker, "/EXPORT:waveInGetPosition=C:\\Windows\\System32\\winmm.waveInGetPosition")
#pragma comment(linker, "/EXPORT:waveInMessage=C:\\Windows\\System32\\winmm.waveInMessage")
#pragma comment(linker, "/EXPORT:waveInOpen=C:\\Windows\\System32\\winmm.waveInOpen")
#pragma comment(linker, "/EXPORT:waveInPrepareHeader=C:\\Windows\\System32\\winmm.waveInPrepareHeader")
#pragma comment(linker, "/EXPORT:waveInReset=C:\\Windows\\System32\\winmm.waveInReset")
#pragma comment(linker, "/EXPORT:waveInStart=C:\\Windows\\System32\\winmm.waveInStart")
#pragma comment(linker, "/EXPORT:waveInStop=C:\\Windows\\System32\\winmm.waveInStop")
#pragma comment(linker, "/EXPORT:waveInUnprepareHeader=C:\\Windows\\System32\\winmm.waveInUnprepareHeader")
#pragma comment(linker, "/EXPORT:waveOutBreakLoop=C:\\Windows\\System32\\winmm.waveOutBreakLoop")
#pragma comment(linker, "/EXPORT:waveOutClose=C:\\Windows\\System32\\winmm.waveOutClose")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsA=C:\\Windows\\System32\\winmm.waveOutGetDevCapsA")
#pragma comment(linker, "/EXPORT:waveOutGetDevCapsW=C:\\Windows\\System32\\winmm.waveOutGetDevCapsW")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextA=C:\\Windows\\System32\\winmm.waveOutGetErrorTextA")
#pragma comment(linker, "/EXPORT:waveOutGetErrorTextW=C:\\Windows\\System32\\winmm.waveOutGetErrorTextW")
#pragma comment(linker, "/EXPORT:waveOutGetID=C:\\Windows\\System32\\winmm.waveOutGetID")
#pragma comment(linker, "/EXPORT:waveOutGetNumDevs=C:\\Windows\\System32\\winmm.waveOutGetNumDevs")
#pragma comment(linker, "/EXPORT:waveOutGetPitch=C:\\Windows\\System32\\winmm.waveOutGetPitch")
#pragma comment(linker, "/EXPORT:waveOutGetPlaybackRate=C:\\Windows\\System32\\winmm.waveOutGetPlaybackRate")
#pragma comment(linker, "/EXPORT:waveOutGetPosition=C:\\Windows\\System32\\winmm.waveOutGetPosition")
#pragma comment(linker, "/EXPORT:waveOutGetVolume=C:\\Windows\\System32\\winmm.waveOutGetVolume")
#pragma comment(linker, "/EXPORT:waveOutMessage=C:\\Windows\\System32\\winmm.waveOutMessage")
#pragma comment(linker, "/EXPORT:waveOutOpen=C:\\Windows\\System32\\winmm.waveOutOpen")
#pragma comment(linker, "/EXPORT:waveOutPause=C:\\Windows\\System32\\winmm.waveOutPause")
#pragma comment(linker, "/EXPORT:waveOutPrepareHeader=C:\\Windows\\System32\\winmm.waveOutPrepareHeader")
#pragma comment(linker, "/EXPORT:waveOutReset=C:\\Windows\\System32\\winmm.waveOutReset")
#pragma comment(linker, "/EXPORT:waveOutRestart=C:\\Windows\\System32\\winmm.waveOutRestart")
#pragma comment(linker, "/EXPORT:waveOutSetPitch=C:\\Windows\\System32\\winmm.waveOutSetPitch")
#pragma comment(linker, "/EXPORT:waveOutSetPlaybackRate=C:\\Windows\\System32\\winmm.waveOutSetPlaybackRate")
#pragma comment(linker, "/EXPORT:waveOutSetVolume=C:\\Windows\\System32\\winmm.waveOutSetVolume")
#pragma comment(linker, "/EXPORT:waveOutUnprepareHeader=C:\\Windows\\System32\\winmm.waveOutUnprepareHeader")
#pragma comment(linker, "/EXPORT:waveOutWrite=C:\\Windows\\System32\\winmm.waveOutWrite")
#pragma comment(linker, "/EXPORT:wid32Message=C:\\Windows\\System32\\winmm.wid32Message")
#pragma comment(linker, "/EXPORT:wod32Message=C:\\Windows\\System32\\winmm.wod32Message")
#pragma endregion

#pragma region D3D Hooks
void OnFrame(IDXGISwapChain*, UINT, UINT);
void D3DInit(IDXGIAdapter*, HMODULE, ID3D11Device**, ID3D11DeviceContext**);

VTABLE_HOOK(HRESULT, WINAPI, IDXGISwapChain, Present, UINT SyncInterval, UINT Flags)
{
	OnFrame(This, SyncInterval, Flags);
	return originalIDXGISwapChainPresent(This, SyncInterval, Flags);
}
VTABLE_HOOK(HRESULT, WINAPI, IDXGIFactory, CreateSwapChain,
	IUnknown* pDevice,
	DXGI_SWAP_CHAIN_DESC* pDesc,
	IDXGISwapChain** ppSwapChain
)
{
	HRESULT result = originalIDXGIFactoryCreateSwapChain(This, pDevice, pDesc, ppSwapChain);
	INSTALL_VTABLE_HOOK(IDXGISwapChain, *ppSwapChain, Present, 8);
	return result;
}
HOOK(HRESULT, WINAPI, D3D11CreateDevice, PROC_ADDRESS("d3d11.dll", "D3D11CreateDevice"),
	IDXGIAdapter* pAdapter,
	D3D_DRIVER_TYPE         DriverType,
	HMODULE                 Software,
	UINT                    Flags,
	const D3D_FEATURE_LEVEL* pFeatureLevels,
	UINT                    FeatureLevels,
	UINT                    SDKVersion,
	ID3D11Device** ppDevice,
	D3D_FEATURE_LEVEL* pFeatureLevel,
	ID3D11DeviceContext** ppImmediateContext)
{
	const HRESULT result = originalD3D11CreateDevice(
		pAdapter,
		DriverType,
		Software,
		Flags,
		pFeatureLevels,
		FeatureLevels,
		SDKVersion,
		ppDevice,
		pFeatureLevel,
		ppImmediateContext);
	D3DInit(pAdapter, Software, ppDevice, ppImmediateContext);
	return result;
}
HOOK(HRESULT, WINAPI, CreateDXGIFactory, PROC_ADDRESS("dxgi.dll", "CreateDXGIFactory"),
	REFIID riid,
	IDXGIFactory** ppFactory
) {
	const HRESULT result = originalCreateDXGIFactory(riid, ppFactory);
	if (SUCCEEDED(result)) {
		INSTALL_VTABLE_HOOK(IDXGIFactory, *ppFactory, CreateSwapChain, 10);
	}
	return result;
}
#pragma endregion

#pragma region EnableDynamicSpeed (FPS++) by zettozoid
// Assembled EnableDynamicSpeed from https://gamebanana.com/tools/download/7059 -- Thanks zettozoid!
const uint8_t patch_[] = "\xF3\x0F\x10\x05\x1C\xF7\x1A\x00\xF3\x0F\x59\x05\x98\x0F\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x0D\xFC\xF6\x1A\x00\xF3\x0F\x59\x0D\x78\x0F\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x15\xDC\xF6\x1A\x00\xF3\x0F\x59\x15\x58\x0F\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x1D\xBC\xF6\x1A\x00\xF3\x0F\x59\x1D\x38\x0F\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x25\x9C\xF6\x1A\x00\xF3\x0F\x59\x25\x18\x0F\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x2D\x7C\xF6\x1A\x00\xF3\x0F\x59\x2D\xF8\x0E\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x35\x5C\xF6\x1A\x00\xF3\x0F\x59\x35\xD8\x0E\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x3D\x3C\xF6\x1A\x00\xF3\x0F\x59\x3D\xB8\x0E\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x44\x0F\x10\x05\x1B\xF6\x1A\x00\xF3\x44\x0F\x59\x05\x96\x0E\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x44\x0F\x10\x0D\xFB\xF5\x1A\x00\xF3\x44\x0F\x59\x0D\x76\x0E\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x05\x14\x71\x0D\x00\xF3\x0F\x5E\x05\x58\x0E\x4A\x02\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x05\x34\x9B\x1C\x00\xC3\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\x00\xF3\x0F\x10\x0D\x14\x9B\x1C\x00\xC3";
uint8_t* patch;
void LoadPatch() {
	// Displacements calculated from 0x13fff000
	patch = (uint8_t*)VirtualAlloc((LPVOID)0x13fff0000, 512, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	if (patch) memcpy(patch, patch_, 394);
}
void Inject() {
	if (patch == 0) return;
	auto addr = (uint64_t)patch;
	writeRelCall(0x1405bcd26, addr); // new0
	writeRelCall(0x14018967c, addr);
	writeRelCall(0x1404fc39f, addr);
	writeRelCall(0x140455099, addr);
	writeRelCall(0x140419839, addr);
	writeRelCall(0x14014be2a, addr);
	writeRelCall(0x140189448, addr);
	writeRelCall(0x142b55bbc, addr);
	writeRelCall(0x140135a37, addr);
	writeRelCall(0x1403c2033, addr);
	writeRelCall(0x140835e0d, addr);
	writeRelCall(0x1406d70fe, addr);
	writeRelCall(0x143aa520f, addr);
	writeRelCall(0x1406d708b, addr);
	writeRelCall(0x1406fe7de, addr);
	writeRelCall(0x1406fe764, addr);
	writeRelCall(0x1401fa410, addr);
	writeRelCall(0x1401ae843, addr);
	writeRelCall(0x1406ecaf2, addr);
	writeRelCall(0x1406ee2b5, addr);
	writeRelCall(0x140704f3e, addr);
	writeRelCall(0x140700254, addr);
	writeRelCall(0x1407002ce, addr);
	writeRelCall(0x1406dbc9e, addr);
	writeRelCall(0x1406e5097, addr);
	writeRelCall(0x1406e50d1, addr);
	writeRelCall(0x1406e506b, addr);
	writeRelCall(0x140704ec4, addr);
	writeRelCall(0x14070624e, addr);
	writeRelCall(0x1407061d4, addr);
	writeRelCall(0x1406dab16, addr + 0x20); // new1
	writeRelCall(0x1406dab96, addr + 0x20);
	writeRelCall(0x140206880, addr + 0x20); // gameplay speed
	writeRelCall(0x1401f83a1, addr + 0x20);
	writeRelCall(0x140159991, addr + 0x20);
	writeRelCall(0x1401ebf07, addr + 0x20);
	writeRelCall(0x140419817, addr + 0x20);
	writeRelCall(0x14018f823, addr + 0x20);
	writeRelCall(0x140158481, addr + 0x20);
	writeRelCall(0x1401517bf, addr + 0x20);
	writeRelCall(0x1401521de, addr + 0x20);
	writeRelCall(0x140158610, addr + 0x20);
	writeRelCall(0x140158795, addr + 0x20);
	writeRelCall(0x140147443, addr + 0x20);
	writeRelCall(0x14011f08f, addr + 0x20);
	writeRelCall(0x140152f94, addr + 0x20);
	writeRelCall(0x140151fb1, addr + 0x20);
	writeRelCall(0x140146177, addr + 0x20);
	writeRelCall(0x1406b8c4a, addr + 0x40); // new2
	writeRelCall(0x1401599b1, addr + 0x40); // ui
	writeRelCall(0x14047f254, addr + 0x40);
	writeRelCall(0x140506de4, addr + 0x40);
	writeRelCall(0x140506e5c, addr + 0x40);
	writeRelCall(0x1401517e6, addr + 0x40);
	writeRelCall(0x1407719e9, addr + 0x40);
	writeRelCall(0x140771e59, addr + 0x40);
	writeRelCall(0x14014746a, addr + 0x40);
	writeRelCall(0x140152206, addr + 0x40);
	writeRelCall(0x14015206e, addr + 0x40);
	writeRelCall(0x1401520d2, addr + 0x40);
	writeRelCall(0x140152fbc, addr + 0x40);
	writeRelCall(0x140153086, addr + 0x40);
	writeRelCall(0x140151fd9, addr + 0x40);
	writeRelCall(0x14014619e, addr + 0x40);
}
void RestoreInject() {
	restoreRelCallWrites(0x1405bcd26);
	restoreRelCallWrites(0x14018967c);
	restoreRelCallWrites(0x1404fc39f);
	restoreRelCallWrites(0x140455099);
	restoreRelCallWrites(0x140419839);
	restoreRelCallWrites(0x14014be2a);
	restoreRelCallWrites(0x140189448);
	restoreRelCallWrites(0x142b55bbc);
	restoreRelCallWrites(0x140135a37);
	restoreRelCallWrites(0x1403c2033);
	restoreRelCallWrites(0x140835e0d);
	restoreRelCallWrites(0x1406d70fe);
	restoreRelCallWrites(0x143aa520f);
	restoreRelCallWrites(0x1406d708b);
	restoreRelCallWrites(0x1406fe7de);
	restoreRelCallWrites(0x1406fe764);
	restoreRelCallWrites(0x1401fa410);
	restoreRelCallWrites(0x1401ae843);
	restoreRelCallWrites(0x1406ecaf2);
	restoreRelCallWrites(0x1406ee2b5);
	restoreRelCallWrites(0x140704f3e);
	restoreRelCallWrites(0x140700254);
	restoreRelCallWrites(0x1407002ce);
	restoreRelCallWrites(0x1406dbc9e);
	restoreRelCallWrites(0x1406e5097);
	restoreRelCallWrites(0x1406e50d1);
	restoreRelCallWrites(0x1406e506b);
	restoreRelCallWrites(0x140704ec4);
	restoreRelCallWrites(0x14070624e);
	restoreRelCallWrites(0x1407061d4);
	restoreRelCallWrites(0x1406dab16);
	restoreRelCallWrites(0x1406dab96);
	restoreRelCallWrites(0x140206880);
	restoreRelCallWrites(0x1401f83a1);
	restoreRelCallWrites(0x140159991);
	restoreRelCallWrites(0x1401ebf07);
	restoreRelCallWrites(0x140419817);
	restoreRelCallWrites(0x14018f823);
	restoreRelCallWrites(0x140158481);
	restoreRelCallWrites(0x1401517bf);
	restoreRelCallWrites(0x1401521de);
	restoreRelCallWrites(0x140158610);
	restoreRelCallWrites(0x140158795);
	restoreRelCallWrites(0x140147443);
	restoreRelCallWrites(0x14011f08f);
	restoreRelCallWrites(0x140152f94);
	restoreRelCallWrites(0x140151fb1);
	restoreRelCallWrites(0x140146177);
	restoreRelCallWrites(0x1406b8c4a);
	restoreRelCallWrites(0x1401599b1);
	restoreRelCallWrites(0x14047f254);
	restoreRelCallWrites(0x140506de4);
	restoreRelCallWrites(0x140506e5c);
	restoreRelCallWrites(0x1401517e6);
	restoreRelCallWrites(0x1407719e9);
	restoreRelCallWrites(0x140771e59);
	restoreRelCallWrites(0x14014746a);
	restoreRelCallWrites(0x140152206);
	restoreRelCallWrites(0x14015206e);
	restoreRelCallWrites(0x1401520d2);
	restoreRelCallWrites(0x140152fbc);
	restoreRelCallWrites(0x140153086);
	restoreRelCallWrites(0x140151fd9);
	restoreRelCallWrites(0x14014619e);
}
#pragma endregion

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
#ifdef _DEBUG
		AllocConsole();
		freopen("CONOUT$", "w", stdout);
		freopen("CONOUT$", "w", stderr);
		LOG("Debugging now.");
#endif       
		LoadPatch();
		RestoreInject(); // 1st call backups 5 bytes from selected addresses
		INSTALL_HOOK(D3D11CreateDevice);
		INSTALL_HOOK(CreateDXGIFactory);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}
auto fps = (DWORD*)0x142284508;
auto fpsCutscene = (float*)0x14228450C;
auto frameTime = (float*)0x142490FA8;

void D3DInit(IDXGIAdapter*, HMODULE, ID3D11Device**, ID3D11DeviceContext**) {
	LOG("D3D Init");
}

void OnFrame(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags) {
#ifdef _DEBUG
	printf("fps=%3d frametime=%.3f        \r", *fps, *frameTime * 1000);
#endif
	if (GetAsyncKeyState(VK_F1) & 1) {
		RestoreInject();
		*fps = 60;
		*fpsCutscene = 60.0f;
	}
	if (GetAsyncKeyState(VK_F2) & 1) {
		Inject();
		*fps = 120;
		*fpsCutscene = 120.0f;
	}
	if (GetAsyncKeyState(VK_F3) & 1) {
		Inject();
		*fps = 144;
		*fpsCutscene = 144.0f;
	}
	if (GetAsyncKeyState(VK_F4) & 1) {
		Inject();
		*fps = 165;
		*fpsCutscene = 165.0f;
	}
	if (GetAsyncKeyState(VK_F6) & 1) {
		Inject();
		*fps = 240;
		*fpsCutscene = 240.0f;
	}
};
