# 14. JavaScript: add tasks and remember them

HTML describes the task board; CSS styles it. **JavaScript** gives the page behaviour. It can respond to a button, read a text field, update the displayed tasks and store information for the next visit.

The browser exposes the page through the **Document Object Model** (DOM): a set of objects representing elements such as the form and task list. JavaScript can work with those objects safely.

## Create `board.js`

Save this complete file beside `board.html` and `board.css`:

```javascript
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
```

Refresh the page, type `Prepare the Umicom Framework build`, and press **Add task**. The new task appears in the list. Refresh again: in browsers where local storage is available for this page, it should still appear.

## Learn what changed

`document.querySelector` finds one element using a CSS selector. `const` declares a binding whose value will not be reassigned; `let` declares one that can be reassigned. An **array** (`[]`) stores several values; in this case, a collection of task descriptions.

`addEventListener("submit", ...)` registers a function to run when the form is submitted. `event.preventDefault()` stops the browser's normal form submission because this example handles the task inside the page.

`renderTasks` is a function that rebuilds the visible list. `document.createElement("li")` creates a new list item, and `item.textContent = task` inserts the description as **text**, not executable HTML. Avoid inserting uncontrolled user input through `innerHTML`, which can create cross-site scripting vulnerabilities.

**Local storage** is a browser facility for saving small pieces of information for a particular site or origin. `JSON.stringify` converts the JavaScript array into JSON text; `JSON.parse` reads it back. Storage availability depends on browser settings and the page's origin, and `file://` behaviour can vary. If persistence fails, use a small local web server rather than treating all browsers as identical.

## Use a local HTTP server if needed

From the `task-board` folder, run:

```powershell
python -m http.server 8000
```

Open `http://localhost:8000/board.html` in a browser. `localhost` means your own computer; the server is for development and should not be exposed as a production service. Stop it using **Ctrl+C** when finished.

## Make the next version

Right now, tasks are only strings. A useful Kanban board needs identifiers and statuses. Replace each string with an object such as:

```javascript
const task = {
  id: "T-101",
  title: "Prepare the monthly report",
  status: "todo"
};
```

The next challenge is to add a **Mark done** button to each task and update its stored status. A future version will move storage behind an application service and database rather than relying on one browser's local storage.

**Next:** [Understand a server-side application with PHP](15-php.md).
