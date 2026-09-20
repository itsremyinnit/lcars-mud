// /d/FinalFrontier/std/turbolift.c
// The spine, and the lateral runs.
//
// Turbolifts on this ship move sideways as well as up, so a destination
// is a place rather than a deck. Say a name ("engineering", "brig",
// "ten-forward") or a deck with an optional section ("deck 6",
// "deck 6 aft"). "stops" lists everything.
//
// A deck with more than one lift simply has more than one entry. There is
// no primary lift per deck: the car goes where you ask.
//
// Adding a stop: one line in STOPS, one add_action for its name if it has
// a one-word one, and a room with an exit back into a lift.

#include <mudlib.h>
#include "/d/FinalFrontier/frontier.h"

inherit FF_ROOM;

// name : ({ deck, section, path, description })
#define STOPS ([ \
  "bridge"      : ({  1, "",     "/d/FinalFrontier/deck01/bridge",            "Main Bridge" }), \
  "transporter" : ({  6, "fore", "/d/FinalFrontier/deck06/corridor_fore",     "Transporter Room Three" }), \
  "brig"        : ({  6, "aft",  "/d/FinalFrontier/deck06/corridor_port_aft", "Security and Cargo" }), \
  "quarters"    : ({  8, "fore", "/d/FinalFrontier/deck08/corridor_fore",     "Officers' Quarters" }), \
  "ten-forward" : ({ 10, "fore", "/d/FinalFrontier/deck10/corridor_ten",      "Ten-Forward" }), \
  "holodecks"   : ({ 11, "",     "/d/FinalFrontier/deck11/corridor",          "Holodecks and Arboretum" }), \
  "sickbay"     : ({ 12, "",     "/d/FinalFrontier/deck12/sickbay",           "Sickbay" }), \
  "engineering" : ({ 36, "",     "/d/FinalFrontier/deck36/engineering",       "Main Engineering" }), \
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

    Say where you want to go, or name a deck. "stops" will list them.
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
    add_action("do_stops", "stops");
    add_action("do_deck", "deck");
    add_action("do_go_to", "bridge");
    add_action("do_go_to", "transporter");
    add_action("do_go_to", "brig");
    add_action("do_go_to", "quarters");
    add_action("do_go_to", "ten-forward");
    add_action("do_go_to", "holodecks");
    add_action("do_go_to", "sickbay");
    add_action("do_go_to", "engineering");
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
        write(sprintf("  %-13s deck %2d %-5s %s\n",
              names[i], stop[0], stop[1], stop[3]));
    }
    write("You may also say a deck, with a section: \"deck 6 aft\".\n");
    return 1;
}

private int travel(mixed *stop) {
    object who, dest;

    who = this_player();
    dest = find_object_or_load(stop[2]);
    if (!dest) {
        write("The computer says: That destination is not accepting arrivals.\n");
        return 1;
    }
    if (dest == environment(who)) {
        write("The computer says: You are there.\n");
        return 1;
    }

    write("The lift moves. There is no sensation of it whatsoever.\n");
    say((string)who->query("cap_name") + " states a destination and is gone.\n",
        who);
    who->move_player(dest, "The turbolift doors open and $N steps out.");
    return 1;
}

int do_go_to(string str) {
    mapping stops;
    string verb;

    stops = STOPS;
    verb = query_verb();
    if (!stops[verb]) return 0;
    return travel(stops[verb]);
}

// "deck 6", "deck 6 aft", "deck six" is not supported and never will be.
int do_deck(string str) {
    mapping stops;
    string *names, section;
    int i, n, matches, found;

    if (!str) {
        notify_fail("The computer says: Which deck?\n");
        return 0;
    }
    section = "";
    if (sscanf(str, "%d %s", n, section) != 2 &&
        sscanf(str, "%d", n) != 1) {
        notify_fail("The computer says: Which deck?\n");
        return 0;
    }

    stops = STOPS;
    names = keys(stops);
    matches = 0;
    found = -1;
    for (i = 0; i < sizeof(names); i++) {
        if (stops[names[i]][0] != n) continue;
        if (section != "" && stops[names[i]][1] != section) continue;
        found = i;
        matches++;
    }

    if (matches == 1) return travel(stops[names[found]]);

    if (matches > 1) {
        write("The computer says: Which part of deck " + n + "?\n");
        for (i = 0; i < sizeof(names); i++)
            if (stops[names[i]][0] == n)
                write(sprintf("  deck %d %-5s %s\n",
                      n, stops[names[i]][1], stops[names[i]][3]));
        return 1;
    }

    write("The computer says: Deck " + n +
          (section != "" ? " " + section : "") +
          " is not on this lift's route. Try 'stops'.\n");
    return 1;
}
