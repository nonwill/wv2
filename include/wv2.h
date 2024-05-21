﻿/*
## 0.0.14(14)	2022-12-13
- minimum WebView2 SDK version 1.0.774.44
	For full API compatibility, this version of the WebView2 SDK requires WebView2
	Runtime version 89.0.774.44 or higher.

## 0.1.0(15)	2023-08-08
- minimum WebView2 SDK version 1.0.774.44
	For full API compatibility, this version of the WebView2 SDK requires WebView2
	Runtime version 89.0.774.44 or higher.

## 0.1.1(16)	2023-08-09
- Fix Casting Error

## 0.2.0(17)	2024-04-18
- Added support for isMutedChangedEvent, isDocumentPlayingAudioEvent.
- Added support for OpenTaskManagerWindow.
- minimum WebView2 SDK version 	1.0.1072.54
	For full API compatibility, this Release version of the WebView2 SDK requires 
	WebView2 Runtime version 97.0.1072.54 or higher.
	https://learn.microsoft.com/en-us/microsoft-edge/webview2/release-notes/archive?tabs=dotnetcsharp

## 0.3.0(18)	2024-05-02
- Added support for browserProcessExited event.

## 0.4.0(19)	2024-05-03
- Change the structure of the 'wv2bool' structure

## 0.5.0(20)	2024-05-17
- Added partial support for the NewWindowRequested event.

## 0.6.0(21)	2024-05-20
- Added documentTitleChanged event handler support
- Removed the old wv2settings structure and setSettings function

## 0.7.0(22)	2024-05-21
- Changed domContentLoaded event type
- Added support for contentLoading, scriptDialogOpening events
*/
#ifndef WEBVIEW2_C_WRAPPER_H_
#define WEBVIEW2_C_WRAPPER_H_

#define WV2_VERSION			"0.7.0"
#define WV2_VERSION_NUM		22

#include <windows.h>
#include <stdbool.h>
#include <stdint.h>
#include "wv2envOpts.h"

#if defined(_MSC_VER) && _MSC_VER < 1900 // Visual Studio 2013 
#define DEPRECATED(message) __declspec(deprecated(message))
#else
#ifdef __cplusplus
#define DEPRECATED(message) [[deprecated(message)]]
#else 
#define DEPRECATED(message)
#endif // __cplusplus
#endif


#ifdef WV2_EXPORTS
#define WV2_API __declspec(dllexport)
#else
#define WV2_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

// @see COREWEBVIEW2_HOST_RESOURCE_ACCESS_KIND ( WebView2.h )
#ifndef __wv2HostResourceAccessKind__DEFINED__
#define __wv2HostResourceAccessKind__DEFINED__
typedef enum wv2HostResourceAccessKind {
	wv2HostResourceAccessKindDeny = 0,
	wv2HostResourceAccessKindAllow = (wv2HostResourceAccessKindDeny + 1),
	wv2HostResourceAccessKindDenyCors = (wv2HostResourceAccessKindAllow + 1)
}wv2HostResourceAccessKind;
#endif // __wv2HostResourceAccessKind__DEFINED__

typedef void* wv2_t;
typedef void* wv2env_t;	// CoreWebView2Environment

// Structure representing the result and support status of a function
typedef struct wv2bool {
	// Result of the function execution
	bool value;
	// HRESULT of the function execution
	HRESULT hr;
} wv2bool;

///////////////////////////////////////////////////////////////////////////////
typedef void* wv2deferral_t; // ICoreWebView2Deferral
WV2_API HRESULT wv2deferral_complete(wv2deferral_t d);

WV2_API void wv2deleteDeferral(wv2deferral_t* d);
///////////////////////////////////////////////////////////////////////////////
typedef void* wv2settings_t; // ICoreWebView2Settings
WV2_API wv2bool 
wv2settings_isScriptEnabled(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setIsScriptEnabled(wv2settings_t s, bool isScriptEnabled);

WV2_API wv2bool 
wv2settings_isWebMessageEnabled(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setIsWebMessageEnabled(wv2settings_t s, bool isWebMessageEnabled);

WV2_API wv2bool 
wv2settings_areDefaultScriptDialogsEnabled(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setAreDefaultScriptDialogsEnabled(wv2settings_t s, bool areDefaultScriptDialogsEnabled);

WV2_API wv2bool 
wv2settings_isStatusBarEnabled(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setIsStatusBarEnabled(wv2settings_t s, bool isStatusBarEnabled);

WV2_API wv2bool 
wv2settings_areDevToolsEnabled(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setAreDevToolsEnabled(wv2settings_t s, bool areDevToolsEnabled);

WV2_API wv2bool 
wv2settings_areDefaultContextMenusEnabled(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setAreDefaultContextMenusEnabled(wv2settings_t s, bool enabled);

WV2_API wv2bool 
wv2settings_areHostObjectsAllowed(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setAreHostObjectsAllowed(wv2settings_t s, bool allowed);

WV2_API wv2bool
wv2settings_isZoomControlEnabled(wv2settings_t s);

WV2_API wv2bool
wv2settings_setIsZoomControlEnabled(wv2settings_t s, bool enabled);

WV2_API wv2bool
wv2settings_isBuiltInErrorPageEnabled(wv2settings_t s);

WV2_API wv2bool 
wv2settings_setIsBuiltInErrorPageEnabled(wv2settings_t s, bool enabled);

// @see COREWEBVIEW2_BROWSER_PROCESS_EXIT_KIND ( WebView2.h )
typedef enum wv2browserProcessExitKind {
	wv2browserProcessExitKindNormal = 0,
	wv2browserProcessExitKindFailed = (wv2browserProcessExitKindNormal + 1)
}wv2browserProcessExitKind;

// @see COREWEBVIEW2_SCRIPT_DIALOG_KIND
typedef enum wv2scriptDialogKind {
	wv2scriptDialogKind_undefined = -1,
	wv2scriptDialogKind_alert = 0,
	wv2scriptDialogKind_confirm = (wv2scriptDialogKind_alert + 1),
	wv2scriptDialogKind_prompt = (wv2scriptDialogKind_confirm + 1),
	wv2scriptDialogKind_beforeunload = (wv2scriptDialogKind_prompt + 1)
}wv2scriptDialogKind;

typedef struct {
	wv2browserProcessExitKind browserProcessExitKind;
	uint32_t browserProcessId;
}wv2browserProcessExitedEventArgs;

///////////////////////////////////////////////////////////////////////////////
typedef void* wv2newWindowRequestedEventArgs_t; // ICoreWebView2NewWindowRequestedEventArgs

/*
@brief      Gets the target uri of the new window request.
@return     The target URI of the new window request.
@note       The returned LPWSTR must be freed using wv2freeMemory after use.
*/
WV2_API LPWSTR 
wv2newWindowRequestedEventArgs_uri(wv2newWindowRequestedEventArgs_t args);

/*
@brief		Indicates whether the NewWindowRequested event is handled by host.
*/
WV2_API bool 
wv2newWindowRequestedEventArgs_handled(wv2newWindowRequestedEventArgs_t args);

/*
@brief		Indicates whether the NewWindowRequested event is handled by host.
*/
WV2_API wv2bool 
wv2newWindowRequestedEventArgs_setHandled(wv2newWindowRequestedEventArgs_t args, bool handled);

/*
@brief		true when the new window request was initiated through a user 
			gesture such as selecting an anchor tag with target.
*/
WV2_API bool 
wv2newWindowRequestedEventArgs_isUserInitiated(wv2newWindowRequestedEventArgs_t args);

//wv2bool setNewWindow(ICoreWebView2* newWindow);
//ICoreWebView2* newWindow();
//ICoreWebView2Deferral* deferral();
//ICoreWebView2WindowFeatures* windowFeatures();

///////////////////////////////////////////////////////////////////////////////
typedef void* wv2domContentLoadedEventArgs_t; // ICoreWebView2DOMContentLoadedEventArgs

WV2_API uint64_t  wv2domContentLoadedEventArgs_navigationId(wv2domContentLoadedEventArgs_t args);
///////////////////////////////////////////////////////////////////////////////
typedef void* wv2contentLoadingEventArgs_t; // ICoreWebView2ContentLoadingEventArgs

WV2_API bool wv2contentLoadingEventArgs_isErrorPage(wv2contentLoadingEventArgs_t args);
WV2_API uint64_t wv2contentLoadingEventArgs_t_navigationId(wv2contentLoadingEventArgs_t args);

///////////////////////////////////////////////////////////////////////////////
typedef void* wv2scriptDialogOpeningEventArgs_t; // ICoreWebView2ScriptDialogOpeningEventArgs
WV2_API LPWSTR 
wv2scriptDialogOpeningEventArgs_uri(wv2scriptDialogOpeningEventArgs_t args);

WV2_API wv2scriptDialogKind 
wv2scriptDialogOpeningEventArgs_kind(wv2scriptDialogOpeningEventArgs_t args);

WV2_API LPWSTR 
wv2scriptDialogOpeningEventArgs_message(wv2scriptDialogOpeningEventArgs_t args);

WV2_API HRESULT 
wv2scriptDialogOpeningEventArgs_accept(wv2scriptDialogOpeningEventArgs_t args);

WV2_API LPWSTR 
wv2scriptDialogOpeningEventArgs_defaultText(wv2scriptDialogOpeningEventArgs_t args);

WV2_API LPWSTR 
wv2scriptDialogOpeningEventArgs_resultText(wv2scriptDialogOpeningEventArgs_t args);

WV2_API HRESULT 
wv2scriptDialogOpeningEventArgs_setResultText(wv2scriptDialogOpeningEventArgs_t args, LPCWSTR resultText);

WV2_API wv2deferral_t 
wv2scriptDialogOpeningEventArgs_deferral(wv2scriptDialogOpeningEventArgs_t args);

///////////////////////////////////////////////////////////////////////////////

typedef void 
(*createCompleted)(wv2_t w, HRESULT errorCode, void* userData);

typedef void 
(*executeScriptCompleted)(wv2_t sender, LPCWSTR resultObjectAsJson);

typedef bool
(*navigationStarting)(wv2_t sender, LPCWSTR uri);

typedef void
(*navigationCompleted)(wv2_t sender);

typedef bool
(*windowCloseRequested)(wv2_t sender);

typedef void
(*historyChanged)(wv2_t sender, bool canGoBack, bool canGoForward);

typedef void 
(*webMessageReceived)(wv2_t sender, LPCWSTR message);

typedef void
(*isMutedChanged)(wv2_t sender);

typedef isMutedChanged isDocumentPlayingAudioChanged;

typedef void
(*browserProcessExited)(wv2env_t sender, wv2browserProcessExitedEventArgs* e);

typedef void
(*newWindowRequested)(wv2_t sender, wv2newWindowRequestedEventArgs_t args);

typedef navigationCompleted documentTitleChanged;

typedef void
(*domContentLoaded)(wv2_t sender, wv2domContentLoadedEventArgs_t args);

typedef void
(*contentLoading)(wv2_t sender, wv2contentLoadingEventArgs_t args);

typedef void
(*scriptDialogOpening)(wv2_t sender, wv2scriptDialogOpeningEventArgs_t args);

///////////////////////////////////////////////////////////////////////////////
WV2_API LPWSTR wv2getAvailableBrowserVersionString(LPCWSTR browserExecutableFolder);

DEPRECATED("wv2create deprecated. Use wv2create2 instead.")
WV2_API bool wv2create(LPCWSTR browserExecutableFolder, LPCWSTR userDataFolder, 
	HWND parentWindow, createCompleted handler, void* userData);

WV2_API bool wv2create2(LPCWSTR browserExecutableFolder, LPCWSTR userDataFolder,
	wv2envOpts_t environmentOptions, HWND parentWindow, 
	createCompleted handler, void* userData);

DEPRECATED("wv2createSync deprecated. Use wv2createSync2 instead.")
WV2_API wv2_t wv2createSync(LPCWSTR browserExecutableFolder, LPCWSTR userDataFolder, 
	HWND parentWindow);

WV2_API wv2_t wv2createSync2(LPCWSTR browserExecutableFolder, LPCWSTR userDataFolder,
	wv2envOpts_t environmentOptions, HWND parentWindow);

WV2_API wv2env_t wv2getEnv(wv2_t w);

/*
@brief		Set an event handler for the browserProcessExited event.
@remark		Minimum WebView2 SDK version required: 	1.0.992.28
*/
WV2_API wv2bool wv2envSetBrowserProcessExitedHandler(wv2env_t e, 
	browserProcessExited handler);

WV2_API void wv2destroy(wv2_t* w);

WV2_API bool wv2setUserData(wv2_t w, void* userData);

WV2_API void* wv2getUserData(wv2_t w);

/*
@brief		Defines properties that enable, disable, or modify WebView features.
*/
WV2_API wv2settings_t wv2getSettings(wv2_t w);

WV2_API bool wv2setVirtualHostNameToFolderMapping(wv2_t w, LPCWSTR hostName, 
	LPCWSTR folderPath, wv2HostResourceAccessKind accessKind);

WV2_API bool wv2executeScript(wv2_t w, LPCWSTR script, executeScriptCompleted handler);

WV2_API LPCWSTR wv2executeScriptSync(wv2_t w, LPCWSTR script);

WV2_API void wv2freeMemory(void* p);

/*		
@brief		The URI of the current top level document.
*/
WV2_API LPCWSTR wv2getSource(wv2_t w);

/*
@brief		Navigates the WebView to the previous page in the navigation history.
*/
WV2_API bool wv2goBack(wv2_t w);

/*
@brief		Navigates the WebView to the next page in the navigation history.
@param		
@return		
@date		2021/06/24
*/
WV2_API bool wv2goForward(wv2_t w);

/*
@brief		Causes a navigation of the top level document to the specified URI.
@param		w
@param		uri		The URI to navigate to.
@return		
@date		2022/12/13
*/
WV2_API bool wv2navigate(wv2_t w, const wchar_t* url);

/*
@brief		Initiates a navigation to htmlContent as source HTML of a new document.
			The htmlContent parameter may not be larger than 2 MB in total size. 
			The origin of the new page is `about:blank`.
*/
WV2_API bool wv2navigateToString(wv2_t w, const wchar_t* htmlContent);

/*
@brief		
@param		w, A handle to the wv2
@param		uri, URI parameter must be absolute URI. 
@param		method	
@param		postData
@param		byteSize
@param		headers, The headers string is the raw request header string 
			delimited by CRLF (optional in last header). 
@return		
@see		https://learn.microsoft.com/en-us/microsoft-edge/webview2/reference/win32/icorewebview2environment2?view=webview2-1.0.1462.37#createwebresourcerequest
@date		2022/12/13
*/
WV2_API bool wv2navigateWithWebResource(wv2_t w, LPCWSTR uri,
	LPCWSTR method, BYTE* postData, size_t byteSize, LPCWSTR headers);

/*		
@brief		Reload the current page.
			This is similar to navigating to the URI of current top level 
			document including all navigation events firing and respecting 
			any entries in the HTTP cache. But, the back or forward history 
			are not modified.
*/
WV2_API bool wv2reload(wv2_t w);

/*
@brief      Changes the size of the WebView2 window.
@param      w, A handle to the wv2.
@param      width, The new width of the window.
@param      height, The new height of the window.
@return     true if the resize operation was successful; otherwise, false.
*/
WV2_API bool wv2resize(wv2_t w, int width, int height);

/*
@brief		Post the specified webMessage to the top level document in this WebView.
*/
WV2_API bool wv2postWebMessageAsJson(wv2_t w, LPCWSTR messageAsJson);

/*
@brief		Posts a message that is a simple string rather than a JSON string
			representation of a JavaScript object.
*/
WV2_API bool wv2postWebMessageAsString(wv2_t w, LPCWSTR messageAsString);

/*
@brief		Set an event handler for the historyChanged event.
*/
WV2_API bool wv2setHistoryChangedHandler(wv2_t w, historyChanged handler);     

/*
@brief		Set an event handler for the navigationStarting event.
*/
WV2_API bool wv2setNavigationStartingHandler(wv2_t w, navigationStarting handler);

/*
@brief		Set an event handler for the navigationCompleted event.
*/
WV2_API bool wv2setNavigationCompletedHandler(wv2_t w, navigationCompleted handler);

/*
@brief		Set an event handler for the domContentLoaded event.
*/
WV2_API bool wv2setDomContentLoadedHandler(wv2_t w, domContentLoaded handler);

/*
@brief		Set an event handler for the windowCloseRequested event.
*/
WV2_API bool wv2setWindowCloseRequestedHandler(wv2_t w, windowCloseRequested handler);

/*
@brief		Set an event handler for the webMessageReceived event.
 */
WV2_API bool wv2setWebMessageReceivedHandler(wv2_t w, webMessageReceived handler);

/*
@brief		Set an event handler for the isMutedChanged event.
*/
WV2_API bool wv2setIsMutedChangedHandler(wv2_t w, isMutedChanged handler);

/*
@brief		Set an event handler for the isDocumentPlayingAudioChanged event.
*/
WV2_API bool wv2setIsDocumentPlayingAudioChangedHandler(wv2_t w, 
	isDocumentPlayingAudioChanged handler);

/*
@brief		Set an event handler for the newWindowRequested event.
*/
WV2_API wv2bool wv2setNewWindowRequestedHandler(wv2_t w, newWindowRequested handler);

/*
@brief		Set an event handler for the documentTitleChanged event.
*/
WV2_API wv2bool wv2setDocumentTitleChangedHandler(wv2_t w, documentTitleChanged handler);

/*
@brief		Set an event handler for the contentLoading event.
*/
WV2_API wv2bool wv2setContentLoadingHandler(wv2_t w, contentLoading handler);

/*
@brief		Set an event handler for the scriptDialogOpening event.
 */
WV2_API wv2bool wv2setScriptDialogOpningHandler(wv2_t w, scriptDialogOpening handler);

/*		
@brief		Stop all navigations and pending resource fetches. Does not stop scripts.
*/
WV2_API bool wv2stop(wv2_t w);

/*
@brief     Get or set the zoom factor for the WebView.
@param     w,	The handle to the wv2 instance.
@param     newZoomFactor,	The new value for the zoom factor.
@return    The current zoom factor. Returns -1 if get/set operation fails.
*/
WV2_API double wv2zoomFactor(wv2_t w, const double* newZoomFactor);

/*
@brief     Get the mute status of the WebView.
@param     wv2_t w      The handle to the wv2.
@return    A wv2bool indicating whether the WebView is muted.
@remark    Minimum WebView2 SDK version required: 1.0.1072.54
*/
WV2_API wv2bool wv2isMuted(wv2_t w);

/*
@brief     Set the mute status of the WebView.
@param     wv2_t w      The handle to the wv2.
@param     muted        The new mute status to be set.
@return    A wv2bool indicating the success or failure of the operation.
@remark    Minimum WebView2 SDK version required: 1.0.1072.54
*/
WV2_API wv2bool wv2setIsMuted(wv2_t w, const bool muted);

/*
@brief     Check if the WebView is currently playing audio.
@param     wv2_t w      The handle to the wv2.
@return    A wv2bool indicating whether the WebView is playing audio.
@remark    Minimum WebView2 SDK version required: 1.0.1072.54
*/
WV2_API wv2bool wv2isDocumentPlayingAudio(wv2_t w);

/*
@brief		Opens the Browser Task Manager view as a new window in the foreground.
@param		wv2_t w      The handle to the wv2.
@return		
@remark		Minimum WebView2 SDK version required: 1.0.992.28
*/
WV2_API wv2bool wv2openTaskManagerWindow(wv2_t w);

/*
@brief		Gets the title for the current top-level document.
@param		wv2_t w      The handle to the wv2.
@return		
@note       The returned LPCWSTR must be freed using wv2freeMemory after use.
*/
WV2_API LPCWSTR wv2documentTitle(wv2_t w);

WV2_API HRESULT wv2lastError(wv2_t w);

#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
struct wv2env {
	virtual ~wv2env() {};

	virtual wv2bool setBrowserProcessExitedHandler(browserProcessExited handler) = 0;
};

struct wv2deferral {
	virtual ~wv2deferral() {};

	virtual HRESULT complete() = 0;
};

struct wv2settings {
	virtual wv2bool isScriptEnabled() = 0;
	virtual wv2bool setIsScriptEnabled(bool isScriptEnabled) = 0;
	virtual wv2bool isWebMessageEnabled() = 0;
	virtual wv2bool setIsWebMessageEnabled(bool isWebMessageEnabled) = 0;
	virtual wv2bool areDefaultScriptDialogsEnabled() = 0;
	virtual wv2bool setAreDefaultScriptDialogsEnabled(bool areDefaultScriptDialogsEnabled) = 0;
	virtual wv2bool isStatusBarEnabled() = 0;
	virtual wv2bool setIsStatusBarEnabled(bool isStatusBarEnabled) = 0;
	virtual wv2bool areDevToolsEnabled() = 0;
	virtual wv2bool setAreDevToolsEnabled(bool areDevToolsEnabled) = 0;
	virtual wv2bool areDefaultContextMenusEnabled() = 0;
	virtual wv2bool setAreDefaultContextMenusEnabled(bool enabled) = 0;
	virtual wv2bool areHostObjectsAllowed() = 0;
	virtual wv2bool setAreHostObjectsAllowed(bool allowed) = 0;
	virtual wv2bool isZoomControlEnabled() = 0;
	virtual wv2bool setIsZoomControlEnabled(bool enabled) = 0;
	virtual wv2bool isBuiltInErrorPageEnabled() = 0;
	virtual wv2bool setIsBuiltInErrorPageEnabled(bool enabled) = 0;
};

struct wv2newWindowRequestedEventArgs {
	virtual LPWSTR uri() = 0;
	virtual bool handled() = 0;
	virtual wv2bool setHandled(bool handled) = 0;
	virtual bool isUserInitiated() = 0;
};

struct wv2domContentLoadedEventArgs {
	virtual uint64_t navigationId() = 0;
};

struct wv2contentLoadingEventArgs {
	virtual bool isErrorPage() = 0;
	virtual uint64_t navigationId() = 0;
};

struct wv2scriptDialogOpeningEventArgs {
	virtual ~wv2scriptDialogOpeningEventArgs() {};
	virtual LPWSTR uri() = 0;
	virtual wv2scriptDialogKind kind() = 0;
	virtual LPWSTR message() = 0;
	virtual HRESULT accept() = 0;
	virtual LPWSTR defaultText() = 0;
	virtual LPWSTR resultText() = 0;
	virtual HRESULT setResultText(LPCWSTR resultText) = 0;
	virtual wv2deferral* deferral() = 0;
};


struct wv2 {
	virtual ~wv2(){};
	virtual void destroy() = 0;
	virtual void detach() = 0;

	virtual wv2settings* getSettings() = 0;
	
	virtual bool executeScript(LPCWSTR script, executeScriptCompleted handler) = 0;
	virtual LPCWSTR executeScriptSync(LPCWSTR script) = 0;
	virtual LPCWSTR getSource() = 0;
	virtual bool goBack() = 0;
	virtual bool goForward() = 0;
	virtual bool navigate(const wchar_t* url) = 0;
	virtual bool navigateToString(const wchar_t* html) = 0;
	virtual bool reload() = 0;
	virtual bool resize(int width, int height) = 0;

	virtual bool setHistoryChangedHandler(historyChanged handler) = 0;
	virtual bool setNavigationStartingHandler(navigationStarting handler) = 0;
	virtual bool setNavigationCompletedHandler(navigationCompleted handler) = 0;
	virtual bool setDomContentLoadedHandler(domContentLoaded handler) = 0;
	virtual bool setWindowCloseRequestedHandler(windowCloseRequested handler) = 0;
	virtual bool setWebMessageReceivedHandler(webMessageReceived handler) = 0;

	virtual bool postWebMessageAsJson(LPCWSTR messageAsJson) = 0;
	virtual bool postWebMessageAsString(LPCWSTR messageAsString) = 0;

	virtual bool stop() = 0;
	virtual double zoomFactor(const double* newZoomFactor) = 0;

	virtual void* getUserData() = 0;
	virtual bool setUserData(void* userData) = 0;

	virtual bool setVirtualHostNameToFolderMapping(LPCWSTR hostName, 
		LPCWSTR folderPath, wv2HostResourceAccessKind accessKind) = 0;
	virtual void freeMemory(void* p) = 0;

	virtual bool navigateWithWebResource(LPCWSTR uri, LPCWSTR method,
		BYTE* postData, size_t byteSize, LPCWSTR headers) = 0;

	virtual bool setIsMutedChangedHandler(isMutedChanged handler) = 0;

	virtual wv2bool isMuted() = 0;
	virtual wv2bool setIsMuted(const bool muted) = 0;

	virtual bool setIsDocumentPlayingAudioChangedHandler(
		isDocumentPlayingAudioChanged handler) = 0;

	virtual wv2bool isDocumentPlayingAudio() = 0;
	virtual wv2bool openTaskManagerWindow() = 0;

	virtual wv2env* getEnvironment() = 0;

	virtual wv2bool setNewWindowRequestedHandler(newWindowRequested handler) = 0;
	virtual wv2bool setDocumentTitleChangedHandler(documentTitleChanged handler) = 0;
	virtual wv2bool setContentLoadingHandler(contentLoading handler) = 0;

	virtual LPCWSTR documentTitle() = 0;
	virtual wv2bool setScriptDialogOpeningHandler(scriptDialogOpening handler) = 0;
};
#endif // __cplusplus


#endif // WEBVIEW2_C_WRAPPER_H_
