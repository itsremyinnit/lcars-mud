// /d/Nexus/std/nexus_room.c
// Base for every Nexus room. Anyone may walk the Nexus; only a wizard
// wearing their own Calenmir may pass through an arch.
// Rooms set "exits" first, then call add_arch() for each arch.

#include <mudlib.h>
#include "/d/Nexus/nexus.h"

inherit ROOM;

void create() {
    ::create();
    seteuid(getuid());
    set("light", 1);
    set("nexus", 1);
}

int has_focus(object who) {
    object *inv;
    int i;
    if (!who || !wizardp(who)) return 0;
    inv = all_inventory(who);
    for (i = 0; i < sizeof(inv); i++)
        if (base_name(inv[i]) == NEXUS_RING &&
            inv[i]->query("equipped") &&
            inv[i]->query("owner") == who->query("name"))
            return 1;
    return 0;
}

// sigil: how the arch is named in messages, e.g. "the Bell Arch"
// sealed: if set, the arch refuses everyone with this message
varargs void add_arch(string dir, string dest, string sigil, string sealed,
                      string passage) {
    set("exits/" + dir, dest);
    set("arches/" + dir, ([ "sigil" : sigil, "sealed" : sealed,
                            "passage" : passage ]));
    set("pre_exit_func/" + dir, "arch_" + dir);
}

int check_arch(string dir) {
    mapping arch = query("arches/" + dir);
    object who = this_player();

    if (!mapp(arch)) return 0;
    if (arch["sealed"]) {
        write(arch["sealed"] + "\n");
        return 1;
    }
    if (!has_focus(who)) {
        if (who && wizardp(who))
            write("You reach toward " + arch["sigil"] + ", but without a focus your will\n" +
                  "cannot find the way through.\n");
        else
            write("The light within " + arch["sigil"] + " parts around you like water around\n" +
                  "a stone, and you find yourself where you began.\n");
        return 1;
    }
    if (arch["passage"])
        write(arch["passage"]);
    else
        write("Calenmîr kindles as you pass beneath " + arch["sigil"] + ".\n");
    return 0;
}

int arch_north() { return check_arch("north"); }
int arch_south() { return check_arch("south"); }
int arch_east()  { return check_arch("east"); }
int arch_west()  { return check_arch("west"); }
