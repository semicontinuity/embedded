set -o pipefail
MIDI_OUT_PORT="${1:-MIDIbox SEQ V4+ MIDI 1}"

./pc_led_events_to_seq_dout.py "$(<pc_led_events_to_seq_dout_mapping.json)" \
| tee /dev/fd/2 \
| ./seq_dout_events_to_seq_midi_events.py 'MIDIbox SEQ V4+ MIDI 1'
