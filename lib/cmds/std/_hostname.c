// hostname.c
// Tells you what MUD you're on and which port.
// LCARS-MUD: rewritten to stop depending on the Intermud-3 mud list.
#include <mudlib.h>
inherit DAEMON;

int cmd_hostname() {
    printf("%s is running on port %d.\n", capitalize(mud_name()), __PORT__);
    return 1;
}

string help() {
    return "Syntax: hostname\n\nTells you the name of the MUD you're playing. For the forgetful. :)\n";
}
