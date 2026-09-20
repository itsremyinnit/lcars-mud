// /d/FinalFrontier/std/ff_room.c
// Base for every room aboard. Same shape as the Avakuma base: stock ROOM
// plus DOORS, sealed exits, tracked spawning. No weather relay, since
// there is no weather in a starship, though the arboretum may want its
// own cycle later.
//
// Ship rooms are lit by default. set_dark() exists for a powered-down
// deck, which will matter the first time somebody writes a crisis.

#include <mudlib.h>
#include "/d/FinalFrontier/frontier.h"

inherit ROOM;
inherit DOORS;

mapping sealed_exits;
nosave object *spawned;

void create() {
    ::create();
    seteuid(getuid());
    set("light", 1);
    set("frontier", 1);
    set("respawn_time", 300);
}

void set_dark() { set("light", 0); }

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
int sealed_out()       { return do_sealed("out"); }

// Call AFTER set("exits", ([...])).
varargs void add_sealed(string dir, string msg) {
    if (!sealed_exits) sealed_exits = ([ ]);
    sealed_exits[dir] = msg ? msg : "That way is sealed off.\n";
    set("exits/" + dir, base_name(this_object()));
    set("pre_exit_func/" + dir, "sealed_" + dir);
}

// See the Avakuma base for why this does not use reset().
void spawn_objects() {
    mapping obs;
    string *paths;
    int i, j, want, alive;
    object ob;

    obs = query("objects");
    if (!obs || !sizeof(obs)) return;
    if (!spawned) spawned = ({ });
    spawned -= ({ 0 });

    paths = keys(obs);
    for (i = 0; i < sizeof(paths); i++) {
        want = obs[paths[i]];
        if (!intp(want)) continue;
        alive = 0;
        for (j = 0; j < sizeof(spawned); j++)
            if (spawned[j] && base_name(spawned[j]) == paths[i]) alive++;
        for (j = alive; j < want; j++) {
            ob = clone_object(paths[i]);
            if (!ob) continue;
            ob->move(this_object());
            spawned += ({ ob });
        }
    }
    call_out("spawn_objects", query("respawn_time"));
}
