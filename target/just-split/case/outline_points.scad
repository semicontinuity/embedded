outline_points = concat(
// LINE (96.48576, -73.27278)->(79.48576, -73.27278); flip=False
[ [96.48576, -73.27278] ],
// ARC (78.38576, -74.37278)->(79.48576, -73.27278); 180.0->90.0 flip=True
[ for(a = [90.0:5:180.0]) [79.48576 + 1.0999999999999943 * cos(a), -74.37278 + 1.0999999999999943 * sin(a)] ],
// LINE (78.38576, -74.37278)->(78.38576, -131.37278); flip=False
[ [78.38576, -74.37278] ],
// ARC (79.48576, -132.47278)->(78.38576, -131.37278); -90.0->180.0 flip=True
[ for(a = [180.0:5:270.0]) [79.48576 + 1.0999999999999943 * cos(a), -131.37278 + 1.0999999999999943 * sin(a)] ],
// LINE (79.48576, -132.47278)->(98.48576, -132.47278); flip=False
[ [79.48576, -132.47278] ],
// ARC (99.58576, -131.37278)->(98.48576, -132.47278); 0.0->-90.0 flip=True
[ for(a = [270.0:5:360.0]) [98.48576 + 1.0999999999999943 * cos(a), -131.37278 + 1.0999999999999943 * sin(a)] ],
// LINE (99.58576, -131.37278)->(99.58576, -124.37278); flip=False
[ [99.58576, -131.37278] ],
// ARC (99.58576, -124.37278)->(100.48576, -123.47278); 180.0->90.0 flip=False
[ for(a = [180.0:-5:90.0]) [100.48576 + 0.9000000000000057 * cos(a), -124.37278 + 0.9000000000000057 * sin(a)] ],
// LINE (100.48576, -123.47278)->(122.78576, -123.47278); flip=False
[ [100.48576, -123.47278] ],
// ARC (122.78576, -123.47278)->(123.68576, -124.37278); 90.0->0.0 flip=False
[ for(a = [90.0:-5:0.0]) [122.78576 + 0.9000000000000057 * cos(a), -124.37278 + 0.9000000000000057 * sin(a)] ],
// LINE (123.68576, -124.37278)->(123.68576, -138.87278); flip=False
[ [123.68576, -124.37278] ],
// ARC (124.78576, -139.97278)->(123.68576, -138.87278); -90.0->180.0 flip=True
[ for(a = [180.0:5:270.0]) [124.78576 + 1.0999999999999943 * cos(a), -138.87278 + 1.0999999999999943 * sin(a)] ],
// LINE (124.78576, -139.97278)->(143.472707, -139.971924); flip=False
[ [124.78576, -139.97278] ],
// LINE (143.472707, -139.971924)->(161.747492, -144.865167); flip=False
[ [143.472707, -139.971924] ],
// LINE (161.747492, -144.865167)->(177.924884, -154.252115); flip=False
[ [161.747492, -144.865167] ],
// LINE (177.924884, -154.252115)->(191.415051, -167.543489); flip=False
[ [177.924884, -154.252115] ],
// ARC (192.956469, -167.543489)->(191.415051, -167.543489); -45.0->-134.99999999999895 flip=True
[ for(a = [225.0:5:315.0]) [192.18576 + 1.089947120443021 * cos(a), -166.77277999999998 + 1.089947120443021 * sin(a)] ],
// LINE (192.956469, -167.543489)->(206.456469, -154.143489); flip=False
[ [192.956469, -167.543489] ],
// ARC (206.775707, -153.37278)->(206.456469, -154.143489); 0.0->-45.0 flip=True
[ for(a = [315.0:5:360.0]) [205.68576000000002 + 1.0899469999999951 * cos(a), -153.37278 + 1.0899469999999951 * sin(a)] ],
// LINE (206.775707, -153.37278)->(206.78576, -65.37278); flip=False
[ [206.775707, -153.37278] ],
// ARC (205.68576, -64.27278)->(206.78576, -65.37278); 90.0->-7.402018167769486e-13 flip=True
[ for(a = [-0.0:5:90.0]) [205.68576 + 1.0999999999999943 * cos(a), -65.37277999999999 + 1.0999999999999943 * sin(a)] ],
// LINE (205.68576, -64.27278)->(157.48576, -64.27278); flip=False
[ [205.68576, -64.27278] ],
// ARC (157.48576, -64.27278)->(156.58576, -63.37278); -90.0->180.0 flip=False
[ for(a = [270.0:-5:180.0]) [157.48576 + 0.8999999999999986 * cos(a), -63.37278 + 0.8999999999999986 * sin(a)] ],
// LINE (156.58576, -63.37278)->(156.58576, -62.87278); flip=False
[ [156.58576, -63.37278] ],
// ARC (155.48576, -61.77278)->(156.58576, -62.87278); 90.0->0.0 flip=True
[ for(a = [0.0:5:90.0]) [155.48576 + 1.1000000000000014 * cos(a), -62.87278 + 1.1000000000000014 * sin(a)] ],
// LINE (155.48576, -61.77278)->(138.48576, -61.77278); flip=False
[ [155.48576, -61.77278] ],
// ARC (138.48576, -61.77278)->(137.58576, -60.87278); -90.0->180.0 flip=False
[ for(a = [270.0:-5:180.0]) [138.48576 + 0.8999999999999986 * cos(a), -60.87278 + 0.8999999999999986 * sin(a)] ],
// LINE (137.58576, -60.87278)->(137.58576, -56.37278); flip=False
[ [137.58576, -60.87278] ],
// ARC (136.48576, -55.27278)->(137.58576, -56.37278); 90.0->0.0 flip=True
[ for(a = [0.0:5:90.0]) [136.48576 + 1.1000000000000014 * cos(a), -56.37278 + 1.1000000000000014 * sin(a)] ],
// LINE (136.48576, -55.27278)->(117.48576, -55.27278); flip=False
[ [136.48576, -55.27278] ],
// ARC (116.38576, -56.37278)->(117.48576, -55.27278); 180.0->90.0 flip=True
[ for(a = [90.0:5:180.0]) [117.48576 + 1.0999999999999943 * cos(a), -56.37278 + 1.0999999999999943 * sin(a)] ],
// LINE (116.38576, -56.37278)->(116.38576, -60.37278); flip=False
[ [116.38576, -56.37278] ],
// ARC (116.38576, -60.37278)->(115.48576, -61.27278); 0.0->-90.0 flip=False
[ for(a = [360.0:-5:270.0]) [115.48576 + 0.9000000000000057 * cos(a), -60.37278 + 0.9000000000000057 * sin(a)] ],
// LINE (115.48576, -61.27278)->(98.48576, -61.27278); flip=False
[ [115.48576, -61.27278] ],
// ARC (97.38576, -62.37278)->(98.48576, -61.27278); 180.0->90.0 flip=True
[ for(a = [90.0:5:180.0]) [98.48576 + 1.0999999999999943 * cos(a), -62.37278 + 1.0999999999999943 * sin(a)] ],
// LINE (97.38576, -62.37278)->(97.38576, -72.37278); flip=False
[ [97.38576, -62.37278] ],
// ARC (97.38576, -72.37278)->(96.48576, -73.27278); 0.0->-90.0 flip=False
[ for(a = [360.0:-5:270.0]) [96.48576 + 0.9000000000000057 * cos(a), -72.37278 + 0.9000000000000057 * sin(a)] ]
);

