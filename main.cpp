// ------------------------------------------------------------------------
// Working with data at the level of bits and bytes using a simple 
// encryption algorithm as an example - Tiny Encryption Algorithm (TEA).
// ------------------------------------------------------------------------

#include "TEA.h"

//----------------------------------------------------------------------------
// Sender
//----------------------------------------------------------------------------

int main() { // �����������
	setlocale(LC_ALL, "RUS");

	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;

	std::string op;
	std::string key;

	std::cout << "������� ���� ����������: ";
	std::cin >> key;

	while (key.size() < kchar) key += '0'; // ���������� �����
	std::ifstream ifs{ "text.txt" };
	std::ofstream ofs{ "en_text.txt" };
	if (!ifs || !ofs) std::cerr << "���� �� ������" << std::endl;

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

	unsigned long outptr[2];
	char inbuf[nchar];
	unsigned long* inptr = reinterpret_cast<unsigned long*>(inbuf);
	int count = 0;

	while (ifs.get(inbuf[count])) {
		ofs << std::hex; // ������������ ����������������� �����
		if (++count == nchar) {
			encipher(inptr, outptr, k);
			// ���������� �������� ������
			ofs << std::setw(8) << std::setfill('0') << outptr[0] << ' '
				<< std::setw(8) << std::setfill('0') << outptr[1] << ' ';
			count = 0;
		}
	}

	if (count) { // ����������
		while (count != nchar) inbuf[count++] = '0';
		encipher(inptr, outptr, k);
		ofs << outptr[0] << ' ' << outptr[1] << ' ';
	}

	return 0;
}

//----------------------------------------------------------------------------
// Recipient
//----------------------------------------------------------------------------

int main2() { // ����������
	setlocale(LC_ALL, "RUS");

	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;

	std::string key;
	std::cout << "������� ���� ������������: ";
	std::cin >> key;

	while (key.size() < kchar) key += '0';

	std::ifstream ifs{ "en_text.txt" };
	if (!ifs) std::cerr << "���� �� ������" << std::endl;

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

	unsigned long inptr[2];
	char outbuf[nchar + 1];
	outbuf[nchar] = 0;
	unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf);

	ifs.setf(std::ios_base::hex, std::ios_base::basefield);

	while (ifs >> inptr[0] >> inptr[1]) {
		decipher(inptr, outptr, k);
		std::cout << outbuf;
	}

	return 0;
}

//----------------------------------------------------------------------------
//----------------------------------------------------------------------------