#include <inttypes.h>
#include "../src/pic_data.h"

static const uint8_t pic_bytes[4903] = {
46,49,7,60,8,0,3,7,27,0,0,62,48,31,32,7,56,0,135,3,
27,8,1,37,54,2,8,18,4,18,62,25,62,3,63,56,0,135,3,27,
24,1,223,2,12,55,12,38,51,1,255,38,12,3,8,39,21,35,12,62,
19,56,31,60,24,0,135,3,25,24,1,127,50,21,2,17,21,9,6,255,
53,20,6,21,50,28,52,20,14,15,35,63,28,15,63,63,135,3,9,24,
1,255,2,25,2,17,21,9,3,1,255,21,20,3,20,34,29,20,24,14,
30,15,56,127,1,63,63,63,63,63,60,135,1,45,40,1,255,55,12,51,
16,37,8,54,1,255,53,12,6,8,35,29,52,12,63,1,56,31,32,7,
48,255,63,63,63,63,63,63,63,56,7,1,45,40,0,0,191,3,33,62,
3,63,48,7,253,48,3,63,63,63,63,63,7,33,45,40,105,1,1,1,
32,157,1,16,1,4,4,191,15,3,56,31,61,48,30,255,3,63,48,63,
63,60,1,63,7,57,37,40,255,2,8,48,21,35,12,32,25,253,35,54,
13,38,9,35,12,223,12,15,3,63,32,1,56,127,63,63,62,15,63,51,
60,7,61,36,32,251,7,21,29,21,20,32,13,255,21,1,19,25,21,20,
52,20,206,60,15,60,3,33,255,63,63,63,47,63,15,63,60,7,14,52,
32,251,2,21,29,22,24,32,21,255,21,1,21,13,21,21,20,20,255,1,
48,63,48,31,63,63,9,255,63,63,63,47,63,31,63,60,7,55,54,48,
251,2,9,29,19,13,48,29,253,19,55,25,22,9,52,12,255,7,3,62,
3,63,63,62,29,255,63,63,63,47,62,31,63,60,7,59,54,48,0,0,
254,15,56,31,56,63,60,61,255,63,63,63,47,62,63,63,60,7,61,54,
48,254,4,52,1,35,9,48,29,56,1,16,8,238,63,3,63,63,61,61,
255,63,63,63,47,62,63,63,60,7,61,54,48,246,9,2,21,25,16,9,
255,34,29,35,1,22,28,50,24,239,3,56,31,56,63,57,61,255,63,63,
63,47,62,63,63,60,7,62,54,16,246,9,2,37,9,48,9,255,21,28,
54,1,51,9,37,20,247,31,1,63,7,63,59,61,255,63,63,63,47,62,
63,63,60,7,62,62,24,254,9,2,1,5,9,16,9,255,21,29,19,1,
53,8,53,20,255,24,15,56,1,63,63,51,61,255,63,63,63,15,62,31,
63,60,7,62,59,24,254,4,52,1,54,9,48,9,255,18,21,54,1,23,
13,34,20,251,1,62,31,49,63,55,60,255,63,63,63,31,63,31,63,60,
7,62,59,24,0,0,255,15,32,7,62,1,63,39,60,255,63,63,63,31,
63,31,63,60,135,62,59,24,8,99,36,1,4,32,170,24,4,4,16,247,
56,1,63,1,63,39,60,255,63,63,63,31,63,31,63,60,195,62,59,3,
1,255,54,21,32,12,39,5,54,20,255,53,8,51,4,55,13,35,24,246,
31,48,7,63,39,60,255,63,63,63,31,63,47,63,60,195,62,63,5,8,
255,37,21,16,17,23,8,37,29,255,5,9,22,9,23,20,54,20,251,3,
60,3,63,63,39,60,255,63,63,62,63,63,47,63,60,195,62,63,7,8,
255,37,21,16,17,23,16,37,29,255,5,9,35,17,39,21,19,20,249,6,
63,49,63,39,62,255,63,63,62,62,15,47,63,60,195,62,63,1,8,255,
53,13,34,12,37,16,54,29,255,3,28,54,16,53,13,54,20,252,63,60,
1,63,39,62,255,63,63,62,60,15,55,63,60,67,62,63,2,64,4,0,
246,63,62,1,63,39,62,255,63,63,61,56,7,55,63,60,3,62,61,0,
0,243,3,48,1,63,55,62,255,63,63,61,56,7,59,63,60,3,60,60,
0,0,248,3,49,63,51,62,255,31,63,59,48,7,59,63,60,3,61,28,
0,0,220,1,63,48,59,62,255,31,63,51,48,3,61,63,60,3,61,28,
0,0,207,3,63,63,60,9,62,255,31,63,39,32,3,62,63,60,3,59,
28,0,2,6,192,12,62,247,31,63,15,2,62,31,60,3,58,28,16,48,
50,6,1,32,192,7,14,247,31,62,31,2,31,47,60,3,54,12,16,48,
50,6,1,32,192,3,32,247,31,49,62,2,31,51,60,3,46,12,0,2,
6,208,48,3,60,118,7,62,1,15,60,3,30,12,252,31,60,48,63,56,
7,255,63,7,48,63,57,33,63,48,223,1,63,63,15,48,1,63,247,63,
63,60,1,7,63,63,1,60,252,63,60,49,63,60,15,255,63,7,49,63,
57,35,63,56,142,31,63,63,63,247,63,63,56,1,35,63,63,1,60,246,
1,48,51,32,14,24,190,6,3,32,1,39,28,140,3,56,63,231,63,63,
32,49,63,63,1,56,214,1,32,51,6,24,182,6,3,1,38,12,128,31,
227,63,62,16,31,63,1,56,214,1,32,51,6,24,182,6,3,1,38,12,
128,15,227,63,32,16,15,63,1,48,222,1,63,60,51,6,15,191,62,6,
3,63,57,38,12,16,56,224,16,1,63,1,32,222,1,63,60,51,6,7,
191,63,6,3,63,57,38,12,24,7,56,164,2,16,6,0,86,1,32,51,
6,183,1,38,3,1,38,12,12,15,63,36,4,48,0,86,1,32,51,6,
183,1,38,3,1,38,12,8,48,44,12,12,32,0,86,1,48,51,6,191,
1,39,3,32,1,38,12,0,28,24,30,3,0,220,63,60,51,6,31,191,
63,3,49,63,57,38,12,0,28,16,56,12,0,220,31,60,51,6,31,191,
62,1,48,63,57,38,12,16,12,4,32,0,1,48,192,1,32,24,3,60,
6,1,32,0,1,48,192,1,32,24,7,32,6,1,4,0,1,48,192,1,
32,0,62,2,13,44,63,56,0,1,48,192,1,32,16,15,126,2,45,44,
63,63,32,252,3,63,62,1,63,48,255,62,15,62,1,63,49,63,48,255,
31,60,3,63,32,31,61,60,48,31,32,126,2,45,44,63,63,48,252,7,
63,63,3,63,56,255,62,31,63,3,63,51,63,48,255,63,62,7,63,48,
63,61,60,112,31,49,48,126,2,45,36,63,63,48,188,14,3,3,39,28,
175,48,56,3,39,6,1,247,48,7,14,57,48,1,32,112,15,63,48,124,
45,36,63,63,32,188,12,3,1,38,12,175,48,48,1,38,6,1,247,32,
3,12,25,32,1,32,112,3,63,56,62,4,44,4,63,63,188,12,3,1,
38,12,175,48,48,1,38,6,1,247,32,3,12,25,32,1,32,64,56,6,
4,36,188,12,3,1,38,12,239,48,48,1,38,3,63,33,247,32,3,12,
25,32,1,32,64,28,6,4,36,188,12,3,1,38,12,239,48,48,1,38,
1,63,49,247,32,3,12,25,32,1,32,64,12,62,4,32,31,63,60,188,
12,3,1,38,12,143,48,48,1,38,25,247,32,3,12,25,32,1,32,64,
6,50,4,1,56,188,12,3,1,38,12,143,48,48,1,38,25,247,32,3,
12,25,32,1,32,64,3,50,4,3,32,188,12,3,1,39,28,143,56,56,
3,38,25,247,32,7,14,57,32,1,48,64,3,26,4,3,56,252,12,3,
1,35,63,56,239,30,31,63,6,7,63,49,191,39,62,7,63,49,32,60,
192,1,32,2,4,252,12,3,1,33,63,48,239,14,15,62,6,7,63,33,
191,39,60,3,63,33,32,28,128,48,0,0,128,1,1,32,128,48,0,0,
128,1,1,32,128,24,0,0,128,1,1,32,0,248,56,17,6,49,4,239,
21,4,16,56,3,33,60,127,21,7,49,4,31,3,32,254,2,33,60,31,
7,48,56,209,4,1,56,31,207,7,48,56,4,16,14,127,3,32,16,31,
7,48,16,252,16,14,7,49,60,4,131,3,32,12,193,3,63,15,255,51,
60,51,12,51,60,63,15,249,48,7,33,8,18,7,249,32,15,51,60,33,
11,191,18,52,33,15,51,60,1,127,48,12,13,4,33,8,12,126,14,4,
17,4,14,1,243,56,4,16,6,1,16,159,16,12,7,1,32,48,127,52,
11,3,16,44,27,6,252,5,16,56,27,3,33,177,20,8,3,56,159,15,
3,32,48,8,8,255,6,3,33,56,14,1,32,8,250,1,56,31,1,1,
60,243,14,1,10,2,32,40,151,10,2,32,10,15,255,5,17,20,13,1,
16,20,5,220,56,17,3,40,6,7,4,16,56,184,30,7,32,4,255,3,
33,60,4,7,48,56,4,255,3,32,4,3,33,60,4,1,230,16,4,16,
4,1,62,16,31,3,32,16,126,16,6,7,48,24,4,232,1,48,31,3,
2,16,46,16,4,1,31,254,10,2,33,60,10,2,32,244,1,16,14,3,
33,227,60,31,31,7,48,23,56,14,1,16,0,248,16,14,3,32,16,233,
4,16,6,49,44,1,18,254,2,33,60,10,2,33,60,185,10,8,3,33,
12,238,33,48,4,1,36,25,126,32,16,8,4,49,12,255,2,1,16,20,
2,1,20,18,91,3,16,12,3,32,192,4,2,110,32,8,2,32,4,238,
32,4,1,16,4,1,226,32,40,14,7,135,48,56,10,1,46,16,31,1,
16,0,135,48,12,2,1,1,60,96,12,3,248,16,8,4,2,1,240,14,
4,17,12,159,21,6,17,4,14,16,187,12,1,16,4,1,56,254,3,33,
4,1,1,32,32,247,16,7,48,14,4,16,4,157,14,17,4,14,2,255,
1,32,40,18,7,48,8,2,254,1,60,16,4,1,56,1,247,4,16,56,
1,32,32,16,191,7,33,4,17,3,32,31,222,16,8,4,2,32,8,252,
14,4,17,4,14,4,231,17,4,14,56,17,4,55,16,60,1,32,48,204,
12,3,12,3,96,48,12,110,48,12,2,2,1,55,32,16,2,16,2,204,
7,48,7,48,180,2,16,2,16,231,8,4,2,14,4,16,39,4,6,1,
4,127,14,4,17,28,21,5,49,249,14,56,17,4,17,4,239,31,4,17,
4,7,33,4,127,17,7,33,4,17,7,32,247,14,4,17,16,4,1,4,
249,14,30,4,17,4,17,239,4,17,4,30,1,60,16,127,4,1,56,16,
4,1,60,187,7,49,16,7,33,16,185,4,14,4,17,23,207,4,17,4,
15,17,4,127,17,4,31,4,17,4,17,238,56,4,1,16,4,1,114,56,
16,4,1,223,17,4,17,3,32,17,4,127,33,16,24,5,1,8,17,238,
16,4,1,16,4,1,250,31,1,4,27,5,17,223,4,17,4,17,4,4,
17,255,36,21,4,49,4,17,4,16,254,14,4,17,4,17,4,17,243,4,
14,30,4,17,4,151,30,4,1,16,56,255,17,4,17,4,21,4,32,52,
254,7,33,4,17,7,33,8,119,17,4,16,14,4,17,157,14,17,4,14,
31,221,1,16,4,1,16,4,254,1,4,17,4,17,4,17,247,4,16,56,
4,17,4,17,159,4,17,4,10,1,17,255,4,17,20,21,5,17,20,10,
252,17,4,16,40,4,2,247,33,4,17,1,4,17,4,175,16,40,4,1,
16,7,223,32,8,4,2,1,16,7,237,32,14,2,32,8,2,70,32,14,
4,27,32,4,32,4,187,56,2,32,8,2,32,53,56,1,40,17,0,192,
15,48,11,12,3,16,224,3,32,4,111,15,4,16,60,4,1,127,30,4,
17,4,17,7,32,248,56,17,4,1,4,233,14,1,16,60,17,15,4,17,
4,15,95,3,33,4,30,4,56,255,1,32,32,8,7,32,32,8,193,2,
60,17,255,4,16,60,1,3,32,16,4,127,1,48,18,4,33,8,18,234,
16,1,16,4,1,82,24,32,6,255,32,8,2,4,32,48,16,4,127,1,
8,20,6,1,16,18,118,4,1,16,4,1,195,16,6,6,33,31,20,21,
4,17,4,254,28,4,33,8,18,4,32,240,56,17,4,17,195,4,14,1,
56,63,17,4,17,4,30,4,254,3,49,4,17,4,16,60,241,1,22,2,
16,32,131,8,7,56,31,16,3,32,4,14,223,2,1,56,8,2,40,4,
240,4,33,8,18,135,5,32,40,17,31,4,17,4,10,1,254,1,4,17,
5,17,60,10,240,1,8,18,3,135,1,8,18,4,127,33,8,18,3,32,
16,24,244,30,32,48,16,7,237,32,6,2,32,24,2,102,32,6,4,1,
53,16,1,16,4,187,48,2,32,12,2,32,29,48,2,33,16,224,4,3,
33,31,44,17,4,17,60,247,14,4,17,16,4,16,56,239,4,3,1,8,
4,33,8,79,18,5,32,40,48,127,14,4,17,56,16,3,32,249,14,56,
1,3,49,4,201,15,10,56,1,79,3,49,4,15,48,127,3,32,4,15,
4,16,60,239,3,32,40,14,16,60,17,243,3,48,3,33,4,16,95,4,
16,56,4,3,14,94,56,17,7,33,14,250,40,3,33,4,30,4,202,56,
3,14,4,95,17,56,16,3,32,10,110,16,4,1,16,6,110,4,2,32,
4,1,83,16,6,32,1,215,16,4,1,24,2,32,254,4,2,33,4,31,
4,16,254,14,2,32,56,27,4,17,211,60,17,3,1,60,23,16,7,33,
31,190,7,32,20,31,5,60,254,3,49,16,20,7,49,16,151,20,5,48,
14,48,159,18,4,33,8,12,10,252,48,18,4,33,8,12,246,1,32,3,
1,8,18,183,4,32,48,3,32,18,191,4,33,8,22,2,32,24,254,1,
8,18,4,33,24,10,244,10,1,8,18,4,255,32,56,4,6,1,8,12,
4,191,33,8,18,4,32,48,2,253,32,18,4,33,8,18,3,232,1,56,
16,4,230,56,4,6,2,16,183,32,30,2,36,23,1,255,4,10,1,1,
60,4,7,48,225,16,30,4,1,239,56,16,7,32,2,1,16,119,16,14,
1,16,20,2,249,6,56,1,3,49,4,169,15,24,1,16,107,4,1,24,
1,32,63,12,4,33,8,18,3,253,6,1,8,18,4,33,24,153,10,10,
5,28,207,4,33,8,18,40,20,126,1,8,26,5,33,8,127,3,32,4,
15,4,16,60,251,3,48,12,4,33,8,18,73,3,30,4,126,16,12,4,
1,4,14,216,7,49,16,4,64,63,195,16,4,16,4,127,33,16,14,4,
16,8,7,254,16,4,33,16,11,5,16,83,28,1,16,1,31,16,14,3,
32,16,30,9,4,32,36,248,1,8,9,4,32,208,21,2,40,214,5,16,
42,1,20,255,42,5,18,40,21,10,33,20,255,42,10,35,60,21,15,50,
40,191,63,5,19,60,4,1,16,187,4,1,16,4,1,4,221,1,16,60,
1,16,4,253,1,16,60,1,3,48,4,253,1,16,4,5,1,16,20,127,
13,1,16,20,5,1,16,248,60,5,1,16,20,233,5,15,16,60,1,254,
16,4,1,1,16,52,1,255,3,16,20,5,1,16,20,5,255,1,16,20,
5,1,16,20,5,235,1,16,15,16,52,5,111,1,16,20,5,20,13,131,
16,60,1,31,16,20,5,3,48,124,1,3,48,4,15,0,118,60,1,16,
4,1,27,4,1,16,7,248,16,4,1,3,60,0,190,15,48,16,4,1,
16,187,4,1,16,7,1,16,131,4,1,63,192,16,4,223,1,3,60,4,
1,16,4,253,1,28,4,1,48,16,4,253,1,16,20,5,1,16,23,223,
5,1,16,20,5,20,5,5,49,31,252,31,4,1,28,20,5,191,1,16,
20,5,3,28,15,129,48,15,253,48,55,5,1,16,20,5,238,20,5,49,
23,5,1,167,16,20,5,63,3,193,60,5,3,253,28,13,49,16,20,5,
1,47,16,4,15,48,63,240,20,5,1,16,1,63,189,63,3,60,4,1,
16,225,4,15,49,16,255,20,5,1,16,20,5,1,16,129,31,4,15,1,
48,16,7,216,7,1,28,4,13,1,16,4,255,7,49,16,20,5,1,16,
20,255,5,1,16,55,5,1,16,20,221,5,4,15,48,63,1,238,16,4,
1,16,4,1,3,3,48,248,1,48,16,4,1,254,16,63,15,51,60,63,
15,31,51,60,63,15,48,252,15,51,60,63,15,51,255,32,56,14,3,32,
56,14,3,255,32,56,1,48,28,7,1,48,255,28,7,1,48,28,63,15,
51,3,60,63,248,52,18,4,32,52,240,28,4,33,48,255,18,4,33,48,
16,7,33,8,55,16,4,1,16,4,254,7,48,40,10,2,32,40,249,10,
30,4,32,32,4,15,2,1,8,30,31,3,49,8,18,3,248,18,4,33,
8,28,195,4,1,40,20,205,1,16,4,14,1,126,56,17,3,32,16,14,
254,48,18,4,33,56,18,4,227,32,48,56,17,4,223,16,40,10,6,48,
12,4,126,32,4,3,33,8,12,240,40,21,5,16,225,40,4,3,33,31,
20,21,3,32,16,47,56,16,7,33,14,252,3,1,8,18,4,33,97,8,
7,32,13,30,1,56,111,4,3,32,16,3,32,122,4,48,2,3,1,118,
7,32,2,3,1,21,12,32,30,222,32,20,4,1,16,4,221,1,16,4,
1,16,4,69,5,32,16,11,7,48,4,119,2,33,16,2,33,16,124,12,
4,33,8,12,0,6,48,12,8,2,248,1,48,16,4,5,231,1,16,8,
20,2,32,131,40,10,1,31,32,4,2,1,48,224,30,7,33,3,56,30,
0,0,16,16,179,41,60,36,16,8,251,34,16,56,23,63,3,16,221,12,
44,32,4,17,8,221,4,2,28,4,4,62,253,4,8,62,7,63,48,62,
8,28,136,24,24,152,30,16,24,187,41,60,30,36,16,24,251,34,16,62,
23,63,3,24,221,12,44,60,4,17,30,221,4,2,62,4,4,62,125,4,
8,28,7,63,48,0,34,3,3,38,3,48,3,38,3,48,3,38,3,48,
3,246,3,32,32,39,50,2,255,17,7,49,4,14,23,52,56,255,32,43,
42,2,17,4,17,4,15,14,3,32,56,175,1,63,56,24,6,24,223,3,
63,60,30,2,7,24,157,46,1,62,40,24,153,40,30,56,24,153,40,28,
40,30,249,40,62,15,32,1,62,110,16,1,28,8,1,6,7,63,48,31,
60,115,16,4,23,53,32,119,23,52,24,23,52,28,119,16,4,20,16,6,
28,255,16,5,4,16,16,5,4,56,255,16,5,5,60,16,4,57,60,191,
16,4,1,60,16,4,56,3,63,62,184,48,31,60,48,251,16,4,60,23,
53,32,48,255,23,52,24,60,23,52,28,48,255,16,4,20,60,16,6,28,
48,255,16,5,4,56,16,5,4,60,255,16,5,5,60,16,4,57,60,59,
16,4,56,16,4,3,63,62,0,255,3,32,3,32,3,32,3,32,159,15,
63,63,56,8,8,217,8,8,8,1,8,223,11,32,3,40,8,1,8,153,
8,8,8,8,153,8,8,8,8,15,15,63,63,56,98,1,5,16,118,2,
32,1,17,5,118,33,2,1,17,5,102,11,40,6,48,118,11,40,1,17,
5,118,33,2,1,17,5,102,2,32,5,16,2,1,216,1,60,2,2,214,
4,1,8,32,8,254,32,28,1,48,60,1,56,255,60,1,56,60,1,56,
28,1,73,48,32,32,9,25,30,210,16,56,1,60,182,3,62,7,63,15,
255,63,32,31,63,48,63,63,56,219,1,60,1,60,1,60,182,1,60,1,
60,1,13,60,1,60,219,1,60,1,60,1,60,182,1,60,1,60,1,237,
60,1,60,63,63,56,255,31,63,48,15,63,32,7,63,54,3,62,1,60,
9,56,16,192,7,60,182,1,62,7,62,1,109,62,7,62,1,62,219,7,
63,1,62,7,63,247,32,1,62,7,63,32,1,125,62,7,63,48,1,62,
223,7,63,56,1,62,7,63,247,56,1,62,7,59,60,1,125,62,7,59,
62,1,62,223,7,57,62,1,62,7,57,247,63,1,62,7,56,63,33,125,
62,7,56,31,33,62,223,7,56,31,49,62,7,56,247,15,49,62,7,56,
15,57,125,62,7,56,7,61,62,223,7,56,3,61,62,7,56,247,3,63,
62,7,56,1,63,109,62,7,56,63,62,219,7,56,63,62,7,56,182,31,
62,7,56,15,109,62,7,56,15,62,219,7,56,7,62,7,56,182,3,62,
7,56,3,1,62,128,3,227,63,60,3,63,60,56,3,63,60,142,3,63,
60,3,195,63,60,3,60,48,3,60,12,3,60,195,3,60,3,60,48,3,
60,12,3,60,195,3,60,3,60,48,3,60,12,3,60,195,3,60,3,60,
48,3,60,12,3,60,195,3,60,3,60,48,3,60,12,3,60,195,3,60,
3,60,48,3,60,12,3,60,195,3,60,3,60,0,0,227,31,56,3,63,
62,120,7,63,63,32,158,15,63,63,48,31,231,63,63,48,63,48,31,121,
56,63,32,15,56,219,1,63,7,56,1,63,182,7,56,1,62,7,97,56,
15,56,24,15,56,198,63,48,1,63,49,32,3,63,12,15,62,227,31,60,
1,63,56,56,3,63,32,134,7,63,7,97,60,15,56,24,31,48,134,31,
48,63,241,32,1,63,63,63,125,60,1,63,63,63,60,223,1,63,63,63,
60,1,63,247,63,63,60,1,63,63,63,1,60,0,227,63,56,3,63,62,
120,15,63,63,32,158,31,63,63,48,31,231,63,63,48,63,48,31,121,56,
63,32,15,56,26,63,7,56,134,7,56,7,97,56,15,56,24,15,48,198,
63,48,63,63,49,32,63,63,12,63,60,195,63,63,63,63,97,32,63,48,
24,15,48,134,15,56,7,97,56,7,56,154,63,7,56,63,231,32,15,56,
63,48,31,121,56,31,63,63,48,158,31,63,63,48,15,231,63,63,32,3,
63,62,0,0,130,31,63,48,1,63,12,3,63,195,7,63,15,63,48,31,
63,140,63,63,1,227,63,31,3,62,31,56,7,60,31,142,15,56,31,31,
227,48,31,63,32,31,44,1,63,31,203,3,62,31,7,60,178,31,15,56,
31,124,15,63,63,63,62,223,15,63,63,63,62,15,63,247,63,63,62,15,
63,63,63,125,62,15,63,63,63,62,8,31,130,31,31,32,31,8,31,130,
31,31,0,
};

const pic_data_t picture_data_records[18] = {
{&pic_bytes[0], 40, 64, 1},
{&pic_bytes[1672], 43, 64, 1},
{&pic_bytes[3841], 4, 15, 1},
{&pic_bytes[3882], 4, 15, 1},
{&pic_bytes[3926], 4, 15, 1},
{&pic_bytes[3971], 4, 15, 1},
{&pic_bytes[4018], 4, 15, 1},
{&pic_bytes[4070], 4, 15, 1},
{&pic_bytes[4128], 4, 15, 1},
{&pic_bytes[4174], 4, 15, 1},
{&pic_bytes[4214], 3, 16, 1},
{&pic_bytes[4249], 3, 15, 1},
{&pic_bytes[4286], 3, 15, 1},
{&pic_bytes[4323], 6, 31, 1},
{&pic_bytes[4485], 6, 31, 1},
{&pic_bytes[4574], 6, 31, 1},
{&pic_bytes[4693], 6, 31, 1},
{&pic_bytes[4803], 6, 31, 1},
};
