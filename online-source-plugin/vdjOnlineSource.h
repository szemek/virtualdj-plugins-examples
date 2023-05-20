//////////////////////////////////////////////////////////////////////////
//
// VirtualDJ
// Plugin SDK
// (c)Atomix Productions 2021
//
//////////////////////////////////////////////////////////////////////////
//
// This file defines online source plugins, that can implement new online content providers.
// It inherits from the base IVdjPlugin class, and defines these additional functions and variables:
//
//////////////////////////////////////////////////////////////////////////

#ifndef VdjOnlineSourceH
#define VdjOnlineSourceH

#include "vdjPlugin8.h"

//////////////////////////////////////////////////////////////////////////
// data types

struct IVdjString
{
    virtual void VDJ_API operator=(const char*) = 0;
};

struct IVdjTracksList
{
    virtual void VDJ_API add(
        const char* uniqueId, // assign a string that uniquely identify this track in your system
        const char* title,
        const char* artist,
        const char* remix = 0,
        const char* genre = 0,
        const char* label = 0,
        const char* comment = 0,
        const char* coverUrl = 0, // if available, set a http url of an image to display for this track
        const char* streamUrl = 0, // you would usually leave this empty, and provide the information when a song is loaded from getStreamUrl
        float length = 0, // in seconds
        float bpm = 0,
        int key = 0, // 1=Am, 2=A#m, ..., 24=G#
        int year = 0,
        bool isVideo = 0,
        bool isKaraoke = 0
    ) = 0;

    // by default, OnSearch can be used as a synchronous blocking call.
    // if you want to implement as an asynchronous operation, return S_FALSE in OnSearch, and call tracksList->finish() when you're finished.
    virtual void VDJ_API finish() = 0;
};

struct IVdjSubfoldersList
{
    virtual void VDJ_API add(const char* folderUniqueId, const char* folderName = 0) = 0;
};

struct IVdjContextMenu
{
    virtual void VDJ_API add(const char* menuEntry) = 0;
};

struct IVdjOAuth
{
    // if your login uses OAuth2, you can use this to facilitate the operation.
    // call oauth->open() with your authorize url, and implement OnOAuth() to monitor the results.
    // if your authorization flow requires to exchange a code for a token, call getToken() from OnOAuth() if code!=null.
    // calls to getToken() or refreshToken() will also cause OnOAuth() to be called.
    virtual void VDJ_API open(const char* authorizeUrl) = 0; // open will add response_type=, redirect_uri= and state= to the authorizeUrl. anything else should be added beforehand to the url.
    virtual void VDJ_API getToken(const char* code, const char* tokenUrl, const char* tokenPost = 0) = 0; // getToken will POST code=, grant_type= and redirect_uri=. anything else should be added in tokenPost.
    virtual void VDJ_API refreshToken(const char* refresh_token, const char* tokenUrl, const char* tokenPost = 0) = 0; // refreshToken will POST code= and grant_type=. anything else should be added in tokenPost.
};

//////////////////////////////////////////////////////////////////////////
// VideoFolder plugin class

class IVdjPluginOnlineSource : public IVdjPlugin8
{
public:
    // implement this to handle login your users in and out
    virtual HRESULT VDJ_API IsLogged() { return E_NOTIMPL; } // return S_OK if the user is logged in, S_FALSE if he's not, or E_NOTIMPL if you don't need virtualdj to handle login
    virtual HRESULT VDJ_API OnLogin() { return E_NOTIMPL; }
    virtual HRESULT VDJ_API OnLogout() { return E_NOTIMPL; }
    IVdjOAuth *oauth;
    virtual HRESULT VDJ_API OnOAuth(const char *access_token, size_t access_token_expire, const char* refresh_token, const char* code, const char* errorMessage) { return E_NOTIMPL; }

    // when the user type something in the search field, this function will be called. call tracksList->add(...) for each tracks from your search results.
    virtual HRESULT VDJ_API OnSearch(const char* search, IVdjTracksList* tracksList) = 0;
    // your onSearch function can take a long time to return. If the user cancel or do a new search in the meantime, we will call this function so you can unblock and return faster from onSearch without finishing
    virtual HRESULT VDJ_API OnSearchCancel() { return E_NOTIMPL; }
    // if you didn't populate the streamUrl fields in tracksList, this function will be called per-track when the user loads a track onto a deck
    virtual HRESULT VDJ_API GetStreamUrl(const char* uniqueId, IVdjString& url, IVdjString& errorMessage) { return E_NOTIMPL; };

    // if you have subfolders, list them here
    virtual HRESULT VDJ_API GetFolderList(IVdjSubfoldersList* subfoldersList) { return E_NOTIMPL; }
    // and this function will be called when the user browses a subfolder
    virtual HRESULT VDJ_API GetFolder(const char* folderUniqueId, IVdjTracksList* tracksList) { return E_NOTIMPL; }

    // if you want to implement extended behavior (like offline cache, buy-links, etc), you can add items to the context menu of your tracks or your folders
    virtual HRESULT VDJ_API GetContextMenu(const char* uniqueId, IVdjContextMenu* contextMenu) { return E_NOTIMPL; }
    virtual HRESULT VDJ_API OnContextMenu(const char* uniqueId, size_t menuIndex) { return E_NOTIMPL; }
    virtual HRESULT VDJ_API GetFolderContextMenu(const char* folderUniqueId, IVdjContextMenu* contextMenu) { return E_NOTIMPL; }
    virtual HRESULT VDJ_API OnFolderContextMenu(const char* folderUniqueId, size_t menuIndex) { return E_NOTIMPL; }
};

//////////////////////////////////////////////////////////////////////////
// GUID definitions

#ifndef VDJONLINESOURCEGUID_DEFINED
#define VDJONLINESOURCEGUID_DEFINED
static const GUID IID_IVdjPluginOnlineSource ={ 0x85d20f05, 0xccf, 0x4cab, { 0xaa, 0x50, 0x1c, 0x4, 0xea, 0xb6, 0xb8, 0x5d } };
#else
extern static const GUID IID_IVdjPluginOnlineSource;
#endif

//////////////////////////////////////////////////////////////////////////

#endif