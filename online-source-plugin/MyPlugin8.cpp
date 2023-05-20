#include "MyPlugin8.h"
#include <string>

using namespace std;

HRESULT VDJ_API CMyPlugin8::OnGetPluginInfo(TVdjPluginInfo8* infos)
{
    infos->PluginName = "CMyPlugin8";
    return S_OK;
}

HRESULT VDJ_API CMyPlugin8::OnSearch(const char* search, IVdjTracksList* tracksList)
{
    // string url = "https://api.testprovider.com/search?query=" + Internet::urlencode(search);
    // string html = Internet::downloadString(url);
    // JSON json = JSON::fromString(html);
    // list.reserve(json.children.size());
    // for (const JSON& item : json.children)
    // {
    //     tracksList->add(item.uniqueId.c_str(), item.title.c_str(), item.artist.c_str(), item.remix.c_str(), nullptr, item.label.c_str(), item.comment.c_str(), item.coverUrl.c_str(), nullptr, item.length, 0, 0, 0, true, false);

    // }
    return S_OK;
}

HRESULT VDJ_API CMyPlugin8::OnSearchCancel()
{
    // Internet::closeDownloads();
    return S_OK;
}

HRESULT VDJ_API CMyPlugin8::GetStreamUrl(const char* uniqueId, IVdjString& url, IVdjString& errorMessage)
{
    // string url = "https://api.testprovider.com/getStreamUrl?id=" + Internet::urlencode(uniqueId);
    // string html = Internet::downloadString(url);
    // JSON json = JSON::fromString(html);
    // if (json.hasParam("url"))
    // {
    //     url = json.getParam("url").c_str();
    //     return S_OK;
    // }
    // else
    // {
    //     errorMessage = json.getParam("error").c_str();
    //     return S_FALSE;
    // }

    return S_OK;
}

HRESULT VDJ_API CMyPlugin8::GetContextMenu(const char* uniqueId, IVdjContextMenu* contextMenu)
{
    contextMenu->add("Open in CMyPlugin8");
    return S_OK;
}

HRESULT VDJ_API CMyPlugin8::OnContextMenu(const char* uniqueId, size_t menuIndex)
{
    // if (menuIndex==0)
    // {
    //     string url = "https://www.testprovider.com/" + Internet::urlencode(uniqueId);
    //     Internet::openBrowser(url);
    // }
    return S_OK;
}
