#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <algorithm>

using namespace std;

class Data
{
public:
	string input_masuk = "";
	bool mengandung_kata_kasar = false;
	int jumlah_kata_kasar = 0;

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
		"asu",
		"anjg",
		"asw",
		"meki"
	};

	map<string, string> huruf_spesial
	{
		{"@", "a"},
		{"1", "i"},
		{"!", "i"},
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
	std::transform(dummy.begin(), dummy.end(), dummy.begin(), ::tolower);

	// Melakukan cek jika kita menggunakan huruf spesial.
	// 
	// kita 'kutip' semua huruf spesial.
	for (auto i = data->huruf_spesial.begin(); i != data->huruf_spesial.end(); i++)
	{
		// cari posisi teks yang akan kita ubah.
		size_t posisi = dummy.find(i->first);

		// mencari teks yang ada karakter spesial-nya.
		while (posisi != string::npos)
		{
			// Mengubah teks yang kita cari.
			// argumen pertama berisi huruf yang akan kita cari, yaitu i->first, i->first adalah isi dari huruf_spesial yang dalam baris pertama.
			// argumen kedua adalah panjangnya teks yang kita cari.
			// argumen ketiga mengubah huruf spesial menjadi huruf normal.
			dummy.replace(dummy.find(i->first), i->first.length(), i->second);

			// Ubah posisi untuk menemukan karakter spesial selanjutnya.
			posisi = dummy.find(i->first, posisi + 1);
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
			data->mengandung_kata_kasar = true;

			// Mengubah teks yang kita cari.
			// argumen pertama berisi huruf yang akan kita cari, yaitu 'posisi', yang berarti kita cari bahasa kasar bertahap-tahap.
			// argumen kedua adalah panjangnya teks yang kita cari.
			// argumen ketiga mengubah kata menjadi sensor.
			hasil.replace(posisi, kata_kasar.length(), string(kata_kasar.length(), '*'));

			// Ubah posisi untuk menemukan kata kasar selanjutnya.
			posisi = dummy.find(kata_kasar, posisi + 1);
			data->jumlah_kata_kasar++;
		}
	}

	return hasil;
}

int main()
{
	// Membuat data.
	Data* data = new Data;

	// Informasi-informasi yang diperlukan.
	
	// Tahapan awal.
	cout << "\x1B[31mKetik kata kasar dalam Bahasa Indonesia:\n";
	getline(cin, data->input_masuk);

	// Melakukan pengolahan dari teks yang telah di-input.
	cout << "\n\x1B[36mKata kasar yang telah di-sensor:\n";
	cout << olah_teks(data->input_masuk, data) << ("\x1B[37m \n");;
	cout << "\nApakah terdapat kata kasar: " << (data->mengandung_kata_kasar ? "ya, " : "tidak ") << (data->mengandung_kata_kasar ? (string("sebanyak: " + to_string(data->jumlah_kata_kasar))) : "") << "\n";

	// Menghapus "data" untuk menghindari memory leak.
	delete data;

	return 0;
}
