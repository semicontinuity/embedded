This is an experimental layout, very similar to "baseline" just-split layout.
Its goal is to move more symbols to Lower layer to have conceptually coherent symbols-only Lower layer,
and to have less symbols on central columns.

Instead of 8 navigation keys, 4 symbols are taken from central columns of base-shifted layer (`;`, `:`, `?`, `'`),
and 4 symbols from central columns of Lower layer (`~`, `^`, `\`, `` ` ``)

In total, there are 32 symbols: 4 on base layer, 2 on Lower thumb cluster, and 26 on the Lower layer.
No symbols on the shift layer.

#### Base layer (Engram)

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             |     |     |     |
+-----+  y  |  o  |  u  +-----+                 +-----+  l  |  d  |  w  +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|  b  |     |     |     |  z  |                 |  q  |     |     |     |  v  |
+-----+  i  |  e  |  a  +-----+                 +-----+  h  |  t  |  s  +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|  c  |     |     |     |  ,  |                 |  .  |     |     |     |  n  |
+-----+  x  |  j  |  k  +-----+                 +-----+  r  |  m  |  f  +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|  g  |                 |  _  |                 |  ?  |                 |  p  |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |Multi|     |     |Mouse|     | Fun |     |     | Num |
            | Esc |Space|Shift| Tab |     |BkSpc|Enter|Lower| Del |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```

#### Navigation layer

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             |     |     |     |
+-----+     |     |     +-----+                 +-----+     |     |     +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|     |     |     |     |     |                 |     |     |     |     |     |
+-----+     |     |     +-----+                 +-----+Left |Down | Up  +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|     |     |     |     |     |                 |     |     |     |     |Right|
+-----+     |     |     +-----+                 +-----+Home |PgDn |PgUp +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|     |                 |     |                 |     |                 |End  |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     |     |     |
            >MULTI<     >RAISE<     |     |     |     >LOWER<     |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
* Hold `Raise` + keys:           navigation
* Hold `Raise` + `Lower` + keys: `Shift` + navigation
* Hold `Multi` + keys:           `Ctrl` + navigation
* Hold `Multi` + `Lower` + keys: `Ctrl` + `Shift` + navigation


#### Lower layer (symbols) - if Lower key also activates Navigation layer

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             |     |     |     |
+-----+  <  |  >  |  &  +-----+                 +-----+  "  |  *  |  /  +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+     |
|  -  |     |     |     |     |                 |     |     |     |     |  '  |
+-----+  (  |  )  |  =  +-----+                 +-----+  ;  |  {  |  }  +-----+
|     +-----+-----+-----+  %  |                 |  :  +-----+-----+-----+     |
|  +  |     |     |     |     |                 |     |     |     |     |  `  |
+-----+  [  |  ]  |  |  +-----+                 +-----+  @  |  ^  |  \  +-----+
|     +-----+-----+-----+     |                 |     +-----+-----+-----+  ~  |
|  !  |                 |     |                 |     |                 |     |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     |     |     |
            |  #  |Space|  _  |  $  |     |     |     >LOWER<     |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
Perhaps, symbols on navigation keys will be activated with leader Lower key only (it influences heavily all design decisions) -
in this case, on these keys there are symbols that usually come alone.

Design decisions and mnemonic rules:
* Curly braces on the home row; they can come together (`{}`), but often `}` is auto-completed with IDEs.
* `;` on the home row, on the stronger index finger
* `:` is next to `;` (can be repeated - thus on non-navigation key)
* `*` and `/` are together in convenient position to type `//`, `/*` and `*/`


#### Lower layer (symbols) - if independent of Navigation layer

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             |     |     |     |
+-----+  <  |  >  |  &  +-----+                 +-----+  @  |  [  |  ]  +-----+
|     +-----+-----+-----+  ^  |                 |  ~  +-----+-----+-----+     |
|  !  |     |     |     |     |                 |     |     |     |     |  `  |
+-----+  (  |  )  |  =  +-----+                 +-----+  ;  |  {  |  }  +-----+
|     +-----+-----+-----+  0  |                 |  2  +-----+-----+-----+     |
|  -  |     |     |     |     |                 |     |     |     |     |  "  |
+-----+  *  |  /  |  |  +-----+                 +-----+  :  |  $  |  %  +-----+
|     +-----+-----+-----+  1  |                 |  3  +-----+-----+-----+  '  |
|  +  |                 |     |                 |     |                 |     |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     |     |     |
            |  #  |Space|  _  |  \  |     |     |     >LOWER<     |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
* Double-quote `"` on home row; again, then come in pairs, but auto-completed by IDEs.
* `=` is used frequently, so it is on the home row
* Frequent combinations with `=` are comfortable inward rolls: `!=`, `+=`, `-=`, `<=`, `>=`
* `-` is frequent: on the home row
* `+` is less frequent than `-`: below `-`
* `:` is under `;`
* `%` has `/` inside; percent sign is "after numbers" - in the end
* `$` is "at the beginning" - before number
* `$%` is in the same order, as on regular keyboard
* `{}` is frequent: on the home row
* `[]` is less frequent, but quite frequent: above `{}`
* `<>` is not very frequent, can be used with `=`: on the same side as `=`: on the top for convenience
* `!` is almost in the same location, as on regular keyboard (inconvenient)
* All string-literal-related characters in one column
* Underscore s unavailable from QWERTY layer - put it next to space
* Frequent numbers 0..3 are available, to avoid layer switching; optimized for typing "= " + number

Alt thumbs layout:

```
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     >LOWER<     |
            |  #  |  .  |  _  |  $  |     |  ~  |  ?  |  ,  |  %  |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
* Makes possible to type all characters without lateral palm motion
* `~` `?` `,` `%` are on the right side, because these characters are unlikely to be repeated
* No way to auto-repeat `,`, but can be implemented with tap dance
* `,` on the LOWER key - for relatively fast typing by double-tap
* `.` on the SPACE key - no thumb motion


Alt thumbs layout 2:

```
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     >RAISE<     |     |     |     |     |     |
            | ^C  | ^V  |     | ^X  |     | ^W  |  ,  |  .  |  ?  |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
```
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     >LOWER<     |
            |  #  |Space|  _  | ^/  |     |  ^  |  \  |     |  ~  |
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
* Common characters `,.?` are on the other side to the SPACE key - SPACE often follows them - for easier typing
* `Lower+Space` is `Space` to prevent typos
* `#` is "at start of the string" (comment char)
* `\` is "at end of the string" (continuation char)
* `^~` are the rarest chars, so they require same-finger motion (or dedicated keys in central column)

#### Java Generics layer (concurrent with Multi Layer)

```
      +-----+-----+-----+                             +-----+-----+-----+
      |     |     |     |                             | Lin |     |     |
+-----+     |     |     +-----+                 +-----+ ked |Array|List >+-----+
|     +-----+-----+-----+     |                 |Prio.+-----+-----+-----+     |
|     |     |     |     |     |                 |Queue|     |     |     |Deque|
+-----+     |     |     +-----+                 +-----+  <  |  ,  |Space+-----+
|     +-----+-----+-----+     |                 |Compa+-----+-----+-----+     |
|     |     |     |     |     |                 |rator|     |     |     |  >  |
+-----+     |     |     +-----+                 +-----+Tree |Hash |Map  +-----+
|     +-----+-----+-----+     |                 |.     +-----+-----+-----+     |
|     |                 |     |                 |Entry|                 | Set |
+-----+                 +-----+                 +-----+                 +-----+

            +-----+-----+-----+-----+     +-----+-----+-----+-----+
            |     |     |     |     |     |     |     |     |     |
            >MULTI<     |     |     |     | new_|Int. |Str. |Char.|
            +-----+-----+-----+-----+     +-----+-----+-----+-----+
```
