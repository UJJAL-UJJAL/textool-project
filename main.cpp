// main.cpp - command-line version of the Intelligent Text Compression
// and Summarization Tool. The real work is done in core.cpp.
#include <iostream>
#include <string>
#include "core.h"
using namespace std;

int main() {
    cout << "Enter your text (finish with an empty line):\n";

    string text, line;
    while (getline(cin, line) && !line.empty()) {
        text += line + " ";
    }

    if (text.empty()) {
        cout << "No text was entered.\n";
        return 0;
    }

    AnalysisResult r = analyze(text);

    cout << "\nCompression (run-length encoding)\n";
    cout << r.compressed << "\n";
    cout << "Original length:   " << r.originalLength << " characters\n";
    cout << "Compressed length: " << r.compressedLength << " characters\n";
    cout << "Space saved:       " << r.percentSaved << "%\n";

    cout << "\n--- Summary (top 2 sentences) ---\n";
    cout << r.summary << "\n";

    return 0;
}
