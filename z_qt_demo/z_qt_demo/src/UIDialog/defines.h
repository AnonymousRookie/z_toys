#pragma once

#define WIDGET_WIDTH  1100
#define WIDGET_HEIGHT 680

#define TITLE_HEIGHT 64

#define MARGIN 10


enum Language
{
    Language_ZH,
    Language_EN,
};

enum FunctionType
{
    FunctionType_Invalid = 0,
    FunctionType_Buttons = 1000,        // Buttons
    FunctionType_ItemViews = 1001,      // Item Views
    FunctionType_ItemWidgets = 1002,    // Item Widgets
    FunctionType_InputWidgets = 1003,   // Input Widgets
    FunctionType_DisplayWidgets = 1004, // Display Widgets
    FunctionType_Others1 = 1005,
    FunctionType_Others2 = 1006,
    FunctionType_Others3 = 1007,
};

