#ifndef MYPLUGIN8_H
#define MYPLUGIN8_H

// we include stdio.h only to use the sprintf() function
// we define _CRT_SECURE_NO_WARNINGS for the warnings of the sprintf() function
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#include "vdjOnlineSource.h"

class CMyPlugin8 : public IVdjPluginOnlineSource
{
public:
    HRESULT VDJ_API OnGetPluginInfo(TVdjPluginInfo8* infos) override;
    HRESULT VDJ_API OnSearch(const char* search, IVdjTracksList* tracksList) override;
    HRESULT VDJ_API OnSearchCancel() override;
    HRESULT VDJ_API GetStreamUrl(const char* uniqueId, IVdjString& url, IVdjString& errorMessage) override;
    HRESULT VDJ_API GetContextMenu(const char* uniqueId, IVdjContextMenu* contextMenu) override;
    HRESULT VDJ_API OnContextMenu(const char* uniqueId, size_t menuIndex) override;
};

#endif
