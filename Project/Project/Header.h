#pragma once

#include <iostream>
#include <fstream> //ReadFile (file.open)
#include <string>  //string.find() , substr (substring)
#include <sstream> //[sentenceToWords inside the istringstream]
#include <vector>  //Vector definition
#include <algorithm>

using namespace std;


//This part is the method of separating sentences into words. 
//O(n) for n words in sentence.
vector<string> sentenceToWords(int i, vector<string> a)
{
	vector<string> b; // where we hold the words (we separated from the sentence)

	istringstream iss(a[i]); //are sentences 

	while (iss)
	{
		string subs; // substring
		iss >> subs; // we divide sentences into words 
	

		if (subs != "") //if is not space it continues
		{
			//If the initials of the words are UpperCase, they will be converted to LowerCase
			if (subs[0] <= 'Z' && subs[0] >= 'A') {
				subs[0] = subs[0] + 32;
			  
				b.push_back(subs);
			}

			else { //If not here - it pushes the vector b
				b.push_back(subs);
			}
		}
	}
	//If it is empty (here it is first if statement) it finishes the work and returns b
	return b;
}

//Similar to sentenceToWords -  but it just counts instead of keeping words.
//Inputs are just a sentence of the document
// O(n) for n words in sentence.
int wordCount(string Sentence)
{
	istringstream iss(Sentence);
	int counter = 0;

	while (iss)
	{
		string subs;
		iss >> subs;
		if (subs != "")
		{
			counter++; //when the words is found, increase the counter
		}
	}
	return counter; // when the word is found counter is returned.
}

//We give doesExist the word/-s to search, and the sentence it searches. 
//Inputs are our word list and source file to be searched.
//O(n) for n words.
int doesExist(vector<string> Words, string Sentence)
{
	int found_word_counter = 0; //Word counter of founded word
	int found_location = 0;     //location of the founded word
	for (int index = 0; index < Words.size(); index++)   //For each word
	{
		found_location = Sentence.find(Words[index]); // We are searching for the word in a normal way.
		if (found_location < 0) {
			Words[index][0] = Words[index][0] - 32;
			found_location = Sentence.find(Words[index]);
		}

		if (Sentence == "" || Sentence == " ")  // The sentence can sometimes be empty or even a space
		{
			return found_word_counter;
		}

		if (found_location >= 0) //word is founded
		{
			int isThere = found_location + Words[index].length(); //Getting the location after the word
			string before = Sentence.substr(0, found_location); //The part up to the word is separated

			try
			{
				if (Sentence.at(isThere) == ' ')   // If there is a blank space after the word, it is a successful search. 
					                              // Word found, exact match.
				{
					found_word_counter++;
					string after = Sentence.substr(found_location + Words[index].length() + 1, Sentence.length()); // After the word is cut off.
					Sentence = before + after; // Merging before and after the words. Then it is assigned to our sentence.
				}
			}
			catch (const exception e)  // If it tries to reach beyond the word at the end of the sentence, it will throw an out-of-bound error.
		   						       //So it is kept with try - catch.The word entering here is exactly matched.
				{ 
				found_word_counter++;
				string after = Sentence.substr(found_location + Words[index].length(), Sentence.length()); // After the word is cut off.
				Sentence = before + after;  // Merging before and after the words. Then it is assigned to our sentence.
			}
		}
	}

	return found_word_counter;
}

// O(a*b) => n = max(a,b) then, O(n^2) for n doesExist function.
vector<vector<double>> comparison(vector<string> MainDocument, vector<string> ComparedDocument)
{
	vector<vector<double>> result(MainDocument.size(), vector<double>(ComparedDocument.size())); //A[i][j] = number;
	double similarity;

	for (int i = 0; i < MainDocument.size(); i++) // From original document ?. sentence is taken
	{
		vector<string> GetWords = sentenceToWords(i, MainDocument); // From original document ?. sentence is divided into words and kept.

		for (int j = 0; j < ComparedDocument.size(); j++)
		{
			string Sentence; //The sentences of the 2nd file will be put into vector sentences in order.
			Sentence = ComparedDocument[j]; // From the source document ?. sentence is taken.

			int found_words = doesExist(GetWords, Sentence); // How many words were found

			if (found_words != 0) //if the found_words is not 0 (it means we found words)
			{
				similarity = (double)found_words / (double)wordCount(Sentence);
			}
			else
			{
				similarity = 0; // If 0 words are found, the similarity is 0
			}

			// how many words have I found / how many words are there in the sentence

			result[i][j] = similarity;
		}
	}

	return result;
}

//O(1)
//All words of the original document and all sentences of the document to be compared
double fullComparison(vector<string> AllWords, string FullSentence)
{
	//allwords and fullsentence are thrown into doesExist function
	int found_words = doesExist(AllWords, FullSentence);
	int total_words = wordCount(FullSentence); //returns until it matches

	//founded words / total words of the sentence
	double similarity = (double)found_words / (double)total_words;

//	cout << "\nInformation: On the document, " << found_words << " words are similar out of " << total_words << " words." << endl;
	return similarity; //The similarity rate is returned.
}

//O(n) for n sentences for a. 
void documentSimilarity(vector<string> a, vector<string> b)
{
	vector<string> allWords;
	string fullSentence;

	for (int i = 0; i < a.size(); i++)
	{
		//all sentences are separated by sending to sentenceToWords - the words are kept in allWords.
		vector<string> Words = sentenceToWords(i, a);
		allWords.insert(allWords.end(), Words.begin(), Words.end());
	}

	for (int i = 0; i < b.size(); i++)
	{ //the sentences are merged in order
		fullSentence = fullSentence + " " + b[i];
	}

	//allWords and fullSentences are sent to fullComparison.
	double result = fullComparison(allWords, fullSentence);

	cout << "Document similarity is: " << result * 100 << "%"<< "\n" << endl; // similarity rate of the compared files
}



//2-dimensional Vector with similarity rates 
// O(5n^2) => O(n^2)
void findMostSimilars(vector<vector<double>> result, vector<string> MainDoc, vector<string> ComparedDoc)

{
	vector<string> display = { "{ ", "{ Second ", "{ Third ", "{ Fourth ", "{ Fifth " };

	for (int repeat = 0; repeat <= 4; repeat++)
	{
		double maxVal = 0;
		int locFirstDoc = -1, locSecDoc = -1;  /* So why are these described here?
											Answer: The above loop is repeated depending on how many times the function has to be executed.
											5 repetitions for 5 sentences.In each repetition, valuesand locations should be deleted
											so that information does not hang over the next repetition.*/

		for (int i = 0; i < result.size(); i++)
		{
			for (int j = 0; j < result[i].size(); j++)
			{
				if (result[i][j] > maxVal)
				{
					maxVal = result[i][j];
					locFirstDoc = i;
					locSecDoc = j;
				}
			}
		}
		if (locFirstDoc == -1 || locSecDoc == -1)
		{
			cout << "No similar sentences are found." << endl;
		}
		else
		{
			cout << display[repeat] <<"Most Similar Sentence: " << ComparedDoc[locSecDoc] << "}" << endl;
			result[locFirstDoc][locSecDoc] = 0;
		}

	}
}
vector<string> linetoSentence(string line)
{
	vector<string> lineFinishers = { "." };
	vector<string> lines;
	int found_location, another_location;
	int sayac = 0;

	for (int i = 0; i < lineFinishers.size(); i++)
	{
		found_location = line.find(lineFinishers[i]);

		if (found_location == -1 || (found_location + 1) == line.size())
		{
			string before = line.substr(0, found_location);
			lines.push_back(before);
		}
		else if ((found_location + 1) != line.size())
		{
			another_location = line.find(lineFinishers[i], found_location + 1);
			while (another_location >= 0)
			{
				found_location = line.find(lineFinishers[i]);
				another_location = line.find(lineFinishers[i], found_location + 1);
				string before = line.substr(0, found_location);
				string after = line.substr(found_location + 1, line.length());

				line = after;
				lines.push_back(before);
			}

		}
	}

	return lines;

}

//string vector variable where the sentences of the file to be opened are stored -
//the name of the file to be opened

vector<string> fileOpener(vector<string> docVector, string docName) {
	ifstream File;
	string line;
	File.open(docName);
	if (File.fail()) { cerr << "Error opening file !!" << endl; exit(1); }
	while (!File.eof()) {
		getline(File, line);
		vector<string> temp = linetoSentence(line);
		docVector.insert(docVector.end(), temp.begin(), temp.end());
		//docVector.push_back(line);
	}
	File.close();
	return docVector;
}

