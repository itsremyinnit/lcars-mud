// _wear.c: friendly alias for equip. LCARS-MUD
#include <mudlib.h>
inherit DAEMON;

int cmd_wear(string str) { return (int)"/cmds/std/_equip"->cmd_equip(str); }

string help() { return "Syntax: wear <armor>\n\nSame as equip.\n"; }
