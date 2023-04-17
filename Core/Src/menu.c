#include "menu.h"
#include "GFX.h"
#include <stdio.h>
#include <string.h>

// constants for foreground and background colors
#define COLOR_BLACK   BLACK
#define COLOR_WHITE   WHITE
#define CHAR_HEIGHT 8
#define  CHAR_WIDTH 6
#define  SCREEN_HEIGHT 96
#define  SCREEN_WIDTH 128
#define  SIZE_MENU_ITEM 2

void display_string(const char *str, uint8_t foreground, uint8_t background) {
    int x = 0, y = 0;
    int len = strlen(str);

    for (int i = 0; i < len; i++) {
        // draw the current character at the current position
        GFX_draw_char(x, y, str[i], foreground, background, SIZE_MENU_ITEM, SIZE_MENU_ITEM);

        // move the position to the next character
        x += CHAR_WIDTH;

        // wrap to the next line if necessary
        if (x >= SCREEN_WIDTH) {
            x = 0;
            y += CHAR_HEIGHT;
        }
    }
}

void menu_init(menu_t *menu) {
    // set the menu title
    menu->title = "Sequencer";

    // initialize the menu items
    menu_item_t tempo_item = {"TEMPO", NULL};
    menu_item_t seq_item = {"SEQ", NULL};
    menu_item_t gate_item = {"GATE", NULL};
    menu_item_t save_item = {"SAVE", NULL};

    // add the menu items to the menu
    menu->items[0] = tempo_item;
    menu->items[1] = seq_item;
    menu->items[2] = gate_item;
    menu->items[3] = save_item;

    // set the number of menu items
    menu->num_items = 4;

    // set the selected item index to the first item
    menu->selected_item_idx = 0;
}

// displays a menu on the screen
void menu_display(menu_t *menu) {
    // clear the screen
    display_string("", COLOR_BLACK, COLOR_WHITE);

    // display the menu title
    if (menu->title != NULL) {
        display_string(menu->title, COLOR_BLACK, COLOR_WHITE);
    }

    // display the menu items
    for (int i = 0; i < menu->num_items; i++) {
        if (i == menu->selected_item_idx) {
            // display the selected item with black text on white background
            display_string(menu->items[i].label, COLOR_BLACK, COLOR_WHITE);
        } else {
            // display the inactive item with white text on black background
            display_string(menu->items[i].label, COLOR_WHITE, COLOR_BLACK);
        }
    }
}

// selects the previous menu item
void menu_select_prev_item(menu_t *menu) {
    if (menu->selected_item_idx > 0) {
        menu->selected_item_idx--;
    }
}

// selects the next menu item
void menu_select_next_item(menu_t *menu) {
    if (menu->selected_item_idx < menu->num_items - 1) {
        menu->selected_item_idx++;
    }
}

// activates the currently selected menu item
void menu_activate_selected_item(menu_t *menu) {
    if (menu->selected_item_idx < menu->num_items) {
        menu->items[menu->selected_item_idx].action();
    }
}

void display_menu_items(menu_t *menu){
	// display the menu title
	display_string(menu->title, BLACK, WHITE);

	// display the menu items
	for (int i = 0; i < menu->num_items; i++) {
		// set the foreground and background colors based on whether the item is selected
		uint8_t fg = (i == menu->selected_item_idx) ? BLACK : WHITE;
		uint8_t bg = (i == menu->selected_item_idx) ? WHITE : BLACK;

		// display the menu items
		display_string(menu->items[i].label, fg, bg);
	}
	SSD1306_display_repaint();
}
