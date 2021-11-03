#### Base layer (Engram)

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             |     |     |     |
+-----+  y  |  o  |  u  +-----+                 +-----+  l  |  d  |  w  +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|  b  |     |     |     |  z  |                 |  q  |     |     |     |  v  |
+-----+  i  |  e  |  a  +-----+                 +-----+  h  |  t  |  s  +-----+
|     +-----+-----+-----+  ;  |                 |  :  +-----+-----+-----+     |
|  c  |     |     |     |  ,  |                 |  .  |     |     |     |  n  |
+-----+  x  |  j  |  k  +-----+                 +-----+  r  |  m  |  f  +-----+
|     +-----+-----+-----+  ?  |                 |  '  +-----+-----+-----+     |
|  g  |                 |  _  |                 |  "  |                 |  p  |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |Multi|     |     |Mouse|     | Fun |     |     | Num |
            | Esc |Space|Shift| Tab |     |BkSpc|Enter|Raise| Del |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
Design decisions:
* Dedicated (not dual-purpose) Space, Shift, Enter and Raise keys
* Shift is one-shot, double-tab shift to capitalize next word, hold shift to capitalize while Shift is held 
* `,` and `.` on home row of inner columns, like in Engram, because `,` and `.` are very frequent
* `q` and `z` on top of inner rows (used less frequently than `,` and `.`)
* `q` on the right side, to avoid single-finger action when typing 'qu'
* `_` as dedicated key, used quite often in programming
* `'` and `"` are reversed, because `"` is more frequent in the programming languages I use
* `?` is a 'general conversation character', so it is kept on the base layer (shifted)


#### Raise layer (symbols + navigation)

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             |     |     |     |
+-----+  <  |  >  |  &  +-----+                 +-----+  *  |  {  |  }  +-----+
|     +-----+-----+-----+  ^  |                 |  \  +-----+-----+-----+     |
|  -  |     |     |     |     |                 |     |     |     |     |  /  |
+-----+  (  |  )  |  =  +-----+                 +-----+Left |Down | Up  +-----+
|     +-----+-----+-----+  %  |                 |  @  +-----+-----+-----+     |
|  +  |     |     |     |     |                 |     |     |     |     |Right|
+-----+  [  |  ]  |  |  +-----+                 +-----+Home |PgDn |PgUp +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|  !  |                 |  ~  |                 |  `  |                 |End  |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     |     |     |
            |  #  |Space|  $  |     |     |     |     >RAISE<     |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
Design decisions and mnemonic rules:
* Dedicated Raise key right under thumb, for fastest typing without dual-key delays.
* Navigation - on the home row and on the lower row, just like in miryoku layout
* Parens, brackets, triangle brackets often come together - placed in pairs at the most convenient positions
* Parens are more frequent, so they are on the home row
* Triangle brackets seem to be used more often in programming, put them to the upper row - easier to reach with longer fingers than on lower row.
* `=` is used frequently, so it is on the home row
* Frequent combinations with `=` are comfortable inward rolls: `!=`, `+=`, `-=`, `<=`, `>=`
* Infrequent combinations with `=` are `&=`, `|=`, `^=`, `~=`, `%=` - put these characters next to `=`.
* Logic operations characters are not on the middle row, used less frequently
* `@` and `%` seem to be more frequent than their neighbors in central columns - put them on the middle row
* `%` resembles `7`, after `6` on keypad.
* `@` is "at" - next to navigation buttons
* `-` is on the top row to type `<-` and `->` easily; `-` and `+` are in the same column.
* `` ` `` is on the same key as quote and double-quote (all related to string literals)
* `/` and `*` are on the same row for symmetry; also opening and closing comments `/*` and `*/` are rolls.
* `/` is used for comments, also on pinky, as in QWERTY layout.
* `` \ `` is on the opposite side to `/`.
* `~` is "curved version of `_`" - put it on the same key.
* `&`: resembles `9`, corresponds to `9` on keypad
* `|`: resembles `1`, on the same row where `1` is on keypad
* `^`: points upwards - on the upper row.
* `Space` remains `Space` for easy typing - usually, spaces are around operator characters.

Questionable decisions:
* `-`, `+` are all on pinky - but they combine well with `=`
* `/` is on pinky, perhaps, swap with `Ins`.


#### Numbers layer

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             |  ^  |  ^  |  ^  |
+-----+  7  |  8  |  9  +-----+                 +-----+  l  |  d  |  w  +-----+
|     +-----+-----+-----+     |                 |  ^  +-----+-----+-----+  ^  |
|  -  |     |     |     |  /  |                 |  q  |  ^  |  ^  |  ^  |  v  |
+-----+  4  |  5  |  6  +-----+                 +-----+  h  |  t  |  s  +-----+
|     +-----+-----+-----+     |                 |  ^  +-----+-----+-----+  ^  |
|  +  |     |     |     |  =  |                 |  .  |  ^  |  ^  |  ^  |  n  |
+-----+  1  |  2  |  3  +-----+                 +-----+  r  |  m  |  f  +-----+
|     +-----+-----+-----+     |                 |  ^  +-----+-----+-----+  ^  |
|NumLk|                 |  *  |                 |  '  |                 |  p  |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     |     > NUM <
            |  .  |Space|  0  |Enter|     |     |     |     |     |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
Design decisions:
* Layer activated when holding down dual-function key `Delete` - 1-key distance for thumb
* Classic numbers layout for easy memorization
* `Space` remains `Space` for easy typing - usually, spaces are around numbers.
* `NumLock` is on the same key as `!` ("Invert" num lock status) - it can be 'smart', output digits until non-digit is typed.
* On the right - single-hand Ctrl+key combinations (mnemonic: works like Right Ctrl, which is on the right in the right modifiers block on the regular keyboard)


#### Function layer

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             | Alt | Alt | Alt |
+-----+ F7  | F8  | F9  +-----+                 +-----+  l  |  d  |  w  +-----+
|     +-----+-----+-----+PrScr|                 | Alt +-----+-----+-----+ Alt |
| F12 |     |     |     |SysRq|                 |  q  | Alt | Alt | Alt |  v  |
+-----+ F4  | F5  | F6  +-----+                 +-----+  h  |  t  |  s  +-----+
|     +-----+-----+-----+     |                 | Alt +-----+-----+-----+ Alt |
| F11 |     |     |     |ScrLk|                 |  .  | Alt | Alt | Alt |  n  |
+-----+ F1  | F2  | F3  +-----+                 +-----+  r  |  m  |  f  +-----+
|     +-----+-----+-----+Pause|                 | Alt +-----+-----+-----+ Alt |
| F10 |                 |Break|                 |  '  |                 |  p  |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     | Alt |     > FUN <     |     |     |
            |Menu | Ins | Caps| Tab |     |     |     |     |     |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
Design decisions:
* Layer activated when holding down dual-function key `BackSpace` - 2-key distance for thumb, because used rarely.
* Same layout as in miryoku and numpad layer. 
* Caps Lock is "Function of Shift". 
* On the right - single-hand Alt+key combinations (mnemonic: works like Right Alt, which is on the left in the right modifiers block on the regular keyboard)


#### Multi-layer (multimedia, programming combos)

```
      +-----+-----+-----+                             +-----+-----+-----+
      |  ^  |  ^  |  ^  |                             |     |     |     |
+-----+  y  |  o  |  u  +-----+                 +-----+  )  |Space|  {  +-----+
|  ^  +-----+-----+-----+  ^  |                 |     +-----+-----+-----+     |
|  b  |  ^  |  ^  |  ^  |  z  |                 |     |     |     |     |Enter|
+-----+  i  |  e  |  a  +-----+                 +-----+Prev |VolDn|VolUp+-----+
|  ^  +-----+-----+-----+  ^  |                 |     +-----+-----+-----+     |
|  c  |  ^  |  ^  |  ^  |  ,  |                 |     |     |     |     |Next |
+-----+  x  |  j  |  k  +-----+                 +-----+  =  |Space|  0  +-----+
|  ^  +-----+-----+-----+  ^  |                 |     +-----+-----+-----+     |
|  g  |                 |  ;  |                 |     |                 |  ;  |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            >MULTI<     |     |     |     |     |     |     |  ^  |
            |     |     |     |     |     |Stop |PlayP|Mute |  /  |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
Design decisions:
* Home row, thumb cluster: media control like in miryoku
* Top row: ") {⏎", common combination in programming
* Bottom row: "= 0;", common combination in programming
* On the left - single-hand Ctrl+key combinations (mnemonic: works like Left Ctrl, which is on the left in the left modifiers block on the regular keyboard)


#### Mouse layer

```
      +-----+-----+-----+                             +-----+-----+-----+
      | Alt | Alt | Alt |                             |     |Mouse|Mouse|
+-----+  y  |  o  |  u  +-----+                 +-----+Paste|WhlDn|WhlUp+-----+
| Alt +-----+-----+-----+ Alt |                 |     +-----+-----+-----+     |
|  b  | Alt | Alt | Alt |  z  |                 | Cut |Mouse|Mouse|Mouse|Copy |
+-----+  i  |  e  |  a  +-----+                 +-----+Left |Down | Up  +-----+
| Alt +-----+-----+-----+ Alt |                 |     +-----+-----+-----+Mouse|
|  c  | Alt | Alt | Alt |  ,  |                 |Undo |Mouse|Mouse|Mouse|Right|
+-----+  x  |  j  |  k  +-----+                 +-----+PgLft|PgDn |PgUp +-----+
| Alt +-----+-----+-----+ Alt |                 |     +-----+-----+-----+Mouse|
|  g  |                 |  ;  |                 |     |                 |PgRgt|
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     >MOUSE<     |     |     |     |     |
            |     |     |     |     |     |  1  |  3  |  2  |     |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
Design decisions:
* On the left - single-hand Alt+key combinations (mnemonic: works like Left Alt, which is on the right in the left modifiers block on the regular keyboard)
