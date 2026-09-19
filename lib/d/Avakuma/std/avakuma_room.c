// /d/Avakuma/std/avakuma_room.c
// Base for every room in Avakuma. Deliberately inherits the stock ROOM
// rather than the Nexus base, so nothing here is coupled to Nexus code.
//
// Defaults: lit, indoors, no weather.
//   set_outdoors()        light follows the day/night cycle; weather on
//   set_outdoors("B")     same, in a named weather zone (zones are not yet
//                         distinguished by weather_d; the letter is stored)
//   set_dark()            unlit interior (cellars, caves, insides of things)
//   add_sealed(dir, msg)  an exit that is visible but refused, for edges
//                         that will be built later

#include <mudlib.h>
#include <daemons.h>
#include "/d/Avakuma/avakuma.h"

inherit ROOM;
inherit DOORS;

mapping sealed_exits;

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

int do_sealed(string dir) {
    if (!sealed_exits || !sealed_exits[dir]) return 0;
    write(sealed_exits[dir]);
    return 1;
}

int sealed_north()     { return do_sealed("north"); }
int sealed_south()     { return do_sealed("south"); }
int sealed_east()      { return do_sealed("east"); }
int sealed_west()      { return do_sealed("west"); }
int sealed_northeast() { return do_sealed("northeast"); }
int sealed_northwest() { return do_sealed("northwest"); }
int sealed_southeast() { return do_sealed("southeast"); }
int sealed_southwest() { return do_sealed("southwest"); }
int sealed_up()        { return do_sealed("up"); }
int sealed_down()      { return do_sealed("down"); }

// Call AFTER set("exits", ([...])), never before: setting the whole exits
// mapping would discard anything added here.
varargs void add_sealed(string dir, string msg) {
    if (!sealed_exits) sealed_exits = ([ ]);
    sealed_exits[dir] = msg ? msg : "You cannot go that way yet.\n";
    set("exits/" + dir, base_name(this_object()));
    set("pre_exit_func/" + dir, "sealed_" + dir);
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
