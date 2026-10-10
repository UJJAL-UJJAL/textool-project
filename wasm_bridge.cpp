// wasm_bridge.cpp - lets the web page call the C++ core.
// Compiled with Emscripten into docs/textool.js + docs/textool.wasm.
// No compression or summary logic lives here: it only calls core.cpp.
#include <emscripten/bind.h>
#include "core.h"

// Called from JavaScript as: Module.analyzeText(textFromTheTextBox)
AnalysisResult analyzeText(const string& input) {
    if (isBlank(input)) {
        return analyze("");                 // empty result
    }
    return analyze(joinLines(input));
}

EMSCRIPTEN_BINDINGS(textool) {
    emscripten::value_object<AnalysisResult>("AnalysisResult")
        .field("empty", &AnalysisResult::empty)
        .field("compressed", &AnalysisResult::compressed)
        .field("originalLength", &AnalysisResult::originalLength)
        .field("compressedLength", &AnalysisResult::compressedLength)
        .field("percentSaved", &AnalysisResult::percentSaved)
        .field("summary", &AnalysisResult::summary);

    emscripten::function("analyzeText", &analyzeText);
}
