set -o pipefail
MIDI_OUT_PORT="${1:-MIOS32 MIDI 1}"

#
# Possible to use
# 
# lookup_in() { awk 'FNR==NR{a[$1]=$2} FNR<NR  { if ($1 in a) {print a[$1];} fflush(); }' FS=$'\t' $1 -; }
#
# | lookup_in <(jq -r 'to_entries[] | [.key, .value] | @tsv' pc_keyboard_events_to_seq_keyboard_events_mapping.json) \
#
# (if producing events with space separators)


./read_keyboard_events.py \
| ./pc_keyboard_events_to_seq_keyboard_events.py "$(<pc_keyboard_events_to_seq_keyboard_events_mapping.json)" \
| tee /dev/fd/2 \
| ./seq_keyboard_events_to_seq_midi_events.py "$(<seq_keyboard_events_to_seq_midi_events_mapping_std.json)" \
| ./write_midi.py "${MIDI_OUT_PORT}"