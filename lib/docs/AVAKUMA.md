# Avakuma — the Tolkien domain

Companion to HANDOFF.md, which covers infrastructure and the Nexus. This
file covers /d/Avakuma/ only.

Framsburg, the Sheriff's Guild, Edoras and the orc newbie dungeon were
built on the original T2T by Jeremy and Jarrod as their introductory admin
project. That content is their own work. Everything here is a
reconstruction of it from in-game captures, with the prose rewritten by
its original author rather than copied.

Named for Tolkien's Avakuma, the Outer Void. Accents dropped: the name
becomes a directory, a [Domain] entry and a path prefix.

---

## 1. Shape

A standalone domain, deliberately not under /d/Nexus/. Rooms inherit the
stock ROOM through the Avakuma base, never the Nexus base, so nothing here
is coupled to Nexus code. The one exception is RING_D, which Avakuma calls
into; the dependency runs Avakuma to Nexus and must not be reversed.

    /d/Avakuma/
      adm/d_master.c          domain permissions
      avakuma.h               shared paths
      std/avakuma_room.c      room base
      std/avakuma_npc.c       NPC base
      std/avakuma_shop.c      shop base (see the warning in section 4)
      obj/                    trash_can, campfire
      framsburg/  12 rooms    npc/ obj/ storeroom.c
      barracks/    7 rooms    npc/
      orc/         8 rooms    npc/
      guild/      11 rooms    npc/ obj/ boards/ storeroom.c

38 rooms, all with finished prose. 26 NPC types.

Entry: the Towers Arch, west from the Nexus Concourse of Arches, opens
onto framsburg/pub. One-way by design; the ring's `recall` is the way
back. `push board` in the pub is the only way into the guild.

---

## 2. The room base

/d/Avakuma/std/avakuma_room.c inherits ROOM and DOORS. Defaults to lit and
indoors.

- set_outdoors([zone]) hands light to WEATHER_D, giving the day/night
  cycle and live weather. _look.c appends the weather text on its own.
  Zones are stored but this weather daemon keeps one global state, so the
  letter is decorative.
- set_dark() for an unlit interior.
- add_sealed(dir, msg) for a visible but refused exit. Call it AFTER
  set("exits", ...), or the exits mapping overwrites it.
- spawn_objects(), see section 3.

Weather-notice relay. WEATHER_D sends change notices ("it begins to rain")
by calling message() on each registered ROOM, but /std/room.c defines no
receive_message, so they are dropped mudlib-wide. The base relays them to
the livings in the room. Avakuma is the only place on this MUD where you
see weather change while standing still.

exit_order. The exits line is built from keys(exits), which is hash order,
not insertion order. /cmds/std/_look.c was extended to honour an
exit_order property naming directions in display order; anything missing
from it is appended in keys() order, so a partial list is safe. Every
Avakuma room pins the order captured from the original. Nexus rooms set
none and are unaffected. Worth knowing: T2T's own exit order is also hash
order, not authored. We pin it because the transcripts recorded it.

---

## 3. Spawning

    set("objects", ([ "/d/Avakuma/framsburg/npc/nurse" : 1 ]));
    spawn_objects();

Two reasons this does not use /std/room.c's reset():

1. reset() runs from the stock create(), BEFORE the inheriting room has
   set "objects", so there is nothing to spawn when it looks.
2. reset() counts NPCs by what is present in the room. Once a wanderer
   leaves, the room sees itself short and clones a replacement, and the
   population grows without limit.

spawn_objects() tracks what it spawned instead, so a wanderer still counts
while away and only a destructed one is replaced. It reschedules itself
every respawn_time seconds (default 300), which also gives respawn after
death.

Shop rooms use spawn_here(path) instead, a simple clone-if-absent, because
they cannot inherit the room base (section 4).

---

## 4. Shops, and why they are a special case

/d/Avakuma/std/avakuma_shop.c inherits /std/shop ONLY, not AVAKUMA_ROOM.
Both inherit ROOM, and FluffOS does not share the duplicate: the second
copy tries to redefine ROOM's nomask property functions (set, query, _set,
_query, query_temp) and the compile fails outright. This is not a
preference, it is a hard error.

Consequence: shop rooms have no weather relay, no set_outdoors, no
add_sealed, no exit_order, no spawn_objects. All indoors and static, so
the only real loss was spawning, which spawn_here() covers.

list, buy, sell and value are REPLACED, not inherited, because:

1. Stock /std/shop.c sells from storeroom + CENTSTORE, the central
   warehouse shared by every shop on the MUD. That is why "buy axe" in
   Belinda's shop once handed over /obj/axe from Fooland. Avakuma shops
   sell from their own storeroom and nothing else.
2. The stock messages are TMI-2's; these match T2T's.

Behaviour, all matching the original:

- Listings show duplicates on their own lines, no deduplication.
- Zero-value items list at 0 and can be bought but NOT handled.
- handle <item> / return <item>, with the room refusing to let you leave
  while holding merchandise (pre_exit_func to "leaving").
- Numbered disambiguation: "handle sword" lists sword 1, sword 2 and asks
  which; "handle sword 1" takes the first.
- Resale is 14/25 of value (a 34 gold backpack fetches 19), capped at 100
  gold with "That exceeds my budget."

Two shops: guild/guild_shop.c (Belinda) and framsburg/armoury_wagon.c
(Malcolm), each with its own self-restocking storeroom keeping two of
everything.

Not built: the list filters the original signs advertise (by type, by
price, by armour coverage) and sell-from-container.

Watch the ids. The broadsword originally answered to "sword", which made
"sword 1" pick a broadsword instead of a short sword. Overlapping ids
break disambiguation quietly.

---

## 5. NPCs

Why /d/Avakuma/std/avakuma_npc.c exists: stock /std/monster.c's
monster_chat() picks a pre-formatted string and emits it with tell_room(),
tagging every line with the message class "tell_room". That makes an NPC's
speech indistinguishable from its emotes to anything downstream, so colour
coding, ignore handling and anything else keyed on message class cannot
tell them apart. On the original T2T this meant every NPC had to be
retuned by hand when colours were added. Here, chat lines are typed:

    set_chat(5, ({
        ({ "say",   "murmurs", "I can't believe I was injured by that Orc." }),
        ({ "emote", "$N ponders something." }),
    }));

"say" lines go out as class "say" with the verb under the NPC's control,
so murmurs, whispers and yells stay available and still classify as
speech. "emote" lines go out as class "emote". $N is the NPC's capitalised
name. Plain strings still fall through to stock tell_room.

Chat rates are per NPC and must account for how many share a room. Three
soldiers at 8% each is 24% per beat for the room, which floods the screen.
The injured soldiers run at 3%.

Wandering is bounded by a whitelist, not stock forbidden_rooms:

    set_range(45, ({ "/d/Avakuma/framsburg/road_north", ... }));

A blacklist would mean listing every room a townsperson must not enter,
including rooms added later. With a whitelist a new room is out of bounds
by default. Orcs are confined to the camp and do not get the battlefield,
which is the seam. Townsfolk do not cross it either, except the cute
little girl, who is deliberately allowed onto the battlefield because that
is where she was found.

Wanderers: the little boy, the cute little girl, the intimidating guard,
the half-orcs. Speeds 45 to 70 seconds; anything faster reads as a parade.

Dialogue uses the mudlib's existing "ask <npc> about <topic>", which reads
an "inquiry" mapping. /cmds/std/_ask.c was patched for the same
message-class reason as chat, and to support a per-NPC "inquiry_default"
brush-off. Helper: set_inquiry(topics, fallback).

### The story

Not decoration, and worth preserving exactly:

- "train" on Eomon turns you away and sends you to Clark.
- "ask clark about training" points at the verb "study".
- "study" gives Clark's speech: the Rim-Ainacam dissolved, he and Dano and
  Eomon came back to Framsburg to die where they started, and he will not
  train anyone into a doomed number. It is framed by two emotes.

Clark is the last Guildmaster. The armchair description in his office
saying the post is unfilled is about him. The hospital, the barracks built
after the raids, the wounded on both sides of the battlefield and the
guildhall hidden behind a fake derelict street all point at this.

The orc camp deliberately mirrors Framsburg: injured orcs with a medic
against injured soldiers with a nurse, a chieftain in the one sound house
against a leader in the one sheltered ruin.

---

## 6. Objects

Trash cans (obj/trash_can.c), in the kitchen, both shops and the guild
bar. Accepts anything not living and not prevent_drop, then destroys it:
"You feel a lot better by helping the environment." / "Ok." / "From deep
inside the trash can you hear a muffled BOOM!"

It delegates the destroying to /adm/daemons/disposal_d.c, and here is why.
/adm/simul_efun/overrides.c permits destruct() only when the caller's euid
matches the target's, or the caller is root or an admin. A domain object
(uid Avakuma) therefore cannot destroy a mudlib object (uid Backbone). And
valid_seteuid() only lets an object claim an euid it already owns, so the
can cannot elevate itself. The daemon lives under /adm and carries the
root uid. It is deliberately narrow: empty(container) and kill_object(ob),
both refusing livings and prevent_drop items.

The campfire (obj/campfire.c) in the orc meeting house refuses "pull
brand" and "extinguish". Note it inherits OBJECT, which defines no
create(), so it must NOT call ::create() -- unlike CONTAINER.

Shop stock, ten items: sheriff's chain 176, sheriff's breastplate 260,
lochaber axe 144, backpack 34 (Belinda); short sword 60, large shield 46,
long sharp spear 32, extremely large broadsword 418, backpack 32, torch 0
(Malcolm). Descriptions are the originals.

---

## 7. The wanted poster

guild/boards/wanted_poster.c, in the conference room. Seeded with the
twelve notes that stood on the original board from 2011 to 2026, with
their real posters and dates, locked so the archiver never ages them off.
The seed runs only when the board comes up empty. The asterisk beside each
note marks it locked; that is the visible difference from T2T and the
price of permanence.

get_time() in /std/board/bboard.c was changed from the stock "Wed Jun 30"
to MM/DD/YY HH:MM to match. Affects every board.

Post 1 is Durmal's "Death to sheriffs!", which is also the line knifed
into the board in the pub at the other end of the passage.

---

## 8. The jail and the corps hook

guild/jail.c. Thrown in by the guard, you are shackled and south is
refused until a Framsburg barracks guard releases you (150s). Walked in
under a green ring, you are a visitor and south works.

The release is a call_out, which does NOT survive a reboot, so leaving()
also checks the expiry timestamp directly. Keep that check.

The guard in guild/entrance_hall.c asks /d/Nexus/adm/ring_d.c what corps
the visitor is wearing, never about Calenmir by name. Green gets a
wordless deference; anything else gets warned once, then jailed. A new
corps is a data change rather than a code change.

Wizard powers stay keyed to Calenmir specifically in cmd_hook in
/std/user.c. Other corps confer no wizardry. Do not widen that check to
"wearing a ring."

---

## 9. Deferred

- Shops: Meryne's food and drink in the Framsburg kitchen (beer 2, whiskey
  10, stew 13; the menu is already readable), and the list filters for
  both existing shops.
- Tarlyn's training (cost, train), against the skill system in
  /std/living/skills.c. Needs a decision on what sheriffs train in.
- The nurse's healing and reviving. She is a functional healer in the
  original. Ties into the death and ghost system.
- The dart game in the guild bar. A real playable game with a persistent
  scoreboard, and Dalin offers a prize for three bulls-eyes. Ours
  preserves the original board verbatim as a plaque under "read
  scoreboard": twenty names and their throw counts, the largest 873,861
  darts thrown. Those are real people. A live game would want its own
  board starting empty.
- Arming the NPCs. The weapons and armour now exist as objects. The
  intimidating guard should carry a long sharp spear and a leather vest,
  the chef a cleaver and cooking wine, the officer a large book and a
  beautiful sword, Dano a feathered cap and a sheriff's badge (which are
  the two items pinned to the wanted poster in Chesed's 2025 note), and so
  on.
- Combat stats for the orcs, and a decision on whether they are meant to
  be killable at all.
- Functional objects not yet built: the supply room chest and badges, the
  scribe's bundle on the Guildmaster's desk.
- The Framsburg barracks locked south door. Answers neither knock nor
  bang.
- The river and the ford. The Anduin runs southwest and southeast of the
  town entrance and the ford lies south. Described but not modelled. The
  entrance's south is sealed as a future expansion; east and west out of
  town are omitted entirely.
- Dorgy and the pipe cart at the town entrance, never captured. He
  wanders.

---

## 10. Mudlib changes made for Avakuma

All of these are in shared code and affect the whole MUD.

/cmds/std/_look.c
    honours exit_order; bracketed counts ("An injured soldier [3]")
    instead of "Three An injured soldiers"

/cmds/std/_ask.c
    answers as class "say" not "tell_room"; per-NPC inquiry_default;
    tells the asker what they asked

/cmds/std/_glance.c
    takes a direction; expands n/e/sw etc; "breif" typo fixed

/std/board/bboard.c
    get_time() to MM/DD/YY HH:MM

/std/container.c
    terse "Ok." confirmations and "Too bulky.", matching T2T; room
    messages unchanged

/std/user.c
    quit() now clears prevent_drop items, fixing "An object vanishes.
    Tell a wiz!" on every logout

/adm/daemons/disposal_d.c
    new; root-uid destruction for objects that cannot destroy across uids
