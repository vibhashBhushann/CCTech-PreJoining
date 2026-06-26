const express = require('express');
const app = express();


// Parses incoming JSON bodies — without this, req.body is undefined
app.use(express.json());

// Logger middleware — prints every request to terminal
app.use((req, res, next) => {
  console.log(`[${new Date().toISOString()}] ${req.method} ${req.path}`);
  next(); // must call next() or request hangs here
});

// No database needed — just an array acting as our data store
let projects = [
  {
    id: 1,
    name: "Bridge Design",
    status: "active",
    createdAt: new Date().toISOString()
  },
  {
    id: 2,
    name: "Road Survey",
    status: "archived",
    createdAt: new Date().toISOString()
  }
];

let nextId = 3; // tracks the next ID to assign

// Returns all projects as an array
app.get('/projects', (req, res) => {
  res.status(200).json(projects);
});

// Creates a new project — validates required fields first
app.post('/projects', (req, res) => {
  const { name, status } = req.body;

  // Validation — matches the required fields from Day 4 spec
  if (!name || typeof name !== 'string') {
    return res.status(400).json({
      error: "Bad Request",
      message: "Field 'name' is required and must be a string"
    });
  }

  const validStatuses = ['active', 'archived'];
  if (!status || !validStatuses.includes(status)) {
    return res.status(400).json({
      error: "Bad Request",
      message: "Field 'status' is required and must be 'active' or 'archived'"
    });
  }

  // Build new project — shape matches the Project schema from Day 4
  const newProject = {
    id: nextId++,
    name,
    status,
    createdAt: new Date().toISOString()
  };

  projects.push(newProject);
  res.status(201).json(newProject);
});

// Returns one project — 404 if not found
app.get('/projects/:id', (req, res) => {
  const id = parseInt(req.params.id);
  const project = projects.find(p => p.id === id);

  if (!project) {
    return res.status(404).json({
      error: "Not Found",
      message: `Project with id ${id} does not exist`
    });
  }

  res.status(200).json(project);
});

// Updates only the status field of a project
app.patch('/projects/:id/status', (req, res) => {
  const id = parseInt(req.params.id);
  const project = projects.find(p => p.id === id);

  if (!project) {
    return res.status(404).json({
      error: "Not Found",
      message: `Project with id ${id} does not exist`
    });
  }

  const { status } = req.body;
  const validStatuses = ['active', 'archived'];

  if (!status || !validStatuses.includes(status)) {
    return res.status(400).json({
      error: "Bad Request",
      message: "Field 'status' must be 'active' or 'archived'"
    });
  }

  project.status = status;
  res.status(200).json(project);
});

const PORT = 3000;
app.listen(PORT, () => {
  console.log(`Server running at http://localhost:${PORT}`);
});