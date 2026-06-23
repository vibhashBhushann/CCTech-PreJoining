import { useState } from "react";
import ProjectDashboard from "./ProjectDashboard";

const initialProjects = [
  { id: 1, name: "Website Redesign", status: "active" as const, createdAt: new Date() },
  { id: 2, name: "Old Mobile App", status: "archived" as const, createdAt: new Date() },
  { id: 3, name: "API Integration", status: "active" as const, createdAt: new Date() },
];

export default function App() {
  const [projects, setProjects] = useState(initialProjects);

  function handleStatusChange(id: number, status: string) {
    setProjects(prev =>
      prev.map(p => p.id === id ? { ...p, status: status as 'active' | 'archived' } : p)
    );
  }

  return (
    <ProjectDashboard
      projects={projects}
      onStatusChange={handleStatusChange}
    />
  );
}