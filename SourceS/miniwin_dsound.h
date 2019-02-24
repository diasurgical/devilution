#pragma once

typedef void *LPDSBCAPS, *LPCDSBUFFERDESC;

struct IDirectSound;
typedef IDirectSound *LPDIRECTSOUND;

DECLARE_INTERFACE_(IDirectSoundBuffer, IUnknown)
{
	// clang-format off
	STDMETHOD(GetCaps)(THIS_ LPDSBCAPS pDSBufferCaps);
	STDMETHOD(GetCurrentPosition)(THIS_ LPDWORD pdwCurrentPlayCursor, LPDWORD pdwCurrentWriteCursor);
	STDMETHOD(GetFormat)(THIS_ LPWAVEFORMATEX pwfxFormat, DWORD dwSizeAllocated, LPDWORD pdwSizeWritten);
	STDMETHOD(GetVolume)(THIS_ LPLONG plVolume);
	STDMETHOD(GetPan)(THIS_ LPLONG plPan);
	STDMETHOD(GetFrequency)(THIS_ LPDWORD pdwFrequency);
	STDMETHOD(GetStatus)(THIS_ LPDWORD pdwStatus);
	STDMETHOD(Initialize)(THIS_ LPDIRECTSOUND pDirectSound, LPCDSBUFFERDESC pcDSBufferDesc);
	STDMETHOD(Lock)(THIS_ DWORD dwOffset, DWORD dwBytes, LPVOID *ppvAudioPtr1, LPDWORD pdwAudioBytes1,
			LPVOID *ppvAudioPtr2, LPDWORD pdwAudioBytes2, DWORD dwFlags);
	STDMETHOD(Play)(THIS_ DWORD dwReserved1, DWORD dwPriority, DWORD dwFlags);
	STDMETHOD(SetCurrentPosition)(THIS_ DWORD dwNewPosition);
	STDMETHOD(SetFormat)(THIS_ LPCWAVEFORMATEX pcfxFormat);
	STDMETHOD(SetVolume)(THIS_ LONG lVolume);
	STDMETHOD(SetPan)(THIS_ LONG lPan);
	STDMETHOD(SetFrequency)(THIS_ DWORD dwFrequency);
	STDMETHOD(Stop)(THIS);
	STDMETHOD(Unlock)(THIS_ LPVOID pvAudioPtr1, DWORD dwAudioBytes1, LPVOID pvAudioPtr2, DWORD dwAudioBytes2);
	STDMETHOD(Restore)(THIS);
	// clang-format on
};

typedef void *LPDIRECTSOUNDBUFFER, *LPDSCAPS, *LPUNKNOWN, *LPCGUID;

DECLARE_INTERFACE_(IDirectSound, IUnknown)
{
	// clang-format off
	STDMETHOD(CreateSoundBuffer)(THIS_ LPCDSBUFFERDESC pcDSBufferDesc, LPDIRECTSOUNDBUFFER *ppDSBuffer, LPUNKNOWN pUnkOuter);
	STDMETHOD(GetCaps)(THIS_ LPDSCAPS pDSCaps);
	STDMETHOD(DuplicateSoundBuffer)(THIS_ LPDIRECTSOUNDBUFFER pDSBufferOriginal, LPDIRECTSOUNDBUFFER *ppDSBufferDuplicate);
	STDMETHOD(SetCooperativeLevel)(THIS_ HWND hwnd, DWORD dwLevel);
	STDMETHOD(Compact)(THIS);
	STDMETHOD(GetSpeakerConfig)(THIS_ LPDWORD pdwSpeakerConfig);
	STDMETHOD(SetSpeakerConfig)(THIS_ DWORD dwSpeakerConfig);
	STDMETHOD(Initialize)(THIS_ LPCGUID pcGuidDevice);
	// clang-format on
};

#define	_FACDS	0x878
#define MAKE_DSHRESULT(code) MAKE_HRESULT(1, _FACDS, code)

#define E_NOINTERFACE 0x80004002
#define DSERR_PRIOLEVELNEEDED MAKE_DSHRESULT(70)
#define DSERR_BADFORMAT MAKE_DSHRESULT(100)
#define DSERR_NODRIVER MAKE_DSHRESULT(120)
#define DSERR_ALREADYINITIALIZED MAKE_DSHRESULT(130)
#define DSERR_BUFFERLOST MAKE_DSHRESULT(150)
#define DS_OK 0
#define DSERR_INVALIDCALL MAKE_DSHRESULT(50)
#define DSERR_NOAGGREGATION 0x80040110
#define DSERR_OUTOFMEMORY 0x8007000E
#define DSERR_INVALIDPARAM 0x80070057
#define DSERR_ALLOCATED MAKE_DSHRESULT(10)
#define DSERR_CONTROLUNAVAIL MAKE_DSHRESULT(30)
