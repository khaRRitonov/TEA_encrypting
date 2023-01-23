//---------------------------------------------------------------
// Алгоритмы шифрования Tiny Encryption Algorithm (TEA)
// --------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>

// шифрование
void encipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k);

// дешифрование
void decipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k);