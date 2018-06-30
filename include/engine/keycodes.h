#ifndef KEYCODES_H
#define KEYCODES_H

#ifndef _glfw3_h_

/* The unknown key */
#define GLFW_KEY_UNKNOWN            -1

/* Printable keys */
#define GLFW_KEY_SPACE              32
#define GLFW_KEY_APOSTROPHE         39  /* ' */
#define GLFW_KEY_COMMA              44  /* , */
#define GLFW_KEY_MINUS              45  /* - */
#define GLFW_KEY_PERIOD             46  /* . */
#define GLFW_KEY_SLASH              47  /* / */
#define GLFW_KEY_0                  48
#define GLFW_KEY_1                  49
#define GLFW_KEY_2                  50
#define GLFW_KEY_3                  51
#define GLFW_KEY_4                  52
#define GLFW_KEY_5                  53
#define GLFW_KEY_6                  54
#define GLFW_KEY_7                  55
#define GLFW_KEY_8                  56
#define GLFW_KEY_9                  57
#define GLFW_KEY_SEMICOLON          59  /* ; */
#define GLFW_KEY_EQUAL              61  /* = */
#define GLFW_KEY_A                  65
#define GLFW_KEY_B                  66
#define GLFW_KEY_C                  67
#define GLFW_KEY_D                  68
#define GLFW_KEY_E                  69
#define GLFW_KEY_F                  70
#define GLFW_KEY_G                  71
#define GLFW_KEY_H                  72
#define GLFW_KEY_I                  73
#define GLFW_KEY_J                  74
#define GLFW_KEY_K                  75
#define GLFW_KEY_L                  76
#define GLFW_KEY_M                  77
#define GLFW_KEY_N                  78
#define GLFW_KEY_O                  79
#define GLFW_KEY_P                  80
#define GLFW_KEY_Q                  81
#define GLFW_KEY_R                  82
#define GLFW_KEY_S                  83
#define GLFW_KEY_T                  84
#define GLFW_KEY_U                  85
#define GLFW_KEY_V                  86
#define GLFW_KEY_W                  87
#define GLFW_KEY_X                  88
#define GLFW_KEY_Y                  89
#define GLFW_KEY_Z                  90
#define GLFW_KEY_LEFT_BRACKET       91  /* [ */
#define GLFW_KEY_BACKSLASH          92  /* \ */
#define GLFW_KEY_RIGHT_BRACKET      93  /* ] */
#define GLFW_KEY_GRAVE_ACCENT       96  /* ` */
#define GLFW_KEY_WORLD_1            161 /* non-US #1 */
#define GLFW_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define GLFW_KEY_ESCAPE             256
#define GLFW_KEY_ENTER              257
#define GLFW_KEY_TAB                258
#define GLFW_KEY_BACKSPACE          259
#define GLFW_KEY_INSERT             260
#define GLFW_KEY_DELETE             261
#define GLFW_KEY_RIGHT              262
#define GLFW_KEY_LEFT               263
#define GLFW_KEY_DOWN               264
#define GLFW_KEY_UP                 265
#define GLFW_KEY_PAGE_UP            266
#define GLFW_KEY_PAGE_DOWN          267
#define GLFW_KEY_HOME               268
#define GLFW_KEY_END                269
#define GLFW_KEY_CAPS_LOCK          280
#define GLFW_KEY_SCROLL_LOCK        281
#define GLFW_KEY_NUM_LOCK           282
#define GLFW_KEY_PRINT_SCREEN       283
#define GLFW_KEY_PAUSE              284
#define GLFW_KEY_F1                 290
#define GLFW_KEY_F2                 291
#define GLFW_KEY_F3                 292
#define GLFW_KEY_F4                 293
#define GLFW_KEY_F5                 294
#define GLFW_KEY_F6                 295
#define GLFW_KEY_F7                 296
#define GLFW_KEY_F8                 297
#define GLFW_KEY_F9                 298
#define GLFW_KEY_F10                299
#define GLFW_KEY_F11                300
#define GLFW_KEY_F12                301
#define GLFW_KEY_F13                302
#define GLFW_KEY_F14                303
#define GLFW_KEY_F15                304
#define GLFW_KEY_F16                305
#define GLFW_KEY_F17                306
#define GLFW_KEY_F18                307
#define GLFW_KEY_F19                308
#define GLFW_KEY_F20                309
#define GLFW_KEY_F21                310
#define GLFW_KEY_F22                311
#define GLFW_KEY_F23                312
#define GLFW_KEY_F24                313
#define GLFW_KEY_F25                314
#define GLFW_KEY_KP_0               320
#define GLFW_KEY_KP_1               321
#define GLFW_KEY_KP_2               322
#define GLFW_KEY_KP_3               323
#define GLFW_KEY_KP_4               324
#define GLFW_KEY_KP_5               325
#define GLFW_KEY_KP_6               326
#define GLFW_KEY_KP_7               327
#define GLFW_KEY_KP_8               328
#define GLFW_KEY_KP_9               329
#define GLFW_KEY_KP_DECIMAL         330
#define GLFW_KEY_KP_DIVIDE          331
#define GLFW_KEY_KP_MULTIPLY        332
#define GLFW_KEY_KP_SUBTRACT        333
#define GLFW_KEY_KP_ADD             334
#define GLFW_KEY_KP_ENTER           335
#define GLFW_KEY_KP_EQUAL           336
#define GLFW_KEY_LEFT_SHIFT         340
#define GLFW_KEY_LEFT_CONTROL       341
#define GLFW_KEY_LEFT_ALT           342
#define GLFW_KEY_LEFT_SUPER         343
#define GLFW_KEY_RIGHT_SHIFT        344
#define GLFW_KEY_RIGHT_CONTROL      345
#define GLFW_KEY_RIGHT_ALT          346
#define GLFW_KEY_RIGHT_SUPER        347
#define GLFW_KEY_MENU               348

#define GLFW_KEY_LAST               GLFW_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 */
#define GLFW_MOD_SHIFT           0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 */
#define GLFW_MOD_CONTROL         0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 */
#define GLFW_MOD_ALT             0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 */
#define GLFW_MOD_SUPER           0x0008

/*! @} */

/*! @defgroup buttons Mouse buttons
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define GLFW_MOUSE_BUTTON_1         0
#define GLFW_MOUSE_BUTTON_2         1
#define GLFW_MOUSE_BUTTON_3         2
#define GLFW_MOUSE_BUTTON_4         3
#define GLFW_MOUSE_BUTTON_5         4
#define GLFW_MOUSE_BUTTON_6         5
#define GLFW_MOUSE_BUTTON_7         6
#define GLFW_MOUSE_BUTTON_8         7
#define GLFW_MOUSE_BUTTON_LAST      GLFW_MOUSE_BUTTON_8
#define GLFW_MOUSE_BUTTON_LEFT      GLFW_MOUSE_BUTTON_1
#define GLFW_MOUSE_BUTTON_RIGHT     GLFW_MOUSE_BUTTON_2
#define GLFW_MOUSE_BUTTON_MIDDLE    GLFW_MOUSE_BUTTON_3
/*! @} */

/*! @defgroup joysticks Joysticks
 *
 *  See [joystick input](@ref joystick) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define GLFW_JOYSTICK_1             0
#define GLFW_JOYSTICK_2             1
#define GLFW_JOYSTICK_3             2
#define GLFW_JOYSTICK_4             3
#define GLFW_JOYSTICK_5             4
#define GLFW_JOYSTICK_6             5
#define GLFW_JOYSTICK_7             6
#define GLFW_JOYSTICK_8             7
#define GLFW_JOYSTICK_9             8
#define GLFW_JOYSTICK_10            9
#define GLFW_JOYSTICK_11            10
#define GLFW_JOYSTICK_12            11
#define GLFW_JOYSTICK_13            12
#define GLFW_JOYSTICK_14            13
#define GLFW_JOYSTICK_15            14
#define GLFW_JOYSTICK_16            15
#define GLFW_JOYSTICK_LAST          GLFW_JOYSTICK_16
/*! @} */

#endif //_glfw3_h_

/* The unknown key */
#define KEY_UNKNOWN            GLFW_KEY_UNKNOWN            //-1

/* Printable keys */
#define KEY_SPACE              GLFW_KEY_SPACE              //32
#define KEY_APOSTROPHE         GLFW_KEY_APOSTROPHE         //39  /* ' */
#define KEY_COMMA              GLFW_KEY_COMMA              //44  /* , */
#define KEY_MINUS              GLFW_KEY_MINUS              //45  /* - */
#define KEY_PERIOD             GLFW_KEY_PERIOD             //46  /* . */
#define KEY_SLASH              GLFW_KEY_SLASH              //47  /* / */
#define KEY_0                  GLFW_KEY_0                  //48
#define KEY_1                  GLFW_KEY_1                  //49
#define KEY_2                  GLFW_KEY_2                  //50
#define KEY_3                  GLFW_KEY_3                  //51
#define KEY_4                  GLFW_KEY_4                  //52
#define KEY_5                  GLFW_KEY_5                  //53
#define KEY_6                  GLFW_KEY_6                  //54
#define KEY_7                  GLFW_KEY_7                  //55
#define KEY_8                  GLFW_KEY_8                  //56
#define KEY_9                  GLFW_KEY_9                  //57
#define KEY_SEMICOLON          GLFW_KEY_SEMICOLON          //59  /* ; */
#define KEY_EQUAL              GLFW_KEY_EQUAL              //61  /* = */
#define KEY_A                  GLFW_KEY_A                  //65
#define KEY_B                  GLFW_KEY_B                  //66
#define KEY_C                  GLFW_KEY_C                  //67
#define KEY_D                  GLFW_KEY_D                  //68
#define KEY_E                  GLFW_KEY_E                  //69
#define KEY_F                  GLFW_KEY_F                  //70
#define KEY_G                  GLFW_KEY_G                  //71
#define KEY_H                  GLFW_KEY_H                  //72
#define KEY_I                  GLFW_KEY_I                  //73
#define KEY_J                  GLFW_KEY_J                  //74
#define KEY_K                  GLFW_KEY_K                  //75
#define KEY_L                  GLFW_KEY_L                  //76
#define KEY_M                  GLFW_KEY_M                  //77
#define KEY_N                  GLFW_KEY_N                  //78
#define KEY_O                  GLFW_KEY_O                  //79
#define KEY_P                  GLFW_KEY_P                  //80
#define KEY_Q                  GLFW_KEY_Q                  //81
#define KEY_R                  GLFW_KEY_R                  //82
#define KEY_S                  GLFW_KEY_S                  //83
#define KEY_T                  GLFW_KEY_T                  //84
#define KEY_U                  GLFW_KEY_U                  //85
#define KEY_V                  GLFW_KEY_V                  //86
#define KEY_W                  GLFW_KEY_W                  //87
#define KEY_X                  GLFW_KEY_X                  //88
#define KEY_Y                  GLFW_KEY_Y                  //89
#define KEY_Z                  GLFW_KEY_Z                  //90
#define KEY_LEFT_BRACKET       GLFW_KEY_LEFT_BRACKET       //91  /* [ */
#define KEY_BACKSLASH          GLFW_KEY_BACKSLASH          //92  /* \ */
#define KEY_RIGHT_BRACKET      GLFW_KEY_RIGHT_BRACKET      //93  /* ] */
#define KEY_GRAVE_ACCENT       GLFW_KEY_GRAVE_ACCENT       //96  /* ` */
#define KEY_WORLD_1            GLFW_KEY_WORLD_1            //161 /* non-US #1 */
#define KEY_WORLD_2            GLFW_KEY_WORLD_2            //162 /* non-US #2 */

/* Function keys */
#define KEY_ESCAPE             GLFW_KEY_ESCAPE             //256
#define KEY_ENTER              GLFW_KEY_ENTER              //257
#define KEY_TAB                GLFW_KEY_TAB                //258
#define KEY_BACKSPACE          GLFW_KEY_BACKSPACE          //259
#define KEY_INSERT             GLFW_KEY_INSERT             //260
#define KEY_DELETE             GLFW_KEY_DELETE             //261
#define KEY_RIGHT              GLFW_KEY_RIGHT              //262
#define KEY_LEFT               GLFW_KEY_LEFT               //263
#define KEY_DOWN               GLFW_KEY_DOWN               //264
#define KEY_UP                 GLFW_KEY_UP                 //265
#define KEY_PAGE_UP            GLFW_KEY_PAGE_UP            //266
#define KEY_PAGE_DOWN          GLFW_KEY_PAGE_DOWN          //267
#define KEY_HOME               GLFW_KEY_HOME               //268
#define KEY_END                GLFW_KEY_END                //269
#define KEY_CAPS_LOCK          GLFW_KEY_CAPS_LOCK          //280
#define KEY_SCROLL_LOCK        GLFW_KEY_SCROLL_LOCK        //281
#define KEY_NUM_LOCK           GLFW_KEY_NUM_LOCK           //282
#define KEY_PRINT_SCREEN       GLFW_KEY_PRINT_SCREEN       //283
#define KEY_PAUSE              GLFW_KEY_PAUSE              //284
#define KEY_F1                 GLFW_KEY_F1                 //290
#define KEY_F2                 GLFW_KEY_F2                 //291
#define KEY_F3                 GLFW_KEY_F3                 //292
#define KEY_F4                 GLFW_KEY_F4                 //293
#define KEY_F5                 GLFW_KEY_F5                 //294
#define KEY_F6                 GLFW_KEY_F6                 //295
#define KEY_F7                 GLFW_KEY_F7                 //296
#define KEY_F8                 GLFW_KEY_F8                 //297
#define KEY_F9                 GLFW_KEY_F9                 //298
#define KEY_F10                GLFW_KEY_F10                //299
#define KEY_F11                GLFW_KEY_F11                //300
#define KEY_F12                GLFW_KEY_F12                //301
#define KEY_F13                GLFW_KEY_F13                //302
#define KEY_F14                GLFW_KEY_F14                //303
#define KEY_F15                GLFW_KEY_F15                //304
#define KEY_F16                GLFW_KEY_F16                //305
#define KEY_F17                GLFW_KEY_F17                //306
#define KEY_F18                GLFW_KEY_F18                //307
#define KEY_F19                GLFW_KEY_F19                //308
#define KEY_F20                GLFW_KEY_F20                //309
#define KEY_F21                GLFW_KEY_F21                //310
#define KEY_F22                GLFW_KEY_F22                //311
#define KEY_F23                GLFW_KEY_F23                //312
#define KEY_F24                GLFW_KEY_F24                //313
#define KEY_F25                GLFW_KEY_F25                //314
#define KEY_KP_0               GLFW_KEY_KP_0               //320
#define KEY_KP_1               GLFW_KEY_KP_1               //321
#define KEY_KP_2               GLFW_KEY_KP_2               //322
#define KEY_KP_3               GLFW_KEY_KP_3               //323
#define KEY_KP_4               GLFW_KEY_KP_4               //324
#define KEY_KP_5               GLFW_KEY_KP_5               //325
#define KEY_KP_6               GLFW_KEY_KP_6               //326
#define KEY_KP_7               GLFW_KEY_KP_7               //327
#define KEY_KP_8               GLFW_KEY_KP_8               //328
#define KEY_KP_9               GLFW_KEY_KP_9               //329
#define KEY_KP_DECIMAL         GLFW_KEY_KP_DECIMAL         //330
#define KEY_KP_DIVIDE          GLFW_KEY_KP_DIVIDE          //331
#define KEY_KP_MULTIPLY        GLFW_KEY_KP_MULTIPLY        //332
#define KEY_KP_SUBTRACT        GLFW_KEY_KP_SUBTRACT        //333
#define KEY_KP_ADD             GLFW_KEY_KP_ADD             //334
#define KEY_KP_ENTER           GLFW_KEY_KP_ENTER           //335
#define KEY_KP_EQUAL           GLFW_KEY_KP_EQUAL           //336
#define KEY_LEFT_SHIFT         GLFW_KEY_LEFT_SHIFT         //340
#define KEY_LEFT_CONTROL       GLFW_KEY_LEFT_CONTROL       //341
#define KEY_LEFT_ALT           GLFW_KEY_LEFT_ALT           //342
#define KEY_LEFT_SUPER         GLFW_KEY_LEFT_SUPER         //343
#define KEY_RIGHT_SHIFT        GLFW_KEY_RIGHT_SHIFT        //344
#define KEY_RIGHT_CONTROL      GLFW_KEY_RIGHT_CONTROL      //345
#define KEY_RIGHT_ALT          GLFW_KEY_RIGHT_ALT          //346
#define KEY_RIGHT_SUPER        GLFW_KEY_RIGHT_SUPER        //347
#define KEY_MENU               GLFW_KEY_MENU               //348

#define KEY_LAST               GLFW_KEY_LAST               //GLFW_KEY_MENU

/*! @} */

/*! @defgroup mods Modifier key flags
 *
 *  See [key input](@ref input_key) for how these are used.
 *
 *  @ingroup input
 *  @{ */

/*! @brief If this bit is set one or more Shift keys were held down.
 */
#define MOD_SHIFT           GLFW_MOD_SHIFT           //0x0001
/*! @brief If this bit is set one or more Control keys were held down.
 */
#define MOD_CONTROL         GLFW_MOD_CONTROL         //0x0002
/*! @brief If this bit is set one or more Alt keys were held down.
 */
#define MOD_ALT             GLFW_MOD_ALT             //0x0004
/*! @brief If this bit is set one or more Super keys were held down.
 */
#define MOD_SUPER           GLFW_MOD_SUPER           //0x0008

/*! @} */

/*! @defgroup buttons Mouse buttons
 *
 *  See [mouse button input](@ref input_mouse_button) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define MOUSE_BUTTON_1         GLFW_MOUSE_BUTTON_1         //0
#define MOUSE_BUTTON_2         GLFW_MOUSE_BUTTON_2         //1
#define MOUSE_BUTTON_3         GLFW_MOUSE_BUTTON_3         //2
#define MOUSE_BUTTON_4         GLFW_MOUSE_BUTTON_4         //3
#define MOUSE_BUTTON_5         GLFW_MOUSE_BUTTON_5         //4
#define MOUSE_BUTTON_6         GLFW_MOUSE_BUTTON_6         //5
#define MOUSE_BUTTON_7         GLFW_MOUSE_BUTTON_7         //6
#define MOUSE_BUTTON_8         GLFW_MOUSE_BUTTON_8         //7
#define MOUSE_BUTTON_LAST      GLFW_MOUSE_BUTTON_LAST      //GLFW_MOUSE_BUTTON_8
#define MOUSE_BUTTON_LEFT      GLFW_MOUSE_BUTTON_LEFT      //GLFW_MOUSE_BUTTON_1
#define MOUSE_BUTTON_RIGHT     GLFW_MOUSE_BUTTON_RIGHT     //GLFW_MOUSE_BUTTON_2
#define MOUSE_BUTTON_MIDDLE    GLFW_MOUSE_BUTTON_MIDDLE    //GLFW_MOUSE_BUTTON_3
/*! @} */

/*! @defgroup joysticks Joysticks
 *
 *  See [joystick input](@ref joystick) for how these are used.
 *
 *  @ingroup input
 *  @{ */
#define JOYSTICK_1             GLFW_JOYSTICK_1             //0
#define JOYSTICK_2             GLFW_JOYSTICK_2             //1
#define JOYSTICK_3             GLFW_JOYSTICK_3             //2
#define JOYSTICK_4             GLFW_JOYSTICK_4             //3
#define JOYSTICK_5             GLFW_JOYSTICK_5             //4
#define JOYSTICK_6             GLFW_JOYSTICK_6             //5
#define JOYSTICK_7             GLFW_JOYSTICK_7             //6
#define JOYSTICK_8             GLFW_JOYSTICK_8             //7
#define JOYSTICK_9             GLFW_JOYSTICK_9             //8
#define JOYSTICK_10            GLFW_JOYSTICK_10            //9
#define JOYSTICK_11            GLFW_JOYSTICK_11            //10
#define JOYSTICK_12            GLFW_JOYSTICK_12            //11
#define JOYSTICK_13            GLFW_JOYSTICK_13            //12
#define JOYSTICK_14            GLFW_JOYSTICK_14            //13
#define JOYSTICK_15            GLFW_JOYSTICK_15            //14
#define JOYSTICK_16            GLFW_JOYSTICK_16            //15
#define JOYSTICK_LAST          GLFW_JOYSTICK_LAST          //GLFW_JOYSTICK_16

#endif //KEYCODES_H