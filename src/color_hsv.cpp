// double threeway_max(double a, double b, double c) {
//     return max(a, max(b, c));
// }
//
// double threeway_min(double a, double b, double c) {
//     return min(a, min(b, c));
// }
//
// void hsv(uint8_t r, uint8_t g, uint8_t b) {
//     double rd = (double) r/255;
//     double gd = (double) g/255;
//     double bd = (double) b/255;
//     double max = threeway_max(rd, gd, bd), min = threeway_min(rd, gd, bd);
//     double h, s, v = max;
//
//     double d = max - min;
//     s = max == 0 ? 0 : d / max;
//
//     if (max == min) { 
//         h = 0; // achromatic
//     } else {
//         if (max == rd) {
//             h = (gd - bd) / d + (gd < bd ? 6 : 0);
//         } else if (max == gd) {
//             h = (bd - rd) / d + 2;
//         } else if (max == bd) {
//             h = (rd - gd) / d + 4;
//         }
//         h /= 6;
//     }
//
//     Serial.print(h);
//     Serial.print(" ");
//     Serial.print(s);
//     Serial.print(" ");
//     Serial.println(v);
//     // logf("%f %f %f", h, s, v);
// }
