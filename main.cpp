#include "TEA.h"

using namespace std;

struct User {
	string name;
	int id = 0;
};

int main() { // отправитель
	setlocale(LC_ALL, "RUS");

	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;

	string op;
	string key;

	cout << "Введите ключ шифрования: ";
	cin >> key;

	while (key.size() < kchar) key += '0'; // дополнение ключа
	ifstream ifs{ "text.txt" };
	ofstream ofs{ "en_text.txt" };
	if (!ifs || !ofs) cerr << "фаил не найден" << endl;

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

	unsigned long outptr[2];
	char inbuf[nchar];
	unsigned long* inptr = reinterpret_cast<unsigned long*>(inbuf);
	int count = 0;

	while (ifs.get(inbuf[count])) {
		ofs << hex; // используется шестнадцатеричный вывод
		if (++count == nchar) {
			encipher(inptr, outptr, k);
			// заполнение ведущими нулями
			ofs << setw(8) << setfill('0') << outptr[0] << ' '
				<< setw(8) << setfill('0') << outptr[1] << ' ';
			count = 0;
		}
	}

	if (count) { // заполнение
		while (count != nchar) inbuf[count++] = '0';
		encipher(inptr, outptr, k);
		ofs << outptr[0] << ' ' << outptr[1] << ' ';
	}

	return 0;
}

int main2() { // получатель
	setlocale(LC_ALL, "RUS");

	const int nchar = 2 * sizeof(long);
	const int kchar = 2 * nchar;

	string key;
	cout << "Введите ключ дешифрования: ";
	cin >> key;

	while (key.size() < kchar) key += '0';

	ifstream ifs{ "en_text.txt" };
	if (!ifs) cerr << "файл не найден" << endl;

	const unsigned long* k = reinterpret_cast<const unsigned long*>(key.data());

	unsigned long inptr[2];
	char outbuf[nchar + 1];
	outbuf[nchar] = 0;
	unsigned long* outptr = reinterpret_cast<unsigned long*>(outbuf);

	ifs.setf(ios_base::hex, ios_base::basefield);

	while (ifs >> inptr[0] >> inptr[1]) {
		decipher(inptr, outptr, k);
		cout << outbuf;
	}

	return 0;
}