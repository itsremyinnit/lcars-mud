// /d/Nexus/std/wing_segment.c: one virtual segment of an Inn wing.
#include "/d/Nexus/nexus.h"
inherit NEXUS_ROOM;

#define QUARTERS_D "/d/Nexus/adm/quarters_d"

string wing, owner;
int seg;

void setup_segment(string w, int k, string o) {
    string back, rune, text, view;
    int more;

    wing = w; seg = k; owner = o;
    back = (w == "west") ? "east" : "west";
    view = (w == "west") ? "a sunset that never quite finishes" : "a sunrise that never quite begins";
    rune = (string)NEXUS_RING->rune_for(o);
    more = QUARTERS_D->owner_at(w, k + 1) ? 1 : 0;

    text = "The Inn's corridor runs " + w + "ward here, its green runner soft underfoot " +
        "and its walls hung with small, mismatched paintings of places no one quite remembers " +
        "visiting. Lamps turned low glow in sconces of hammered copper. On the north wall stands " +
        "a door of dark wood, carved with " + rune + ", the mark of " + capitalize(o) + ". ";
    if (more)
        text += "The corridor continues " + w + ", and leads back " + back + ".";
    else
        text += "To the " + w + " the corridor ends in a deep window seat piled with cushions, " +
            "looking out on " + view + ". The way back lies " + back + ".";

    set("short", capitalize(w) + " Wing of the Inn");
    set("long", wrap(text));
    set("item_desc", ([
        "door" : wrap("Dark wood, warm to the touch, carved with " + rune + ". It belongs to " +
                      capitalize(o) + ".") ,
        "paintings" : "Small and mismatched. One shows a place that looks suspiciously like a school hallway.\n",
    ]));
    set("exits", ([
        back    : (k == 1) ? "/d/Nexus/rooms/inn" : "/d/Nexus/wings/" + w + "_" + (k - 1),
        "north" : "/d/Nexus/quarters/" + o,
    ]));
    if (more) set("exits/" + w, "/d/Nexus/wings/" + w + "_" + (k + 1));
    set("pre_exit_func/north", "try_door");
}

int try_door() {
    object who = this_player(), q;
    string name = who ? (string)who->query("name") : 0;

    if (QUARTERS_D->may_enter(owner, name)) return 0;
    write("You try the door, but it stays politely, firmly shut.\n");
    say((string)who->query("cap_name") + " knocks on " + capitalize(owner) + "'s door and waits.\n");
    if (q = find_object("/d/Nexus/quarters/" + owner))
        tell_room(q, "There is a knock at the door. It sounds like " +
                  (string)who->query("cap_name") + ".\n");
    return 1;
}
