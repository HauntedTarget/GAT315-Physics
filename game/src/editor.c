#include "editor.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
elEditorData_t elEditorData;

Vector2 anchor01 = { 950, 56 };

bool EditorBoxActive = true;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

    elEditorData.gravitationValue = 2.0f;
    elEditorData.massMinValue = 0.1f;
    elEditorData.massMaxValue = 1.0f;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor()
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 304, 616 }, "Editor");
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 80, 120, 16 }, "Mass Min", NULL, & elEditorData.massMinValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 120, 120, 16 }, "Mass Max", NULL, & elEditorData.massMaxValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 168, 120, 16 }, "Gravitation", NULL, & elEditorData.gravitationValue, 0, 100);
    }
}
