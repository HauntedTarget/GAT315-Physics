/*******************************************************************************************
*
*   LayoutName v1.0.0 - Tool Description
*
*   LICENSE: Propietary License
*
*   Copyright (c) 2022 raylib technologies. All Rights Reserved.
*
*   Unauthorized copying of this file, via any medium is strictly prohibited
*   This project is proprietary and confidential unless the owner allows
*   usage in any other form by expresely written permission.
*
**********************************************************************************************/

//#include "raylib.h"
//
//#define RAYGUI_IMPLEMENTATION
//#include "raygui.h"

//----------------------------------------------------------------------------------
// Controls Functions Declaration
//----------------------------------------------------------------------------------


//------------------------------------------------------------------------------------
// Program main entry point
//------------------------------------------------------------------------------------
//int main()
//{
//    // Initialization
//    //---------------------------------------------------------------------------------------
//    int screenWidth = 800;
//    int screenHeight = 450;
//
//    InitWindow(screenWidth, screenHeight, "layout_name");
//
//    // layout_name: controls initialization
//    //----------------------------------------------------------------------------------
//    bool WindowBox000Active = true;
//    bool DropdownBox002EditMode = false;
//    int DropdownBox002Active = 0;
//    float SliderBar005Value = 0.0f;
//    float SliderBar004Value = 0.0f;
//    float SliderBar005Value = 0.0f;
//    float SliderBar006Value = 0.0f;
//    float SliderBar007Value = 0.0f;
//    float SliderBar019Value = 0.0f;
//    float SliderBar020Value = 0.0f;
//    float SliderBar021Value = 0.0f;
//    //----------------------------------------------------------------------------------
//
//    SetTargetFPS(60);
//    //--------------------------------------------------------------------------------------
//
//    // Main game loop
//    while (!WindowShouldClose())    // Detect window close button or ESC key
//    {
//        // Update
//        //----------------------------------------------------------------------------------
//        // TODO: Implement required update logic
//        //----------------------------------------------------------------------------------
//
//        // Draw
//        //----------------------------------------------------------------------------------
//        BeginDrawing();
//
//            ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR))); 
//
//            // raygui: controls drawing
//            //----------------------------------------------------------------------------------
//            if (DropdownBox002EditMode) GuiLock();
//
//            if (WindowBox000Active)
//            {
//                WindowBox000Active = !GuiWindowBox((Rectangle){ 896, 64, 200, 648 }, "Editor");
//                GuiLabel((Rectangle){ 1024, 280, 32, 16 }, "[num]");
//                GuiLabel((Rectangle){ 1024, 248, 32, 16 }, "[num]");
//                GuiLabel((Rectangle){ 1024, 216, 32, 12 }, "[num]");
//                GuiLabel((Rectangle){ 1024, 184, 32, 16 }, "[num]");
//                GuiLabel((Rectangle){ 1024, 152, 32, 16 }, "[num]");
//            }
//            GuiGroupBox((Rectangle){ 912, 72, 168, 248 }, "Body");
//            GuiSliderBar((Rectangle){ 936, 200, 120, 16 }, NULL, NULL, &SliderBar005Value, 0, 100);
//            GuiSliderBar((Rectangle){ 936, 136, 120, 16 }, NULL, NULL, &SliderBar004Value, 0, 100);
//            GuiSliderBar((Rectangle){ 936, 168, 120, 16 }, NULL, NULL, &SliderBar005Value, 0, 100);
//            GuiSliderBar((Rectangle){ 936, 232, 120, 16 }, NULL, NULL, &SliderBar006Value, 0, 100);
//            GuiSliderBar((Rectangle){ 936, 264, 120, 16 }, NULL, NULL, &SliderBar007Value, 0, 100);
//            GuiLabel((Rectangle){ 936, 152, 48, 16 }, "Mass");
//            GuiLabel((Rectangle){ 936, 184, 64, 16 }, "Damping");
//            GuiLabel((Rectangle){ 936, 216, 80, 16 }, "Gravity Scale");
//            GuiLabel((Rectangle){ 936, 248, 56, 16 }, "Stiffness");
//            GuiLabel((Rectangle){ 936, 280, 64, 16 }, "Restitution");
//            GuiGroupBox((Rectangle){ 912, 368, 168, 280 }, "World");
//            GuiSliderBar((Rectangle){ 936, 408, 120, 16 }, NULL, NULL, &SliderBar019Value, 0, 100);
//            GuiSliderBar((Rectangle){ 936, 448, 120, 16 }, NULL, NULL, &SliderBar020Value, 0, 100);
//            GuiSliderBar((Rectangle){ 936, 488, 120, 16 }, NULL, NULL, &SliderBar021Value, 0, 100);
//            GuiLabel((Rectangle){ 936, 424, 120, 24 }, "Gravety");
//            GuiLabel((Rectangle){ 936, 464, 120, 24 }, "Gravitation");
//            GuiLabel((Rectangle){ 936, 504, 120, 24 }, "Time Step");
//            if (GuiDropdownBox((Rectangle){ 936, 96, 120, 24 }, "DYNAMIC;KINEMATIC;STATIC", &DropdownBox002Active, DropdownBox002EditMode)) DropdownBox002EditMode = !DropdownBox002EditMode;
//            
//            GuiUnlock();
//            //----------------------------------------------------------------------------------
//
//        EndDrawing();
//        //----------------------------------------------------------------------------------
//    }
//
//    // De-Initialization
//    //--------------------------------------------------------------------------------------
//    CloseWindow();        // Close window and OpenGL context
//    //--------------------------------------------------------------------------------------
//
//    return 0;
//}

//------------------------------------------------------------------------------------
// Controls Functions Definitions (local)
//------------------------------------------------------------------------------------

