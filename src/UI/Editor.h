#pragma once

#include "Core/Reflection/Reflection.h"
#include "UI/MenuItem.h"
#include "UI/Widget.h"

class Editor : public Widget
{
public:
    const ClassDescriptor* GetClassDescriptor() const override { return ClassDescriptor::Get<Editor>(); }

    Editor();

    virtual std::string_view GetEditorPath() const;
    virtual std::string_view GetEditorName() const;
};

class EditorMenuItem : public MenuItem
{
public:
    EditorMenuItem(Editor* editor);
    ~EditorMenuItem();

    void AddToMenuBar();
    void RemoveFromMenuBar();

    void OnClick() override;

    Editor* GetEditor() const { return m_Editor; }

private:
    Editor* m_Editor;
};