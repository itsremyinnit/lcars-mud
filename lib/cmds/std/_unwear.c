// _unwear.c: friendly alias for unequip. LCARS-MUD
#include <mudlib.h>
inherit DAEMON;

int cmd_unwear(string str) { return (int)"/cmds/std/_unequip"->cmd_unequip(str); }

string help() { return "Syntax: unwear <armor>\n\nSame as unequip.\n"; }
