const request = require('supertest');
const app = require('./app');

// ─────────────────────────────────────────────────────────────────
// GET /projects
// ─────────────────────────────────────────────────────────────────

describe('GET /projects', () => {
  it('should return 200 and an array of projects', async () => {
    // Arrange — nothing extra needed, app already has seed data
    // Act
    const response = await request(app).get('/projects');
    // Assert
    expect(response.status).toBe(200);
    expect(Array.isArray(response.body)).toBe(true);
    expect(response.body.length).toBeGreaterThan(0);
  });
});

// ─────────────────────────────────────────────────────────────────
// POST /projects
// ─────────────────────────────────────────────────────────────────

describe('POST /projects', () => {
  it('should create a project and return 201 with the new project', async () => {
    // Arrange
    const newProject = { name: 'Tunnel Survey', status: 'active' };
    // Act
    const response = await request(app).post('/projects').send(newProject);
    // Assert
    expect(response.status).toBe(201);
    expect(response.body.name).toBe('Tunnel Survey');
    expect(response.body.status).toBe('active');
    expect(response.body).toHaveProperty('id');
    expect(response.body).toHaveProperty('createdAt');
  });

  it('should return 400 when name is missing', async () => {
    // Arrange
    const invalidProject = { status: 'active' };
    // Act
    const response = await request(app).post('/projects').send(invalidProject);
    // Assert
    expect(response.status).toBe(400);
    expect(response.body.error).toBe('Bad Request');
  });

  it('should return 400 when status is invalid', async () => {
    // Arrange
    const invalidProject = { name: 'Test', status: 'unknown_status' };
    // Act
    const response = await request(app).post('/projects').send(invalidProject);
    // Assert
    expect(response.status).toBe(400);
    expect(response.body.error).toBe('Bad Request');
  });
});

// ─────────────────────────────────────────────────────────────────
// GET /projects/:id
// ─────────────────────────────────────────────────────────────────

describe('GET /projects/:id', () => {
  it('should return 200 and the matching project for a valid id', async () => {
    // Arrange — project with id 1 exists in seed data
    // Act
    const response = await request(app).get('/projects/1');
    // Assert
    expect(response.status).toBe(200);
    expect(response.body.id).toBe(1);
  });

  it('should return 404 when project id does not exist', async () => {
    // Arrange
    const nonExistentId = 9999;
    // Act
    const response = await request(app).get(`/projects/${nonExistentId}`);
    // Assert
    expect(response.status).toBe(404);
    expect(response.body.error).toBe('Not Found');
  });
});

// ─────────────────────────────────────────────────────────────────
// PATCH /projects/:id/status
// ─────────────────────────────────────────────────────────────────

describe('PATCH /projects/:id/status', () => {
  it('should update status and return 200 for a valid id', async () => {
    // Arrange
    const update = { status: 'archived' };
    // Act
    const response = await request(app).patch('/projects/2/status').send(update);
    // Assert
    expect(response.status).toBe(200);
    expect(response.body.status).toBe('archived');
  });

  it('should return 404 when updating a non-existent project', async () => {
    // Arrange
    const update = { status: 'active' };
    // Act
    const response = await request(app).patch('/projects/9999/status').send(update);
    // Assert
    expect(response.status).toBe(404);
  });

  it('should return 400 when status value is invalid', async () => {
    // Arrange
    const update = { status: 'not_a_real_status' };
    // Act
    const response = await request(app).patch('/projects/1/status').send(update);
    // Assert
    expect(response.status).toBe(400);
  });
});