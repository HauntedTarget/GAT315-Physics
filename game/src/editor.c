#include "editor.h"
#include "Body.h"
#include "render.h"
#define RAYGUI_IMPLEMENTATION
#include "../../raygui/src/raygui.h"

bool ncEditorActive = true;
bool ncEditorIntersect = false;
Rectangle editorRect;
elEditorData_t elEditorData;

Vector2 anchor01 = { 950, 56 };
Texture2D cursorTexture;

bool EditorBoxActive = true;

void InitEditor()
{
    GuiLoadStyle("raygui/styles/cyber/style_cyber.rgs");

    Image reticle = LoadImage("resources/reticle 1.png");
    cursorTexture = LoadTextureFromImage(reticle);
    UnloadImage(reticle);
    HideCursor();

    elEditorData.objectGravity = 2.0f;
    elEditorData.gravitationValue = 0.0f;
    elEditorData.massMinValue = 1.0f;
    elEditorData.massMaxValue = 4.0f;
}

void UpdateEditor(Vector2 position)
{
    //
}

void DrawEditor(Vector2 position)
{
    if (EditorBoxActive)
    {
        EditorBoxActive = !GuiWindowBox((Rectangle) { anchor01.x + 0, anchor01.y + 0, 304, 616 }, "Editor");

        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 80, 120, 16 }, "Mass Min", NULL, & elEditorData.massMinValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 120, 120, 16 }, "Mass Max", NULL, & elEditorData.massMaxValue, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 216, 120, 16 }, "Object Gravity", NULL, & elEditorData.objectGravity, 0, 100);
        GuiSliderBar((Rectangle) { anchor01.x + 80, anchor01.y + 168, 120, 16 }, "World Gravitaty", NULL, & elEditorData.gravitationValue, 0, 100);
    }

    DrawTexture(cursorTexture, (int)position.x - cursorTexture.width / 2, (int)position.y - cursorTexture.height / 2, YELLOW);
}

elBody* GetBodyIntersect(elBody* bodies, Vector2 position)
{
    for (elBody* body = bodies; body; body = body->next)
    {
        Vector2 screen = ConvertWorldToScreen(body->position);
        if (CheckCollisionPointCircle(position, screen, ConvertWorldToPixel(body->mass)))
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