// /cmds/adm/_banish.c: banish a character and park their name. LCARS-MUD
// The stock permanent name ban is now "banishname".
#include <mudlib.h>
#include <uid.h>
inherit DAEMON;

#define SYNTAX       "Syntax: banish [days] <player>\n"
#define BANISH_D     "/d/Nexus/adm/banish_d"
#define DEFAULT_DAYS 90

int cmd_banish(string str) {
    string name;
    int days;

    if (!adminp(geteuid(previous_object()))) {
        write("Illegal attempt at banish by " + file_name(previous_object()) + "\n");
        return 1;
    }
    seteuid(ROOT_UID);

    notify_fail(SYNTAX);
    if (!str || str == "") return 0;
    if (sscanf(str, "%d %s", days, name) != 2) { name = str; days = DEFAULT_DAYS; }
    if (days < 1) { write("Banish: the number of days must be at least 1.\n"); return 1; }
    name = lower_case(name);

    if (!user_exists(name)) { write("Banish: No such player.\n"); return 1; }
    if (adminp(name)) { write("Banish: " + capitalize(name) + " is an admin.\n"); return 1; }
    if (BANISH_D->query_banished(name)) {
        write("Banish: " + capitalize(name) + " is already banished.\n");
        return 1;
    }

    write("Do you wish to banish " + capitalize(name) + " and park their name for " +
          days + " day" + (days == 1 ? "" : "s") + "? [y/n] ");
    input_to("confirm", 0, name, days);
    return 1;
}

protected void confirm(string answer, string name, int days) {
    object who;
    string cap = capitalize(name), art;

    if (!answer || member_array(lower_case(answer), ({ "y", "yes" })) == -1) {
        write("Banish: aborted.\n");
        return;
    }
    seteuid(ROOT_UID);

    "/cmds/adm/_unwiz"->cmd_unwiz(name);  // quietly skips non-wizards
    BANISH_D->add_banish(name, (string)this_player()->query("name"), days);

    art =
"\n" +
"                         .             *              .\n" +
"              *                  _______________                  .\n" +
"                     .         /|               |\\        *\n" +
"                              / |   .       .   | \\\n" +
"           .                 /  |       o       |  \\         .\n" +
"                            |   |      /|\\      |   |\n" +
"                *           |   |      / \\      |   |    *\n" +
"                             \\  |               |  /\n" +
"                  .           \\ |   .       .   | /           .\n" +
"                               \\|_______________|/\n" +
"                                 \\   \\  |  /   /\n" +
"          *            .           \\  \\ | /  /          .\n" +
"                                     \\ \\|/ /\n" +
"                  .                    \\|/              *\n" +
"                                        '\n" +
"         Sealed in a spinning pane of crystal, a figure is hurled\n" +
"               into the endless silence between the stars.\n\n" +
"                 " + cap + " has been BANISHED.\n\n";

    if (who = find_player(name)) {
        tell_object(who, "\nThe air around you hardens into crystal, and the world falls away.\n");
        shout(art, ({ who }));
        tell_object(who, art);
        who->save_data();
        who->remove();
    } else {
        shout(art);
    }
    write("Banish: " + cap + " is banished, and their name is parked for " +
          days + " day" + (days == 1 ? "" : "s") + ".\n");
}

string help() {
    return SYNTAX + "\nParks a character (default " + DEFAULT_DAYS + " days): login and re-creation\n" +
           "are refused, finger shows the banishment, and when the time is up their\n" +
           "data is archived and the name is freed. Players are never told the length.\n" +
           "Use unbanish to reverse it. The permanent name ban is now 'banishname'.\n";
}
