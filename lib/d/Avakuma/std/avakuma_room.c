// /d/Avakuma/std/avakuma_room.c
// Base for every room in Avakuma. Deliberately inherits the stock ROOM
// rather than the Nexus base, so nothing here is coupled to Nexus code.
//
// Defaults: lit, indoors, no weather.
//   set_outdoors()      light follows the day/night cycle; weather notices on
//   set_outdoors("B")   same, in a named weather zone (zones are not yet
//                       distinguished by weather_d; the letter is stored only)
//   set_dark()          unlit interior (cellars, caves, the inside of things)

#include <mudlib.h>
#include <daemons.h>
#include "/d/Avakuma/avakuma.h"

inherit ROOM;

void create() {
    ::create();
    seteuid(getuid());
    set("light", 1);
    set("avakuma", 1);
}

// Hands this room's light over to WEATHER_D and registers it for change
// notices. /cmds/std/_look.c appends the weather, sun and moon text to any
// room with "outside" set, so nothing further is needed for the description.
varargs void set_outdoors(string zone) {
    set_outside(zone ? zone : AVAKUMA_ZONE);
}

void set_dark() {
    set("light", 0);
}

// WEATHER_D delivers change notices ("it begins to rain") by calling
// message() on each registered ROOM, but /std/room.c defines no
// receive_message, so they are dropped and players never see weather
// change while standing still. Relay them to the livings in the room.
void receive_message(string Class, string msg) {
    object *inv;
    int i;

    inv = all_inventory(this_object());
    for (i = 0; i < sizeof(inv); i++)
        if (living(inv[i]))
            inv[i]->receive_message(Class, msg);
}
