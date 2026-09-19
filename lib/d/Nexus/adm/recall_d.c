// /d/Nexus/adm/recall_d.c
// The ring carries its bearer home. Roughly fifteen seconds of narration,
// spent in the Between so the bearer cannot wander mid-passage.
//
// Entry is via "recall" on /d/Nexus/obj/calenmir.c, which checks that the
// ring is worn and owned before calling here.
#include <mudlib.h>
#include "/d/Nexus/nexus.h"
inherit DAEMON;

#define BETWEEN "/d/Nexus/rooms/between"

private string *beats = ({
    "\nThe green fire does not carry you so much as unmake the distance. Walls\n" +
    "thin to gauze and blow away. Whatever ground you were standing on stops\n" +
    "being ground, and you do not fall, because there is no longer a down.\n",

    "\nSomething vast turns over beneath you, patient and unhurried, the way a\n" +
    "sleeper shifts without waking. You have the distinct sense of being\n" +
    "carried, carefully, by something that has done this many times before.\n",
});

void create() { seteuid(getuid()); }
void clean_up() { }

int begin(object who) {
    object po = previous_object();
    object env;

    if (!who || !po) return 0;
    if (base_name(po) != NEXUS_RING) return 0;
    if (environment(po) != who) return 0;

    env = environment(who);
    if (!env) return 0;
    if (env->query("nexus")) {
        tell_object(who,
            "Naurcalen stirs, then settles. You are already home.\n");
        return 1;
    }
    if (who->query("nexus_recalling")) {
        tell_object(who, "The green fire is already gathering.\n");
        return 1;
    }

    who->set("nexus_recalling", 1);
    tell_object(who,
        "\nYou close your hand around Calenmir and think of the Threshold.\n" +
        "Naurcalen answers: green light spills between your fingers, and the\n" +
        "world begins to come apart at its edges.\n");
    tell_room(env,
        (string)who->query("cap_name") + "'s stone ring flares, and the air\n" +
        "around " + (string)who->query("cap_name") + " begins to come apart.\n",
        ({ who }));

    call_out("depart", 5, who);
    return 1;
}

void depart(object who) {
    if (!who || !interactive(who)) return;
    if (environment(who))
        tell_room(environment(who),
            (string)who->query("cap_name") + " unravels into green light and is gone.\n",
            ({ who }));
    who->move(BETWEEN);   // silent: no room description in transit
    call_out("beat", 5, who, 0);
}

void beat(object who, int n) {
    if (!who || !interactive(who)) return;
    if (n < sizeof(beats)) {
        tell_object(who, beats[n]);
        call_out("beat", 5, who, n + 1);
        return;
    }
    who->delete("nexus_recalling");
    tell_object(who, "\nPale radiance opens ahead of you, and the fire sets you down.\n\n");
    who->move_player(THRESHOLD,
        (string)who->query("cap_name") + " settles out of the air in a fading green light.");
}
