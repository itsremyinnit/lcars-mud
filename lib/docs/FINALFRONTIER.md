# FinalFrontier — the Enterprise-D

Companion to HANDOFF.md and AVAKUMA.md. This covers /d/FinalFrontier/.

A USS Enterprise-D, late in its seventh season: the Borg are behind the
captain, Q has come and gone several times, and the crew has been
de-evolved, duplicated, kidnapped and replaced often enough to be tired
of it.

Built as an experiment. Jeremy and Jarrod built an Enterprise on the
original T2T, with Picard, Q, phasers and custom combat, in a private
repo. This one was built from scratch without reference to theirs, to
see how close an independent build lands. Compare them before changing
the voice.

---

## 1. Shape

Reached through the Far Concourse east arch in the Nexus, which opens
onto Ten-Forward. One-way, like the Towers Arch: you arrive as a guest,
and the ring's `recall` is the way home.

    /d/FinalFrontier/
      adm/d_master.c        domain permissions
      frontier.h            shared paths
      std/ff_room.c         room base
      std/ff_npc.c          crew base
      std/turbolift.c       the lift, shared by every car
      npc/                  fourteen crew
      deck01/  bridge, ready room, aft passage, observation lounge
      deck06/  transporter, brig, cargo bay, cargo control
      deck08/  quarters arc, guest quarters, aft viewport
      deck10/  Ten-Forward
      deck11/  holodecks, arboretum
      deck12/  sickbay
      deck36/  main engineering

28 rooms. Decks 6 and 8 are closed loops. Each deck has at least one
turbolift car; decks 6 and 8 have two.

The bases mirror Avakuma's (sealed exits, tracked spawning, typed chat,
bounded wandering) and were copied rather than shared, so the two
domains stay independent. See AVAKUMA.md for why each of those exists.

---

## 2. Conventions

Exits:

- Cardinals where you are navigating: corridors, the quarters arc.
- Named exits where the destination is its own place: readyroom,
  lounge, holodeck, transporter, brig, cargo, cells, lift.
- `out` where a room has one way back.
- No port or starboard as exits. They stay in the prose, which is
  where that vocabulary belongs.

Compass, for decks laid out as rings:

- Forward is north. Port is therefore WEST and starboard is EAST.
  Getting this backwards is easy and has happened.
- Trace every ring on paper before wiring it. Each step must reverse
  cleanly, and walking the whole ring must return you to where you
  started. Rooms can connect correctly by name while the directions
  describe a shape that does not exist, and it feels wrong to walk
  long before anyone can say why.
- Decks 6 and 8 are both traced and closed.

Register, split deliberately:

- Public spaces are plain and functional. Corridors, engineering,
  cargo and the transporter room are described the way the people who
  work in them would describe them. A warp core is a machine.
- Personal spaces are loaded. The ready room, quarters and the
  holodeck are mostly subtext: objects that mean something to whoever
  lives there, left unexplained.

This matches how the original T2T Enterprise was written.

---

## 3. The turbolift

`std/turbolift.c`. You do not walk out of a lift into a corridor; you
tell it where to go. Destinations are places, not decks, because
turbolifts move laterally as well as vertically:

    stops             list every destination, in deck order, with an
                      asterisk on the one this car serves
    bridge            say a destination by name
    deck 6            a deck; asks which part if there are several
    deck 6 aft        a deck and a section

Each car is a four-line file inheriting the lift and giving it an `out`
exit. Adding a stop means one line in STOPS, one add_action for its
name, and a room with an exit into a car.

Two gotchas that each cost a round trip:

- The car figures out which stop it serves by matching its own `out`
  exit against the stop table, so a car's `out` must point at exactly
  the room its stop names.
- Update `std/turbolift` BEFORE the deck directories. Updating a deck
  first recompiles its cars against the old lift and they keep the old
  stop table.

`sort_array` with a named comparator did not order the stops here. They
are sorted by hand instead.

---

## 4. The brig

`deck06/brig_cells.c`. Three cells with working forcefields, usable as a
holding area for players.

    status                  list the cells
    enter cell <n>          step in (field must be down)
    activate [cell] [<n>]   raise a field
    deactivate [cell] [<n>] drop a field
    brig <person> [<n>]     put somebody in a cell and seal it
    release <person|cell>   open it and let them out

The cell number is optional wherever only one cell makes sense:
`deactivate field` with one field up drops that one.

Occupancy is pruned on every command, because a prisoner can leave by
means the room does not control: a wizard's recall, a goto, a summon.
Treat what the room tracks as a hint, never truth.

The room description names who is in which cell. _look.c reads
query("long") directly and query is nomask, so there is no long() to
override; the property is rewritten whenever occupancy changes. Note
that ROOM defines neither init() nor long(), so a room must not call
::init() or ::long().

Not built: a timed sentence like the Avakuma jail's.

---

## 5. Crew

Fourteen, in npc/. Named officers get a few idle lines and a handful of
`ask` topics, deliberately brief. None of them gives speeches: an
extended speech from a character this well known is where an imitation
shows its seams.

    Picard            ready room
    Riker             bridge; wanders deck 1
    Data              bridge, at ops
    Worf              security office, deck 6
    La Forge          main engineering, with two engineers
    Crusher, Ogawa    sickbay
    Guinan            Ten-Forward, behind the bar
    Troi              Ten-Forward; wanders deck 10
    Barclay           deck 11; wanders deck 11
    Transporter chief transporter room three
    Spot              deck 8; wanders deck 8
    Crewmen           one each on decks 6, 8 and 10; wander their decks

O'Brien left for Deep Space Nine at the start of season six, so the
transporter chief is somebody else. He has a goatee and is extremely
tired of what people think when they see it. Ask him about it.

Wanderers move by exits, and turbolift cars have none, so nobody crosses
decks on their own. One shared range list therefore serves every
generic crewman: one on deck 6 cannot reach deck 8.

Spot used to be scenery in the deck 8 port corridor. She is an NPC now,
and the room keeps only her hairs.

---

## 6. The thread

**Deliberate. Do not explain it, and do not tidy it away.**

Something happened on deck 11. Nobody says what. The pieces:

- Ready room: a terminal open on PERSONNEL - PROMOTION RECOMMENDATIONS.
- Observation lounge: a roster with three names circled, and ASK HIM.
- Aft passage replicator: thousands of cups of tea, then once, three
  weeks ago, hot chocolate with cinnamon at 0340.
- Engineering: a fault on the deck 11 plasma conduit, closed three
  times as no fault found, reopened at 0340 three weeks ago.
- The master display: three amber marks on deck 11.
- Deck 8: an open maintenance hatch, a toolkit missing its spanner, a
  work order for the deck 11 conduit.
- Deck 11: the conduit open, a phase burn with four tally marks beside
  it, a work light on for nineteen days, and the missing spanner.
- Holodeck two: a program suspended mid-frame. A small kitchen built
  from memory, rain stopped outside, hot chocolate with cinnamon on the
  stove, two used cups, one chair pushed back fast.
- Arboretum: hand-thrown clay pots, one with a chip smoothed down. The
  same pot, planted and watered, sits in guest quarters 0804.
- Transporter log: four transports to deck 11, one person, after 0300.
- Security: an incident report on the deck 11 conduit, findings empty,
  recommendation "Leave it."
- Cargo control: personal effects held pending instruction for eleven
  months, no name. In the bay, a container with its seal broken and
  something missing from the packing.
- La Forge: "Closed it four times. Still open. Leave it with me."
- Worf: "The recommendation stands."
- Troi likes chocolate and asks why you want to know.
- Barclay knows nothing about a kitchen.

It is built to be pulled on and never answered. If it is ever answered,
that is a decision for Jeremy and Jarrod, not something to be filled in.

---

## 7. Deferred

- A timed sentence for the brig.
- The four sealed compartments on deck 6 stay sealed. That is the point
  of them.
- Deck 10 and 11 have one lift each; fine at their size.
- Q. Built on the original T2T, deliberately not here yet.
- Phasers and combat, likewise.
- Anything that crosses decks on its own, which would need wanderers
  that can use a lift.
