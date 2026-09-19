// /d/Avakuma/guild/boards/wanted_poster.c
// The wanted poster in the Rim-Ainacam conference room.
//
// Seeded with the twelve notes that stood on the original board, with
// their real posters and dates, and locked so the automatic archiver
// never ages them off. New posts go on top of them.
//
// Seeding happens once: set_save_file() restores the save if there is
// one, and the seed only runs when the board comes up empty.
#include <mudlib.h>
inherit "/std/board/bboard";

void seed_archive();

void create() {
    bboard::create();
    set_attic_dir("/d/Avakuma/data/attic");
    set_save_dir("/d/Avakuma/data");
    set_save_file("wanted");
    set_location("/d/Avakuma/guild/conference");
    set("short.text", "A wanted poster hanging here on the wall");
    if (!messages || !sizeof(messages))
        seed_archive();
}

private mapping mknote(int id, string who, int when, string what, string body) {
    return ([
        "id"     : id,
        "poster" : who,
        "time"   : when,
        "title"  : what,
        "body"   : body,
        "locked" : "root",
        "doer"   : 0,
    ]);
}

void seed_archive() {
    messages = ({
      mknote(1, "Durmal", 1298614920, "Death to sheriffs!",
":P\n"
"Death to sheriffs!\n"),

      mknote(2, "Saleth", 1307171040, "Re: To sheriffs past",
"On 01/31/08 02:27, Variel wrote:\n"
">  \n"
"> Nice to have a beer in the old guildhall... \n"
">  \n"
"> A toast to fond memories, old friends, and times past.\n"
">  \n"
">  - Variel Firefax, Grey Sheriff of Arda\n"
">  \n"
" \n"
"It's been too long, my friend. If you see me on,\n"
"send me a tell. You're one of the few wonderful\n"
"memories of old times.\n"),

      mknote(3, "Papacholo", 1312718520, "< no title >",
" \n"
" \n"
"               I Miss This Place. \n"
"                       ~Morphiend\n"
" \n"),

      mknote(4, "Glen", 1348340400, "Riona",
"I miss Riona. She was a good friend. \n"),

      mknote(5, "Stryker", 1365245880, "Memories",
"   For old times, I walked into the ruined pub at\n"
"Framsburg and pressed on the board that used to grant me\n"
"access to our old guildhall... and it worked. Imagine\n"
"my surprised when I strode into the Rim-Ainacam hall of old,\n"
"where so many laughs were shared, so many friends were made,\n"
"and so many criminals were brought to justice.\n"
"   I see several names on this board that bring a broad\n"
"grin to my face. My fellow sheriffs, those who put their\n"
"lives on the line for justice.\n"
" \n"
"Be well, my friends.\n"
" \n"
"Stryker Orcslayer, Sheriff of Arda\n"
" \n"
"Honor, Safety, Dedication!\n"),

      mknote(6, "Gorin", 1402220040, "< no title >",
"I was but a distant gleam on the horizon when the Sheriffs were\n"
"disbanded, yet still I get a palpable sense of nostalgia as I explore\n"
"this historic sight. Long live the memories.\n"),

      mknote(7, "Ailyth", 1483484820, "Glen",
"Glen, miss you too :)\n"),

      mknote(8, "Variel", 1584694260, "A note to anyone who wore a badge",
" \n"
" ... Variel Waz Here. \n"
" \n"),

      mknote(9, "Christof", 1612764300, "note",
"goodbye.\n"),

      mknote(10, "Still", 1621812120, "< no title >",
"Greetings,\n"
"This is nice that this still exists.\n"),

      mknote(11, "Chesed", 1757947800, "The irony, the delicious irony",
"**You are staring in horror at a sheriff's badge and a feathered\n"
"cap pinned to the board with a blackened, rusty dagger**\n"
" \n"
"I cannot tell you the joy it brings me to come here and to leave\n"
"these mementos for whoever comes behind. There are no Sheriffs\n"
"in Arda, and rogues like myself run wild. \n"
" \n"
"**A signature is scrawled below, but you can't make it out**\n"),

      mknote(12, "Woric", 1781334300, "i was here",
"once\n"),
    });

    num_messages = sizeof(messages);
    set_id_ref(12);
    save_object(file);
}
