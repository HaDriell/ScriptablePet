#include "ScriptablePet/PetEditor.h"

#include "Core/Engine.h"

#include "ScriptablePet/ScriptablePetSubsystem.h"

#include "ScriptablePet/Actions/SetBooleanAction.h"
#include "ScriptablePet/Conditions/IsBooleanEqualCondition.h"
#include "ScriptablePet/Actions/SetFloatAction.h"
#include "ScriptablePet/Actions/SetIntegerAction.h"
#include "ScriptablePet/Actions/SetStringAction.h"
#include "ScriptablePet/Actions/UndefineAction.h"

#include <imgui.h>
#include <misc/cpp/imgui_stdlib.h>
#include <iostream>

auto g_PetEditor_Decl = ClassDecl<PetEditor>()
    .Super<Editor>()
    .Constructible()
    .Destructible();

template<class BaseClass>
bool SelectClassPopup(const char* name, const ClassDescriptor*& selectedClassDescriptor)
{
    static const ClassDescriptor* selectionCache = nullptr;
    static std::vector<const ClassDescriptor*> classesCache;

    //Populate Cache
    if (classesCache.empty())
    {
        ClassDescriptor::GetDerivedClasses<BaseClass>(classesCache);
    }

    bool unused_open = true;
    if (ImGui::BeginPopupModal(name, &unused_open, ImGuiWindowFlags_AlwaysAutoResize))
    {
        if (ImGui::BeginListBox("Class Selector", ImVec2(300, 10 * ImGui::GetTextLineHeightWithSpacing())))
        {
            for (const ClassDescriptor* classDescriptor : classesCache)
            {
                if (!classDescriptor->IsConstructible()) continue;

                bool selected = selectionCache == classDescriptor;
                if (ImGui::Selectable(std::string(classDescriptor->ClassName).c_str(), &selected))
                {
                    selectionCache = classDescriptor;
                }
            }
            ImGui::EndListBox();
        }

        if (ImGui::Button("Select"))
        {
            selectedClassDescriptor = selectionCache;
            ImGui::CloseCurrentPopup();
        }
        ImGui::SameLine();
        if (ImGui::Button("Cancel"))
        {
            ImGui::CloseCurrentPopup();
        }

        ImGui::EndPopup();
    }

    return selectionCache != nullptr && selectionCache == selectedClassDescriptor;
}

void PetEditor::RenderPetRule(PetRule* rule)
{
    if (ImGui::CollapsingHeader(rule->GetName().c_str()))
    {
        ImGui::PushID(rule);
        ImGui::Columns(2);
        
        ImGui::Separator();
        ImGui::Text("Conditions");
        ImGui::NextColumn();
        ImGui::Text("Actions");
        ImGui::NextColumn();

        for (size_t index = 0; index < std::max(rule->GetConditions().size(), rule->GetActions().size()); ++index)
        {
            ImGui::Separator();
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
        ImGui::Separator();
        ImGui::Columns();

        if (ImGui::Button("New Condition..."))
        {
            ImGui::OpenPopup("Select Condition Class");
        }
        ImGui::SameLine();
        if (ImGui::Button("New Action..."))
        {
            ImGui::OpenPopup("Select Action Class");
        }
        ImGui::SameLine();
        if (ImGui::Button("Delete Rule"))
        {
            ImGui::OpenPopup("Delete Rule");
        }

        // --- Popup Implementations ---

        // New Condition Popup
        { 
            const ClassDescriptor* selectedClass = nullptr;
            if (SelectClassPopup<PetCondition>("Select Condition Class", selectedClass))
            {
                rule->AddCondition(selectedClass->NewInstance()->Cast<PetCondition>());
            }
        }

        // New Action Popup
        {
            const ClassDescriptor* selectedClass = nullptr;
            if (SelectClassPopup<PetAction>("Select Action Class", selectedClass))
            {
                rule->AddAction(selectedClass->NewInstance()->Cast<PetAction>());
            }
        }

        // Delete Rule Popup
        {
            bool open = true;
            if (ImGui::BeginPopupModal("Delete Rule", &open, ImGuiWindowFlags_AlwaysAutoResize))
            {
                ImGui::Text("Are you sure about that ?");

                if (ImGui::Button("OK"))
                {
                    rule->GetOwner()->RemoveRule(rule);
                    ImGui::CloseCurrentPopup();
                }

                if (ImGui::Button("Cancel"))
                {
                    ImGui::CloseCurrentPopup();
                }

                ImGui::EndPopup();
            }
        }

        
        ImGui::PopID();
    }
}

void PetEditor::RenderPetAction(PetAction* baseAction)
{
    if (SetBooleanAction* action = baseAction->Cast<SetBooleanAction>())
    {
        ImGui::InputText("Variable", &action->GetVariable());
        bool value = action->GetValue();
        if (ImGui::Checkbox("Value", &value)) action->SetValue(value);
    }
    else if (SetFloatAction* action = baseAction->Cast<SetFloatAction>())
    {
        ImGui::InputText("Variable", &action->GetVariable());
        float value = action->GetValue(); 
        if (ImGui::InputFloat("Value", &value)) action->SetValue(value);        
    }
    else if (SetIntegerAction* action = baseAction->Cast<SetIntegerAction>())
    {
        ImGui::InputText("Variable", &action->GetVariable());
        int32_t value = action->GetValue(); 
        if (ImGui::InputInt("Value", &value)) action->SetValue(value);        
    }
    else if (SetStringAction* action = baseAction->Cast<SetStringAction>())
    {
        ImGui::InputText("Variable", &action->GetVariable());
        ImGui::InputText("Value", &action->GetValue());
    }
    else
    {
        ImGui::Text("no renderer for %s yet !", std::string(baseAction->GetClassDescriptor()->ClassName).c_str());
    }
}

void PetEditor::RenderPetCondition(PetCondition* condition)
{
    ImGui::Text("PetCondition has no renderer yet !");
}

void PetEditor::OnRender()
{
    ScriptablePetSubsystem* petSubsystem = Engine::GetApplication()->GetSubsystem<ScriptablePetSubsystem>();
    if (petSubsystem == nullptr)
    {
        ImGui::Text("ScriptablePetSubsystem missing from the Application...");
        return;
    }
    ScriptablePet& pet = petSubsystem->GetPet();

    for (PetRule* rule : pet.GetRules())
    {
        ImGui::PushID(rule);
        RenderPetRule(rule);
        ImGui::Separator();
        ImGui::PopID();
    }

    if (ImGui::Button("New Rule"))
    {
        pet.AddRule(new PetRule);
    }
}