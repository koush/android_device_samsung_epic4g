/*
 * Copyright (C) 2009 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* Edited by DRockstar for the Samsung Epic 4G Gingerbread ClockworkMod */

#include <linux/input.h>

#include "recovery_ui.h"
#include "common.h"
#include "extendedcommands.h"

char* MENU_HEADERS[] = { "Use vol keys to highlight and home to select.",
                         "",
                         NULL };

char* MENU_ITEMS[] = { "Reboot system now",
                       "Apply sdcard:update.zip",
                       "Wipe data/factory reset",
                       "Wipe cache partition",
                       "Install zip from sdcard",
                       "Backup and Restore",
                       "Mounts and Storage",
                       "Advanced",
                       "Power Off",
			NULL };

int device_recovery_start() {
    return 0;
}

int device_toggle_display(volatile char* key_pressed, int key_code) { 
    return key_code == 23; // keypad d key
}

int device_reboot_now(volatile char* key_pressed, int key_code) {
    // Reboot if the power key is pressed five times in a row, with
    // no other keys in between.
    static int presses = 0;
    if (key_code == 116) { // power button
        ++presses;
        return presses == 5;
    } else {
        presses = 0;
        return 0;
    }
}

int device_handle_key(int key_code, int visible) {
    if (visible) {
        switch (key_code) {
            case 51:  // side volume up button
            case 48:  // keypad left key
            case 39:  // keypad up key
                return HIGHLIGHT_UP;

            case 52:  // side volume down button
            case 50:  // keypad right key
            case 49:  // keypad down key
                return HIGHLIGHT_DOWN;

            case 102: // menu cap key
            case 53:  // keypad home key 
            case 46:  // side camera button full press 
            case 40:  // keypad enter/return key
                return SELECT_ITEM;
            
            case 158: // back cap key
            case 116: // side power button
            case 57:  // keypad back key 
            case 30:  // keypad delete key
                if (!get_allow_toggle_display())
                    return GO_BACK;
        }
    }

    return NO_ACTION;
}

int device_perform_action(int which) {
    return which;
}

int device_wipe_data() {
    return 0;
}
