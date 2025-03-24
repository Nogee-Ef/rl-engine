#include "header.h"

void handleInput(int input) {
    switch (input) {
        case 49: // NUMPAD Down Left
            player.position.x -= 1;
            player.position.y += 1;
            break;
        case 51: // NUMPAD Down Right
            player.position.x += 1;
            player.position.y += 1;
            break;
        case 52: // NUMPAD Left
            player.position.x -= 1;
            break;
        case 54: // NUMPAD Right
            player.position.x += 1;
            break;
        case 55: // NUMPAD Up Left
            player.position.x -= 1;
            player.position.y -= 1;
            break;
        case 57: // NUMPAD Up Right
            player.position.x += 1;
            player.position.y -= 1;
            break;
        case 75: // Arrow Left
            player.position.x -= 1;
            break;
        case 77: // Arrow Right
            player.position.x += 1;
            break;
    }
}