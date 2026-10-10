// app.js - the page's user interface only.
// All compression and summarizing is done by the C++ code (core.cpp),
// compiled to WebAssembly (textool.wasm). This file just sends the text
// to C++ and shows what comes back.

var textool = null;   // the loaded C++ module

var input = document.getElementById("input");
var runButton = document.getElementById("run");
var sampleButton = document.getElementById("sample");
var clearButton = document.getElementById("clear");
var statusLine = document.getElementById("status");
var errorLine = document.getElementById("error");
var results = document.getElementById("results");

var SAMPLE_TEXT =
  "Wooooow!!! That was sooooo cooool. Aaaaaaand the crowd went wiiiiild. " +
  "Nothing beats a goooood show.";

function showError(message) {
  errorLine.textContent = message;
  errorLine.hidden = false;
  results.hidden = true;
}

function hideError() {
  errorLine.hidden = true;
  errorLine.textContent = "";
}

function runTool() {
  hideError();

  // The C++ function does all the work and tells us if the text was empty.
  var result = textool.analyzeText(input.value);

  if (result.empty) {
    showError("There is no text to process. Type or paste some text first.");
    return;
  }

  document.getElementById("compressed").textContent = result.compressed;
  document.getElementById("original").textContent = result.originalLength;
  document.getElementById("compressedLength").textContent = result.compressedLength;
  document.getElementById("saved").textContent = result.percentSaved;
  document.getElementById("summary").textContent = result.summary;
  results.hidden = false;
}

sampleButton.addEventListener("click", function () {
  input.value = SAMPLE_TEXT;
  input.focus();
});

clearButton.addEventListener("click", function () {
  input.value = "";
  hideError();
  results.hidden = true;
  input.focus();
});

runButton.addEventListener("click", function () {
  if (textool) {
    runTool();
  }
});

// Load the WebAssembly module, then enable the button.
if (typeof createTextool !== "function") {
  statusLine.textContent = "";
  showError("The C++ code could not be loaded (textool.js is missing). " +
            "Run ./build.sh to create it.");
} else {
  createTextool().then(function (module) {
    textool = module;
    runButton.disabled = false;
    statusLine.textContent = "Ready.";
  }).catch(function () {
    statusLine.textContent = "";
    showError("The C++ code could not be loaded. If you opened this file by " +
              "double-clicking it, start a local server instead (see the README).");
  });
}
