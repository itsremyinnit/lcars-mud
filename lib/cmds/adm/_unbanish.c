// /cmds/adm/_unbanish.c: lift a 90-day banishment. LCARS-MUD
#include <mudlib.h>
#include <uid.h>
inherit DAEMON;

#define BANISH_D "/d/Nexus/adm/banish_d"

int cmd_unbanish(string str) {
    if (!adminp(geteuid(previous_object()))) return 0;
    notify_fail("Syntax: unbanish <player>\n");
    if (!str || str == "") return 0;
    str = lower_case(str);
    if (!BANISH_D->remove_banish(str)) {
        write("Unbanish: " + capitalize(str) + " is not banished.\n");
        return 1;
    }
    write("Unbanish: " + capitalize(str) + " may return (as a player).\n");
    return 1;
}

string help() { return "Syntax: unbanish <player>\n\nLifts a 90-day banishment.\n"; }
