#include "ScriptablePet/PetEditor.h"

#include "Core/Engine.h"

#include "ScriptablePet/ScriptablePetSubsystem.h"

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
        size_t index = 0;
        for (PetRule* rule : pet.GetRules())
        {
            ImGui::PushID(index);
            ImGui::Indent(16.0f);
            RenderPetRule(rule);
            ImGui::Unindent(16.0f);
            ImGui::PopID();
        }
    }
}

void PetEditor::RenderPetRule(PetRule* rule)
{
    if (ImGui::CollapsingHeader(rule->GetName().c_str()))
    {
        ImGui::Indent(16.0f);
        ImGui::PushID(rule);

        if (ImGui::CollapsingHeader("Conditions"))
        {
            size_t index = 0; 
            for (PetCondition* condition : rule->GetConditions())
            {
                ImGui::PushID(index);
                RenderPetCondition(condition);
                ImGui::PopID();
                index++;
            }
            
            //TODO : Options (Popup ?) to create PetConditions
        }

        if (ImGui::CollapsingHeader("Actions"))
        {
            size_t index = 0; 
            for (PetAction* action : rule->GetActions())
            {
                ImGui::PushID(index);
                RenderPetAction(action);
                ImGui::PopID();
                index++;
            }

            //TODO : Options (Popup ?) to create PetActions
        }

        ImGui::PopID();
        ImGui::Unindent(16.0f);
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