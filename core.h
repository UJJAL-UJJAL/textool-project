// core.h - the text tool's logic (compression + summarization).
// Used by both the command-line program (main.cpp) and the web page
// (wasm_bridge.cpp, compiled to WebAssembly).
#ifndef CORE_H
#define CORE_H

#include <string>
#include <vector>
using namespace std;

// Run-length encoding: "aaabbbbc" -> "a3b4c"
string compress(const string& text);

// Splits text into sentences at '.', '!' and '?'.
vector<string> splitSentences(const string& text);

// Lowercase words made of letters, four or more letters long.
vector<string> getWords(const string& text);

// Picks the best-scoring sentences (by word frequency), in original order.
string summarize(const string& text, int howMany);

// Everything the program shows the user, in one place.
struct AnalysisResult {
    bool empty;                // true if there was no text to work on
    string compressed;         // run-length encoded text
    size_t originalLength;     // characters before compression
    size_t compressedLength;   // characters after compression
    size_t percentSaved;       // (original - compressed) * 100 / original
    string summary;            // up to two sentences
};

// Compresses and summarizes the text.
AnalysisResult analyze(const string& text);

// Turns line breaks into spaces so text from a web text box
// is treated like the lines typed in the command-line program.
string joinLines(const string& text);

// true if the text has no characters other than spaces/tabs/line breaks.
bool isBlank(const string& text);

#endif
