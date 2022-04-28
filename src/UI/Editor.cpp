#include "UI/Editor.h"
#include "UI/UISubsystem.h"

auto g_Editor_Decl = ClassDecl<Editor>()
    .Super<Widget>()
    .Destructible();

Editor::Editor()
    : Widget(std::string(GetEditorName()))
{
}

std::string_view Editor::GetEditorPath() const
{
    return "Editors";
}

std::string_view Editor::GetEditorName() const
{
    return GetClassDescriptor()->ClassName;
}

EditorMenuItem::EditorMenuItem(Editor* editor)
    : MenuItem(std::string(editor->GetEditorName()))
    , m_Editor(editor)
{
}

EditorMenuItem::~EditorMenuItem()
{
    if (m_Editor != nullptr)
    {
        delete m_Editor;
    }
}

void EditorMenuItem::AddToMenuBar()
{
    if (UISubsystem* ui = Engine::GetApplication()->GetSubsystem<UISubsystem>())
    {
        ui->AddMenuItem(std::string(m_Editor->GetEditorPath()), this);
        ui->AddWidget(m_Editor);
    }
}

void EditorMenuItem::RemoveFromMenuBar()
{
    if (UISubsystem* ui = Engine::GetApplication()->GetSubsystem<UISubsystem>())
    {
        ui->RemoveWidget(m_Editor);
        ui->RemoveMenuItem(std::string(m_Editor->GetEditorPath()), this);
    }
}

void EditorMenuItem::OnClick()
{
    switch (m_Editor->GetState())
    {
    case Widget::State::Closed:
        m_Editor->Open();
        break;
    case Widget::State::Open:
        m_Editor->Close();
        break;    
    default:
        break;
    }
}
