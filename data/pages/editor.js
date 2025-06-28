
export function initEditor() {
  const editorEl = document.getElementById("editor");
  editorEl.contentEditable = true;
  editorEl.spellcheck = false;
  editorEl.style.whiteSpace = "pre";
  editorEl.style.fontFamily = "monospace";
  editorEl.style.outline = "none";

  editorEl.addEventListener("keydown", function(e) {
    if (e.key === "Tab") {
      e.preventDefault();
      document.execCommand("insertText", false, "  ");
    }
  });
}

export function getEditorContent() {
  return document.getElementById("editor").innerText;
}

export function setEditorContent(text) {
  document.getElementById("editor").innerText = text;
}
