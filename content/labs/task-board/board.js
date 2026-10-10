const form = document.querySelector("#task-form");
const input = document.querySelector("#task-title");
const list = document.querySelector("#task-list");
const storageKey = "umicom-learning-tasks";

let tasks = [];

try {
  const saved = JSON.parse(localStorage.getItem(storageKey) || "[]");
  if (Array.isArray(saved)) {
    tasks = saved.filter(task =>
      typeof task === "string" && task.trim().length > 0
    );
  }
} catch (error) {
  console.warn("Saved tasks could not be read", error);
}

function renderTasks() {
  list.replaceChildren();
  for (const task of tasks) {
    const item = document.createElement("li");
    item.textContent = task;
    list.appendChild(item);
  }
}

form.addEventListener("submit", event => {
  event.preventDefault();
  const title = input.value.trim();
  if (!title) return;

  tasks.push(title);
  try {
    localStorage.setItem(storageKey, JSON.stringify(tasks));
  } catch (error) {
    console.warn("Task could not be stored", error);
  }
  input.value = "";
  renderTasks();
});

renderTasks();
