// /d/FinalFrontier/std/turbolift.c
// The spine. One car, many stops.
//
// You do not walk out of a turbolift into a corridor; you tell it where
// you want to go. "bridge", "engineering", "ten-forward" and so on, or
// "deck 8". "stops" lists them. The car reports the deck it is on, which
// changes as you travel, so the room's short is dynamic.
//
// Every destination is a room that has its own exit back into the lift,
// so the lift is a hub rather than a corridor. New decks only need a line
// in STOPS and a room with a "lift" exit.

#include <mudlib.h>
#include "/d/FinalFrontier/frontier.h"

inherit FF_ROOM;

#define STOPS ([ \
  "bridge"       : ({  1, "/d/FinalFrontier/deck01/bridge",           "Main Bridge" }), \
  "security"     : ({  6, "/d/FinalFrontier/deck06/corridor_fore",    "Security and Transporters" }), \
  "quarters"     : ({  8, "/d/FinalFrontier/deck08/corridor_fore",    "Officers' Quarters" }), \
  "ten-forward"  : ({ 10, "/d/FinalFrontier/deck10/ten_forward",      "Ten-Forward" }), \
  "sickbay"      : ({ 12, "/d/FinalFrontier/deck12/sickbay",          "Sickbay" }), \
  "holodecks"    : ({ 11, "/d/FinalFrontier/deck11/corridor",         "Holodecks and Arboretum" }), \
  "engineering"  : ({ 36, "/d/FinalFrontier/deck36/engineering",      "Main Engineering" }), \
])

void create() {
    ::create();
    set("short", "Turbolift");
    set("long", @EndText
    A cylinder barely large enough for four, lit from a strip that runs
the whole way round where the wall meets the ceiling. There are no
buttons anywhere. A single black handle rises from the wall beside the
door, and the computer waits with the particular patience of something
that has never once been in a hurry.

    Say where you want to go. "stops" will list them.
EndText
    );
    set("item_desc", ([
        "handle" : @EndText
    A black grip rising out of the wall at hand height. It moves, but not
in any direction that corresponds to where the lift then goes.
EndText
        ,
        "strip" : @EndText
    A continuous band of light where the wall meets the ceiling. It
brightens very slightly when the car is moving, which you only notice
after it stops.
EndText
        ,
        "door" : "    It opens when it has a reason to and not before.\n",
    ]));
    set("exits", ([ ]));
}

void init() {
    // No ::init() here: ROOM defines none.
    add_action("do_stops", "stops");
    add_action("do_go_to", "bridge");
    add_action("do_go_to", "quarters");
    add_action("do_go_to", "ten-forward");
    add_action("do_go_to", "sickbay");
    add_action("do_go_to", "security");
    add_action("do_go_to", "holodecks");
    add_action("do_go_to", "engineering");
    add_action("do_deck", "deck");
}

int do_stops(string str) {
    mapping stops;
    string *names;
    mixed *stop;
    int i;

    stops = STOPS;
    names = sort_array(keys(stops), 1);
    write("The computer offers, without being asked twice:\n");
    for (i = 0; i < sizeof(names); i++) {
        stop = stops[names[i]];
        write(sprintf("  %-14s deck %2d   %s\n", names[i], stop[0], stop[2]));
    }
    return 1;
}

private int travel(mixed *stop) {
    object who, dest;

    who = this_player();
    dest = find_object_or_load(stop[1]);
    if (!dest) {
        write("The computer says: That deck is not accepting arrivals.\n");
        return 1;
    }

    write("The lift moves. There is no sensation of it whatsoever.\n");
    say((string)who->query("cap_name") + " states a destination and is gone.\n",
        who);
    who->move_player(dest, "The turbolift doors open and $N steps out.");
    return 1;
}

// "bridge", "engineering" and so on, said as bare commands.
int do_go_to(string str) {
    mapping stops;
    string verb;

    stops = STOPS;
    verb = query_verb();
    if (!stops[verb]) return 0;
    return travel(stops[verb]);
}

// "deck 8"
int do_deck(string str) {
    mapping stops;
    string *names;
    int i, n;

    if (!str || sscanf(str, "%d", n) != 1) {
        notify_fail("The computer says: Which deck?\n");
        return 0;
    }
    stops = STOPS;
    names = keys(stops);
    for (i = 0; i < sizeof(names); i++)
        if (stops[names[i]][0] == n) return travel(stops[names[i]]);

    write("The computer says: Deck " + n +
          " is not on this lift's route. Try 'stops'.\n");
    return 1;
}
