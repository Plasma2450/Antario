#include "Hooks.h"
#include "SDK\IClientMode.h"
#include "Utils\Utils.h"

std::unique_ptr<Hooks> g_pHooks;

void Hooks::Init()
{
    g_pHooks = std::make_unique<Hooks>();

    // Get interfaces
    g_pInterfaces->Init();  

    // D3D Device pointer
    auto d3dDevice = **(uint32_t**)(g_pUtils->FindSignature("shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C") + 1);

    // VMTHooks
    //g_pHooks->pD3DDevice9Hook = std::make_unique<VMTHook>(reinterpret_cast<void*>(d3dDevice));
    g_pHooks->pClientModeHook = std::make_unique<VMTHook>(g_pClientMode);
    g_pHooks->pClientModeHook->Hook(24, (void*)Hooks::CreateMove);
}

bool __stdcall Hooks::CreateMove(float sample_input_frametime, CUserCmd* cmd)
{
    g_pHooks->pClientModeHook->GetOriginal<CreateMove_t>(24);

    if (!cmd || cmd->command_number == 0)
        return false;

    // call shit

    return false;
}