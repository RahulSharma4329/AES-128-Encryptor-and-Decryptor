#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>
#include "key_expand.h"
#include "encoding.h"
#include "decoding.h"
#include <typeinfo>
#include <windows.h>
using namespace std;

class Encryption
{
public:
	void dispkey()
	{
		string k;
		ifstream infile;
		infile.open("key.txt");
		if (infile.is_open())
		{
			getline(infile, k);
			infile.close();
		}

		else
			cout << "Unable to open file";
		cout << "The key from the key file" << endl
			 << k << endl;
	}
	void dispkey(string ipkey)
	{

		cout << "The key from the input" << endl
			 << ipkey << endl;
	}
	virtual void dispip()
	{
		cout << "just virtual fn in base class" << endl;
	}
	virtual void dispip(string ip)
	{
		cout << "just virtual fn in base class" << endl;
	}

public:
	void encrypt()
	{
		ifstream File;
		string filepath = "encryption.aes";
		// clearing encryption.aes before editing
		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		if (!File.is_open() || File.fail())
		{
			File.close();
			printf("\nError : failed to erase file content !");
		}
		File.close();
		// reading plain text from input.txt
		fstream newfile;
		newfile.open("input.txt", ios::in); // open a file to perform read operation using file object
		if (newfile.is_open())
		{ // checking whether the file is open
			cout << "Reading plain text from input.txt .........\n";
			Sleep(1000);
			string tp;
			cout << "Reading KEY from key.txt ......\n";
			Sleep(1000);
			cout << "Now encrypting ....\n";
			Sleep(1000);
			cout << "writing encrypted data in encryption.aes ..\n";
			Sleep(1000);
			cout << endl;
			while (getline(newfile, tp))
			{
				// read data from file object and put it into string.
				int messlength = tp.length();
				int extendedlength;
				if ((messlength % 16) != 0)
				{
					extendedlength = messlength + (16 - (messlength % 16));
				}
				else
				{
					extendedlength = messlength;
				}
				unsigned char *encryptedtext = new unsigned char[extendedlength];
				for (int i = 0; i < extendedlength; i++)
				{
					if (i < messlength)
						encryptedtext[i] = tp[i];
					else
						encryptedtext[i] = 0;
				}
				// getting key from key.txt
				string k;
				ifstream infile;
				infile.open("key.txt");
				if (infile.is_open())
				{
					getline(infile, k);
					infile.close();
				}

				else
					cout << "Unable to open file";

				istringstream tempkey(k);
				unsigned char key[16];
				unsigned int x;
				for (int i = 0; i < 16; i++)
				{
					tempkey >> hex >> x;
					key[i] = x;
				}
				// extending key
				unsigned char extendedkeys[176];
				Key_extenxion(key, extendedkeys);

				// encrypting our plain text
				for (int i = 0; i < extendedlength; i += 16)
				{
					unsigned char *temp = new unsigned char[16];
					for (int j = 0; j < 16; j++)
					{
						temp[j] = encryptedtext[i + j];
					}
					encryption(temp, extendedkeys);
					for (int j = 0; j < 16; j++)
					{
						encryptedtext[i + j] = temp[j];
					}
				}
				// storing our encrypted data in encryption.aes
				ofstream fout; // Create Object of Ofstream
				ifstream fin;
				fin.open("encryption.aes");
				fout.open("encryption.aes", ios::app); // Append mode
				if (fin.is_open())
					fout << encryptedtext << "\n"; // Writing data to file
				fin.close();
				fout.close();
			}
			cout << "128-bit AES encryption is done sucessfully\n";
			cout << "Data has been appended to file encryption.aes\n";
			newfile.close(); // close the file object.
		}
	}

public:
	void encrypt(string ip)
	{
		ifstream File;
		string filepath = "encryption.aes";
		// clearing encryption.aes before editing
		File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
		if (!File.is_open() || File.fail())
		{
			File.close();
			printf("\nError : failed to erase file content !");
		}
		File.close();
		// reading plain text from input.txt
		// fstream newfile;
		// newfile.open("input.txt", ios::in); // open a file to perform read operation using file object

		string tp;

		Sleep(1000);
		cout << "Now encrypting ....\n";
		Sleep(1000);
		cout << "writing encrypted data in encryption.aes ..\n";
		Sleep(1000);
		cout << endl;
		
			// read data from file object and put it into string.
			int messlength = ip.length();
			int extendedlength;
			if ((messlength % 16) != 0)
			{
				extendedlength = messlength + (16 - (messlength % 16));
			}
			else
			{
				extendedlength = messlength;
			}
			unsigned char *encryptedtext = new unsigned char[extendedlength];
			for (int i = 0; i < extendedlength; i++)
			{
				if (i < messlength)
					encryptedtext[i] = ip[i];
				else
					encryptedtext[i] = 0;
			}
			// getting key from key.txt
			string k;
			ifstream infile;
			infile.open("key.txt");
			if (infile.is_open())
			{
				getline(infile, k);
				infile.close();
			}

			else
				cout << "Unable to open file";

			istringstream tempkey(k);
			unsigned char key[16];
			unsigned int x;
			for (int i = 0; i < 16; i++)
			{
				tempkey >> hex >> x;
				key[i] = x;
			}
			// extending key
			unsigned char extendedkeys[176];
			Key_extenxion(key, extendedkeys);

			// encrypting our plain text
			for (int i = 0; i < extendedlength; i += 16)
			{
				unsigned char *temp = new unsigned char[16];
				for (int j = 0; j < 16; j++)
				{
					temp[j] = encryptedtext[i + j];
				}
				encryption(temp, extendedkeys);
				for (int j = 0; j < 16; j++)
				{
					encryptedtext[i + j] = temp[j];
				}
			}
			// storing our encrypted data in encryption.aes
			ofstream fout; // Create Object of Ofstream
			ifstream fin;
			fin.open("encryption.aes");
			fout.open("encryption.aes", ios::app); // Append mode
			if (fin.is_open())
				fout << encryptedtext << "\n"; // Writing data to file
			fin.close();
			fout.close();
		
		cout << "128-bit AES encryption is done sucessfully\n";
		cout << "Data has been appended to file encryption.aes\n";
	}
};
class Decryption
{
	friend void decrypt(string myText);
};

class Driver : public Encryption, public Decryption
{
	void dispkey()
	{
		string k;
		ifstream infile;
		infile.open("key.txt");
		if (infile.is_open())
		{
			getline(infile, k);
			infile.close();
		}

		else
			cout << "Unable to open file";
		cout << "The key from the key file" << endl
			 << k << endl;
	}

	void dispip()
	{
		fstream newfile;
		newfile.open("input.txt", ios::in); // open a file to perform read operation using file object
		if (newfile.is_open())
		{ // checking whether the file is open
			cout << "Reading plain text from input.txt .........\n";
			Sleep(1000);
			Sleep(1000);
			string tp;
			cout << "The ip is \n";
			Sleep(1000);
			while (getline(newfile, tp))
			{
				cout << tp << endl;
			}
		}
	}
	void dispip(string ip)
	{
		cout << "The ip is \n";
		Sleep(1000);
			cout << ip << endl;
	}
};

void decrypt(string myText)
{
	cout << "Reading encrypted data from encryption.txt .........\n";
	Sleep(1000);
	string tp;
	cout << "Reading KEY from key.txt ......\n";
	Sleep(1000);
	cout << "Now Decrypting ....\n";
	Sleep(1000);
	cout << "writing decrypted data in outputtext.txt ..\n";
	Sleep(1000);
	cout << endl;
	cout << "Following is our decrypted text:- \n";
	// clearing outputtext file
	ifstream File;
	string filepath = "outputtext.txt";
	File.open(filepath.c_str(), std::ifstream::out | std::ifstream::trunc);
	if (!File.is_open() || File.fail())
	{
		File.close();
		printf("\nError : failed to erase file content !");
	}
	File.close();

	ifstream MyReadFile;
	MyReadFile.open("encryption.aes", ios::in | ios::binary);
	if (MyReadFile.is_open())
	{
		while (getline(MyReadFile, myText))
		{
			cout.flush();
			char *x;
			x = &myText[0];
			int messlength = strlen(x);
			char *msg = new char[myText.size() + 1];

			strcpy(msg, myText.c_str());

			int n = strlen((const char *)msg);
			unsigned char *decryptedtext = new unsigned char[n];
			// decrypting our encrypted data
			for (int i = 0; i < n; i++)
			{
				decryptedtext[i] = (unsigned char)msg[i];
			}
			// reading key from key.txt file
			string k;
			ifstream infile;
			infile.open("key.txt");
			if (infile.is_open())
			{
				getline(infile, k); // The first line of file should be the key
				infile.close();
			}

			else
				cout << "Unable to open file";
			istringstream tempkey(k);
			unsigned char key[16];
			unsigned int x1;
			for (int i = 0; i < 16; i++)
			{
				tempkey >> hex >> x1;
				key[i] = x1;
			}
			// extending key
			unsigned char extendedkeys[176];
			Key_extenxion(key, extendedkeys);
			// decrypting our data
			for (int i = 0; i < messlength; i += 16)
			{
				unsigned char *temp = new unsigned char[16];
				for (int j = 0; j < 16; j++)
					temp[j] = decryptedtext[i + j];
				decryption(temp, extendedkeys);
				for (int j = 0; j < 16; j++)
					decryptedtext[i + j] = temp[j];
			}
			// printing our plain text
			for (int i = 0; i < messlength; i++)
			{
				cout << decryptedtext[i];
				if (decryptedtext[i] == 0 && decryptedtext[i - 1] == 0)
					break;
			}
			// storing plain text in outputtext.txt file
			cout << endl;
			ofstream fout; // Create Object of Ofstream
			ifstream fin;
			fin.open("outputtext.txt");
			fout.open("outputtext.txt", ios::app); // Append mode
			if (fin.is_open())
				fout << decryptedtext << "\n"; // Writing data to file

			fin.close();
			fout.close(); // Closing the file
			Sleep(500);
		}
	}
	else
	{
		cout << "Can not open input file\n ";
	}
	cout << "\n Data has been appended to file outputtext.txt";
	MyReadFile.close();
}

class final : public Encryption, public Decryption, public Driver
{
public:
	string ip;
	int extendedlength;
	int choice;
	string myText;
	final()
	{
		extendedlength = 0;
		choice = 0;
		myText = "";
	}
	final(string input)
	{
		extendedlength = 0;
		choice = 0;
		myText = "";
		ip = input;
	}
	~final()
	{
		cout << "object destroyed" << endl;
	}

public:
	void main1()
	{
	label:
		cout << "Welcome to 128 bits AES encryption" << endl;
		cout << endl;
		cout << "Enter you choice " << endl;
		cout << "1- Encoding" << endl;
		cout << "2- Decoding" << endl;
		cin >> choice;
		try
		{
			if (choice > 3)
			{
				throw(choice);
			}
			else
			{
				Encryption *eptr;
				Driver dr1;
				eptr = &dr1;
				Decryption d1;
				Encryption e1;
				switch (choice)
				{
				case 1:
					if (ip == "")
					{
						//when user wants to give input from file
						eptr->dispip();
						eptr->dispkey();
						eptr->encrypt();
					}
					else
					{
						//when user wants to give input from command line
						eptr->dispip(ip);
						eptr->encrypt(ip);
					}
					break;
				case 2:
					decrypt(myText);
				default:
					break;
				}
			}
		}
		catch (int err)
		{
			cout << "the choice cannot be " << err << endl;
		}
	}
};
int main()
{
	//calling code for input from input files
	{
	final f;
	f.main1();
	}

	//calling code for input as a text
	// {
	// string s1;
	// cout <<"Enter the text"<<endl;
	// cin >> s1;
	// final f1(s1);
	// f1.main1();
	// }

	cout << "program execution ended\n";
}