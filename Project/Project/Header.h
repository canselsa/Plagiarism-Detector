#pragma once

#include <iostream>
#include <fstream> 
#include <string>  
#include <sstream> 
#include <vector>  
#include <algorithm>

using namespace std;


//This part is the method of separating sentences into words. 
//O(n) for n words in sentence.
vector<string> sentenceToWords(int i, vector<string> a)
{
	vector<string> b; 

	istringstream iss(a[i]); //are sentences 

	while (iss)
	{
		string subs; 
		iss >> subs; 
	

		if (subs != "")
		{
		        	if (subs[0] <= 'Z' && subs[0] >= 'A') {
				subs[0] = subs[0] + 32;
			  
				b.push_back(subs);
			}

			else { //If not here - it pushes the vector b
				b.push_back(subs);
			}
		}
	}
	return b;
}

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
			counter++; 
		}
	}
	return counter; 
}

//We give doesExist the word/-s to search, and the sentence it searches. 
//Inputs are our word list and source file to be searched.
//O(n) for n words.
int doesExist(vector<string> Words, string Sentence)
{
	int found_word_counter = 0; 
	int found_location = 0;    
	for (int index = 0; index < Words.size(); index++)   
	{
		found_location = Sentence.find(Words[index]);
		if (found_location < 0) {
			Words[index][0] = Words[index][0] - 32;
			found_location = Sentence.find(Words[index]);
		}

		if (Sentence == "" || Sentence == " ")  
		{
			return found_word_counter;
		}

		if (found_location >= 0) //word is founded
		{
			int isThere = found_location + Words[index].length(); 
			string before = Sentence.substr(0, found_location); 

			try
			{
				if (Sentence.at(isThere) == ' ')   
				{
					found_word_counter++;
					string after = Sentence.substr(found_location + Words[index].length() + 1, Sentence.length()); 
					Sentence = before + after; 
				}
			}
			catch (const exception e)  
				{ 
				found_word_counter++;
				string after = Sentence.substr(found_location + Words[index].length(), Sentence.length()); 
				Sentence = before + after;  
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
			string Sentence; 
			Sentence = ComparedDocument[j]; // From the source document ?. sentence is taken.

			int found_words = doesExist(GetWords, Sentence); 

			if (found_words != 0) 
			{
				similarity = (double)found_words / (double)wordCount(Sentence);
			}
			else
			{
				similarity = 0; 
			}
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
		int locFirstDoc = -1, locSecDoc = -1;  

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

