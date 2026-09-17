// /cmds/std/_legend.c: alias for finger, with me/self. LCARS-MUD
#include <mudlib.h>
inherit DAEMON;

int cmd_legend(string str) {
    if (!str || str == "" || str == "me" || str == "self")
        str = (string)this_player()->query("name");
    return (int)"/cmds/std/_finger"->cmd_finger(str);
}

string help() { return "Syntax: legend [name|me]\n\nShows a character's legend card. Same as finger.\n"; }
