/*
 * Contoh penggunaan library DMDESP
 * 
 * email : bonny@grobak.net - www.grobak.net - www.elektronmart.com
*/

#include <DMDESP.h>
#include <fonts/thai8x16.h>

// SETUP DMD
#define DISPLAYS_WIDE 1 // Kolom Panel
#define DISPLAYS_HIGH 1 // Baris Panel
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);  // Jumlah Panel P10 yang digunakan (KOLOM,BARIS)

//----------------------------------------------------------------------
// SETUP

void setup() {
  // DMDESP Setup
  Disp.start(); // Jalankan library DMDESP
  Disp.setBrightness(20); // Tingkat kecerahan
  Disp.setFont(thai8x16); // Tentukan huruf
}

//----------------------------------------------------------------------
// LOOP

void loop() {
  Disp.loop(); // Jalankan Disp loop untuk refresh LED

  // Disp.drawText(0, 0, "DMDESP"); // Tampilkan teks
  TeksJalan(0, 80); // Tampilkan teks berjalan TeksJalan(posisi y, kecepatan);
}

//--------------------------
// TAMPILKAN SCROLLING TEKS

// TAMPILKAN SCROLLING TEKS
// TAMPILKAN SCROLLING TEKS

// TAMPILKAN SCROLLING TEKS

void TeksJalan(int y, uint8_t kecepatan) {
  static uint32_t pM;
  static uint32_t x;
  int width = Disp.width();
  
  // Generate the text from \x20 to \xe2, skipping \x61 to \x7a
  static char scrollingText[1024]; // Increased buffer size for more spacing
  int index = 0;

  for (char c = 0x20; c <= 0xe2; c++) {
    if (c >= 0x61 && c <= 0x7a) {
      continue; // Skip characters from \x61 to \x7a
    }
    scrollingText[index++] = c; // Add the character
    scrollingText[index++] = ' '; // Add a space
    scrollingText[index++] = ' '; // Add another space for more spacing
  }
  scrollingText[index] = '\0'; // Null-terminate the string

  Disp.setFont(thai8x16);
  int fullScroll = Disp.textWidth(scrollingText) + width;

  if ((millis() - pM) > kecepatan) { 
    pM = millis();
    if (x < fullScroll) {
      ++x;
    } else {
      x = 0;
      return;
    }
    Disp.drawText(width - x, y, scrollingText);
  }  
}


