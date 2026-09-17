// /d/Nexus/adm/ceremony_d.c: Calenmir finds a new wizard; on first wearing, it carries them home.
// Player flag "nexus_ceremony": 1 = ring on its way, 2 = ring given, not yet worn.
#include <mudlib.h>
#include <move.h>
#include "/d/Nexus/nexus.h"
inherit DAEMON;

#define BETWEEN "/d/Nexus/rooms/between"

private string *beats = ({
    "You are falling upward. Stars wheel past like sparks thrown from a forge,\n" +
    "then whole galaxies, turning slowly in the dark like great lamps being lit.\n" +
    "The cold should frighten you. It doesn't. The green fire keeps you warm.\n",

    "\nThe stars smear into ribbons, and the ribbons into rivers. You glimpse\n" +
    "mountains rising and wearing away, cities kindling and going quiet, a child\n" +
    "learning to read by candlelight. Centuries pass like breaths, and you\n" +
    "understand, without being told, that none of it is lost.\n",

    "\nThen even time falls away. There is only thought: yours, and something\n" +
    "vaster, patient and old, turning toward you the way a sunflower turns to\n" +
    "light. It knows your name. It has, you realize, been waiting for you.\n",

    "\nFar ahead, a single point of pale radiance opens like a door left ajar.\n" +
    "The green fire gathers around you, bright and sure, and carries you\n" +
    "toward it.\n",
});

void create() { seteuid(getuid()); }
void clean_up() { }

private object find_ring(object who) {
    object *inv = all_inventory(who);
    int i;
    for (i = 0; i < sizeof(inv); i++)
        if (base_name(inv[i]) == NEXUS_RING && inv[i]->query("owner") == who->query("name"))
            return inv[i];
    return 0;
}

// Called by makewiz when the new wizard is online.
int begin(object who) {
    object po = previous_object();
    if (!who || !po || strsrch(file_name(po), "/cmds/adm/_makewiz") != 0) return 0;
    who->set("nexus_ceremony", 1);
    call_out("deliver", 2, who);
    return 1;
}

// Called by the player object at login.
int resume(object who) {
    if (!who || previous_object() != who) return 0;
    if ((int)who->query("nexus_ceremony") == 1) call_out("deliver", 3, who);
    else if ((int)who->query("nexus_ceremony") == 2) call_out("remind", 3, who);
    return 1;
}

void deliver(object who) {
    object ring;
    string cap;
    if (!who || !interactive(who) || (int)who->query("nexus_ceremony") != 1) return;
    if (!find_ring(who)) {
        ring = new(NEXUS_RING);
        if (!ring || ring->move(who) != MOVE_OK) return;
    }
    who->set("nexus_ceremony", 2);
    cap = (string)who->query("cap_name");
    tell_object(who,
        "\nA point of green light kindles in the air before you, no bigger than a spark.\n" +
        "It grows, and turns, and settles into your open palm: a heavy band of dark\n" +
        "stone, and deep within its crystal, a small green flame just beginning to wake.\n\n" +
        "A voice like wind over old stone speaks from within it:\n" +
        "  \"You have been judged worthy. Great power waits within me, and within you.\n" +
        "   Wear me, and I will show you where you belong.\"\n\n" +
        "(Type: wear ring)\n");
    if (environment(who))
        tell_room(environment(who),
            "A spark of green light kindles before " + cap + " and settles into " +
            cap + "'s hand as a ring of dark stone.\n", ({ who }));
}

void remind(object who) {
    if (!who || !interactive(who) || (int)who->query("nexus_ceremony") != 2) return;
    tell_object(who,
        "\nCalenmîr stirs among your belongings, patient as stone.\n" +
        "  \"Wear me,\" it murmurs, \"whenever you are ready.\"\n\n" +
        "(Type: wear ring)\n");
}

// Called by the ring the first time it is worn.
void journey(object who) {
    object po = previous_object();
    string cap;
    if (!who || !po || base_name(po) != NEXUS_RING || environment(po) != who) return;
    if ((int)who->query("nexus_ceremony") != 2) return;
    who->delete("nexus_ceremony");
    cap = (string)who->query("cap_name");
    tell_object(who,
        "\nThe instant the ring closes around your finger, Naurcalen roars awake. Green\n" +
        "fire races up your arm and through your chest, and the world around you\n" +
        "turns thin as paper, then thinner, then gone.\n\n");
    if (environment(who))
        tell_room(environment(who), cap + " flares with green light, and is gone.\n", ({ who }));
    who->move(BETWEEN);  // silent: no room description in transit
    call_out("beat", 8, who, 0);
}

void beat(object who, int n) {
    if (!who || !interactive(who)) return;
    if (n < sizeof(beats)) {
        tell_object(who, beats[n]);
        call_out("beat", 8, who, n + 1);
        return;
    }
    tell_object(who, "\nThe light takes you in.\n\n");
    who->move_player(THRESHOLD, (string)who->query("cap_name") + " dissolves into the light.");
    tell_object(who,
        "\nA voice like wind over old stone speaks from Calenmîr:\n" +
        "  \"Welcome home, " + (string)who->query("cap_name") + ". Everything beyond this place\n" +
        "   is yours to shape. Ask me anything you like; I have waited a long time to talk.\"\n\n" +
        "(Try: ask ring about flame, or ask ring about here.)\n");
}
