#ifndef MENU_H
#define MENU_H

#include <stdint.h>

// menu items
#define SEQUENCER "Sequencer"
#define TEMPO "Tempo"
#define SEQ "CV Seq"
#define GATE "Gate"
#define SAVE  "Save"

// maximum number of menu items
#define MAX_MENU_ITEMS 10

// function pointer type for menu item actions
typedef void (*menu_action_t)(void);

// menu item struct
typedef struct menu_item {
    const char *label;      // item label
    menu_action_t action;   // item action
} menu_item_t;

// menu struct
typedef struct menu {
    const char *title;          // menu title
    menu_item_t items[MAX_MENU_ITEMS];  // menu items
    uint8_t num_items;           // number of items in the menu
    uint8_t selected_item_idx;   // index of the currently selected item
} menu_t;

// function prototypes
void menu_init(menu_t *menu);
void menu_display(menu_t *menu);
void menu_select_prev_item(menu_t *menu);
void menu_select_next_item(menu_t *menu);
void menu_activate_selected_item(menu_t *menu);
void display_menu_items(menu_t *menu);

#endif
