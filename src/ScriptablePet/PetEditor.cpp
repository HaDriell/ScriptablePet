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
        if (ImGui::BeginTable("##Rules", 4))
        {
            ImGui::TableSetupColumn("+/-", ImGuiTableColumnFlags_WidthFixed, 24);
            ImGui::TableSetupColumn("Name");
            ImGui::TableSetupColumn("Conditions");
            ImGui::TableSetupColumn("Actions");
            ImGui::TableHeadersRow();

            PetRule* removedRule { nullptr };
            for (uint32_t i = 0; i < pet.GetRules().size(); ++i)
            {
                PetRule* rule = pet.GetRules()[i];
                ImGui::PushID(i);

                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ImGui::Button("-"))
                {
                    removedRule = rule;
                }

                ImGui::TableNextColumn();
                ImGui::InputText("##RuleName", &rule->GetName());
                
                ImGui::TableNextColumn();
                // Conditions
                ImGui::Text("%llu Conditions", rule->GetConditions().size());

                ImGui::TableNextColumn();
                // Actions
                ImGui::Text("%llu Action", rule->GetActions().size());

                ImGui::PopID();
            }
            pet.RemoveRule(removedRule);

            //Footer Row for Rule creation
            {            
                ImGui::TableNextRow();
                ImGui::TableNextColumn();
                if (ImGui::Button("+"))
                {
                    PetRule* rule = new PetRule();
                    rule->SetName("New Rule");
                    pet.AddRule(rule);
                }
                ImGui::TableNextColumn();
                ImGui::TableNextColumn();
                ImGui::TableNextColumn();
            }

            ImGui::EndTable();
        }
    }
}
