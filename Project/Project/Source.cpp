#include "Header.h"

using namespace std;

int main() {
    vector<string> MainDoc;
    vector<string> SimilarDoc;

    MainDoc = fileOpener(MainDoc, "main_doc.txt");
    int a;

    cout << "How much documents do you want to compare ? "; //For example we want to compare 2 files then we enter 2
    cin >> a;
    clock_t start = clock(), stop;
    for (int index = 0; index < a; index++) {

        string p = to_string(index + 1);
        SimilarDoc = fileOpener(SimilarDoc, "document" + p + ".txt");
        vector<vector<double>> results = comparison(MainDoc, SimilarDoc);
        findMostSimilars(results, MainDoc, SimilarDoc); //En benzer 5 cümþlenin yazýlmasý
        documentSimilarity(MainDoc, SimilarDoc); //Belgenin benzerlik oranýnýn yazýlmasý
        SimilarDoc.~vector();
        results.~vector();
    }
    stop = clock();
    cout << "Total Elapsed Time : " << (float)(stop - start) / CLOCKS_PER_SEC << " seconds." << endl;
    return 0;
}