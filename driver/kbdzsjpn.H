/****************************** Module Header ******************************\
* Module Name: kbdzsjpn.H
*
* keyboard layout header
*
* Copyright (c) 1985-2001, Microsoft Corporation
*
* Various defines for use by keyboard input code.
*
* History:
*
* created by KBDTOOL v3.40 Sun Jan 11 19:21:24 2009
*
\***************************************************************************/

/*
 * kbd type should be controlled by cl command-line argument
 */
#define KBD_TYPE 7

/*
* Include the basis of all keyboard table values
*/
#include "kbd.h"
/***************************************************************************\
* The table below defines the virtual keys for various keyboard types where
* the keyboard differ from the US keyboard.
*
* _EQ() : all keyboard types have the same virtual key for this scancode
* _NE() : different virtual keys for this scancode, depending on kbd type
*
*     +------+ +----------+----------+----------+----------+----------+----------+
*     | Scan | |    kbd   |    kbd   |    kbd   |    kbd   |    kbd   |    kbd   |
*     | code | |   type 1 |   type 2 |   type 3 |   type 4 |   type 5 |   type 6 |
\****+-------+_+----------+----------+----------+----------+----------+----------+*/


#define VK_BROWSER_BACK        0xA6
#define VK_BROWSER_FORWARD     0xA7
#define VK_BROWSER_REFRESH     0xA8
#define VK_BROWSER_STOP        0xA9
#define VK_BROWSER_SEARCH      0xAA
#define VK_BROWSER_FAVORITES   0xAB
#define VK_BROWSER_HOME        0xAC

#define VK_VOLUME_MUTE         0xAD
#define VK_VOLUME_DOWN         0xAE
#define VK_VOLUME_UP           0xAF
#define VK_MEDIA_NEXT_TRACK    0xB0
#define VK_MEDIA_PREV_TRACK    0xB1
#define VK_MEDIA_STOP          0xB2
#define VK_MEDIA_PLAY_PAUSE    0xB3
#define VK_LAUNCH_MAIL         0xB4
#define VK_LAUNCH_MEDIA_SELECT 0xB5
#define VK_LAUNCH_APP1         0xB6
#define VK_LAUNCH_APP2         0xB7

