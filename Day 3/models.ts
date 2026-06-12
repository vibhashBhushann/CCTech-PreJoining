interface Project{
    id: number;
    name: string;
    status: 'active' | 'archived';
    createdAt: Date;
}

interface Task {
    id: number;
    projectId: number;
    title: string;
    completed: boolean;
}

function filterByStatus<T extends {status: string}>(
    items: T[],
    status: string
): T[] {
    return items.filter(item => item.status === status);
}

function groupTasksByProject(tasks: Task[]): Map<number, Task[]> {
  const map = new Map<number, Task[]>();
  for (const task of tasks) {
    if (!map.has(task.projectId)) {
      map.set(task.projectId, []); 
    }
    map.get(task.projectId)!.push(task);
  }
  return map;
}



// sample
const projects: Project[] = [
    { id: 1, name: "Website", status: "active", createdAt: new Date() },
    { id: 2, name: "Old App", status: "archived", createdAt: new Date() }
];

const tasks: Task[] = [
  { id: 1, projectId: 1, title: "Design homepage", completed: false },
  { id: 2, projectId: 1, title: "Setup server", completed: true },
  { id: 3, projectId: 2, title: "Archive data", completed: true },
];

const activeProjects = filterByStatus(projects, "active");
console.log("Active projects:", activeProjects);

const grouped = groupTasksByProject(tasks);
console.log("Grouped tasks:", grouped);