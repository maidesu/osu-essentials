#include "BlockDomain.hpp"

#include <netfw.h>
#include <atlbase.h>
#include <shlobj_core.h>

#include "FindProcess.hpp"

namespace osuessentials::util {

bool BlockDomainOut()
{
    INetFwPolicy2* policy = NULL;
    INetFwRule* rule = NULL;
    INetFwRules* rules = NULL;

    if (FAILED(CoInitializeEx(0, COINIT_APARTMENTTHREADED)))
    {
        return false;
    }

    if (FAILED(CoCreateInstance(__uuidof(NetFwPolicy2), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwPolicy2), (void**)&policy)))
    {
        CoUninitialize();

        return false;
    }

    if (FAILED(CoCreateInstance(__uuidof(NetFwRule), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwRule), (void**)&rule)))
    {
        policy->Release();
        CoUninitialize();

        return false;
    }

    if (FAILED(policy->get_Rules(&rules)))
    {
        rule->Release();
        policy->Release();
        CoUninitialize();

        return false;
    }

    rules->Remove(CComBSTR(L"DoNotSubmitOsu"));

    PWSTR localAppDataPath = NULL;
    if (FAILED(SHGetKnownFolderPath(FOLDERID_LocalAppData, 0, NULL, &localAppDataPath)))
    {
        rule->Release();
        policy->Release();
        CoUninitialize();

        return false;
    }

    WCHAR path[MAX_PATH];
    PathCombine(path, localAppDataPath, L"osu!\\osu!.exe");

    rule->put_Name(CComBSTR(L"DoNotSubmitOsu"));
    rule->put_Description(CComBSTR(L"Block score submissions"));
    rule->put_Action(NET_FW_ACTION_BLOCK);
    rule->put_Direction(NET_FW_RULE_DIR_OUT);
    rule->put_Protocol(NET_FW_IP_PROTOCOL_ANY);
    rule->put_ApplicationName(CComBSTR(path));
    rule->put_Enabled(VARIANT_TRUE);

    CoTaskMemFree(localAppDataPath);

    if (FAILED(rules->Add(rule)))
    {
        rules->Release();
        rule->Release();
        policy->Release();
        CoUninitialize();

        return false;
    }

    rules->Release();
    rule->Release();
    policy->Release();
    CoUninitialize();

    return true;
}

bool UnBlockDomainOut()
{
    INetFwPolicy2* policy = NULL;
    INetFwRule* rule = NULL;
    INetFwRules* rules = NULL;

    if (FAILED(CoInitializeEx(0, COINIT_APARTMENTTHREADED)))
    {
        return false;
    }

    if (FAILED(CoCreateInstance(__uuidof(NetFwPolicy2), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwPolicy2), (void**)&policy)))
    {
        CoUninitialize();

        return false;
    }

    if (FAILED(CoCreateInstance(__uuidof(NetFwRule), NULL, CLSCTX_INPROC_SERVER, __uuidof(INetFwRule), (void**)&rule)))
    {
        policy->Release();
        CoUninitialize();

        return false;
    }

    if (FAILED(policy->get_Rules(&rules)))
    {
        rule->Release();
        policy->Release();
        CoUninitialize();

        return false;
    }

    rules->Remove(CComBSTR(L"DoNotSubmitOsu"));

    rules->Release();
    rule->Release();
    policy->Release();
    CoUninitialize();

    return true;
}

} // namespace osuessentials::util
