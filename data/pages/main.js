
import { initEditor, getEditorContent, setEditorContent } from './editor.js';


document.addEventListener("DOMContentLoaded", () => {
  const mainView = document.getElementById("main-view");
  const configView = document.getElementById("config-view");
  const aboutView = document.getElementById("about-view");

  document.getElementById("nav-main").onclick = () => {
    mainView.classList.remove("hidden");
    configView.classList.add("hidden");
    aboutView.classList.add("hidden");
  };
  document.getElementById("nav-config").onclick = () => {
    mainView.classList.add("hidden");
    configView.classList.remove("hidden");
    aboutView.classList.add("hidden");
  };
  document.getElementById("nav-about").onclick = () => {
    mainView.classList.add("hidden");
    configView.classList.add("hidden");
    aboutView.classList.remove("hidden");
  };

  fetch("/api/status").then(r => r.json()).then(data => {
    document.getElementById("cpu-load").textContent = data.cpu;
    document.getElementById("free-ram").textContent = data.ram;
    document.getElementById("disk-usage").textContent = data.disk;
    document.getElementById("status-img").src = data.active ? "/assets/n3wb_main_evil.png" : "/assets/n3wb_main.png";
  });

  fetch("/api/payloads").then(r => r.json()).then(data => {
    const list = document.getElementById("payload-list");
    data.forEach(name => {
      const li = document.createElement("li");
      li.textContent = name;
      li.onclick = () => loadPayload(name);
      list.appendChild(li);
    });
  });

  function loadPayload(name) {
    fetch("/api/payloads/" + name)
      .then(r => r.text())
      .then(text => {
        document.getElementById("editor").textContent = text;
      });
  }
});


// Live navigation
document.getElementById("nav-live").onclick = () => {
  document.getElementById("main-view").classList.add("hidden");
  document.getElementById("live-view").classList.remove("hidden");
  document.getElementById("config-view").classList.add("hidden");
  document.getElementById("about-view").classList.add("hidden");
};

// Send keyboard input
document.querySelectorAll('#live-keyboard button').forEach(btn => {
  btn.onclick = () => {
    fetch("/api/hid/keyboard", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify({ key: btn.dataset.key })
    });
  };
});

// Send mouse input
document.querySelectorAll('#live-mouse button').forEach(btn => {
  btn.onclick = () => {
    fetch("/api/hid/mouse", {
      method: "POST",
      headers: {"Content-Type": "application/json"},
      body: JSON.stringify({ action: btn.dataset.move })
    });
  };
});


document.addEventListener("DOMContentLoaded", () => {
  initEditor();
});
