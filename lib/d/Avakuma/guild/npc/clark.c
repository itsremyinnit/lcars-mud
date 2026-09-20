// /d/Avakuma/guild/npc/clark.c
#include "/d/Avakuma/avakuma.h"
inherit "/d/Avakuma/std/avakuma_npc";

void create() {
    ::create();
    set_name("clark");
    set("short", "A roughly-dressed sheriff");
    set("long", @EndText
    This weathered-looking elf has the appearance of an old and
experienced officer. His shrewd eyes move over a great many reports and
you are certain they miss nothing. He is plainly tackling something very
dire. You have no doubt this former sheriff always got his man, but the
lines on his face say there is a deep worry in him now.
EndText
    );
    set("id", ({ "clark", "sheriff", "roughly-dressed sheriff", "elf" }));
    set("gender", "male");
    set("capacity", 10000);
    set("max_cap", 10000);
    set("max_vol", 10000);
    set("volume", 10000);
    set("mass", 9000);
    set("bulk", 250);
    enable_commands();
    set_chat(6, ({
        ({ "say", "says", "I KNOW there's got to be a way..." }),
        ({ "say", "says", "Get out of my way. Can't you see I'm trying to save a town here?" }),
        ({ "emote", "$N sneers at you." }),
        ({ "emote", "$N ponders something." }),
        ({ "emote", "$N prods a pile with his quill, as if thinking idly." }),
        ({ "emote", "$N leans over and examines some battle reports." }),
        ({ "emote", "$N tilts his head as if listening." }),
    }));
    set_inquiry(([
        "sheriffs"      : "We sheriffs have decided to make our last stand here.",
        "sheriff"       : "We sheriffs have decided to make our last stand here.",
        "training"      : "Alas, I have given up that task. Would you really seek to 'study' under us?",
        "train"         : "Alas, I have given up that task. Would you really seek to 'study' under us?",
        "rim-ainacam"   : "It was a fine thing once. Ask Eomon; he still believes it.",
        "guildmaster"   : "The post is mine, for whatever that is worth now.",
        "orcs"          : "They come down from Mount Gundabad and they do not stop coming.",
        "gundabad"      : "North of here, and the source of all of it.",
        "framsburg"     : "We started down the path to Law and Order in this town. It seemed right to end here.",
        "dano"          : "Dano came back with us. He sits in the bar now.",
        "eomon"         : "Eomon was Sheriff of Edoras. He is a better man than the times deserve.",
    ]), "Ahh, that is one thing of which I know naught!");

}

void init() {
    ::init();
    add_action("do_study", "study");
}

// The area's story. Eomon sends you here; "ask clark about training"
// points at this verb.
int do_study(string str) {
    write(
"\n    Clark looks up from his work for a moment and smiles at you, his face\n"
"for one brief moment showing a hint of the happiness which is now totally\n"
"absent from his diminished career.\n");
    message("emote", (string)query("cap_name") + " looks up at you with a smile.\n",
            environment());
    write(
"\n    \"I'm sorry...\" he begins. \"But I cannot train you anymore, my friend.\n"
"That function is now beyond my power. Dano, Eomon, and I returned to \n"
"Framsburg where we first started down the path to Law and Order because \n"
"we had little left to do with our lives after our noble profession \n"
"dissolved into nothingness. We know it's a losing struggle fighting \n"
"against the dark tide from the Mount Gundabad to the north, but we can't \n"
"think of a better way to see our lives to the very end...\"\n"
"\n"
"\n    The elf pauses for a second, his eyes almost misty, then continues on.\n"
"\"I could not bear to train anyone again in the arts of the Sheriff, for\n"
"it would only be to induct them in a doomed number, and never again would\n"
"I endure watching my charges get cut down. It would surely result in me\n"
"wasting away with grief as the Elves of old once did. My handcuffs are\n"
"neatly hung and my club rests somewhere deep where no evil can touch it.\n"
"I shall not pick them up again.\"\n"
"\n"
"\n    \"If you have it in you to aid us in some way by stemming the rush of\n"
"evil from the passes northward, I beg you to at least spare us a few\n"
"extra weeks or days to live yet. It is a fool's errand, I know, but I\n"
"cannot help but be selfish in this request. Nothing can stop the Dark\n"
"Lord's conquest of Middle Earth, I know that now. But I often still look\n"
"back to the past - to when things were brighter - and think to myself. \n"
"Of what could have been...\"\n"
"\n"
"    Clark falls silent and returns to his papers, too lost in himself to\n"
"even bid you farewell.\n\n");
    message("emote", (string)query("cap_name") +
            " lets his head fall down to his papers again.\n", environment());
    return 1;
}
