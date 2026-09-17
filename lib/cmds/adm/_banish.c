// /cmds/adm/_banish.c: banish a character for 90 days. LCARS-MUD
// The stock permanent name ban is now "banishname".
#include <mudlib.h>
#include <uid.h>
inherit DAEMON;

#define SYNTAX   "Syntax: banish <player>\n"
#define BANISH_D "/d/Nexus/adm/banish_d"

int cmd_banish(string str) {
    object who;
    string cap, art;

    if (!adminp(geteuid(previous_object()))) {
        write("Illegal attempt at banish by " + file_name(previous_object()) + "\n");
        return 1;
    }
    seteuid(ROOT_UID);

    notify_fail(SYNTAX);
    if (!str || str == "") return 0;
    str = lower_case(str);

    if (!user_exists(str)) { write("Banish: No such player.\n"); return 1; }
    if (adminp(str)) { write("Banish: " + capitalize(str) + " is an admin.\n"); return 1; }
    if (BANISH_D->query_banished(str)) {
        write("Banish: " + capitalize(str) + " is already banished.\n");
        return 1;
    }

    write("Banish " + capitalize(str) + " for 90 days? [y/n] ");
    input_to("confirm", 0, str);
    return 1;
}

protected void confirm(string answer, string str) {
    object who;
    string cap = capitalize(str), art;

    if (!answer || member_array(lower_case(answer), ({ "y", "yes" })) == -1) {
        write("Banish: aborted.\n");
        return;
    }
    seteuid(ROOT_UID);

    if (wizardp(str)) "/cmds/adm/_unwiz"->cmd_unwiz(str);
    BANISH_D->add_banish(str, (string)this_player()->query("name"));

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

    if (who = find_player(str)) {
        tell_object(who, "\nThe air around you hardens into crystal, and the world falls away.\n");
        shout(art, ({ who }));
        tell_object(who, art);
        who->save_data();
        who->remove();
    } else {
        shout(art);
    }
    write("Banish: " + cap + " has been banished for 90 days.\n");
}

string help() {
    return SYNTAX + "\nParks a character for 90 days: login and re-creation are refused,\n" +
           "finger shows the banishment, and on day 90 their data is archived.\n" +
           "Use unbanish to reverse it. The permanent name ban is now 'banishname'.\n";
}
