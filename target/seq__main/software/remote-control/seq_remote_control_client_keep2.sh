set -o pipefail
MIDI_OUT_PORT="${1:-MIDIbox SEQ V4+ MIDI 1}"

seq_client_mode() {
  echo "F0 00 00 7E 4D 00 09 00 02 F7" | ./midi_write_bytes.sh "${MIDI_OUT_PORT}"
}

seq_text() {
  local X=$1
  local Y=$2
  local TEXT=$3
  echo -e "$X\t$Y\t$TEXT" | ./seq_lcd_events_to_seq_midi_events.py | ./midi_write_bytes.sh "${MIDI_OUT_PORT}"
}


seq_client_mode
seq_text 0  0 "                    "
seq_text 20 0 "                    "
seq_text 40 0 "                    "
seq_text 60 0 "                    "

(cat <<'EOF'
OFF	GP_1_G
OFF	GP_2_G
OFF	GP_3_G
OFF	GP_4_G
OFF	GP_5_G
OFF	GP_6_G
OFF	GP_7_G
OFF	GP_8_G
OFF	GP_9_G
OFF	GP_10_G
OFF	GP_11_G
OFF	GP_12_G
OFF	GP_13_G
OFF	GP_14_G
OFF	GP_15_G
OFF	GP_16_G
OFF	DIRECT_TRACK_1_G
OFF	DIRECT_TRACK_2_G
OFF	DIRECT_TRACK_3_G
OFF	DIRECT_TRACK_4_G
OFF	DIRECT_TRACK_5_G
OFF	DIRECT_TRACK_6_G
OFF	DIRECT_TRACK_7_G
OFF	DIRECT_TRACK_8_G
OFF	DIRECT_TRACK_9_G
OFF	DIRECT_TRACK_10_G
OFF	DIRECT_TRACK_11_G
OFF	DIRECT_TRACK_12_G
OFF	DIRECT_TRACK_13_G
OFF	DIRECT_TRACK_14_G
OFF	DIRECT_TRACK_15_G
OFF	DIRECT_TRACK_16_G
EOF
) | ./seq_remote_control_leds.sh "${MIDI_OUTPUT_PORT}"

while true; do
  seq_client_mode
  sleep 1
done

