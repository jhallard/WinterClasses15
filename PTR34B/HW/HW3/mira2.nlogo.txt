;;; 1/18/15: mira2.nlogo by ralph

;;; BREEDS ;;;;;;;;;;;
breed [ particles ]

;;; VARIABLES ;;;;;;;;;;;
globals
[
  deltax deltay   ;;; window widths for conversion routines
  deltau deltav   ;;; world coord window widths
  umin umax vmin vmax ;;; from def of map-u and map-v
  xmin xmax ymin ymax ;;; from Graphics Window attributes
  u-smallest u-largest v-smallest v-largest
  color-0 color-1 color-2 color-3 color-4 color-5 color-6 color-7 color-8 color-9
  delta-x delta-hue
  u0 v0 ;;; inits, added 9/21/13
  unow vnow
  max-hits ;;; used to be local
  ;;; a, b from sliders
]
patches-own [ hits ] ;;; record number of hits by a particle (new to dorband2)

;;; PROCEDURES ;;;;;;;;;;;;;;;;;;;;

;;; these are for coord conversion functions (affine isomorphisms)
to init-globals
  set xmin min-pxcor
  set xmax max-pxcor
  set ymin min-pycor
  set ymax max-pycor
  set deltax world-width - 1 ;;; this is Graphics Window attribute
  set deltay world-height - 1 ;;; this is Graphics Window attribute
  set umin -3
  set umax 3
  set vmin -3
  set vmax 3
  set deltau (umax - umin) 
  set deltav (vmax - vmin)
  ;;; 22 jan 2011
  set u-smallest 0 ;;; initial value
  set u-largest 0
  set v-smallest 0
  set v-largest 0
  ;;; 17 july 2013, add hues
  set delta-x world-width / 10
  set delta-hue ( hue-max - hue-min ) / 10
  set color-0 approximate-hsb hue-min 255 255
  set color-1 approximate-hsb ( hue-min + delta-hue ) 255 255
  set color-2 approximate-hsb ( hue-min + 2 * delta-hue ) 255 255
  set color-3 approximate-hsb ( hue-min + 3 * delta-hue ) 255 255
  set color-4 approximate-hsb ( hue-min + 4 * delta-hue ) 255 255
  set color-5 approximate-hsb ( hue-min + 5 * delta-hue ) 255 255
  set color-6 approximate-hsb ( hue-min + 6 * delta-hue ) 255 255
  set color-7 approximate-hsb ( hue-min + 7 * delta-hue ) 255 255
  set color-8 approximate-hsb ( hue-min + 8 * delta-hue ) 255 255
  set color-9 approximate-hsb hue-max 255 255
  set u0 0.05 ;;; sprott values
  set v0 0.05
  set unow u0
  set vnow v0
  set max-hits 0
end

;;; REPORTERS ;;;;;;;;;;;;;;;

;;; ==============================================
;;; conversion functions, world-coords <--> turtle-screen-coords:
;;; horizontal: (u <--> x), vertical (v <--> y)
;;; ----------------------------------------------
;;; (u <-- x): u = convert(x)
to-report horizconvert [ x ]
  let u (deltau * ( x - xmin ) / deltax) + umin
  report u
end

;;; (u --> x): x = deconvert(u)
to-report horizdeconvert [ u ]
  let x (deltax * ( u - umin ) / deltau) + xmin
  report x
end

;;; (v <-- y): v = convert(y)
to-report vertconvert [ y ]
  let v (deltav * ( y - ymin ) / deltay) + vmin
  report v
end

;;; (v --> y): y = deconvert(v)
to-report vertdeconvert [ v ]
  let y (deltay * ( v - vmin ) / deltav) + ymin
  report y
end
;;; ==============================================
;;; more procedures
to setup
  clear-all
  init-globals
  let x0 horizdeconvert u0
  let y0 vertdeconvert v0
  crt 1 
    [ 
    setxy x0 y0 
    set size 5
    ]
  reset-ticks
end

;;; green test particles move along trajectories, leaving red blotches
to go
  step
end

to paint-hits
  ;;; let hit-max 100
  let hit-max max-hits
  let delta-hit hit-max / 10
  ask patches [ 
    ifelse hits > 9 * delta-hit [ set pcolor color-9 ]
     [ ifelse hits > 8 * delta-hit [ set pcolor color-9 ] 
      [ ifelse hits > 7 * delta-hit [ set pcolor color-8 ] 
        [ ifelse hits > 6 * delta-hit [ set pcolor color-7 ] 
         [ ifelse hits > 5 * delta-hit [ set pcolor color-6 ] 
          [ ifelse hits > 4 * delta-hit [ set pcolor color-5 ] 
           [ ifelse hits > 3 * delta-hit [ set pcolor color-4 ] 
            [ ifelse hits > 2 * delta-hit [ set pcolor color-3 ] 
             [ ifelse hits > 1 * delta-hit [ set pcolor color-2 ] 
               [ ifelse hits > 0 [ set pcolor color-1 ]
               [set pcolor black ] ] ] ] ] ] ] ] ] ]
  ]
end

to step
  ask turtle 0 [
    let utemp map-u unow vnow ;;; compute next u-v
    let vtemp map-v unow vnow
    set unow utemp
    set vnow vtemp
    let xtemp horizdeconvert utemp ;;; move to image point
    if ( xtemp > xmax ) [ set xtemp xmax ] ;;; clipping for x
    if ( xtemp < xmin ) [ set xtemp xmin ] 
    let ytemp vertdeconvert vtemp
    if ( ytemp > ymax ) [ set ytemp ymax ] ;;; clipping for y
    if ( ytemp < ymin ) [ set ytemp ymin ]  
    set xcor xtemp ;;; now move turtle0
    set ycor ytemp  
    set hits ( hits + 1 ) ;;; then increment hits of new patch
  ]
  tick
end

;;; ============== import hue movie procs from H-SDa ============

to reset-colors
  set delta-hue ( hue-max - hue-min ) / 10
  set color-0 approximate-hsb hue-min 255 255
  set color-1 approximate-hsb ( hue-min + delta-hue ) 255 255
  set color-2 approximate-hsb ( hue-min + 2 * delta-hue ) 255 255
  set color-3 approximate-hsb ( hue-min + 3 * delta-hue ) 255 255
  set color-4 approximate-hsb ( hue-min + 4 * delta-hue ) 255 255
  set color-5 approximate-hsb ( hue-min + 5 * delta-hue ) 255 255
  set color-6 approximate-hsb ( hue-min + 6 * delta-hue ) 255 255
  set color-7 approximate-hsb ( hue-min + 7 * delta-hue ) 255 255
  set color-8 approximate-hsb ( hue-min + 8 * delta-hue ) 255 255
  set color-9 approximate-hsb hue-max 255 255
end

to paint-hues
  reset-colors
  set max-hits max [ hits ] of patches ;;; hits of most populated patch
  let delta-hit hit-scale * max-hits / 10000 ;;; old value
  ;;; let delta-hit max-hits / 10 ;;; new on 17 jun 2014
  ask patches
    [ 
    ifelse hits > 9 * delta-hit [ set pcolor color-9 ]
     [ ifelse hits > 8 * delta-hit [ set pcolor color-8 ] 
      [ ifelse hits > 7 * delta-hit [ set pcolor color-7 ] 
        [ ifelse hits > 6 * delta-hit [ set pcolor color-6 ] 
         [ ifelse hits > 5 * delta-hit [ set pcolor color-5 ] 
          [ ifelse hits > 4 * delta-hit [ set pcolor color-4 ] 
           [ ifelse hits > 3 * delta-hit [ set pcolor color-3 ] 
            [ ifelse hits > 2 * delta-hit [ set pcolor color-2 ] 
             [ ifelse hits > 1 * delta-hit [ set pcolor color-1 ] 
               [ ifelse hits > 0 [ set pcolor color-0 ]
                 [set pcolor black ] ] ] ] ] ] ] ] ] ]
    ]
end

;;; reset pcolor of all patches
to clear
  ask patches
  [
    set pcolor black
  ]
end

;;; and at last, the map in math world coords

to-report map-u [ u v ]
  let new-u ( a * u + v )
  if new-u < u-smallest [ set u-smallest new-u ]
  if new-u > u-largest [ set u-largest new-u ]
  report new-u
end

to-report map-v [ u v ]
  let new-v ( b + u * u )  
  if new-v < v-smallest [ set v-smallest new-v ]
  if new-v > v-largest [ set v-largest new-v ]
  report new-v
end

;;; END code: mira2.nlogo
@#$#@#$#@
GRAPHICS-WINDOW
462
15
1193
527
360
240
1.0
1
10
1
1
1
0
1
1
1
-360
360
-240
240
0
0
1
ticks
30.0

BUTTON
16
10
130
43
setup
setup
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
134
147
219
180
go
go
T
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
11
188
125
221
NIL
clear
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

BUTTON
12
148
125
181
NIL
step
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

MONITOR
13
234
92
279
NIL
u-smallest
2
1
11

MONITOR
99
234
170
279
NIL
u-largest
2
1
11

MONITOR
13
287
91
332
NIL
v-smallest
2
1
11

MONITOR
99
288
169
333
NIL
v-largest
2
1
11

MONITOR
14
349
71
394
NIL
umin
2
1
11

MONITOR
98
351
155
396
NIL
umax
2
1
11

MONITOR
14
402
71
447
NIL
vmin
2
1
11

MONITOR
98
403
155
448
NIL
vmax
2
1
11

SLIDER
11
465
183
498
hue-min
hue-min
0
255
255
1
1
NIL
HORIZONTAL

SLIDER
12
509
184
542
hue-max
hue-max
0
255
510
1
1
NIL
HORIZONTAL

BUTTON
228
188
342
221
NIL
clear-patches
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SLIDER
13
554
185
587
vernier
vernier
-1.3
1.3
0.4
0.1
1
NIL
HORIZONTAL

BUTTON
229
272
322
305
NIL
paint-hits
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

MONITOR
206
464
276
509
NIL
max-hits
0
1
11

BUTTON
298
463
398
496
NIL
paint-hues
NIL
1
T
OBSERVER
NIL
NIL
NIL
NIL
1

SLIDER
278
549
450
582
hit-scale
hit-scale
0
100
5
0.1
1
NIL
HORIZONTAL

SLIDER
15
56
187
89
a
a
-2
2
0.7
0.1
1
NIL
HORIZONTAL

SLIDER
14
96
186
129
b
b
-3
0
-0.974
0.1
1
NIL
HORIZONTAL

@#$#@#$#@
## WHAT IS IT?

Iterates the KKM map (see Abraham, Gardini, and Mira, ch. 4)

## HOW IT WORKS

Long iteration records number of hits in each patch.Then colors the patches according to the number of hits.

## HOW TO USE IT

SETUP: Clears the screen and and variables (including hits).  
 
GO: Starts and stops the simulation, recording the hits.

PAINT-HITS or PAINT-HUES: colors the patches.

## CREDITS AND REFERENCES

www.visual-chaos.org
@#$#@#$#@
default
true
0
Polygon -7500403 true true 150 5 40 250 150 205 260 250

airplane
true
0
Polygon -7500403 true true 150 0 135 15 120 60 120 105 15 165 15 195 120 180 135 240 105 270 120 285 150 270 180 285 210 270 165 240 180 180 285 195 285 165 180 105 180 60 165 15

arrow
true
0
Polygon -7500403 true true 150 0 0 150 105 150 105 293 195 293 195 150 300 150

box
false
0
Polygon -7500403 true true 150 285 285 225 285 75 150 135
Polygon -7500403 true true 150 135 15 75 150 15 285 75
Polygon -7500403 true true 15 75 15 225 150 285 150 135
Line -16777216 false 150 285 150 135
Line -16777216 false 150 135 15 75
Line -16777216 false 150 135 285 75

bug
true
0
Circle -7500403 true true 96 182 108
Circle -7500403 true true 110 127 80
Circle -7500403 true true 110 75 80
Line -7500403 true 150 100 80 30
Line -7500403 true 150 100 220 30

butterfly
true
0
Polygon -7500403 true true 150 165 209 199 225 225 225 255 195 270 165 255 150 240
Polygon -7500403 true true 150 165 89 198 75 225 75 255 105 270 135 255 150 240
Polygon -7500403 true true 139 148 100 105 55 90 25 90 10 105 10 135 25 180 40 195 85 194 139 163
Polygon -7500403 true true 162 150 200 105 245 90 275 90 290 105 290 135 275 180 260 195 215 195 162 165
Polygon -16777216 true false 150 255 135 225 120 150 135 120 150 105 165 120 180 150 165 225
Circle -16777216 true false 135 90 30
Line -16777216 false 150 105 195 60
Line -16777216 false 150 105 105 60

car
false
0
Polygon -7500403 true true 300 180 279 164 261 144 240 135 226 132 213 106 203 84 185 63 159 50 135 50 75 60 0 150 0 165 0 225 300 225 300 180
Circle -16777216 true false 180 180 90
Circle -16777216 true false 30 180 90
Polygon -16777216 true false 162 80 132 78 134 135 209 135 194 105 189 96 180 89
Circle -7500403 true true 47 195 58
Circle -7500403 true true 195 195 58

circle
false
0
Circle -7500403 true true 30 30 240

circle 2
false
0
Circle -7500403 true true 16 16 270
Circle -16777216 true false 46 46 210

cow
false
0
Polygon -7500403 true true 200 193 197 249 179 249 177 196 166 187 140 189 93 191 78 179 72 211 49 209 48 181 37 149 25 120 25 89 45 72 103 84 179 75 198 76 252 64 272 81 293 103 285 121 255 121 242 118 224 167
Polygon -7500403 true true 73 210 86 251 62 249 48 208
Polygon -7500403 true true 25 114 16 195 9 204 23 213 25 200 39 123

face happy
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 255 90 239 62 213 47 191 67 179 90 203 109 218 150 225 192 218 210 203 227 181 251 194 236 217 212 240

face neutral
false
0
Circle -7500403 true true 8 7 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Rectangle -16777216 true false 60 195 240 225

face sad
false
0
Circle -7500403 true true 8 8 285
Circle -16777216 true false 60 75 60
Circle -16777216 true false 180 75 60
Polygon -16777216 true false 150 168 90 184 62 210 47 232 67 244 90 220 109 205 150 198 192 205 210 220 227 242 251 229 236 206 212 183

fish
false
0
Polygon -1 true false 44 131 21 87 15 86 0 120 15 150 0 180 13 214 20 212 45 166
Polygon -1 true false 135 195 119 235 95 218 76 210 46 204 60 165
Polygon -1 true false 75 45 83 77 71 103 86 114 166 78 135 60
Polygon -7500403 true true 30 136 151 77 226 81 280 119 292 146 292 160 287 170 270 195 195 210 151 212 30 166
Circle -16777216 true false 215 106 30

flag
false
0
Rectangle -7500403 true true 60 15 75 300
Polygon -7500403 true true 90 150 270 90 90 30
Line -7500403 true 75 135 90 135
Line -7500403 true 75 45 90 45

flower
false
0
Polygon -10899396 true false 135 120 165 165 180 210 180 240 150 300 165 300 195 240 195 195 165 135
Circle -7500403 true true 85 132 38
Circle -7500403 true true 130 147 38
Circle -7500403 true true 192 85 38
Circle -7500403 true true 85 40 38
Circle -7500403 true true 177 40 38
Circle -7500403 true true 177 132 38
Circle -7500403 true true 70 85 38
Circle -7500403 true true 130 25 38
Circle -7500403 true true 96 51 108
Circle -16777216 true false 113 68 74
Polygon -10899396 true false 189 233 219 188 249 173 279 188 234 218
Polygon -10899396 true false 180 255 150 210 105 210 75 240 135 240

house
false
0
Rectangle -7500403 true true 45 120 255 285
Rectangle -16777216 true false 120 210 180 285
Polygon -7500403 true true 15 120 150 15 285 120
Line -16777216 false 30 120 270 120

leaf
false
0
Polygon -7500403 true true 150 210 135 195 120 210 60 210 30 195 60 180 60 165 15 135 30 120 15 105 40 104 45 90 60 90 90 105 105 120 120 120 105 60 120 60 135 30 150 15 165 30 180 60 195 60 180 120 195 120 210 105 240 90 255 90 263 104 285 105 270 120 285 135 240 165 240 180 270 195 240 210 180 210 165 195
Polygon -7500403 true true 135 195 135 240 120 255 105 255 105 285 135 285 165 240 165 195

line
true
0
Line -7500403 true 150 0 150 300

pentagon
false
0
Polygon -7500403 true true 150 15 15 120 60 285 240 285 285 120

person
false
0
Circle -7500403 true true 110 5 80
Polygon -7500403 true true 105 90 120 195 90 285 105 300 135 300 150 225 165 300 195 300 210 285 180 195 195 90
Rectangle -7500403 true true 127 79 172 94
Polygon -7500403 true true 195 90 240 150 225 180 165 105
Polygon -7500403 true true 105 90 60 150 75 180 135 105

plant
false
0
Rectangle -7500403 true true 135 90 165 300
Polygon -7500403 true true 135 255 90 210 45 195 75 255 135 285
Polygon -7500403 true true 165 255 210 210 255 195 225 255 165 285
Polygon -7500403 true true 135 180 90 135 45 120 75 180 135 210
Polygon -7500403 true true 165 180 165 210 225 180 255 120 210 135
Polygon -7500403 true true 135 105 90 60 45 45 75 105 135 135
Polygon -7500403 true true 165 105 165 135 225 105 255 45 210 60
Polygon -7500403 true true 135 90 120 45 150 15 180 45 165 90

square
false
0
Rectangle -7500403 true true 30 30 270 270

square 2
false
0
Rectangle -7500403 true true 30 30 270 270
Rectangle -16777216 true false 60 60 240 240

star
false
0
Polygon -7500403 true true 60 270 150 0 240 270 15 105 285 105
Polygon -7500403 true true 75 120 105 210 195 210 225 120 150 75

target
false
0
Circle -7500403 true true 0 0 300
Circle -16777216 true false 30 30 240
Circle -7500403 true true 60 60 180
Circle -16777216 true false 90 90 120
Circle -7500403 true true 120 120 60

tree
false
0
Circle -7500403 true true 118 3 94
Rectangle -6459832 true false 120 195 180 300
Circle -7500403 true true 65 21 108
Circle -7500403 true true 116 41 127
Circle -7500403 true true 45 90 120
Circle -7500403 true true 104 74 152

triangle
false
0
Polygon -7500403 true true 150 30 15 255 285 255

triangle 2
false
0
Polygon -7500403 true true 150 30 15 255 285 255
Polygon -16777216 true false 151 99 225 223 75 224

truck
false
0
Rectangle -7500403 true true 4 45 195 187
Polygon -7500403 true true 296 193 296 150 259 134 244 104 208 104 207 194
Rectangle -1 true false 195 60 195 105
Polygon -16777216 true false 238 112 252 141 219 141 218 112
Circle -16777216 true false 234 174 42
Rectangle -7500403 true true 181 185 214 194
Circle -16777216 true false 144 174 42
Circle -16777216 true false 24 174 42
Circle -7500403 false true 24 174 42
Circle -7500403 false true 144 174 42
Circle -7500403 false true 234 174 42

turtle
true
0
Polygon -10899396 true false 215 204 240 233 246 254 228 266 215 252 193 210
Polygon -10899396 true false 195 90 225 75 245 75 260 89 269 108 261 124 240 105 225 105 210 105
Polygon -10899396 true false 105 90 75 75 55 75 40 89 31 108 39 124 60 105 75 105 90 105
Polygon -10899396 true false 132 85 134 64 107 51 108 17 150 2 192 18 192 52 169 65 172 87
Polygon -10899396 true false 85 204 60 233 54 254 72 266 85 252 107 210
Polygon -7500403 true true 119 75 179 75 209 101 224 135 220 225 175 261 128 261 81 224 74 135 88 99

wheel
false
0
Circle -7500403 true true 3 3 294
Circle -16777216 true false 30 30 240
Line -7500403 true 150 285 150 15
Line -7500403 true 15 150 285 150
Circle -7500403 true true 120 120 60
Line -7500403 true 216 40 79 269
Line -7500403 true 40 84 269 221
Line -7500403 true 40 216 269 79
Line -7500403 true 84 40 221 269

x
false
0
Polygon -7500403 true true 270 75 225 30 30 225 75 270
Polygon -7500403 true true 30 75 75 30 270 225 225 270

@#$#@#$#@
NetLogo 5.1.0
@#$#@#$#@
setup
place-particle 0 screen-edge-y - 3
repeat 50000 [ go ]
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
@#$#@#$#@
default
0.0
-0.2 0 0.0 1.0
0.0 1 1.0 0.0
0.2 0 0.0 1.0
link direction
true
0
Line -7500403 true 150 150 90 180
Line -7500403 true 150 150 210 180

@#$#@#$#@
0
@#$#@#$#@
