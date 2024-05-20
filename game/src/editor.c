#include "editor.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
elEditorData_t elEditorData;

Vector2 anchor01 = { 950, 56 };
Texture2D cursorTexture;

bool EditorBoxActive = true,
typeDropDownActive = false;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

    Image reticle = LoadImage("resources/reticle 1.png");
    cursorTexture = LoadTextureFromImage(reticle);
    UnloadImage(reticle);
    HideCursor();

    elEditorData.objectGravity = 2.0f;
    elEditorData.gravitationValue = 0.0f;
    elEditorData.massValue = 4.0f;
    elEditorData.resitution = 1.0f;
    elEditorData.dampening = 0.0f;
    elEditorData.stiffness = 20.0f;

    elEditorData.selectedType = DYNAMIC;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { 896, 64, 200, 648 }, "Editor");
    }
    GuiGroupBox((Rectangle) { 912, 72, 168, 248 }, "Body");
    GuiSliderBar((Rectangle) { 936, 200, 120, 16 }, "Mass", TextFormat("%0.2f", elEditorData.massValue), & elEditorData.massValue, 0, 100);
    GuiSliderBar((Rectangle) { 936, 136, 120, 16 }, "Damping", TextFormat("%0.2f", elEditorData.dampening), & elEditorData.dampening, 0, 100);
    GuiSliderBar((Rectangle) { 936, 168, 120, 16 }, "Gravity Scale", TextFormat("%0.2f", elEditorData.objectGravity), & elEditorData.objectGravity, 0, 100);
    GuiSliderBar((Rectangle) { 936, 232, 120, 16 }, "Stiffness", TextFormat("%0.2f", elEditorData.stiffness), & elEditorData.stiffness, 0, 100);
    GuiSliderBar((Rectangle) { 936, 264, 120, 16 }, "Restitution", TextFormat("%0.2f", elEditorData.resitution), & elEditorData.resitution, 0, 100);

    GuiSliderBar((Rectangle) { 936, 448, 120, 16 }, "Gravitation", TextFormat("%0.2f", elEditorData.gravitationValue), & elEditorData.gravitationValue, 0, 100);
    //GuiSliderBar((Rectangle) { 936, 488, 120, 16 }, "Time Step", NULL, & SliderBar021Value, 0, 100);

    if (GuiDropdownBox((Rectangle) { 936, 96, 120, 24 }, "DYNAMIC;KINEMATIC;STATIC", &elEditorData.selectedType, typeDropDownActive)) typeDropDownActive = !typeDropDownActive;

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}

elBody* GetBodyIntersect(elBody* bodies, Vector2 position)
{
    for (elBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass * 0.5f)))
        {
            return body;
        }
    }

    return NULL;
}

void DrawLineBodyToPosition(elBody* body, Vector2 position)
{
    Vector2 screen = ConvertWorldToScreen(body->position);
    DrawLine((int)screen.x, (int)screen.y, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}