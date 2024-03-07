-- Table Ta
CREATE TABLE Employees (
    employee_id INT PRIMARY KEY,
    employee_name VARCHAR(255) UNIQUE,
    salary INT
);

-- Table Tb
CREATE TABLE Projects (
    project_id INT PRIMARY KEY,
    project_name VARCHAR(255),
    deadline DATE
);

-- Table Tc
CREATE TABLE ProjectAssignments (
    assignment_id INT PRIMARY KEY,
    employee_id INT FOREIGN KEY REFERENCES Employees(employee_id),
    project_id INT FOREIGN KEY REFERENCES Projects(project_id),
    hours_worked INT
);

CREATE or alter PROCEDURE InsertRandomEmployees
    @numInserts INT
AS
BEGIN
	DELETE Employees
    DECLARE @counter INT = 1;

    WHILE @counter <= @numInserts
    BEGIN
        INSERT INTO Employees (employee_id,employee_name, salary)
        VALUES 
            (	@counter,
                CONCAT('Employee', @counter),
                ROUND(RAND() * 50000 + 50000, 2)  -- Generating random salary between 50000 and 100000
            );

        SET @counter = @counter + 1;
    END;
END;

-- Procedure for inserting random data into Projects table (Table Y)
CREATE or ALTER PROCEDURE InsertRandomProjects
    @numInserts INT
AS
BEGIN
	DELETE FROM Projects
    DECLARE @counter INT = 1;

    WHILE @counter <= @numInserts
    BEGIN
        INSERT INTO Projects (project_id,project_name, deadline)
        VALUES 
            (	@counter,
                CONCAT('Project', @counter),
                DATEADD(DAY, ROUND(RAND() * 365, 0), GETDATE())  -- Generating random deadline within the next year
            );

        SET @counter = @counter + 1;
    END;
END;

-- Procedure for inserting random data into ProjectAssignments table (Table Tc)
CREATE or alter PROCEDURE InsertRandomProjectAssignments
    @numInserts INT
AS
BEGIN
	Delete from ProjectAssignments
    DECLARE @counter INT = 1;
	DECLARE @maxEmployeeId INT;
	DECLARE @maxProjectId INT;

    -- Get the maximum employee_id in the Employees table
    SELECT @maxEmployeeId = MAX(employee_id) FROM Employees;
	SELECT @maxProjectId = MAX(project_id) FROM Projects;

    WHILE @counter <= @numInserts
    BEGIN
        INSERT INTO ProjectAssignments (assignment_id,employee_id, project_id, hours_worked)
        VALUES 
            (	@counter,
               CEILING(RAND() * @maxEmployeeId),  -- Random employee_id between 1 and @maxEmployeeId
                CEILING(RAND() * @maxProjectId),  -- Random project_id between 1 and @maxProjectId
                ROUND(RAND() * 40, 2)  -- Random hours_worked between 0 and 40
            );

        SET @counter = @counter + 1;
    END;
END;
Delete from ProjectAssignments
delete from Projects
delete from Employees
-- Example: Insert 10 random employees
EXEC InsertRandomEmployees @numInserts = 10000;
select* from Employees
-- Example: Insert 5 random projects
EXEC InsertRandomProjects @numInserts = 8900;
select* from Projects
-- Example: Insert 15 random project assignments
EXEC InsertRandomProjectAssignments @numInserts = 5000;
Select* from ProjectAssignments

EXEC sp_helpindex Employees
-- Primary key constraint = clustered index on employee_id
-- Unique constraint = non-clustered index on employee_name
--a) clustered index scan;
SELECT * FROM Employees;

--b)clustered index seek;
SELECT * FROM Employees WHERE employee_id = 1;

--c)nonclustered index scan;
CREATE nonclustered INDEX IX_EmployeeName ON Employees(employee_name);
-- Drop the IX_EmployeeName index
--DROP INDEX IX_EmployeeName ON Employees;

--SELECT * FROM Employees WHERE employee_name LIKE 'Employee1%';
SELECT employee_name FROM Employees order by employee_name;

--d)nonclustered index seek;
SELECT employee_name FROM Employees WHERE employee_name ='Employee1';

--e)key lookup;
SELECT salary FROM Employees WHERE employee_name = 'Employee1';


--2.

-- Original query
SELECT * FROM Projects WHERE project_name = 'Project367';
--0.049
-- Create nonclustered index to optimize the query
CREATE nonclustered INDEX IX_ProjectName ON Projects(project_name) include (project_id);
DROP INDEX IX_ProjectName ON Projects;
-- Rerun the query with the index
SELECT * FROM Projects WHERE project_name = 'Project367'; --0.0065



CREATE or alter VIEW EmployeeProjectView AS
SELECT
    e.employee_id,
    e.employee_name,
    pa.assignment_id,
    pa.hours_worked,
    p.project_name
FROM
    Employees e
JOIN
    ProjectAssignments pa ON e.employee_id = pa.employee_id
JOIN
    Projects p ON pa.project_id = p.project_id
Where salary =1500
Select* from EmployeeProjectView 
-- no index 0.142
-- using index 0.08


Select* from EmployeeProjectView  --0.098 w indexes , 0.15 no index
order by hours_worked;

CREATE nonclustered INDEX IX_EmployeeProjectView_salary ON Employees(salary);
drop index IX_EmployeeProjectView_salary on employees;



--CREATE nonclustered INDEX IX_EmployeeProjectView_ProjectId ON Projects(project_id);
--CREATE nonclustered INDEX IX_EmployeeProjectView_EmployeeId ON Employees(employee_id);
--drop Index IX_EmployeeProjectView_ProjectId On projects
--drop index IX_EmployeeProjectView_EmployeeId on employees
--drop index IX_EmployeeProjectView_salary on employees;
--drop index IX_EmployeeHours on ProjectAssignments;
--CREATE nonclustered INDEX IX_EmployeeHours ON ProjectAssignments(hours_worked);

