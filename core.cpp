#include "core.h"
#include <map>
#include <cctype>

string compress(const string& text) {
    string result;
    size_t i = 0;
    while (i < text.size()) {
        size_t count = 1;
        while (i + count < text.size() && text[i + count] == text[i]) {
            count++;
        }
        result += text[i];
        if (count > 1) {
            result += to_string(count);
        }
        i += count;
    }
    return result;
}

vector<string> splitSentences(const string& text) {
    vector<string> sentences;
    string current;
    for (char c : text) {
        if (current.empty() && c == ' ') {
            continue;
        }
        current += c;
        if (c == '.' || c == '!' || c == '?') {
            sentences.push_back(current);
            current = "";
        }
    }
    if (!current.empty()) {
        sentences.push_back(current);
    }
    return sentences;
}

vector<string> getWords(const string& text) {
    vector<string> words;
    string word;
    for (char c : text) {
        if (isalpha((unsigned char)c)) {
            word += (char)tolower((unsigned char)c);
        } else {
            if (word.size() >= 4) {
                words.push_back(word);
            }
            word = "";
        }
    }
    if (word.size() >= 4) {
        words.push_back(word);
    }
    return words;
}

string summarize(const string& text, int howMany) {
    vector<string> sentences = splitSentences(text);

    map<string, int> frequency;
    for (const string& word : getWords(text)) {
        frequency[word]++;
    }

    vector<int> score(sentences.size(), 0);
    for (size_t i = 0; i < sentences.size(); i++) {
        for (const string& word : getWords(sentences[i])) {
            score[i] += frequency[word];
        }
    }

    vector<bool> chosen(sentences.size(), false);
    for (int k = 0; k < howMany && k < (int)sentences.size(); k++) {
        int best = -1;
        for (size_t i = 0; i < sentences.size(); i++) {
            if (!chosen[i] && (best == -1 || score[i] > score[best])) {
                best = (int)i;
            }
        }
        chosen[best] = true;
    }

    string summary;
    for (size_t i = 0; i < sentences.size(); i++) {
        if (chosen[i]) {
            summary += sentences[i] + " ";
        }
    }
    return summary;
}

AnalysisResult analyze(const string& text) {
    AnalysisResult result;
    result.empty = text.empty();
    result.originalLength = text.size();
    result.compressedLength = 0;
    result.percentSaved = 0;
    if (result.empty) {
        return result;
    }
    result.compressed = compress(text);
    result.compressedLength = result.compressed.size();
    result.percentSaved =
        (text.size() - result.compressed.size()) * 100 / text.size();
    result.summary = summarize(text, 2);
    return result;
}

string joinLines(const string& text) {
    string result;
    for (char c : text) {
        if (c == '\r') {
            continue;            // ignore Windows-style carriage returns
        }
        result += (c == '\n') ? ' ' : c;
    }
    return result;
}

bool isBlank(const string& text) {
    for (char c : text) {
        if (!isspace((unsigned char)c)) {
            return false;
        }
    }
    return true;
}
