#pragma once

// cheapino/config.h sets TAPPING_TERM 230; we want 250 to match the
// design spec (DESIGN.md §Home row mods).
#undef TAPPING_TERM
#define TAPPING_TERM 250

#define PERMISSIVE_HOLD
#define FLOW_TAP_TERM 150
#define CHORDAL_HOLD
#define SPECULATIVE_HOLD

// Identifier the ahdinosaur/keyboard_helper community module reports to
// the host. Must match the table key in this repo's keymaps.toml.
#define KEYBOARD_HELPER_ID "cheapino-dinosaur"
