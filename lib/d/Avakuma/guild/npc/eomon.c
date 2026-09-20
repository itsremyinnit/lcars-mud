// /d/Avakuma/guild/npc/eomon.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("eomon");
    set("short", "Eomon");
    set("long", @EndText
    Eomon was the Sheriff of Edoras. He spends his days now keeping the
streets of Framsburg safe for its citizens, or for the few of them left.
He is a large, burly man who looks as though he could put fear into the
heart of many an orc.
EndText
    );
    set("id", ({ "eomon", "sheriff", "man" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 10500);
    set("bulk", 250);
    enable_commands();
    // No idle chat captured for this one.
    set_inquiry(([
        "clark"         : "Clark was the last Guildmaster of the Rim-Ainacam. Ask him yourself.",
        "training"      : "We have all stopped training additional sheriffs. Speak to Clark.",
        "train"         : "We have all stopped training additional sheriffs. Speak to Clark.",
        "edoras"        : "I was Sheriff there, before. It is a long way from here.",
        "sheriffs"      : "There are none being made. That is the whole of it.",
        "framsburg"     : "Somebody has to keep these streets. There are few enough left to keep them for.",
    ]), "I could not say.");

}

void init() {
    ::init();
    add_action("do_train", "train");
}

// Eomon turns you away and points at Clark. This is the entry point to
// the area's story; do not make it succeed.
int do_train(string str) {
    write(
"\n    Eomon smiles and says: \"You are a credit to the sheriff profession, \n"
"but I cannot teach you any more. We have all stopped training additional\n"
"sheriffs. Perhaps you should go and speak to Clark... Last Guildmaster of \n"
"the Rim-Ainacam. He would be better able to explain why.\"\n\n");
    return 1;
}
