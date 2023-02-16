//---------------------------------------------------------------
// Àëãîðèòìû øèôðîâàíèÿ Tiny Encryption Algorithm (TEA)
// --------------------------------------------------------------

#include <iostream>
#include <fstream>
#include <iomanip>

// øèôðîâàíèå
void encipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k);

// äåøèôðîâàíèå
void decipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k);

// --------------------------------------------------------------
// --------------------------------------------------------------
