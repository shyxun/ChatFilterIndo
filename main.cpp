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

string censor(string text,
	string word)
{

	// Break down sentence by ' ' spaces
	// and store each individual word in
	// a different list
	vector<string> word_list;

	// A new string to store the result
	string result = "";

	// Creating the censor which is an asterisks
	// "*" text of the length of censor word
	string stars = "";
	for (int i = 0; i < word.size(); i++)
		stars += '*';

	// Iterating through our list
	// of extracted words
	int index = 0;
	for (string i : word_list)
	{

		if (i.compare(word) == 0)
		{

			// changing the censored word to
			// created asterisks censor
			word_list[index] = stars;
		}
		index++;
	}

	// join the words
	for (string i : word_list)
	{
		result += i + ' ';
	}
	return result;
}

int main()
{
	// Membuat data.
	Data* data = new Data;

	// Informasi-informasi yang diperlukan.
	string input_masuk, dummy;

	// Tahapan awal.
	cout << "Ketik kata kasar dalam Bahasa Indonesia: \n";
	getline(cin, input_masuk);

	// Membuat dummy, untuk mengolah teks yang untuk difilter.
	dummy = input_masuk;

	// mengubah teks menjadi lowercase.
	for (char& low : dummy)
		low = tolower(low);

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
				// mengubah teks yang kita cari.
				// argumen pertama berisi huruf yang akan kita cari, yaitu i->first, i->first adalah isi dari huruf_spesial yang dalam baris pertama.
				// argumen kedua adalah panjangnya teks yang kita cari
				// argumen ketiga adalah kata ternormalisasi dari huruf spesial.
				dummy.replace(dummy.find(i->first), i->first.length(), i->second);
			}
		}
	}

	// Mengubah kata kasar menjadi bintang-bintang.
	// 
	// kita cari kata kasar-nya.
	for (auto i = 0; i < data->kata_kasar.size(); i++)
	{
		// cari posisi teks yang akan kita ubah.
		size_t posisi = dummy.find(data->kata_kasar.at(i));

		// teks yang berada di-posisi saat ini adalah teks yang berbau bahasa kasar!
		while (posisi != string::npos)
		{
			// mengubah teks yang kita cari.
			// argumen pertama berisi huruf yang akan kita cari, yaitu 'posisi', yang berarti kita cari bahasa kasar bertahap-tahap.
			// argumen kedua adalah panjangnya teks yang kita cari
			// argumen ketiga adalah kata yang telah di sensor.
			input_masuk.replace(posisi, data->kata_kasar.at(i).length(), string(data->kata_kasar.at(i).length(), '*'));
			
			// ubah posisi untuk menemukan bahasa kasar selanjutnya.
			posisi = dummy.find(data->kata_kasar.at(i), posisi + 1);
		}
	}

	// Hasil dari teks yang telah di-input.
	cout << "Kata kasar yang telah di-sensor: \n";
	cout << input_masuk;

	return 0;
}