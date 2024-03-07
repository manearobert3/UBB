
--b. add / remove a column;

create or alter procedure AddColumnExperienceToCook as
	alter table Cook add Experience INT;

create or alter procedure DropColumnExperienceFromCook as
	alter table Cook drop column Experience;

--a. modify the type of a column;

create or alter procedure ModifySupplierPriceType as
	alter table Supplier alter column Price INT;

create or alter procedure RevertSupplierPriceType as
	alter table Supplier alter column Price VarChar(50);

--c. add / remove a DEFAULT constraint;

create or alter procedure AddDefaultWaiterShift as
	alter table Waiter ADD Constraint df_Shift DEFAULT 'day' for WShift;

create or alter procedure RevertWaiterShift as
	alter table Waiter drop constraint df_Shift;

--g. create / drop a table.

create or alter procedure AddSpecializationTable as
	CREATE TABLE Specialization
	(SpecializationID INT PRIMARY KEY,
	NameOfSpecialization VARCHAR(50))

create or alter procedure DropSpecializationTable as
	Drop Table Specialization
--5
create or alter procedure AddCookHasSpecializationTable as
	Create Table CookHasSpecialization
	(CookID INT References Cook(CookID) not null)

create or alter Procedure DropCookHasSpecializationTable as
	drop table CookHasSpecialization

	
create or alter procedure AddForeignKeyToCookHasSpecialization as
	--alter table CookHasSpecialization add SpecializationID INT References Specialization(SpecializationID) not null
	begin
	alter table CookHasSpecialization
    add SpecializationID INT not null;
	alter table CookHasSpecialization add constraint FK_SpecializationID 
foreign key (SpecializationID) references Specialization(SpecializationID)
end
create or alter procedure DropForeignKeyToCookHasSpecialization as
begin
	alter table CookHasSpecialization drop constraint FK_SpecializationID 
	alter table CookHasSpecialization drop column SpecializationID

end
	

--d. add / remove a primary key;
--6
create or alter Procedure AddPKCookHasSpecialization as
	alter table CookHasSpecialization add Constraint PK_CookSpecialization PRimary key(CookID,SpecializationID)


create or alter procedure RemovePKCookHasSpecialization as
	alter table CookHasSpecialization drop constraint PK_CookSpecialization

--e. add / remove a candidate key;
--7
create or alter procedure AddHelperChefPhoneCandidateKey as
	alter table HelperChef add constraint UQ_HelperChef_Phone unique (Phone);




create or alter procedure RemoveHelperChefPhoneCandidateKey as
	alter table HelperChef drop constraint UQ_HelperChef_Phone ;




--8	
--f. add / remove a foreign key;

create or alter PROCEDURE BaseVersion AS



	
	
create Table TheProcedures
	(uspUp VARCHAR(50),
	uspDown VarChar(50),
	targetVersion INT)

create Table crtVersion
	(crtVersion INT)

Insert crtVersion(crtVersion)
	Values(1);

Insert TheProcedures(uspUp,uspDown,targetVersion)
	Values('BaseVersion','BaseVersion',0),
	('AddColumnExperienceToCook','DropColumnExperienceFromCook',1),
	('ModifySupplierPriceType','RevertSupplierPriceType',2),
	('AddDefaultWaiterShift','RevertWaiterShift',3),
	('AddSpecializationTable','DropSpecializationTable',4),
	('AddCookHasSpecializationTable','DropCookHasSpecializationTable',5),
	('AddForeignKeyToCookHasSpecialization','DropForeignKeyToCookHasSpecialization',6),
	('AddPKCookHasSpecialization','RemovePKCookHasSpecialization',7),
	('AddHelperChefPhoneCandidateKey','RemoveHelperChefPhoneCandidateKey',8)	

	select * from sys.objects where type = 'D'

Select* from crtVersion
Select* from TheProcedures
Select* from 
Drop table crtVersion
Drop table TheProcedures
Drop table CookHasSpecialization
Drop table Specialization
Select* from CookHasSpecialization




CREATE OR ALTER PROCEDURE UpdateDatabaseToVersion
    @TargetVersion INT
AS
BEGIN
    DECLARE @CurrentVersion INT;
    SELECT @CurrentVersion = crtVersion FROM crtVersion;

    IF @CurrentVersion > @TargetVersion
    BEGIN
        -- Downgrade: Run "down" procedures
        WHILE @CurrentVersion > @TargetVersion
        BEGIN
            DECLARE @DownsertProcedure VARCHAR(50);

            -- Get the procedures for the current version
            SELECT @DownsertProcedure = uspDown
            FROM TheProcedures
            WHERE targetVersion = @CurrentVersion;

            -- Execute the "down" procedure to downgrade the database
            IF @DownsertProcedure IS NOT NULL
            BEGIN
                EXEC (@DownsertProcedure);
                PRINT 'Executed ' + @DownsertProcedure;
            END

            -- Update the version number
            UPDATE crtVersion SET crtVersion = @CurrentVersion - 1;

            -- Decrement the current version
            SET @CurrentVersion = @CurrentVersion - 1;
        END
    END
    ELSE
    BEGIN
        -- Upgrade: Run "up" procedures
		SET @CurrentVersion = @CurrentVersion + 1;
        WHILE @CurrentVersion < @TargetVersion
        BEGIN
            DECLARE @UpsertProcedure VARCHAR(50);

            -- Get the procedures for the next version
            SELECT @UpsertProcedure = uspUp
            FROM TheProcedures
            WHERE targetVersion = @CurrentVersion;

            -- Execute the "up" procedure to upgrade the database
            IF @UpsertProcedure IS NOT NULL
            BEGIN
                EXEC (@UpsertProcedure);
                PRINT 'Executed ' + @UpsertProcedure;
            END

            -- Update the version number
            UPDATE crtVersion SET crtVersion = @CurrentVersion + 1;

            -- Increment the current version
            SET @CurrentVersion = @CurrentVersion + 1;
        END
		
		IF @CurrentVersion = @TargetVersion
		Begin
            -- Get the procedures for the next version
            SELECT @UpsertProcedure = uspUp
            FROM TheProcedures
            WHERE targetVersion = @CurrentVersion;
		IF @UpsertProcedure IS NOT NULL
            BEGIN
                EXEC (@UpsertProcedure);
                PRINT 'Executed ' + @UpsertProcedure;
            END
		end


    END

    PRINT 'Database updated to version ' + CAST(@TargetVersion AS VARCHAR(10));
END;



EXEC UpdateDatabaseToVersion @TargetVersion =1;

Select* from Cook
Select* from Supplier
Select* from crtVersion
Select* from TheProcedures
Select* from HelperChef
Drop table crtVersion
Drop table TheProcedures
Drop table CookHasSpecialization
Drop table Specialization


Select* from CookHasSpecialization

SELECT 
    COLUMN_NAME, 
    DATA_TYPE, 
    CHARACTER_MAXIMUM_LENGTH AS MAX_LENGTH, 
    CHARACTER_OCTET_LENGTH AS OCTET_LENGTH 
FROM INFORMATION_SCHEMA.COLUMNS 
WHERE TABLE_NAME = 'HelperChef' 
AND COLUMN_NAME = 'Phone';