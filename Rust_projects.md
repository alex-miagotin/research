# 🦀 Rust Pet Projects Collection

A collection of small and useful Rust projects for learning, experimenting, or building tools to improve productivity.

---

## 📁 Project Index

1. [📝 CLI Task Manager](#-cli-task-manager)
2. [🌐 Static Site Generator](#-static-site-generator)
3. [🔗 URL Shortener](#-url-shortener)
4. [👀 File Watcher with Live Reload](#-file-watcher-with-live-reload)
5. [⚙️ Config Reader (JSON/CSV/INI)](#-config-reader-jsoncsvini)

---

## 📝 CLI Task Manager

A command-line utility to manage your daily tasks.

### 📂 Folder Structure

```
cli-task-manager/
├── src/
│   ├── main.rs
│   ├── task.rs
│   └── storage.rs
├── data/
│   └── tasks.json
├── Cargo.toml
└── README.md
```

### 🧠 Features

- Add, remove, and list tasks
- Save tasks in a local JSON file
- Add due dates and categories

### 🚀 Example Commands

```bash
cargo run -- add "Buy groceries"
cargo run -- list
cargo run -- remove 1
```

---

## 🌐 Static Site Generator

Converts markdown files into a static HTML website.

### 📂 Folder Structure

```
static-site-generator/
├── src/
│   ├── main.rs
│   ├── parser.rs
│   ├── renderer.rs
│   └── utils.rs
├── content/
│   └── example.md
├── templates/
│   └── base.html
├── output/
├── Cargo.toml
└── README.md
```

### 🧠 Features

- Markdown-to-HTML conversion
- Template rendering
- Outputs full HTML files

### 🚀 Example Command

```bash
cargo run
```

---

## 🔗 URL Shortener

A CLI tool to shorten URLs and store them locally.

### 📂 Folder Structure

```
url-shortener/
├── src/
│   ├── main.rs
│   ├── db.rs
│   └── shortener.rs
├── data/
│   └── urls.json
├── Cargo.toml
└── README.md
```

### 🧠 Features

- Generate short codes
- Store and retrieve from JSON
- Optional HTTP redirect server

### 🚀 Example Command

```bash
cargo run -- shorten https://example.com
```

---

## 👀 File Watcher with Live Reload

Watches files for changes and runs a command.

### 📂 Folder Structure

```
file-watcher/
├── src/
│   ├── main.rs
│   └── watcher.rs
├── Cargo.toml
└── README.md
```

### 🧠 Features

- Watch specific paths
- Execute custom shell commands on change

### 🚀 Example Command

```bash
cargo run -- watch ./src --exec "echo File changed!"
```

---

## ⚙️ Config Reader (JSON/CSV/INI)

Read and unify configuration data from multiple formats.

### 📂 Folder Structure

```
config-reader/
├── src/
│   ├── main.rs
│   ├── json.rs
│   ├── csv.rs
│   └── ini.rs
├── config/
│   ├── example.json
│   ├── example.ini
│   └── example.csv
├── Cargo.toml
└── README.md
```

### 🧠 Features

- Read and merge config files
- Normalize into unified structure
- Useful for layered app configs

### 🚀 Example Command

```bash
cargo run -- config/example.json
```

---

## 🛠️ Requirements

- Rust & Cargo (latest stable)
- JSON or Markdown for input (depending on the project)
- Optional: `fswatch`, `curl`, etc., for extended CLI tools

---

Happy Rusting! 🦀
```

---

Let me know if you want this as a downloadable `.md` file or to generate any starter code scaffolding!