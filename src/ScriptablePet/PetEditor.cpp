#include "ScriptablePet/PetEditor.h"

#include "Core/Engine.h"

#include "ScriptablePet/ScriptablePetSubsystem.h"

#include "ScriptablePet/Actions/SetBooleanAction.h"
#include "ScriptablePet/Conditions/IsBooleanEqualCondition.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>

auto g_PetEditor_Decl = ClassDecl<PetEditor>()
    .Super<Editor>()
    .Constructible()
    .Destructible();

void PetEditor::OnRender()
{
    ScriptablePetSubsystem* petSubsystem = Engine::GetApplication()->GetSubsystem<ScriptablePetSubsystem>();
    if (petSubsystem == nullptr)
    {
        ImGui::Text("ScriptablePetSubsystem missing from the Application...");
        return;
    }
    ScriptablePet& pet = petSubsystem->GetPet();

    if (ImGui::CollapsingHeader("Rules", ImGuiTreeNodeFlags_DefaultOpen))
    {
        for (PetRule* rule : pet.GetRules())
        {
            ImGui::Indent(16.0f);
            RenderPetRule(rule);
            ImGui::Unindent(16.0f);
        }
    }
}

void PetEditor::RenderPetRule(PetRule* rule)
{
    if (ImGui::CollapsingHeader(rule->GetName().c_str()))
    {
        ImGui::PushID(rule);
        ImGui::Columns(2);
        for (size_t index = 0; index < std::max(rule->GetConditions().size(), rule->GetActions().size()); ++index)
        {
            if (index < rule->GetConditions().size())
            {
                PetCondition* condition = rule->GetConditions()[index];
                ImGui::PushID(condition);
                RenderPetCondition(condition);
                ImGui::PopID();
            }
            ImGui::NextColumn();
            if (index < rule->GetActions().size())
            {
                PetAction* action = rule->GetActions()[index];
                ImGui::PushID(action);
                RenderPetAction(action);
                ImGui::PopID();
            }
            ImGui::NextColumn();
        }

        //TODO : Replace with actual Popup
        if (ImGui::Button("Add PetCondition..."))
        {
            rule->AddCondition(new IsBooleanEqualCondition);
        }
        
        ImGui::NextColumn();
        //TODO : Replace with actual Popup
        if (ImGui::Button("Add PetAction..."))
        {
            rule->AddAction(new SetBooleanAction);
        }
        ImGui::NextColumn();
        ImGui::Columns();
        ImGui::PopID();
    }
}

void PetEditor::RenderPetAction(PetAction* action)
{
    ImGui::Text("PetAction has no renderer yet !");
}

void PetEditor::RenderPetCondition(PetCondition* condition)
{
    ImGui::Text("PetCondition has no renderer yet !");
}