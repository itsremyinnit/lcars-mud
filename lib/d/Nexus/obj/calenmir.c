// /d/Nexus/obj/calenmir.c
// Calenmir, "green jewel": a stone-hewn focus ring.
// Within its crystal burns Naurcalen, "green fire".
// Bound to its bearer: once held, it refuses to leave their inventory.

#include <mudlib.h>
#include <move.h>

inherit ARMOR;

private string *runes = ({
    "the Rune of the Unbroken Road",
    "the Rune of the Kindled Hearth",
    "the Rune of the Far Shore",
    "the Rune of the Standing Stone",
    "the Rune of the Open Door",
    "the Rune of the Returning Light",
});

string rune_for(string name) {
    int i, sum;
    for (i = 0; i < strlen(name); i++) sum += name[i];
    return runes[sum % sizeof(runes)];
}

void bind_to(string name) {
    set("owner", name);
    set("long",
        "A heavy band, rough-hewn from a single piece of dark stone. A clear\n" +
        "crystal is set into its face, and deep within the crystal a small green\n" +
        "flame burns without flickering: Naurcalen, the green fire. Fine cracks\n" +
        "run through the stone like the veins of a leaf.\n" +
        "Carved on the inner band is " + rune_for(name) + ", the mark of " +
        capitalize(name) + ".\n");
}

void create() {
    seteuid(getuid());
    set("id", ({ "ring", "calenmir", "calenmîr", "stone ring" }));
    set("short", "Calenmîr, a stone-hewn ring");
    set("long", "A heavy band of dark stone, with a green flame asleep in its crystal.\n");
    set("armor", 0);
    set("type", "ring");
    set("prevent_drop", 1);
    set("equip_func", "kindle");
    set("unequip_func", "dim");
}

mixed query_auto_load() { return 0; }  // LCARS-MUD: re-forge on login is the single source, no autoload stacking

int move(mixed dest) {
    int res;
    if (environment()) return MOVE_NOT_ALLOWED;  // bound: never leaves its bearer
    if (stringp(dest)) dest = find_object_or_load(dest);
    if (!objectp(dest)) return MOVE_NOT_ALLOWED;
    res = ::move(dest);
    if (res == MOVE_OK && dest->query("name")) bind_to((string)dest->query("name"));
    return res;
}

void kindle() {
    if (environment() && (int)environment()->query("nexus_ceremony") == 2) {  // LCARS-MUD: first wearing
        "/d/Nexus/adm/ceremony_d"->journey(environment());
        return;
    }
    write("Deep in the crystal, Naurcalen wakes. Green light seeps through the\n" +
          "cracks in the stone, and your thoughts feel suddenly, sharply focused.\n");
    say((string)this_player()->query("cap_name") + "'s stone ring kindles with a soft green light.\n");
}

void dim() {
    write("Naurcalen settles back to a sleeping ember, and the green light fades.\n");
}

void init() {
    add_action("do_ask", "ask");
}

string answer(string t) {
    object env = environment(this_player());
    string owner = (string)query("owner");

    if (strsrch(t, "here") != -1 || strsrch(t, "where") != -1)
        return "You stand in " + (env ? (string)env->query("short") : "no place at all") +
               ". I have seen stranger rooms. Not many, but some.";
    if (strsrch(t, "arch") != -1 || strsrch(t, "door") != -1)
        return "The arches are doorways to other realities. Your will opens them, and I lend it focus. " +
               "Some are ready. Others are still dreaming.";
    if (strsrch(t, "rune") != -1 || strsrch(t, "mark") != -1)
        return "I carry " + rune_for(owner ? owner : "") + ". It is yours, and no one else's. " +
               "I would not answer to another hand.";
    if (strsrch(t, "flame") != -1 || strsrch(t, "fire") != -1 || strsrch(t, "naurcalen") != -1)
        return "Naurcalen, the green fire. It burns on will, not wood. Keep yours steady, " +
               "and it will never go out.";
    if (strsrch(t, "name") != -1 || strsrch(t, "calenm") != -1 || strsrch(t, "you") != -1)
        return "I am Calenmîr, the green jewel. Old enough to be patient, young enough to be curious.";
    return "On that, I confess, the stone is silent. Ask me of this place, the arches, " +
           "your rune, or the flame.";
}

int do_ask(string str) {
    string who, topic;
    if (!str || sscanf(str, "%s about %s", who, topic) != 2) return 0;
    if (!id(lower_case(who)) || environment() != this_player()) return 0;
    write("A voice like wind over old stone speaks from your ring:\n  \"" +
          answer(lower_case(topic)) + "\"\n");
    say((string)this_player()->query("cap_name") +
        " murmurs to a stone ring, and it seems to murmur back.\n");
    return 1;
}
