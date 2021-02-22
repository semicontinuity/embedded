set -o pipefail
MIDI_OUT_PORT="${1:-MIDIbox SEQ V4+ MIDI 1}"

./midi_sysex_send_set_server.py "${MIDI_OUT_PORT}"
