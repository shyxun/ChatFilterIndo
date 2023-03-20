#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

class Data
{
public:
	vector<string> kata_kasar
	{
		"anjing",
		"kontol",
		"memek",
		"ngentod",
		"babi",
		"bego",
		"jembut",
		"bangsat",
		"ngewe",
		"lonte",
		"asu"
	};

	map<string, string> huruf_spesial
	{
		{"@", "a"},
		{"1", "i"},
		{"0", "o"},
		{"3", "e"},
		{"6", "g"},
		{"7", "t"},
		{"4", "a"}
	};
};

string olah_teks(string input, Data* data)
{
	// membuat dummy, untuk mengolah teks yang untuk difilter.
	string hasil = input, dummy = input;

	// mengubah teks menjadi lowercase.
	for (char& lowercase : dummy)
		lowercase = tolower(lowercase);

	// Melakukan cek jika kita menggunakan huruf spesial.
	// 
	// kita 'kutip' semua huruf spesial.
	for (auto i = data->huruf_spesial.begin(); i != data->huruf_spesial.end(); i++)
	{
		// kita mengulang-mengulang lagi kode-nya sampai kita dapat mengubah huruf spesial menjadi huruf biasa.
		for (int k = 0; k < dummy.size(); k++)
		{
			// saatnya kita mencari teks yang ada karakter spesial-nya.
			if (dummy.find(i->first) != string::npos)
			{
				// Mengubah teks yang kita cari.
				// argumen pertama berisi huruf yang akan kita cari, yaitu i->first, i->first adalah isi dari huruf_spesial yang dalam baris pertama.
				// argumen kedua adalah panjangnya teks yang kita cari.
				// argumen ketiga mengubah huruf spesial menjadi huruf normal.
				dummy.replace(dummy.find(i->first), i->first.length(), i->second);
			}
		}
	}

	// Mengubah kata kasar menjadi bintang-bintang.
	// 
	// kita cari kata kasar-nya.
	for (auto& kata_kasar : data->kata_kasar)
	{
		// cari posisi teks yang akan kita ubah.
		size_t posisi = dummy.find(kata_kasar);

		// teks yang berada di-posisi saat ini adalah teks yang berbau kasar!
		while (posisi != string::npos)
		{
			// Mengubah teks yang kita cari.
			// argumen pertama berisi huruf yang akan kita cari, yaitu 'posisi', yang berarti kita cari bahasa kasar bertahap-tahap.
			// argumen kedua adalah panjangnya teks yang kita cari.
			// argumen ketiga mengubah kata menjadi sensor.
			hasil.replace(posisi, kata_kasar.length(), string(kata_kasar.length(), '*'));

			// Ubah posisi untuk menemukan kata kasar selanjutnya.
			posisi = dummy.find(kata_kasar, posisi + 1);
		}
	}

	return hasil;
}

int main()
{
	// Membuat data.
	Data* data = new Data;

	// Informasi-informasi yang diperlukan.
	string input_masuk;

	// Tahapan awal.
	cout << "\x1B[31mKetik kata kasar dalam Bahasa Indonesia: \n";
	getline(cin, input_masuk);

	// pembatas.
	cout << "\n";

	// Melakukan pengolahan dari teks yang telah di-input.
	cout << "\x1B[36mKata kasar yang telah di-sensor: \n";
	cout << olah_teks(input_masuk, data);

	// mengubah warna menjadi warna putih.
	cout << ("\x1B[37m \n");

	return 0;
}
