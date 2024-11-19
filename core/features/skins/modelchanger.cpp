#include "modelchanger.hpp"
#include "source-sdk/sdk.hpp"
#include "../globals.hpp" // Ensure access to ClientStringTableContainer and ModelInfo

bool PrecacheModel(const char* modelName) {
    // Access the model precache table
    auto modelPrecacheTable = ClientStringTableContainer->FindTable("modelprecache");
    if (modelPrecacheTable) {
        // Load the model into memory
        interfaces::model_info->FindOrLoadModel(modelName);

        // Add model to the precache table
        int idx = modelPrecacheTable->AddString(false, modelName);
        return idx != INVALID_STRING_INDEX; // Ensure it's successfully added
    }
    return false;
}

void ChangePlayerModel(C_BasePlayer* player, const char* modelPath) {
    if (!player || !modelPath) return;

    // Precache the desired model
    if (!PrecacheModel(modelPath)) return;

    // Get the model index
    int modelIndex = interfaces::model_info->GetModelIndex(modelPath);
    if (modelIndex == -1) return;

    // Apply the model to the player
    using FnSetModelIndex = void(__thiscall*)(void*, int);
    call_vfunc<FnSetModelIndex>(player, 75)(player, modelIndex);
}

void ModelChanger::apply() {
    auto localPlayer = interfaces::entity_list->GetClientEntity(interfaces::engine->GetLocalPlayer());
    if (!localPlayer) return;

    // Replace with the desired model path
    const char* customModel = "models/player/custom_model.mdl";
    ChangePlayerModel(localPlayer, customModel);
}
