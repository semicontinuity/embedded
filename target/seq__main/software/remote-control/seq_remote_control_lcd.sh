set -o pipefail
MIDI_OUT_PORT="${1:-MIDIbox SEQ V4+ MIDI 1}"

./seq_remote_control_lcd.py "${MIDI_OUT_PORT}"
