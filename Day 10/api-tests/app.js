const express = require('express');
const app = express();

app.use(express.json());

app.use((req, res, next) => {
  console.log(`[${new Date().toISOString()}] ${req.method} ${req.path}`);
  next();
});

let projects = [
  { id: 1, name: "Bridge Design", status: "active", createdAt: new Date().toISOString() },
  { id: 2, name: "Road Survey", status: "archived", createdAt: new Date().toISOString() }
];
let nextId = 3;

app.get('/projects', (req, res) => {
  res.status(200).json(projects);
});

app.post('/projects', (req, res) => {
  const { name, status } = req.body;

  if (!name || typeof name !== 'string') {
    return res.status(400).json({ error: "Bad Request", message: "Field 'name' is required and must be a string" });
  }
  const validStatuses = ['active', 'archived'];
  if (!status || !validStatuses.includes(status)) {
    return res.status(400).json({ error: "Bad Request", message: "Field 'status' is required and must be 'active' or 'archived'" });
  }

  const newProject = { id: nextId++, name, status, createdAt: new Date().toISOString() };
  projects.push(newProject);
  res.status(201).json(newProject);
});

app.get('/projects/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const project = projects.find(p => p.id === id);
  if (!project) {
    return res.status(404).json({ error: "Not Found", message: `Project with id ${id} does not exist` });
  }
  res.status(200).json(project);
});

app.patch('/projects/:id/status', (req, res) => {
  const id = parseInt(req.params.id);
  const project = projects.find(p => p.id === id);
  if (!project) {
    return res.status(404).json({ error: "Not Found", message: `Project with id ${id} does not exist` });
  }
  const { status } = req.body;
  const validStatuses = ['active', 'archived'];
  if (!status || !validStatuses.includes(status)) {
    return res.status(400).json({ error: "Bad Request", message: "Field 'status' must be 'active' or 'archived'" });
  }
  project.status = status;
  res.status(200).json(project);
});

module.exports = app; // exported, NOT listening — that's the key difference