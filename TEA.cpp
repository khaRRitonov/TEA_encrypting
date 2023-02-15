//---------------------------------------------------------------
// Tiny Encryption Algorithm (TEA)
// --------------------------------------------------------------

// шифрование
void encipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k) {
	static_assert(sizeof(long) == 4, "неверный размер long для TEA");

	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0;
	const unsigned long delta = 0x9E3779B9;

	for (unsigned long n = 32; n-- > 0;) {
		y += (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
		sum += delta;
		z += (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
	}
	w[0] = y;
	w[1] = z;
}

// дешифрование
void decipher(const unsigned long* const v, unsigned long* const w, const unsigned long* const k) {
	static_assert(sizeof(long) == 4, "неверный размер long для TEA");

	unsigned long y = v[0];
	unsigned long z = v[1];
	unsigned long sum = 0xC6EF3720;
	const unsigned long delta = 0x9E3779B9;

	for (unsigned long n = 32; n-- > 0;) {
		z -= (y << 4 ^ y >> 5) + y ^ sum + k[sum >> 11 & 3];
		sum -= delta;
		y -= (z << 4 ^ z >> 5) + z ^ sum + k[sum & 3];
	}
	w[0] = y;
	w[1] = z;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------