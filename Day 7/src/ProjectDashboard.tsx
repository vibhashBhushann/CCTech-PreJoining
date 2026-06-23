interface Project {
  id: number;
  name: string;
  status: 'active' | 'archived';
  createdAt: Date;
}

interface ProjectDashboardProps {
  projects: Project[];
  onStatusChange: (id: number, status: string) => void;
}

function useProjectFilter(projects: Project[], status: string): Project[] {
  return projects.filter(project => project.status === status);
}

function StatusBadge({ status }: { status: string }) {
  const style = {
    padding: '2px 8px',
    borderRadius: '4px',
    backgroundColor: status === 'active' ? '#22c55e' : '#94a3b8',
    color: 'white',
    fontSize: '12px'
  };
  return <span style={style}>{status}</span>;
}



import { useState } from "react";

export default function ProjectDashboard({ projects, onStatusChange }: ProjectDashboardProps) {
  const [selectedStatus, setSelectedStatus] = useState<string>("active");

  // custom hook — filter logic is here, not inline
  const filteredProjects = useProjectFilter(projects, selectedStatus);

  function toggleStatus(project: Project) {
    const newStatus = project.status === 'active' ? 'archived' : 'active';
    onStatusChange(project.id, newStatus);
  }

  return (
    <div>
      {/* Filter buttons */}
      <div>
        <button onClick={() => setSelectedStatus("active")}>Active</button>
        <button onClick={() => setSelectedStatus("archived")}>Archived</button>
      </div>

      {/* Project list */}
      {filteredProjects.map(project => (
        <div key={project.id} style={{ border: '1px solid #ccc', margin: '8px', padding: '8px' }}>
          <span>{project.name}</span>
          <StatusBadge status={project.status} />
          <button onClick={() => toggleStatus(project)}>
            Toggle Status
          </button>
        </div>
      ))}

      {filteredProjects.length === 0 && (
        <p>No projects with status: {selectedStatus}</p>
      )}
    </div>
  );
}